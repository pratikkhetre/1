#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int nodes;
const int max_node=20000;
int adj_mat[max_node][max_node];
int visited_s[max_node]; // for seq DFS
int visited_p[max_node]; // for parallel DFS


void s_DFS(int i) // function for DFS traversal
{

    
    visited_s[i] = 1; // marking current node as visited
    for (int j = 0; j < nodes; j++)
    {
        if (adj_mat[i][j] == 1 && !visited_s[j])
        {
            s_DFS(j); // recurrsive call for unvisited nodes
        }
    }
}
void p_DFS(int i) // function for DFS traversal
{
    visited_p[i] = 1; // marking current node as visited
    #pragma omp parallel for
    for (int j = 0; j < nodes; j++)
    {
        if (adj_mat[i][j] == 1 && !visited_p[j])
        {
            p_DFS(j); // recurrsive call for unvisited nodes
        }
    }
}

int main()
{
    cout << "Enter the number of nodes: "; // taking user input for nodes
    cin >> nodes;


    for (int i = 0; i < (nodes); i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            if (i != j) {
                adj_mat[i][j] = 1; // Set edge between node i and node j
            } else {
                adj_mat[i][j] = 0; // No self-loops
            }
        }
    }

 auto start = high_resolution_clock::now();
    s_DFS(0);
    auto stop = high_resolution_clock::now();
    auto result = stop - start;
    auto duration = duration_cast<microseconds>(result);
    cout<<"\nTime taken by sequential DFS: "<<duration.count()<<" nanoseconds";


    auto start2 = high_resolution_clock::now();
    #pragma omp parallel num_threads(4)
    {
        p_DFS(0);
    }
    auto stop2 = high_resolution_clock::now();
    auto result2 = stop2 - start2;
    auto duration2 = duration_cast<microseconds>(result2);
    cout<<"\nTime taken by parallel DFS: "<<duration2.count()<<" nanoseconds";

return 0;
}