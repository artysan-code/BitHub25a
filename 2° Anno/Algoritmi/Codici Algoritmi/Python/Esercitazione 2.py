import random, math

'''
    Esercizio 1
'''


def GenIstance(dim: int) -> list:
    array = []
    for _ in range(dim):
        array.append(random.randint(0, 100))
    return array

## Soluzione: usare la ricerca binaria
def BinarySearchUnimodale(array: list, start: int, end: int) -> list:
    if start > end:
        return -1
    middle = math.ceil((start+end)/2)
    if array[middle] > array[middle-1] and array[middle] < array[middle+1]:
        return middle
    elif array[middle] > array[middle+1]:
        return BinarySearchUnimodale(array, start, middle-1)
    else:
        return BinarySearchUnimodale(array, middle+1, end)

def MaxUnimodale(array: list) -> list:
    if array[0] > array[1]:
        return 1
    elif array[len(array)] < array[len(array) - 1]:
        return len(array)
    else:
        BinarySearchUnimodale(array, 2, len(array)-1)

## Esercizio implementare Invert e Merge.
def Invert(array: list, start: int, end: int) -> list:
    pass

def SpecialMerge(array: list, start: int, middlemax: int, end: int) -> list:
    pass
def SortUnimodale(array: list) -> list:
    maxnum = MaxUnimodale(array)
    if maxnum != len(array):
        Invert(array, maxnum + 1, len(array))
        if maxnum != 1:
            SpecialMerge(A, 1, maxnum, len(array))

'''
    Esercizio 2:
        Dato un array, trovare due indici i* e j* tali che i* < j* e per ogni altra coppia
        di indici i, j con i < j A[j*] - A[i*] >= A[j] - A[i]
        Guardiamolo come se l'array sia la lista dei prezzi di un prodotto durante le giornate:

        A [4, 10, 2, 23, 24, 1, 29]
           1   2  3   4   5  6   7

        Conviene comprarlo al giorno 6 e vendere al giorno 7
'''

A= GenIstance(7)
print(A)
def MaxProfit(array: list) -> list:
    pass


Max[k]=