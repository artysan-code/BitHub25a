#!/bin/bash

# Script per verificare la struttura dei corsi in BitHub25a
# Controlla che ogni corso abbia almeno un README.md

echo "=== Verifica Struttura Corsi BitHub25a ==="
echo ""

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CORSI_DIR="$REPO_ROOT/Corsi"

total_corsi=0
corsi_senza_readme=0
corsi_ok=0

# Funzione per controllare un corso
check_corso() {
    local corso_path="$1"
    local corso_name=$(basename "$corso_path")

    ((total_corsi++))

    if [ ! -f "$corso_path/README.md" ]; then
        echo "❌ $corso_name - Manca README.md"
        ((corsi_senza_readme++))
    else
        echo "✅ $corso_name"
        ((corsi_ok++))
    fi
}

# Scansiona tutti gli anni
for anno_dir in "$CORSI_DIR"/*; do
    if [ -d "$anno_dir" ]; then
        anno_name=$(basename "$anno_dir")
        echo ""
        echo "--- $anno_name ---"

        for corso_dir in "$anno_dir"/*; do
            if [ -d "$corso_dir" ]; then
                check_corso "$corso_dir"
            fi
        done
    fi
done

echo ""
echo "=== Riepilogo ==="
echo "Corsi totali: $total_corsi"
echo "Corsi OK: $corsi_ok"
echo "Corsi senza README: $corsi_senza_readme"
echo ""

if [ $corsi_senza_readme -eq 0 ]; then
    echo "✨ Tutti i corsi hanno la struttura corretta!"
    exit 0
else
    echo "⚠️  Alcuni corsi necessitano di un README.md"
    exit 1
fi
