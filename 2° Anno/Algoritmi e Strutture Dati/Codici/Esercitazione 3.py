def count(A):
    i,z,u = 0,0,0
    j=len(A)-1
    while i<j:
        if A[i]==0:
            z+=1
            i+=1
        else:
            i+=1
        if A[j]==1:
            u+=1
            j-=1
        else:
            j-=1
    return i

A=[0,1,1,1,0,0,1,0,1,1,1,0,0,1,0,0,0,1,1,1,0,1,1,0,0,1,0,0,1]
print(count(A))

#costo computazionale all'aumentare della dimensione di A
#O(n)