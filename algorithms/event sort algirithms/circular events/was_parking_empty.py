def was_parking_empty(cars, n):
    events = []
    occupied = 0
    for car in cars:
        time_in, time_out, place_from, place_to = car
        events.append((time_out, -1, place_to-place_from+1))
        events.append((time_in, 1, place_to-place_from+1))
    events.sort()
    for event in events:
        if(event[1]==1):
            occupied+=event[2]
        else:
            occupied-=event[2]
        if(occupied == n):
            return True
    return False