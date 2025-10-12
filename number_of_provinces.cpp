//Ref:https://leetcode.com/problems/number-of-provinces/description/

#include <map>
#include <queue>
#include <vector>
#include <string>
#include <set>

using namespace std;


class UnionFind{
private:
 vector<int> parent, rank;
 int count;

public:
 UnionFind(int size)
 {
    parent.resize(size);
    rank.resize(size);
    count = size;
    for(int ii = 0; ii < size; ++ii)
    {
        parent[ii] = ii; //everyone is their own parent to start
    }
 }

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y)
{
    int xSet = find(x);
    int ySet = find(y);
    if (rank[xSet] < rank[ySet])
    {
        parent[xSet] = ySet; //Put X in Y set
    }
    else if (rank[xSet] > rank[ySet])
    {
        parent[ySet] = xSet; //Put Y in X set
    }
    else
    {
        parent[ySet] = xSet;
        rank[xSet]++;
    }
}
};

int findCircleNum_union_find(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    UnionFind uf(n);
    int numberOfComponents = n; //All cities are their own component at the start

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (isConnected[i][j] && uf.find(i) != uf.find(j))
            {
                //Since the two cities are connected- make them connected if they aren't already
                numberOfComponents--;
                uf.union_set(i, j);
            }
        }
    }        
}

int main()
{
   
    return 0;
}
