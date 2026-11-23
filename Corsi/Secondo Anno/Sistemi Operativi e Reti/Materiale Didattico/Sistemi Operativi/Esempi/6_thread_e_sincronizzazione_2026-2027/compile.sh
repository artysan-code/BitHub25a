#!/bin/bash

# Compilazione degli esempi della lezione 6
# Thread, semafori e sincronizzazione

CC=gcc

# Opzioni di compilazione:
# -O0      : disabilita le ottimizzazioni, utile per il debug
# -g       : aggiunge informazioni per il debugger
# -Wall    : abilita i warning più comuni
# -Wextra  : abilita warning aggiuntivi
# -pthread : abilita il supporto POSIX Threads
OPTIONS="-O0 -g -Wall -Wextra -pthread"

# Creazione dei thread
$CC $OPTIONS 6.1_threads.c -o 6.1_threads

# Produttore-consumatore con semafori
$CC $OPTIONS 6.2_producer_consumer_semaphore.c -o 6.2_producer_consumer_semaphore

# Lettori-scrittori con semafori
$CC $OPTIONS 6.3_reader_writer_semaphore.c -o 6.3_reader_writer_semaphore

# Produttore-consumatore con mutex e variabili condizionali
$CC $OPTIONS 6.4_producer_consumer_pthread.c -o 6.4_producer_consumer_pthread
