"""
Sorting Algorithms Module
------------------------
This module provides a Sorting class that implements various sorting algorithms, including:
- Selection Sort
- Insertion Sort
- Bubble Sort
- Merge Sort
- Quick Sort
- Integer (Counting) Sort
- Bucket Sort
- Radix Sort

The class also provides methods to generate random arrays and bucket arrays for testing purposes.
"""
import time
import random

class Sorting:
    """
    A class that implements various sorting algorithms and utilities for generating test arrays.
    """
    def __init__(self, array:list):
        """
        Initialize the Sorting object with an array.
        :param array: List of integers or buckets to sort.
        """
        self.array:list = array

    def selectionSort(self, input_array=None):
        """
        Sorts an array using selection sort algorithm.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        n = len(arr)
        for i in range(n):
            min_idx = i
            for j in range(i+1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
        return [arr, "O(n^2)"]

    def insertSort(self, input_array=None):
        """
        Sorts an array using insertion sort algorithm.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        for i in range(1, len(arr)):
            key = arr[i]
            j = i-1
            while j >= 0 and key < arr[j]:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key
        return [arr, "O(n^2)"]

    def bubbleSort(self, input_array=None):
        """
        Sorts an array using bubble sort algorithm.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        n = len(arr)
        for i in range(n):
            for j in range(0, n-i-1):
                if arr[j] > arr[j+1]:
                    arr[j], arr[j+1] = arr[j+1], arr[j]
        return [arr, "O(n^2)"]

    def mergeSort(self, input_array=None) -> list:
        """
        Sorts an array using merge sort algorithm.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        self.mergeSortHelper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]
    def mergeSortHelper(self, arr: list, left: int, right: int)-> None: 
        """
        Helper function for merge sort algorithm.
        :param arr: Array to sort.
        :param left: Left index.
        :param right: Right index.
        """
        if left < right:
            mid = (left + right) // 2
            self.mergeSortHelper(arr, left, mid)
            self.mergeSortHelper(arr, mid + 1, right)
            self.Merge(arr, left, mid, right)
    @staticmethod
    def Merge(arr: list, left: int, mid: int, right: int) -> None:
        """
        Merges two halves of an array sorted in ascending order.
        :param arr: Array to merge.
        :param left: Left index of the first half.
        :param mid: Right index of the first half / Left index of the second half.
        :param right: Right index of the second half.
        """
        arr_aux = []
        left_c, right_c = left, mid + 1
        while (left_c <= mid) and (right_c <= right):
            if arr[left_c] < arr[right_c]:
                arr_aux.append(arr[left_c])
                left_c += 1
            else:
                arr_aux.append(arr[right_c])
                right_c += 1
        if left_c <= mid:
            arr_aux.extend(arr[left_c:mid + 1])
        else:
            arr_aux.extend(arr[right_c:right + 1])
        arr[left:right + 1] = arr_aux

    def quickSort(self, input_array=None):
        """
        Sorts an array using quick sort algorithm (randomized version).
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        self.quickSortHelper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]
    def quickSortHelper(self, arr, init, final):
        """
        Helper function for quick sort algorithm.
        :param arr: Array to sort.
        :param init: Initial index.
        :param final: Final index.
        """
        if init < final:
            pivot = self.Partition(arr, init, final)
            self.quickSortHelper(arr, init, pivot - 1)
            self.quickSortHelper(arr, pivot + 1, final)
    @staticmethod
    def Partition(arr, init, final):
        """
        Partitions the array for quick sort.
        :param arr: Array to partition.
        :param init: Initial index.
        :param final: Final index.
        :return: Pivot index.
        """
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

    def integerSort(self, input_array=None):
        """
        Sorts an array of integers using integer sort (counting sort) algorithm.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array and time complexity string.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        if not arr:
            return [arr, "O(n + k)"]
        
        max_val = max(arr)
        min_val = min(arr)
        range_val = max_val - min_val + 1
        
        count = [0] * range_val
        output = [0] * len(arr)
        
        for num in arr:
            count[num - min_val] += 1
        
        for i in range(1, len(count)):
            count[i] += count[i - 1]
        
        for i in range(len(arr) - 1, -1, -1):
            output[count[arr[i] - min_val] - 1] = arr[i]
            count[arr[i] - min_val] -= 1
        
        return [output, "O(n + k)"]

    def bucketSort(self, input_array=None):
        """
        Sorts an array of buckets (lists) by their first element (key) using bucket sort.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array, time complexity string, and max value.
        """
        arr: list = input_array.copy() if input_array is not None else self.array.copy()
        if not arr:
            return [arr, "O(n + k)"]
        if not all(isinstance(bucket, list) and len(bucket) > 0 and isinstance(bucket[0], int) for bucket in arr):
            raise ValueError("All elements must be non-empty lists with an integer key as the first element.")
        is_bucket_array = isinstance(arr[0], list)
        if is_bucket_array:
            max_val: int = max(bucket[0] for bucket in arr)
            temp: list = [None] * (max_val+1)
        else:
            return [arr, "O(n + k)"]
        for bucket in arr:
            key = bucket[0]
            if key < 0 or key > max_val:
                raise ValueError(f"Bucket key {key} out of range 0..{max_val}")
            if temp[key] is None:
                temp[key] = bucket.copy()
            else:
                temp[key].extend(bucket[1:])
        arr = [bucket for bucket in temp if bucket is not None]
        return [arr, "O(n + k)", max_val]
    def radixSort(self, input_array=None):
        """
        Sorts an array of integers or buckets by their keys using radix sort.
        :param input_array: Optional array to sort. If None, uses self.array.
        :return: Sorted array, time complexity string, and max digits.
        """
        arr = input_array.copy() if input_array is not None else self.array.copy()
        if not arr:
            return [arr, "O(d*(n+k))"]
        is_bucket_array = isinstance(arr[0], list)
        if is_bucket_array:
            if not all(isinstance(bucket, list) and len(bucket) > 0 and isinstance(bucket[0], int) for bucket in arr):
                raise ValueError("All elements must be non-empty lists with an integer key as the first element.")
            max_num = max(bucket[0] for bucket in arr)
        else:
            if not all(isinstance(x, int) for x in arr):
                raise ValueError("All elements must be integers for radix sort.")
            max_num = max(arr)
        max_digits = len(str(abs(max_num)))
        for digit_place in range(max_digits):
            buckets = [[] for _ in range(10)]
            for item in arr:
                key = item[0] if is_bucket_array else item
                digit = (abs(key) // (10 ** digit_place)) % 10
                buckets[digit].append(item)
            arr = []
            for bucket in buckets:
                arr.extend(bucket)
        return [arr, "O(d*(n+k))", max_digits]

    def generate_random_array(self, num_elements):
        """
        Generates a random array of integers and assigns it to self.array.
        :param num_elements: Number of elements in the array.
        """
        if not isinstance(num_elements, int) or num_elements < 0:
            raise ValueError("num_elements must be a non-negative integer.")
        self.array = [random.randint(0, num_elements*5) for _ in range(num_elements)]
        print(f"Generated array: {self.array}")

    def generate_random_buckets_array(self, num_elements, satellite_info_count=3):
        """
        Generates a random array of buckets (lists) with a key and satellite info, assigns to self.array.
        :param num_elements: Number of buckets.
        :param satellite_info_count: Number of satellite info elements per bucket.
        """
        if not isinstance(num_elements, int) or num_elements < 0:
            raise ValueError("num_elements must be a non-negative integer.")
        if not isinstance(satellite_info_count, int) or satellite_info_count < 0:
            raise ValueError("satellite_info_count must be a non-negative integer.")
        self.array = []
        for _ in range(num_elements):
            key = random.randint(0, num_elements*5)
            satellite_info = [random.randint(1, 100) for _ in range(satellite_info_count)]
            bucket = [key] + satellite_info
            self.array.append(bucket)
        print(f"Generated bucket array: {self.array}")
        print(f"Format: [key, satellite_info1, satellite_info2, ...]")
        
    def generate_random_radix_array(self, num_elements, max_digits=3):
        """
        Generates a random array of integers with a specified number of digits for radix sort.
        :param num_elements: Number of elements in the array.
        :param max_digits: Maximum number of digits for each number.
        """
        max_value = 10**max_digits - 1
        self.array = [random.randint(0, max_value) for _ in range(num_elements)]
        print(f"Generated array for radix sort: {self.array}")
        print(f"Max digits: {max_digits}")
        
    def generate_random_radix_buckets(self, num_elements, satellite_info_count=3, max_digits=3):
        """
        Generates a random array of buckets (lists) with a key and satellite info for radix sort.
        :param num_elements: Number of buckets.
        :param satellite_info_count: Number of satellite info elements per bucket.
        :param max_digits: Maximum number of digits for each key.
        """
        self.array = []
        max_value = 10**max_digits - 1

        for _ in range(num_elements):
            key = random.randint(0, max_value)
            satellite_info = [random.randint(1, 100) for _ in range(satellite_info_count)]
            bucket = [key] + satellite_info
            self.array.append(bucket)
        
        print(f"Generated bucket array for radix sort: {self.array}")
        print(f"Format: [key, satellite_info1, satellite_info2, ...]")
        print(f"Max digits in keys: {max_digits}")

    def select_sorting_algorithm(self, input_array=None):
        """
        Selects and executes a sorting algorithm based on user input.
        :param input_array: Optional array to sort. If None, uses self.array.
        """
        print("Select sorting algorithm:")
        print("1. Selection Sort")
        print("2. Insertion Sort")
        print("3. Bubble Sort")
        print("4. Merge Sort")
        print("5. Quick Sort (Random Version)")
        print("6. Integer Sort")
        print("7. Bucket Sort")
        print("8. Radix Sort")
        
        choice = int(input("Enter choice (1/2/3/4/5/6/7/8): "))
        
        arr_to_sort = input_array
        
        if (arr_to_sort is None and not self.array) or (choice == 7 and arr_to_sort is None and not isinstance(self.array[0], list)):
            num_elements = len(self.array) if self.array else int(input("Enter the number of elements for the array: "))
            if choice == 7:
                satellite_info_count = int(input("Enter number of satellite information elements per bucket (default 3): ") or "3")
                self.generate_random_buckets_array(num_elements, satellite_info_count)
                arr_to_sort = self.array.copy()
            elif choice == 8:
                max_digits = int(input("Enter maximum number of digits for radix sort (default 3): ") or "3")
                bucket_array = input("Do you want to use bucket arrays for radix sort? (y/n): ").lower() == 'y'
                if bucket_array:
                    satellite_info_count = int(input("Enter number of satellite information elements per bucket (default 3): ") or "3")
                    self.generate_random_radix_buckets(num_elements, satellite_info_count, max_digits)
                    arr_to_sort = self.array.copy()
                else:
                    self.generate_random_radix_array(num_elements, max_digits)
                    arr_to_sort = self.array.copy()
            else:
                if arr_to_sort is None and not self.array:
                    self.generate_random_array(num_elements)
                    arr_to_sort = self.array.copy()
        elif arr_to_sort is None:
            arr_to_sort = self.array.copy()
            
        print(f"Array to sort: {arr_to_sort}")
        
        max_value = None
        max_digits = None
        start_time = time.time()
        
        
        if choice == 1:
            sorted_array, cost = self.selectionSort(arr_to_sort)
        elif choice == 2:
            sorted_array, cost = self.insertSort(arr_to_sort)
        elif choice == 3:
            sorted_array, cost = self.bubbleSort(arr_to_sort)
        elif choice == 4:
            sorted_array, cost = self.mergeSort(arr_to_sort)
        elif choice == 5:
            sorted_array, cost = self.quickSort(arr_to_sort)
        elif choice == 6:
            sorted_array, cost = self.integerSort(arr_to_sort)
        elif choice == 7:
            sorted_array, cost, max_value = self.bucketSort(arr_to_sort)
        elif choice == 8:
            sorted_array, cost, max_digits = self.radixSort(arr_to_sort)
        else:
            print("Invalid choice")
            return
        
        end_time = time.time()
        elapsed_time = end_time - start_time
        
        print(f"Sorted array: {sorted_array}")
        print(f"Algorithm Cost: {cost}")
        print(f"Time taken: {elapsed_time:.6f} seconds")
        if choice == 7 and max_value: print(f"Max value in bucket sort: {max_value}")
        if choice == 8 and max_digits: print(f"Max digits in radix sort: {max_digits}")
        temp=sorted_array.copy()
        if sorted(temp) == sorted_array: print("The array is sorted correctly") 
        else: print("The array is not sorted correctly")

# ------ Sezione Main ------
if __name__ == "__main__":
    sorting = Sorting([])
    sorting.select_sorting_algorithm()