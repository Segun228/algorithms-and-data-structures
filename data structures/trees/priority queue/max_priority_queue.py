import math

class Max_priority_queue():
    def __init__(self):
        self.heap = []
        print("queue initialized")
    
    def push(self, el_value, el_priority) -> int:
        self.heap.append((el_value, el_priority))
        self._validate_up(len(self.heap)-1)
        return self.heap[0][0]
    
    def _validate_up(self, el_index: int):
        if(el_index==0):
            return
        parent = (el_index-1)//2
        if(self.heap[parent][1] < self.heap[el_index][1]):
            self.heap[parent], self.heap[el_index] = self.heap[el_index], self.heap[parent]
        self._validate_up(parent)
        return
    
    def _validate_down(self, el_index: int):
        left = el_index * 2 + 1
        right = el_index * 2 + 2
        biggest = el_index
        if left < len(self.heap) and self.heap[left][1] > self.heap[biggest][1]:
            biggest = left
        if right < len(self.heap) and self.heap[right][1] > self.heap[biggest][1]:
            biggest = right
        if biggest != el_index:
            self.heap[el_index], self.heap[biggest] = self.heap[biggest], self.heap[el_index]
            self._validate_down(biggest)
    

    def print_heap(self):
        if not self.heap:
            print("Heap is empty")
            return

        levels = math.floor(math.log2(len(self.heap))) + 1
        max_width = 2 ** levels * 6
        index = 0

        for level in range(levels):
            level_nodes = 2 ** level
            spacing = max_width // (level_nodes + 1)
            line = ""
            for i in range(level_nodes):
                if index >= len(self.heap):
                    break
                value, priority = self.heap[index]
                node_str = f"{value}:{priority}"
                line += node_str.center(spacing)
                index += 1
            print(line)
        print("-" * max_width)

    def top(self) -> int:
        if(len(self.heap)==0):
            print("The heap is empty")
            return None
        print(self.heap[0][0])
        return self.heap[0][0]

    def pop(self, silent=False) -> int:
        if not self.heap:
            return None
        buf = self.heap[0][0]
        self.heap[0] = self.heap[-1]
        self.heap.pop(-1)
        self._validate_down(0)
        if not silent:
            print(f"{buf} was succesfully deleted")
        return buf

    def heap_sort(self, data=None):
        if data is not None:
            for el in data:
                if isinstance(el, tuple) and len(el) == 2 and isinstance(el[0], int) and isinstance(el[1], int):
                    self.push(el[0], el[1])
                else:
                    continue
        backup = self.heap[:]
        result = []
        while self.heap:
            result.append(self.pop(True))
        self.heap = backup
        for el in result:
            print(el, end="\t")
        print()
        return result

def main():
    example = Max_priority_queue()
    example.print_heap()
    example.push(3, 56)
    example.print_heap()
    example.push(4, 563)
    example.print_heap()
    example.push(777, 1)
    example.print_heap()
    example.push(3, 511)
    example.print_heap()
    example.push(33, 5632)
    example.print_heap()
    example.push(311, 5343)
    example.print_heap()
    example.push(356, 534)
    example.print_heap()
    example.push(984, 523)
    example.print_heap()
    example.print_heap()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.top()
    example.print_heap()
    example.top()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.pop()
    example.print_heap()
    example.push(94, 233)
    example.push(944, 23)
    example.push(924, 953)
    example.push(594, 333)
    example.push(894, 733)
    example.push(694, 833)
    example.push(994, 133)
    print("Теперь сортировки")
    example.heap_sort()
    data = [(94, 233), (944, 23), (924, 953), (594, 333), (894, 733), (694, 833), (994, 133)]
    example.heap_sort(data)

if __name__ == "__main__":
    main()