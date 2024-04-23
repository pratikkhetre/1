#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include<string>
#include <omp.h>
#include<chrono>


using namespace std;
  // Graph class representing an undirected graph using adjacency list representation
class Graph {
private:
    int numVertices;          // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int vertices) : numVertices(vertices), adj(vertices) {}

    // Add an edge between two vertices
    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }
    

    // View the graph
    void viewGraph() {
        cout << "Graph:\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }


    void s_bfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        // Mark the start vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            // Enqueue all adjacent unvisited vertices
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }


    // Perform Breadth First Search (BFS) in parallel
    void p_bfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        // Mark the start vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            // Enqueue all adjacent unvisited vertices
            #pragma omp parallel for
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }


    void s_dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Mark the start vertex as visited and push it onto the stack
        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            // Push all adjacent unvisited vertices onto the stack
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }


    // Perform Depth First Search (DFS) in parallel
    void p_dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Mark the start vertex as visited and push it onto the stack
        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            // Push all adjacent unvisited vertices onto the stack
            #pragma omp parallel for
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Create a graph with the specified number of vertices
    Graph graph(numVertices);

    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    // View the graph
    graph.viewGraph();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    cout << "Sequential Breadth First Search (BFS): ";
	auto start = chrono::high_resolution_clock::now();
	graph.s_bfs(startVertex);
	auto stop = chrono::high_resolution_clock::now();
	auto result = stop - start;
	auto duration = chrono::duration_cast<chrono::microseconds>(result);
	string time1 =  to_string(duration.count());
    cout << "\nSequential BFS Traversal " << time1 << " microseconds\n";
    cout << endl;


    cout << "Parallel Breadth First Search (BFS): ";
	auto start1 = chrono::high_resolution_clock::now();
	graph.p_bfs(startVertex);
	auto stop1 = chrono::high_resolution_clock::now();
	auto result1 = stop1 - start1;
	auto duration1 = chrono::duration_cast<chrono::microseconds>(result1);
	string time2 =  to_string(duration1.count());
    cout << "\nParallel BFS Traversal " << time2 << " microseconds\n";
    cout << endl;
    
    cout << "Sequential Breadth First Search (BFS): ";
	auto start2 = chrono::high_resolution_clock::now();
	graph.s_dfs(startVertex);
	auto stop2 = chrono::high_resolution_clock::now();
	auto result2 = stop2 - start2;
	auto duration2 = chrono::duration_cast<chrono::microseconds>(result);
	string time3 =  to_string(duration2.count());
    cout << "\nSequential DFS Traversal " << time3 << " microseconds\n";
    cout << endl;
    
    
    cout << "Parallel Breadth First Search (BFS): ";
	auto start3 = chrono::high_resolution_clock::now();
	graph.p_dfs(startVertex);
	auto stop3 = chrono::high_resolution_clock::now();
	auto result3 = stop3 - start3;
	auto duration3 = chrono::duration_cast<chrono::microseconds>(result3);
	string time4 =  to_string(duration3.count());
    cout << "\nParallel DFS Traversal " << time4 << " microseconds\n";
    cout << endl;

    

    return 0;
}
