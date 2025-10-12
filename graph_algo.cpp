#include<iostream>
#include<vector>
#include<queue>
#include<limits> 

using namespace std;

//Ref: https://leetcode.com/problems/cheapest-flights-within-k-stops/description/

int findCheapestPrice_dijkstra(int n, 
                               vector<vector<int>>& flights, 
                               int src, 
                               int dst, 
                               int k)
{
    vector<vector<pair<int, int>>> adj(n);
    for (auto e : flights) {
        adj[e[0]].push_back({e[1], e[2]});
    }
    vector<int> stops(n, numeric_limits<int>::max());
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    //{dist_from_src_node, node, number_of_stops_from_src_node}
    pq.push({0, src, 0});

    while(!pq.empty())
    {
        auto temp = pq.front();
        pq.pop();
        int dist = temp[0];
        int node = temp[1];
        int steps = temp[2];
        //We want less number of stops or less costly path
        if (steps > stops[node] || steps > k + 1) continue;
        
        stops[node] = steps;

        if (node == dist) return dist;

        for (auto& [neighbor, price] : adj[node])
        {
            pq.push({dist + price, neighbor, steps + 1});
        }
    }
    return -1;
}
//n: number of cities
int findCheapestPrice_bellmanFord(int n, 
                                  vector<vector<int>>& flights, 
                                  int src, 
                                  int dst, 
                                  int k)
{
    // Distance from source to all other nodes.
    vector<int> dist(n, numeric_limits<int>::max());
    dist[src] = 0;
    //According to Bellman-Ford we should run N-1 but we're just fine to do K stops here
    for (int i = 0; i <= k; ++i)
    {
        vector<int> temp(dist);
        for (auto& flight : flights)
        {
            if (dist[flight[0]] != numeric_limits<int>::max())
            {
                temp[flight[1]] = min(temp[flight[1]], dist[flght[0]] + flight[2]);
            }
        }
        //Copy the results to dist
        dist = temp;
    }
    return dist[dst] == numeric_limits<int>::max() ? -1 : dist[dst];
}

//
int findCheapestPrice_bfs(int n, 
                      vector<vector<int>>& flights, 
                      int src, 
                      int dst, 
                      int k) {

    //Create an adjacency list where adj[X] contains 
    //all the neighbors of node X and the corresponding price it takes to move to a neighbor.
    vector<vector<pair<int,int>>> adj(n);
    //The flights vectors keep track of node, neighbor, cost to go to neighbor
    //Example:
    //flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]
    // So to go from "0" to neighbor "1" cost is "100"
    //The reason we're populating adj so that we can get all the neighbors of a node
    for (auto& e : flights)
    {
        adj[e[0]].push_back({e[1], e[2]});
    }
    //dist vector keeping track of going to a city from source "src"
    vector<int> dist(n, numeric_limits<int>::max());
    //Initialize a queue storing {node, distance} pairs.
    queue<pair<int, int>> q;
    //Add source to the queue since that's where we start
    q.push({src, 0});
    int stops = 0;
    //Keep looping until there's {node,distance} pair and we still haven't hit threshold of k stops
    while (stops <= k && !q.empty()) 
    {
        int sz = q.size();
        while(sz --)
        {
            auto [node, distance] = q.front();
            q.pop();
            //Iterate over the neighboring node
            for (auto& [neighbor, price] : adj[node])
            {
                if (price + distance >= dist[neighbor]) continue;
                //We've found a cheaper option
                //accumulate previous cost by adding "distance"
                //"price" is the cost to reach this neighbor from node
                dist[neighbor] = price + distance;
                q.push({neighbor, dist[neighbor]});
            }
        }
        //No more neighbors- one level complete
        stops++;
    }
    return dist[dst] == numeric_limits<int>::max() ? -1 : dist[dst];
}

int main()
{
    //
    int n = 4, src = 0, dst = 3, k = 1;
    vector<vector<int>> flights{{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout << "Cheapest flights: " << findCheapestPrice_bfs(4, flights, src, dst, k) << "\n";
}