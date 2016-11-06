int dataRoute(int resource, int server, std::vector<std::vector<int>> network) {
    int flow = 0;
    std::vector<std::vector<int>> tempNet = network;
    std::vector<int> paths(tempNet.size());
    
    // Use Edmonds-Karp Algorithm 
    while (bfs(tempNet, resource, server, paths)){

        int path_flow;
        
        // max load through the path
        for (int i = server; i!= resource; i=paths[i])
            path_flow = min(path_flow, tempNet[paths[i]][i]);
        
        //update the load
        for (int i = server; i!= resource; i=paths[i])
        {
            tempNet[paths[i]][i] -= path_flow;
            tempNet[i][paths[i]] += path_flow;
        }
        
        // add the flow
        flow += path_flow;
        
    }
    
    return flow;
}


bool bfs( std::vector<std::vector<int>> tempNet, 
             int source, int destination, std::vector<int> &paths)
{
    std::vector<bool> visited(tempNet.size());
    std::queue <int> q;
    q.push(source);
    visited[source] = true;
    paths[source] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int i = q.front();
        q.pop();
 
        for (int j=0; j<tempNet.size(); j++)
        {
            if (visited[j]==false && tempNet[i][j] > 0)
            {
                q.push(j);
                paths[j] = i;
                visited[j] = true;
            }
        }
    }
 
    return (visited[destination] == true);
}
