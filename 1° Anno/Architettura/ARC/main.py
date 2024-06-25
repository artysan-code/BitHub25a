from modules.multiprogram import solve_multiprogram
from modules.convert import convert_base

def req_exec_input() -> None:
    exercise = int(input("""Inserisci che esercizio vuoi fare:
    
- 0 Multiprogrammazione
- 1 Sistema batch
- 2 Sistema Interattivo 
- 3 Sistema Soft-Realtime

- 10 Convertire un numero
                         
> """))
    match exercise:
        # Sistemi Operativi
        case 0:
            print("Inserire i valori senza caratteri alfabetici, se il valore manca inserire 0.\n\n")
            mem_tot = int(input("Inserisci la memoria totale del sistema: "))
            mem_os = int(input("Inserisci la memoria del sistema operativo: "))
            mem_proc = int(input("Inserisci lo spazio occupato da un processo: "))
            wait_io = float(input("Inserisci in intero il tempo di attesa medio I/O (Se 80% allora 0.80): "))
            cpu_load = float(input("Inserisci il tempo di attesa medio della CPU (come sopra): "))
            solve_multiprogram(mem_tot, mem_os, mem_proc, wait_io, cpu_load)
        case 1:
            pass
        case 2:
            pass
        case 3:
            pass
        # Architettura
        case 10:
            print("\n\n\nInserire i valori nell'ordine richiesto, possono essere usate lettere ma solo nel numero.\n\n")
            num = input("Inserisci il numero da convertire: ")
            from_base = int(input("\nInserisci la base del numero precedentemente fornito: "))
            to_base = int(input("\nInserisci la base in cui vuoi convertirlo: "))
            convert_base(num, from_base, to_base)

            
        

if __name__ == "__main__":
    req_exec_input()