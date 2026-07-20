#!/usr/bin/env python3
"""Verifica i wikilink Obsidian interni del vault.

Controlla, per ogni `[[Nota]]`, `[[Nota#heading]]`, `[[#heading]]`, `[[Nota#^blocco]]`
(con eventuale alias `|testo`), che la nota target, l'heading o il blocco esistano.
lychee non parsa i wikilink: questo checker copre quel buco.

Uso:
  python3 .github/scripts/check-wikilinks.py            # report (exit 0)
  python3 .github/scripts/check-wikilinks.py --strict   # exit 1 se trova link rotti
"""
import glob
import os
import re
import sys
from fnmatch import fnmatch

SCAN_DIRS = ("Corsi", "Hackathons")
EXCLUDE_SUBSTR = ("/.obsidian/", "/.github/", "/.claude/", "/.trash/")
EXCLUDE_BASENAMES = {"CLAUDE.md"}  # contengono wikilink-esempio, non reali

# Note personali volutamente non versionate (vedi .gitignore): esistono in locale
# ma non nel repo, quindi in CI non sono raggiungibili. I wikilink che le
# referenziano sono intenzionali e NON vanno segnalati come rotti. Pattern in
# minuscolo, confrontati col nome target (senza estensione) via fnmatch.
PERSONAL_NOTE_GLOBS = (
    "piano *",                  # .gitignore: Piano *.md (di studi, esame, orale...)
    "situazione universitaria",
)

FENCE_RE = re.compile(r"```.*?```", re.DOTALL)
WIKILINK_RE = re.compile(r"(?<!!)\[\[([^\[\]\n]+?)\]\]")  # esclude gli embed ![[...]]
ASSET_EXT = (".png", ".jpg", ".jpeg", ".gif", ".svg", ".webp", ".pdf",
             ".mp4", ".mov", ".excalidraw")
HEADING_RE = re.compile(r"^#{1,6}\s+(.*?)\s*$")
BLOCK_RE = re.compile(r"\s\^([\w-]+)\s*$")


def norm(text):
    text = re.sub(r"[*_`]", "", text)          # via enfasi/code inline
    text = re.sub(r"\s+", " ", text).strip()
    return text.lower()


def collect_md():
    files = []
    for base in SCAN_DIRS:
        files += glob.glob(f"{base}/**/*.md", recursive=True)
    out = []
    for f in files:
        p = "/" + f
        if any(s in p for s in EXCLUDE_SUBSTR):
            continue
        if os.path.basename(f) in EXCLUDE_BASENAMES:
            continue
        out.append(f)
    return out


def main():
    strict = "--strict" in sys.argv
    targets = [a for a in sys.argv[1:] if not a.startswith("--")]
    md = collect_md()

    note_by_name = {}      # basename lower -> [paths]
    headings = {}          # path -> set(norm heading)
    blocks = {}            # path -> set(block id)
    raw_text = {}          # path -> testo senza code fence

    for f in md:
        name = os.path.splitext(os.path.basename(f))[0]
        note_by_name.setdefault(name.lower(), []).append(f)
        hs, bs = set(), set()
        with open(f, encoding="utf-8") as fh:
            lines = fh.readlines()
        for line in lines:
            hm = HEADING_RE.match(line)
            if hm:
                hs.add(norm(hm.group(1)))
            bm = BLOCK_RE.search(line)
            if bm:
                bs.add(bm.group(1))
        headings[f] = hs
        blocks[f] = bs
        raw_text[f] = FENCE_RE.sub("", "".join(lines))

    broken = []
    check_files = [f for f in targets if f in raw_text] if targets else md
    for f in check_files:
        for m in WIKILINK_RE.finditer(raw_text[f]):
            link = m.group(1).replace("\\|", "|").split("|")[0].strip()
            if not link:
                continue
            if link.startswith("#"):
                target_path, anchor = f, link[1:]
            else:
                target, anchor = (link.split("#", 1) + [None])[:2]
                target = target.strip()
                if target.lower().endswith(ASSET_EXT):
                    continue  # embed/link a un asset, non a una nota
                paths = note_by_name.get(target.lower())
                if not paths:
                    if any(fnmatch(target.lower(), g) for g in PERSONAL_NOTE_GLOBS):
                        continue  # nota personale non versionata: link intenzionale
                    broken.append((f, m.group(0), "nota inesistente"))
                    continue
                target_path = paths[0]
            if anchor:
                anchor = anchor.strip()
                if anchor.startswith("^"):
                    if anchor[1:] not in blocks.get(target_path, set()):
                        broken.append((f, m.group(0), "blocco inesistente"))
                elif norm(anchor) not in headings.get(target_path, set()):
                    broken.append((f, m.group(0), "heading inesistente"))

    if broken:
        print(f"Wikilink rotti: {len(broken)}\n")
        for f, link, why in sorted(broken):
            print(f"  {f}\n    {link}  -> {why}")
    else:
        print(f"OK: nessun wikilink rotto ({len(md)} note controllate).")

    return 1 if (broken and strict) else 0


if __name__ == "__main__":
    sys.exit(main())
