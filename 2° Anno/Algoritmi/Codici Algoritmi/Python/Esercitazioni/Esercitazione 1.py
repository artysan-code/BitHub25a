def Banale(A,n):    
    for i in range(1,n-1):
        for j in range(i+1,n):
            if (A[i]+A[j]==x):
                return (i,j)
    return (-1,-1)

def MenoBanale(A,x):
    for i in range(len(A)):
        val = x - A[i]
        low = 0
        high = len(A) - 1
        while low <= high:
            mid = (low + high) // 2
            if A[mid] == val:
                return (i, mid)
            elif A[mid] < val:
                low = mid + 1
            else:
                high = mid - 1
    return (-1,-1)

def Lineare(A,x):
    i=1,j=x
    while i<j:
        if A[i]+A[j] == x:
            return (i,j)
        if A[i]+A[j] < x:
            i=i+1 
        else :
            j=j-1
    return (-1,-1)

A = [2, 5, 9, 14, 20, 21, 25, 40]

x = 26
# x = 20

print(Banale(A,x))
print(MenoBanale(A,x))
print(Lineare(A,x))


