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
            arr = [random.randint(start, end) for _ in range(size)]
            return [None] + arr, "O(n)"
        elif choice.lower() in ['n', 'no']:
            user_input = input("Enter numbers separated by commas: ")
            typed_list = [int(x.strip()) for x in user_input.split(',')]
            return [None] + typed_list, "O(n)"

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1

class BST:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
            return
        current = self.root
        while True:
            if value < current.value:
                if current.left is None:
                    current.left = Node(value)
                    break
                current = current.left
            else:
                if current.right is None:
                    current.right = Node(value)
                    break
                current = current.right

    def search(self, value):
        current = self.root
        while current:
            if current.value == value:
                return True
            elif value < current.value:
                current = current.left
            else:
                current = current.right
        return False

    def inorder_traversal(self):
        result = []
        def traverse(node):
            if node:
                traverse(node.left)
                result.append(node.value)
                traverse(node.right)
        traverse(self.root)
        return result

class AVL(BST):
    def __init__(self):
        self.root = None

    def getHeight(self, node):
        return node.height if node else 0

    def getBalance(self, node):
        return self.getHeight(node.left) - self.getHeight(node.right) if node else 0

    def rightRotate(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3
        z.height = 1 + max(self.getHeight(z.left), self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))
        return y

    def leftRotate(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self.getHeight(z.left), self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))
        return y

    def _insert(self, node, value):
        if not node:
            return Node(value)
        if value < node.value:
            node.left = self._insert(node.left, value)
        else:
            node.right = self._insert(node.right, value)
        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        balance = self.getBalance(node)
        if balance > 1 and value < node.left.value:
            return self.rightRotate(node)
        if balance < -1 and value > node.right.value:
            return self.leftRotate(node)
        if balance > 1 and value > node.left.value:
            node.left = self.leftRotate(node.left)
            return self.rightRotate(node)
        if balance < -1 and value < node.right.value:
            node.right = self.rightRotate(node.right)
            return self.leftRotate(node)
        return node

    def insert(self, value):
        self.root = self._insert(self.root, value)

if __name__ == "__main__":
    array, cost_input = Heap.getArrayInput()
    print("Original array:", array)
    print("getArrayInput cost:", cost_input)
    heap_instance = Heap(array)
    sorted_array, cost_sort = heap_instance.heapSort()
    print("Sorted array:", sorted_array)
    print("heapSort cost:", cost_sort)