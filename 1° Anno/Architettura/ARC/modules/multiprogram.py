def solve_multiprogram(mem_tot: int, mem_os: int, mem_proc: int, wait_io: int, cpu_load: int):
    if cpu_load == 0:
        num_proc = (mem_tot - mem_os)/mem_proc
        cpu_load = 1 - wait_io**num_proc
        print("Il carico medio della CPU è: " + str(cpu_load*100) + "%\nSono allocabili ", num_proc, " processi.")
    elif mem_proc == 0:
        num_proc = (math.log(1 - cpu_load))/(math.log(wait_io))
        mem_proc = (mem_tot - mem_os)/num_proc
        print("Lo spazio medio occupato da un processo è di: " + str(mem_proc) + " e ci sono " + str(num_proc) + " processi.")