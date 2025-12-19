#!/bin/bash

# Script per generare statistiche sulla repository BitHub25a

echo "=== Statistiche BitHub25a ==="
echo ""

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CORSI_DIR="$REPO_ROOT/Corsi"

# Conta corsi per anno
echo "📚 Corsi per Anno:"
for anno_dir in "$CORSI_DIR"/*; do
    if [ -d "$anno_dir" ]; then
        anno_name=$(basename "$anno_dir")
        num_corsi=$(find "$anno_dir" -mindepth 1 -maxdepth 1 -type d | wc -l)
        echo "  $anno_name: $num_corsi corsi"
    fi
done

echo ""

# Conta file markdown
num_md=$(find "$CORSI_DIR" -type f -name "*.md" | wc -l)
echo "📝 File Markdown: $num_md"

# Conta immagini
num_png=$(find "$CORSI_DIR" -type f -name "*.png" | wc -l)
num_jpg=$(find "$CORSI_DIR" -type f \( -name "*.jpg" -o -name "*.jpeg" \) | wc -l)
echo "🖼️  Immagini: $((num_png + num_jpg)) (PNG: $num_png, JPG: $num_jpg)"

# Conta PDF
num_pdf=$(find "$CORSI_DIR" -type f -name "*.pdf" | wc -l)
echo "📄 PDF: $num_pdf"

# Conta file Xournal
num_xopp=$(find "$CORSI_DIR" -type f -name "*.xopp" | wc -l)
echo "✏️  File Xournal: $num_xopp"

# Conta README
num_readme=$(find "$CORSI_DIR" -type f -name "README.md" | wc -l)
echo "📖 README: $num_readme"

echo ""

# Dimensione totale
total_size=$(du -sh "$CORSI_DIR" 2>/dev/null | cut -f1)
echo "💾 Dimensione totale Corsi: $total_size"

echo ""

# Top 5 corsi per numero di file
echo "🏆 Top 5 Corsi per Numero di File:"
for anno_dir in "$CORSI_DIR"/*; do
    if [ -d "$anno_dir" ]; then
        for corso_dir in "$anno_dir"/*; do
            if [ -d "$corso_dir" ]; then
                num_files=$(find "$corso_dir" -type f | wc -l)
                echo "$num_files|$(basename "$corso_dir")"
            fi
        done
    fi
done | sort -rn | head -5 | nl | while read num count nome; do
    echo "  $num. $nome ($count file)"
done

echo ""
echo "=== Fine Statistiche ==="
