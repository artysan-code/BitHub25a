class Heap:
    def __init__(self, heap: list):
        self.heap = heap

    def fixHeap(self, i: int) -> None:
        sin = 2 * i
        des = 2 * i + 1
        if (sin <= len(self.heap) - 1 and self.heap[sin] > self.heap[i]):
            max_idx = sin
        else:
            max_idx = i
        if (des <= len(self.heap) - 1 and self.heap[des] > self.heap[max_idx]):
            max_idx = des
        if max_idx != i:
            self.heap[i], self.heap[max_idx] = self.heap[max_idx], self.heap[i]
            self.fixHeap(max_idx)
        return "O(log n)"

    def extractMax(self) -> int:
        if len(self.heap) < 2:
            return None
        max_value = self.heap[1]
        self.heap[1] = self.heap[-1]
        self.heap.pop()
        self.fixHeap(1)
        return max_value, "O(log n)"

    def heapify(self) -> None:
        for i in range((len(self.heap) - 1) // 2, 0, -1):
            self.fixHeap(i)
        return "O(n)"

    def heapSort(self) -> list:
        self.heapify()
        sorted_arr = []
        while len(self.heap) > 1:
            self.heap[1], self.heap[-1] = self.heap[-1], self.heap[1]
            sorted_arr.append(self.heap.pop())
            self.fixHeap(1)
        return sorted_arr, "O(n log n)"

    @staticmethod
    def getArrayInput():
        import random
        print("Do you want a random array to sort?")
        choice = input("Enter your choice (y/n): ")
        if choice.lower() in ['y', '', ' ', 'yes']:
            start = int(input("Enter the start of the range: "))
            end = int(input("Enter the end of the range: "))
            size = int(input("Enter the size of the array: "))
            return [None] + random.sample(range(start, end + 1), size), "O(n)"
        elif choice.lower() in ['n', 'no']:
            user_input = input("Enter numbers separated by commas: ")
            typed_list = [int(x.strip()) for x in user_input.split(',')]
            return [None] + typed_list, "O(n)"

if __name__ == "__main__":
    array, cost_input = Heap.getArrayInput()
    print("Original array:", array)
    print("getArrayInput cost:", cost_input)
    heap_instance = Heap(array)
    sorted_array, cost_sort = heap_instance.heapSort()
    print("Sorted array:", sorted_array)
    print("heapSort cost:", cost_sort)