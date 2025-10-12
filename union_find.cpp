//Ref:https://leetcode.com/explore/learn/card/graph/618/disjoint-set/3879/

#include <map>
#include <queue>
#include <vector>
#include <string>
#include <set>

using namespace std;


class UnionFind{
public:
    UnionFind(int size)
    : root(size)
    , rank(size)
    {
        for (int i = 0; i < size; ++i)
        {
            root[i] = i;
            rank[i] = 1;
        }
    }
    
    int find(int x)
    {
        while (x != root[x])
        {
            x = root[x];
        }
        return x;
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                root[rootY] = rootX;
            }
            else if(rank[rootX] < rank[rootY])
            {
                root[rootX] = rootY;
            }
            else
            {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }
    
    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

private:
    vector<int> root;
    vector<int> rank;
};

int main()
{
    auto uf = UnionFind(6);
    uf.unionSet(0, 1);
    uf.unionSet(0, 2);
    uf.unionSet(0, 3);
    uf.unionSet(0, 4);
    uf.unionSet(4, 5);
    return 0;
}

