#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int dest;
    int weight;
};

// Структура для представления графа
class Graph {
    int V; // Количество вершин
    vector<vector<Edge>> adj; // Список смежности

public:
    Graph(int v) : V(v), adj(v) {}

    // Добавление ребра в граф
    void addEdge(int src, int dest, int weight) {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight}); // Для неориентированного графа
    }

    // Алгоритм Прима для нахождения MST
    void primMST() {
        // Приоритетная очередь для выбора ребра с минимальным весом
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int src = 0; // Начинаем с вершины 0 (можно выбрать любую)

        // Вектор для хранения ключей (минимальных весов)
        vector<int> key(V, INT_MAX);

        // Вектор для хранения родительских вершин в MST
        vector<int> parent(V, -1);

        // Вектор для отметки включения вершины в MST
        vector<bool> inMST(V, false);

        // Добавляем начальную вершину в очередь
        pq.push({0, src});
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true; // Включаем вершину в MST

            // Обходим все смежные вершины
            for (const Edge& edge : adj[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                // Если вершина v еще не в MST и вес ребра меньше текущего ключа
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }

        // Выводим ребра MST
        cout << "Ребра минимального остовного дерева (алгоритм Прима):\n";
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " -- " << i << " (вес: " << key[i] << ")\n";
        }
    }
};

int main() {
    // Создаем граф из примера (как в алгоритме Краскала)
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.primMST();

    return 0;
}