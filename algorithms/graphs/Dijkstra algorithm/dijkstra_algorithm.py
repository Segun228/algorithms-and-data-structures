from math import inf
import heapq

def graph_input():  #словарь смежности вида:     вершина : [(сосед 1, длина до соседа 1), (сосед 2, длина до соседа 2) ...]
    adjacency_list = {}
    print("Enter the number of vertices")
    v = int(input())
    print("Enter the number of edges")
    e = int(input())
    print("Enter the edges in format: edge_1 edge_2 edge_weight")
    print("The numeration starts from 0")
    for _ in range(e):
        edge1, edge2, weight = map(int, input().split())
        if edge1 not in adjacency_list:
            adjacency_list[edge1] = []
        if edge2 not in adjacency_list:
            adjacency_list[edge2] = []
        adjacency_list[edge1].append([edge2, weight])
        adjacency_list[edge2].append([edge1, weight])
    return adjacency_list

def dijkstra(graph, start, end):
    if start == end:
        return 0
    shortest_distances = {vertex:inf for vertex in graph}
    shortest_distances[start]=0
    previous_visited = {vertex:None for vertex in graph}
    min_heap_queue = [[0, start]]
    while(min_heap_queue):
        current_way_length, current_vertex = heapq.heappop(min_heap_queue)
        if current_vertex==end:
            break
        if current_way_length > shortest_distances[current_vertex]:
            continue
        for neighbor in graph[current_vertex]:
            if shortest_distances[neighbor[0]] > shortest_distances[current_vertex] + neighbor[1]:
                shortest_distances[neighbor[0]] = shortest_distances[current_vertex] + neighbor[1]
                previous_visited[neighbor[0]] = current_vertex
            if previous_visited[neighbor]!=None:
                heapq.heappush(min_heap_queue, [shortest_distances[neighbor[0]], neighbor[0]])
    #а теперь все это дело нужно восстановить
    current_vertex = end
    min_sum_way = shortest_distances[end]
    final_way = []
    while(current_vertex!=None):
        final_way.append(current_vertex)
        current_vertex = previous_visited[current_vertex]
    final_way.reverse()
    return min_sum_way, final_way

def main():
    my_graph = graph_input()
    print("Enter the start vertex")
    start = int(input())
    print("Enter the end vertex")
    end = int(input())
    min_way, way = dijkstra(my_graph, start, end)
    print(f"minimum way is {min_way}")
    print(f"Path: {' -> '.join(map(str, way))}")

if __name__ == "__main__":
    main()
