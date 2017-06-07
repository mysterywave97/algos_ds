#include<bits/stdc++.h>
using namespace std;
#define V 256
int n;
/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int residual_graph[V][V],int src,int sink,int parent[]){
	bool visited[V];
	memset(visited,0,sizeof(visited));
	queue <int> q;
    q.push(src);
    visited[src] = true;
    parent[src] = -1;
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && residual_graph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[sink] == true);
}
int ford_fulkerson(int graph[V][V],int src,int sink){
	// Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
	int residual_graph[V][V];
	// Residual graph where rGraph[i][j] indicates 
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not) 
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		residual_graph[i][j]=graph[i][j];
	int parent[V]; // This array is filled by BFS and to store path
	int max_flow=0;
	// Augment the flow while tere is path from source to sink
	while(bfs(residual_graph,src,sink,parent)){
		// Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
		int path_flow=INT_MAX;
		for(int j=sink;j!=src;j=parent[j]){
			int i=parent[j];
			path_flow=min(path_flow,residual_graph[i][j]);
		}
		// update residual capacities of the edges and reverse edges
        // along the path
		for(int j=sink;j!=src;j=parent[j]){
			int i=parent[j];
			residual_graph[i][j]-=path_flow;
			residual_graph[j][i]+=path_flow;
		}
		// Add path flow to overall flow
		max_flow+=path_flow;
	}
	return max_flow;
}
main(){
	n=6;
	
	 int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
	cout<<ford_fulkerson(graph,0,5);
}
