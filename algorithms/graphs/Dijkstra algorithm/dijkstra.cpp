#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);    // Кратчайшие расстояния
    vector<bool> visited(n, false);  // Посещенные вершины
    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        // Находим вершину с минимальным расстоянием среди непосещенных
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        // Если все вершины посещены или оставшиеся недостижимы
        if (u == -1 || dist[u] == INT_MAX) {
            break;
        }

        visited[u] = true;

        // Обновляем расстояния до соседей
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

int main() {
    // Пример графа в виде списка смежности
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 1}},  // Вершина 0 соединена с 1 (вес 4) и 2 (вес 1)
        {{3, 1}},           // Вершина 1 соединена с 3 (вес 1)
        {{1, 2}, {3, 5}},   // Вершина 2 соединена с 1 (вес 2) и 3 (вес 5)
        {{4, 3}},           // Вершина 3 соединена с 4 (вес 3)
        {}                  // Вершина 4 не имеет исходящих ребер
    };

    int start_vertex = 0;
    vector<int> distances = dijkstra(graph, start_vertex);

    cout << "Кратчайшие расстояния от вершины " << start_vertex << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "До вершины " << i << ": ";
        if (distances[i] == INT_MAX) {
            cout << "недостижима";
        } else {
            cout << distances[i];
        }
        cout << endl;
    }

    return 0;
}