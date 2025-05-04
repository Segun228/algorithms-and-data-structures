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
        adjacency_list[edge1].append((edge2, weight))
        adjacency_list[edge2].append((edge1, weight))
    return adjacency_list

def dijkstra(graph, start, end):
    if start == end:
        return 0
    distances = {vertex: inf for vertex in graph} #словарь расстояний до вершин вида {вершина : кратчайшее расстояние до нее ...}
    distances[start] = 0
    previous = {vertex: None for vertex in graph}
    priority_queue = [(0, start)]
    while (priority_queue):
        current_distance, current_vertex = heapq.heappop(priority_queue)
        if current_vertex == end:
            break
        if current_distance > distances[current_vertex]:
            continue
        for neighbor, weight in graph[current_vertex]:
            distance = current_distance + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous[neighbor] = current_vertex
                heapq.heappush(priority_queue, (distance, neighbor))
    path = []
    current = end
    while current is not None:
        path.append(current)
        current = previous[current]
    path.reverse()
    return distances[end], path if distances[end] != inf else None

def main():
    start_edge = int(input("Enter start vertex: "))
    end_edge = int(input("Enter end vertex: "))
    my_graph = graph_input()
    result = dijkstra(my_graph, start_edge, end_edge)

    if result is None:
        print(f"No path exists from {start_edge} to {end_edge}")
    else:
        distance, path = result
        print(f"Shortest distance from {start_edge} to {end_edge}: {distance}")
        print(f"Path: {' -> '.join(map(str, path))}")

if __name__ == "__main__":
    main()
