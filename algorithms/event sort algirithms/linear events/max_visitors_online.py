"""
Даны массивы времени входа и выхода для n людей. 
Опеределить максимальное количество посетителей на сайте единовременно
"""

def max_visitors_online(n: int, times_in: list, times_out: list) -> int:
    event_list = []
    counter = 0, max_counter=0
    for i in range(n):
        event_list.append((times_in[i], -1))
        event_list.append((times_out[i], 1))
    event_list.sort()
    for el in event_list:
        if(el[1]==-1):
            counter+=1
            max_counter = max(max_counter, counter)
        else:
            counter-=1
            max_counter = max(max_counter, counter)
    return max_counter