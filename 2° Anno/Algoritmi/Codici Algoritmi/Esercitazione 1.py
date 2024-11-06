
def Banale(A,x):    #O(n^2)
for i=1 in range(n-1):
	for j=i+1 in range(n):
		if (A[i]+A[j]=x) then return (i,j)
return (-1,-1)

def MenoBanale(A,x):    #O(n log(n))
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
        if A[i]+A[j] == x then return (i,j)
        if A[i]+A[j] < x then i=i+1 else j=j-1
    return (-1,-1)

A = [2, 5, 9, 14, 20, 21, 25, 40]

x = 26
# x = 20

print(Banale(A,x))
print(MenoBanale(A,x))
print(Lineare(A,x))


