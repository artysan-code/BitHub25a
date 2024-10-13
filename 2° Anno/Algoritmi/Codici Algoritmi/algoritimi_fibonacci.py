from math import sqrt
import numpy as np

def fibonacci1(n: int) -> int:
    return int((pow((1+sqrt(5))/2, n) - pow((1-sqrt(5))/2, n)) / sqrt(5))

def fibonacci2(n: int) -> int:
    if n < 2:
        return n
    else:
        return fibonacci2(n-1) + fibonacci2(n-2)

def fibonacci3(n: int) -> int:
    Fib = [1, 1]
    for i in range(2, n):
        Fib.append(Fib[i-1] + Fib[i-2])
    return Fib[n-1]

def fibonacci4(n: int) -> int:
    a = 1 # F_n-1
    b = 1 # F_n-2
    for _ in range(3, n+1):
        c = a + b # F_n
        a = b
        b = c
    return c

def fibonacci5(n: int) -> int:
    N = np.array([[1, 1], [1, 0]])
    M = np.array([[1, 0], [0, 1]])
    for _ in range(1, n):
        M = np.dot(M, N)
    return M[0][0]

def fibonacci6(n: int) -> int:
    A = np.array([[1, 1], [1, 0]])
    M = potenzadiMatrice(A, n - 1)
    return M[0][0]
def potenzadiMatrice(A: np.array, k: int) -> np.array:
    if k == 0: return np.array([[1, 0], [0, 1]])
    else:
        M = potenzadiMatrice(A, k // 2)
        M = np.dot(M, M)
        if k % 2 == 1: M = np.dot(M, A)
        return M

# Ci mette del tempo considerevole a causa degli algoritmi meno efficienti
print(fibonacci1(40) == fibonacci2(40) == fibonacci3(40) == fibonacci4(40) == fibonacci5(40) == fibonacci6(40))