//Ref:https://www.interviewcake.com/concept/java/topological-sort#:~:text=The%20topological%20sort%20algorithm%20takes,before%20them%20in%20the%20ordering.

#include <map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

vector<string> topologicalSort(const map<string, vector<string>>& graph)
{
    std::vector<string> results;
    //Find indegrees for each node in the graph
    map<string, int> nodeIndegrees;
    for (auto& each : graph)
    {
        //Find the node in the indegrees map
        auto mapItr = nodeIndegrees.find(each.first);
        if (mapItr == nodeIndegrees.end())
        {
            nodeIndegrees.insert(pair<string, int>(each.first, 0));
        }
        for (auto& neighbor : each.second)
        {
            if (graph.find(neighbor) != graph.end())
            {
                nodeIndegrees[neighbor]++;
            }     
        }
    }
    queue<string> nodesWithNoIncomingEdges;
    for (auto& entry : nodeIndegrees)
    {
        if (entry.second == 0)
            nodesWithNoIncomingEdges.push(entry.first);
    }
    //Now go over the queue
    while (!nodesWithNoIncomingEdges.empty())
    {
        auto node = nodesWithNoIncomingEdges.front();
        nodesWithNoIncomingEdges.pop();
        results.push_back(node);
        for (const auto& neighbor : graph.at(node))
        {
            auto mapItr = nodeIndegrees.find(neighbor);
            if (mapItr != nodeIndegrees.end())
            {
                (*mapItr).second--;
                if ((*mapItr).second == 0)
                {
                    nodesWithNoIncomingEdges.push((*mapItr).first);
                }
            }
            
        }
    }
    return results;
}

int main()
{
    map<string, vector<string>> graph;
    graph["B"] = vector<string>{"E", "C"};
    graph["E"] = vector<string>{"C", "A"};
    graph["C"] = vector<string>{"D"};
    graph["A"] = vector<string>{"C", "D"};
    graph["D"] = vector<string>{""};
    topologicalSort(graph);
    return 0;
}