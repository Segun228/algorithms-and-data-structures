heap = []

def top(heap: list) -> int:
    if(len(heap)==0):
        print("The heap is empty")
        return None
    print(heap[0])
    return heap[0]

def push(el_value: int, heap: list) -> int:
    heap.append(el_value)
    validate_up(len(heap)-1, heap)
    return heap[0]


def pop_element(heap: list) -> int:
    buf = heap[0]
    heap[0] = heap[-1]
    heap.pop(-1)
    validate_down(0, heap)
    return buf



def validate_up(el_index: int, heap: list):
    if(el_index==0):
        return
    parent = (el_index-1)//2
    if(heap[parent] > heap[el_index]):
        heap[parent], heap[el_index]= heap[el_index], heap[parent]
    validate_up(parent, heap)
    return

def validate_down(el_index: int, heap: list):
    left = el_index*2 + 1
    right = el_index*2 + 2
    if(left>len(heap) and heap[left]<heap[el_index]):
        heap[left], heap[el_index]= heap[el_index], heap[left]
        validate_down(left, heap)
    if(right>len(heap) and heap[right]<heap[el_index]):
        heap[right], heap[el_index]= heap[el_index], heap[right]
        validate_down(left, heap)
    return


def print_heap(heap: list):
    for i in range(len(heap)):
        print(heap[i], end="\t")
    print()


push(5, heap)
push(20, heap)
push(33, heap)
push(45, heap)
push(225, heap)
print_heap(heap)
print(top(heap))
pop_element(heap)
pop_element(heap)
print(top(heap))
print_heap(heap)

