import math

def req_exec_input() -> None:
    exercise = int(input("Inserisci che esercizio vuoi fare:\n\n- 0 per multiprogrammazione\n- 1 per Sistema batch\n\n> "))
    match exercise:
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
def solve_batch(algorithm: str, num_proc: int)-> None:
    algorithm = algorithm.upper()
    match algorithm:
        case "FCFS":
            data = {}
            for i in range(num_proc - 1):
                data["P" + i] = input("Inserisci il tempo di esecuzione del processo " + str(i+1)+ ": ")
                print("\n")

def solve_multiprogram(mem_tot: int, mem_os: int, mem_proc: int, wait_io: int, cpu_load: int):
    if cpu_load == 0:
        num_proc = (mem_tot - mem_os)/mem_proc
        cpu_load = 1 - wait_io**num_proc
        print("Il carico medio della CPU è: " + str(cpu_load*100) + "%\nSono allocabili ", num_proc, " processi.")
    elif mem_proc == 0:
        num_proc = (math.log(1 - cpu_load))/(math.log(wait_io))
        mem_proc = (mem_tot - mem_os)/num_proc
        print("Lo spazio medio occupato da un processo è di: " + str(mem_proc) + " e ci sono " + str(num_proc) + " processi.")

if __name__ == "__main__":
    req_exec_input()