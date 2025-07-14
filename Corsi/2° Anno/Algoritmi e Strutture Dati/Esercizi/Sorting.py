import time
import random

class Sorting:
    def __init__(self, array:list):
        self.array:list = array

    def selectionSort(self, input_array=None):
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
        arr = input_array.copy() if input_array is not None else self.array.copy()
        n = len(arr)
        for i in range(n):
            for j in range(0, n-i-1):
                if arr[j] > arr[j+1]:
                    arr[j], arr[j+1] = arr[j+1], arr[j]
        return [arr, "O(n^2)"]

    def mergeSort(self, input_array=None) -> list:
        arr = input_array.copy() if input_array is not None else self.array.copy()
        self.mergeSortHelper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]
    def mergeSortHelper(self, arr: list, left: int, right: int)-> None: 
        if left < right:
            mid = (left + right) // 2
            self.mergeSortHelper(arr, left, mid)
            self.mergeSortHelper(arr, mid + 1, right)
            self.Merge(arr, left, mid, right)
    def Merge(self, arr: list, left: int, mid: int, right: int) -> None:
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

    def quickSort(self, input_array=None):
        arr = input_array.copy() if input_array is not None else self.array.copy()
        self.quickSortHelper(arr, 0, len(arr) - 1)
        return [arr, "O(n log n)"]
    def quickSortHelper(self, arr, init, final):
        if init < final:
            pivot = self.Partition(arr, init, final)
            self.quickSortHelper(arr, init, pivot - 1)
            self.quickSortHelper(arr, pivot + 1, final)
    def Partition(self, arr, init, final):
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
        arr = input_array.copy() if input_array is not None else self.array.copy()
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

    def bucketSort(self, input_array=None):
        arr: list = input_array.copy() if input_array is not None else self.array.copy()
        
        if not arr:
            return [arr, "O(n + k)"]
        
        is_bucket_array = isinstance(arr[0], list)
        
        if is_bucket_array:
            max_val: int = max(bucket[0] for bucket in arr)
            temp: list = [None] * (max_val+1)
        else:
            return [arr, "O(n + k)"]
        
        for bucket in arr:
            key = bucket[0]
            if temp[key] is None:
                temp[key] = bucket
            else:
                temp[key].extend(bucket[1:])
        
        arr = [bucket for bucket in temp if bucket is not None]
        
        return [arr, "O(n + k)", max_val]
        
    def radixSort(self, input_array=None):
        arr = input_array.copy() if input_array is not None else self.array.copy()
        if not arr:
            return [arr, "O(d*(n+k))"]
        is_bucket_array = isinstance(arr[0], list)
        
        if is_bucket_array:
            max_num = max(bucket[0] for bucket in arr)
        else:
            max_num = max(arr)
        
        max_digits = len(str(max_num))
        
        for digit_place in range(max_digits):
            buckets = [[] for _ in range(10)]
            
            for item in arr:
                # Extract the key based on array type
                key = item[0] if is_bucket_array else item
                # Get the digit at the current position
                digit = (key // (10 ** digit_place)) % 10
                buckets[digit].append(item)
            
            # Reconstruct the array
            arr = []
            for bucket in buckets:
                arr.extend(bucket)
                
        return [arr, "O(d*(n+k))", max_digits]

    def generate_random_array(self, num_elements):
        self.array = [random.randint(0, num_elements*5) for _ in range(num_elements)]
        print(f"Generated array: {self.array}")

    def generate_random_buckets_array(self, num_elements, satellite_info_count=3):
        self.array = []
        for _ in range(num_elements):
            key = random.randint(0, num_elements*5)
            satellite_info = [random.randint(1, 100) for _ in range(satellite_info_count)]
            bucket = [key] + satellite_info
            self.array.append(bucket)
        
        print(f"Generated bucket array: {self.array}")
        print(f"Format: [key, satellite_info1, satellite_info2, ...]")
        
    def generate_random_radix_array(self, num_elements, max_digits=3):
        """Generate an array of random integers suitable for radix sort."""
        max_value = 10**max_digits - 1  # Maximum possible value with max_digits
        self.array = [random.randint(0, max_value) for _ in range(num_elements)]
        print(f"Generated array for radix sort: {self.array}")
        print(f"Max digits: {max_digits}")
        
    def generate_random_radix_buckets(self, num_elements, satellite_info_count=3, max_digits=3):
        """Generate an array of buckets with random keys suitable for radix sort."""
        self.array = []
        max_value = 10**max_digits - 1  # Maximum possible value with max_digits
        
        for _ in range(num_elements):
            key = random.randint(0, max_value)
            satellite_info = [random.randint(1, 100) for _ in range(satellite_info_count)]
            bucket = [key] + satellite_info
            self.array.append(bucket)
        
        print(f"Generated bucket array for radix sort: {self.array}")
        print(f"Format: [key, satellite_info1, satellite_info2, ...]")
        print(f"Max digits in keys: {max_digits}")

    def select_sorting_algorithm(self, input_array=None):
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
        
        # Use the input array if provided, otherwise use the instance's array
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
            # If no input array is provided, use the instance's array
            arr_to_sort = self.array.copy()
            
        # Display the array being sorted
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