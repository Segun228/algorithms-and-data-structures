def add(index: int, diff: int, fenwick_list: list):
    while(index < len(fenwick_list)):
        fenwick_list[index] += diff
        index = index | (index + 1)

def set_value(index: int, new_value: int, original_list: list, fenwick_list: list):
    diff = new_value - original_list[index]
    original_list[index] = new_value
    add(index, diff, fenwick_list)

def build(original_list: list, fenwick_list: list):
    for index in range(len(original_list)):
        add(index, original_list[index], fenwick_list)

def prefix_sum(index: int, fenwick_list: list)->int:
    result = 0
    while(index >= 0):
        result+=fenwick_list[index]
        index = fenwick_function(index) - 1
    return result

def fenwick_function(index: int) -> int:
    return (index & (index + 1))

def interval_sum(left: int, right: int, fenwick_list : list):
    return prefix_sum(right, fenwick_list) - prefix_sum(left-1, fenwick_list)


original_list = [2, 4, 5, 6, 33, 66, 34, 234, 909, 45, 234, 434]
fenwick_list = list()
for _ in original_list:
    fenwick_list.append(0)


build(original_list, fenwick_list)
add(2, 133, fenwick_list)
set_value(5, 0, original_list, fenwick_list)
print(original_list)
print(fenwick_list)
print(prefix_sum(5, fenwick_list))
print(prefix_sum(1, fenwick_list))
print(interval_sum(2, 4, fenwick_list))