"""
Даны массивы времени входа и выхода для n людей. 
Опеределить суммарное время, когда на сайте был хотя бы один человек
"""
def max_visitors_online(n: int, times_in: list, times_out: list) -> int:
    event_list = []
    counter = 0
    for i in range(n):
        event_list.append((times_in[i], -1))
        event_list.append((times_out[i], 1))
    event_list.sort()
    prev_action = 0
    total_time = 0
    for el in event_list:
        if(counter>0):
            total_time+=(el[0]-prev_action)
        prev_action = el[0]
        if(el[1]==-1): 
            counter+=1
        else:
            counter-=1
            
    return total_time