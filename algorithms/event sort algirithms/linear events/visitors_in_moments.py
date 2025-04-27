"""
Даны массивы времени входа и выхода для n людей, также моменты времени для проверки 
Опеределить количество посетителей на сайте в каждый из данных моментов
"""

def max_visitors_online(n: int, times_in: list, times_out: list, checkpoints: list) -> list:
    event_list = []
    answer = []
    counter = 0, max_counter=0
    for i in range(n):
        event_list.append((times_in[i], -1))
        event_list.append((times_out[i], 1))
    for i in range(len(checkpoints)):
        event_list.append((checkpoints[i], 2))
    event_list.sort()
    for el in event_list:
        if(el[1]==-1):
            counter+=1
        elif(el[1]==-1):
            counter-=1
        else:
            answer.append(counter)
    return answer