import time
import random

class SortingAlgorithms:
    def __init__(self, array):
        self.array = array

    def selection_sort(self):
        arr = self.array.copy()
        n = len(arr)
        for i in range(n):
            min_idx = i
            for j in range(i+1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
        return [arr, "O(n^2)"]

    def insertion_sort(self):
        arr = self.array.copy()
        for i in range(1, len(arr)):
            key = arr[i]
            j = i-1
            while j >= 0 and key < arr[j]:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key
        return [arr, "O(n^2)"]

    def bubble_sort(self):
        arr = self.array.copy()
        n = len(arr)
        for i in range(n):
            for j in range(0, n-i-1):
                if arr[j] > arr[j+1]:
                    arr[j], arr[j+1] = arr[j+1], arr[j]
        return [arr, "O(n^2)"]
    
    def merge_sort(self) -> list:
        arr = self.array.copy()
        self._merge_sort_helper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]
    
    def _merge_sort_helper(self, arr: list, left: int, right: int)-> None: 
        if left < right:
            mid = (left + right) // 2
            self._merge_sort_helper(arr, left, mid)
            self._merge_sort_helper(arr, mid + 1, right)
            self._merge(arr, left, mid, right)
        else:
            print("Critical Error with Algorithm")
            
    def _merge(self, arr: list, left: int, mid: int, right: int) -> None:
        arr_aux = []
        left_c, right_c = left, mid + 1
        while (left_c <= mid) and (right_c <= right):
            if arr[left_c] < arr[right_c]:
                arr_aux.append(arr[left_c])
                left_c += 1
            else:
                arr_aux.append(arr[right_c])
                right_c += 1
        if (left_c <= mid):
            arr_aux.extend(arr[left_c:mid + 1])
        else:
            arr_aux.extend(arr[right_c:right + 1])
        arr[left:right + 1] = arr_aux

    def quick_sort(self):
        arr = self.array.copy()
        self._quick_sort_helper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]

    def _partition(self, arr, low, high):
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        return i + 1

    def _quick_sort_helper(self, arr, low, high):
        if low < high:
            pi = self._partition(arr, low, high)
            self._quick_sort_helper(arr, low, pi - 1)
            self._quick_sort_helper(arr, pi + 1, high)

    def generate_random_array(self, num_elements):
        self.array = [random.randint(0, 2000) for _ in range(num_elements)]
        print(f"Generated array: {self.array}")

    def select_sorting_algorithm(self):
        print("Select sorting algorithm:")
        print("1. Bubble Sort")
        print("2. Selection Sort")
        print("3. Insertion Sort")
        print("4. Quick Sort")
        print("5. Merge Sort")
        
        choice = int(input("Enter choice (1/2/3/4/5): "))
        
        start_time = time.time()
        
        if choice == 1:
            sorted_array, cost = self.bubble_sort()
        elif choice == 2:
            sorted_array, cost = self.selection_sort()
        elif choice == 3:
            sorted_array, cost = self.insertion_sort()
        elif choice == 4:
            sorted_array, cost = self.quick_sort()
        elif choice == 5:
            sorted_array, cost = self.merge_sort()
        else:
            print("Invalid choice")
            return
        
        end_time = time.time()
        elapsed_time = end_time - start_time
        
        print(f"Algorithm Cost: {cost}")
        print(f"Sorted array: {sorted_array}")
        print(f"Time taken: {elapsed_time:.6f} seconds")

if __name__ == "__main__":
    lenght = int(input("Enter the number of elements for the array: "))
    sorting_algorithms = SortingAlgorithms([])
    sorting_algorithms.generate_random_array(lenght)
    sorting_algorithms.select_sorting_algorithm()
