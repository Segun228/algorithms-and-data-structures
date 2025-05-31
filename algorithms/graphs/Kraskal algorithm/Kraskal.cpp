#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E; // V - количество вершин, E - количество ребер
    vector<Edge> edges;
    
    Graph(int v, int e) : V(v), E(e) {}
};

// Система непересекающихся множеств (DSU)
struct DSU {
    vector<int> parent, rank; //rank - высота дерева, нужно для балансировки (оптимизация поиска и unite)
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; 
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Объединяем два множества
    void unite(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);
        
        if (xroot == yroot) return;
        
        // Присоединяем меньшее дерево к большему
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}


void Kruskal(Graph &graph) {
    int V = graph.V;
    vector<Edge> result(V - 1);
    
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);
    
    DSU dsu(V);
    
    int e = 0; 
    int i = 0; 
    
    while (e < V - 1 && i < graph.E) {
        Edge next_edge = graph.edges[i++];
        
        int x = dsu.find(next_edge.src);
        int y = dsu.find(next_edge.dest);
        
        //Проверка на цикл
        if (x != y) {
            result[e++] = next_edge;
            dsu.unite(x, y);
        }
    }
    
    cout << "Ребра минимального остовного дерева:\n";
    for (i = 0; i < e; i++) {
        cout << result[i].src << " -- " << result[i].dest 
             << " (вес: " << result[i].weight << ")\n";
    }
}

int main() {
    int V = 10; // Количество вершин
    int E = 21 ; // Количество ребер
    Graph graph(V, E);
    
    // Добавляем ребра
    graph.edges = {
        {0, 1, 3}, // src, dest, weight
        {0, 2, 6},
        {0, 3, 9},
        {1, 2, 4},
        {1, 3, 9},
        {1, 5, 2},
        {1, 4, 9},
        {2, 5, 2},
        {2, 6, 9},
        {3, 4, 8},
        {3, 9, 18},
        {4, 5, 8},
        {4, 6, 7},
        {4, 8, 9},
        {4, 9, 10},
        {5, 6, 9},
        {6, 7, 4},
        {6, 8, 5},
        {7, 9, 4},
        {7,8,1},
        {8,9,3}
    };
    
    Kruskal(graph);
    
    return 0;
}