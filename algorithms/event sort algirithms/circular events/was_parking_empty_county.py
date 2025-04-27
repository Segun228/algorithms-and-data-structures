def was_parking_empty(cars, n):
    events = []
    occupied = 0
    car_counter = 0
    min_car_counter = 0
    car_id = 0
    current_state = set()
    for car in cars:
        time_in, time_out, place_from, place_to = car
        events.append((time_out, -1, place_to-place_from+1, car_id))
        events.append((time_in, 1, place_to-place_from+1, car_id))
        car_id+=1
    events.sort()
    for event in events:
        if(event[1]==1):
            occupied+=event[2]
            current_state.add(event[3])
            car_counter+=1
        elif(event[1]==-1 and (event[3] in current_state)):
            occupied-=event[2]
            car_counter-=1
            current_state.pop(event[3])
        if(occupied == n):
            min_car_counter = min(car_counter, min_car_counter)
    min_car_counter = 0

    for event in events:
        if(event[1]==1):
            occupied+=event[2]
            current_state.add(event[3])
            car_counter+=1
        elif(event[1]==-1 and (event[3] in current_state)):
            occupied-=event[2]
            car_counter-=1
            current_state.pop(event[3])
        if(occupied == n):
            min_car_counter = min(car_counter, min_car_counter)

    return min_car_counter