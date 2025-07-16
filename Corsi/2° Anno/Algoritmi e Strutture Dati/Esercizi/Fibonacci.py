import time
from math import sqrt
import numpy as np

def potenzadiMatrice(A: np.array, k: int) -> np.array:
    if k == 0: return np.array([[1, 0], [0, 1]])
    else:
        M = potenzadiMatrice(A, k // 2)
        M = np.dot(M, M)
        if k % 2 == 1: M = np.dot(M, A)
        return M

class Fibonacci:
    def __init__(self):
        self.nome = "Samuel"
    @staticmethod
    def alg1(n: int) -> int:
        return int((pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n)) / sqrt(5))
 
    @staticmethod
    def alg2(n: int) -> int:
        if n < 2:
            return n
        else:
            return Fibonacci.alg2(n-1) + Fibonacci.alg2(n-2)

    @staticmethod
    def alg3(n: int) -> int:
        Fib = [1, 1]
        for i in range(2, n):
            Fib.append(Fib[i-1] + Fib[i-2])
        return Fib[n-1]

    @staticmethod
    def alg4(n: int) -> int:
        a = 1
        b = 1
        i = 3
        while i<=n:
            c = a + b
            a = b
            b = c
            i += 1
        return c

    @staticmethod
    def alg5(n: int) -> int:
        N = np.array([[1, 1], [1, 0]])
        M = np.array([[1, 0], [0, 1]])
        for _ in range(1, n):
            M = np.dot(M, N)
        return M[0][0]

    @staticmethod
    def alg6(n: int) -> int:
        A = np.array([[1, 1], [1, 0]])
        M = potenzadiMatrice(A, n - 1)
        return M[0][0]
    
    @staticmethod
    def calc(ist: int, num: int) -> None:
        if (ist >= 1) and (ist <= 6):
            print(f"Il numero di Fibonacci di {num} è: ")
        
        start_time = time.time()
        
        result = None
        match ist:
            case 1:
                result = Fibonacci.alg1(num)
            case 2:
                result = Fibonacci.alg2(num)
            case 3:
                result = Fibonacci.alg3(num)
            case 4:
                result = Fibonacci.alg4(num)
            case 5:
                result = Fibonacci.alg5(num)
            case 6:
                result = Fibonacci.alg6(num)
            case _:
                print("Non esiste questo algoritmo richiesto.")
                return

        end_time = time.time()
        execution_time = end_time - start_time
        
        print(f"Risultato: {result}")
        print(f"Tempo di esecuzione: {execution_time:.6f} secondi")

Soluzione = Fibonacci()
ist = int(input("Inserisci il tipo di algoritmo che vuoi eseguire (1-6): "))
num = int(input("Inserisci il numero su cui calcolare Fibonacci: "))
Soluzione.calc(ist, num)
# Ci mette del tempo considerevole a causa degli algoritmi meno efficienti
