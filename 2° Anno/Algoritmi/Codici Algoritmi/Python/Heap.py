def fixHeap(i: int, heap: list) -> None:
    sin = 2 * i
    des = 2 * i + 1
    if (sin <= len(heap) and heap[sin] > heap[i]):
        max = sin
    else: 
        max = i
    if (des <= len(heap) and heap[des] > heap[max]):
        max = des
    if max != i:
        heap[i], heap[max] = heap[max], heap[i]
        fixHeap(max, heap)

def heapify(heap: list) -> None:
    pass