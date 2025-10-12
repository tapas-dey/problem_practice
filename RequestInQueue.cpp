#include <vector>
#include <map>
#include <queue>
#include <set>


using namespace std;

vector<int> findNumberOfRequestsInQ(vector<int>& wait)
{
    vector<int> numOfRequests;
    
    queue<int> serveIndex;
    int curServIndex = 0;
    std::set<int> removedIdx;
    int numOfRequestsLeft = wait.size();
    for (int time = 0; ; time++)
    {
        if (!serveIndex.empty())
        {
            numOfRequestsLeft--;
            curServIndex = serveIndex.front() + 1;
            // while (curServIndex < wait.size() - 1 && wait[curServIndex]<= time)
            // {
            //     numOfRequestsLeft--;
            //     curServIndex++;
            // }
            serveIndex.pop();
            serveIndex.push(curServIndex);
        }
        else
        {
            serveIndex.push(0);
        }
        for (int waitQIndx = curServIndex + 1 ; waitQIndx < wait.size(); ++waitQIndx)
        {   
            if (wait[waitQIndx] <= time && removedIdx.find(waitQIndx) == removedIdx.end())
            {
                removedIdx.insert(waitQIndx);
                numOfRequestsLeft = numOfRequestsLeft - 1;
            }
            
        }
        numOfRequests.push_back(numOfRequestsLeft);

        if (numOfRequestsLeft == 0)
            break;
        
    }

    return numOfRequests;
}
int main()
{
    vector<int> queue {2,2,3,1};
    vector<int> numOfRequests = findNumberOfRequestsInQ(queue);
}