import time
import random

class Sorting:
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
    
    # Implementazione che rispetta pseudocodice del professore
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
    def _quick_sort_helper(self, arr, init, final):
        if init < final:
            pivot = self._partition(arr, init, final)
            self._quick_sort_helper(arr, init, pivot - 1)
            self._quick_sort_helper(arr, pivot + 1, final)
    def _partition(self, arr, init, final):
        pivot_index = random.randint(init, final)
        arr[init], arr[pivot_index] = arr[pivot_index], arr[init]
        pivot = arr[init]
        left = init
        right = final + 1
        while True:
            left += 1
            while left <= final and arr[left] <= pivot:
                left += 1
            right -= 1
            while arr[right] > pivot:
                right -= 1
            if left >= right: break
            arr[left], arr[right] = arr[right], arr[left]
        arr[init], arr[right] = arr[right], arr[init]
        return right

    def integer_sort(self):
        arr = self.array.copy()
        if not arr:
            return [arr, "O(n + k)"]
        
        max_val = max(arr)
        min_val = min(arr)
        range_val = max_val - min_val + 1
        
        count = [0] * range_val
        output = [0] * len(arr)
        
        # Store count of each element
        for num in arr:
            count[num - min_val] += 1
        
        # Modify count array to store actual positions
        for i in range(1, len(count)):
            count[i] += count[i - 1]
        
        # Build output array
        for i in range(len(arr) - 1, -1, -1):
            output[count[arr[i] - min_val] - 1] = arr[i]
            count[arr[i] - min_val] -= 1
        
        return [output, "O(n + k)"]

    def generate_random_array(self, num_elements):
        self.array = [random.randint(0, num_elements*5) for _ in range(num_elements)]
        print(f"Generated array: {self.array}")

    def select_sorting_algorithm(self):
        print("Select sorting algorithm:")
        print("1. Selection Sort")
        print("2. Insertion Sort")
        print("3. Bubble Sort")
        print("4. Merge Sort")
        print("5. Quick Sort (Random Version)")
        print("6. Integer Sort")
        
        choice = int(input("Enter choice (1/2/3/4/5/6): "))
        
        start_time = time.time()
        
        if choice == 1:
            sorted_array, cost = self.selection_sort()
        elif choice == 2:
            sorted_array, cost = self.insertion_sort()
        elif choice == 3:
            sorted_array, cost = self.bubble_sort()
        elif choice == 4:
            sorted_array, cost = self.merge_sort()
        elif choice == 5:
            sorted_array, cost = self.quick_sort()
        elif choice == 6:
            sorted_array, cost = self.integer_sort()
        else:
            print("Invalid choice")
            return
        
        end_time = time.time()
        elapsed_time = end_time - start_time
        
        print(f"Sorted array: {sorted_array}")
        print(f"Algorithm Cost: {cost}")
        print(f"Time taken: {elapsed_time:.6f} seconds")
        print(f"Is the array really sorted? ")
        temp=sorted_array.copy()
        if sorted(temp) == sorted_array:
            print("Yes")
        else:
            print("No")

if __name__ == "__main__":
    choice = input("Do you want to input the array elements manually? (y/n): ").strip().lower()
    if choice in ["y", "yes", "Y", "YES", "", " ", None]:
        array = list(map(int, input("Enter the elements of the array separated by space: ").split()))
        sorting = Sorting(array)
    else:
        length = int(input("Enter the number of elements for the array: "))
        sorting = Sorting([])
        sorting.generate_random_array(length)
    
    sorting.select_sorting_algorithm()
