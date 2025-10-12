//https://www.geeksforgeeks.org/find-all-pairs-possible-from-the-given-array/

#include <vector>

using namespace std;

void mergePairs(const vector<int>& numberArr, size_t left, size_t mid, size_t right, vector<pair<int,int>>& results)
{
    
    int i = left, k = left, j = mid +1;
    while (i <= mid && j <= right)
    {
        if (numberArr[i] > numberArr[j])
        {
            results.push_back(pair<int,int>(numberArr[i], numberArr[j]));
            results.push_back(pair<int,int>(numberArr[j], numberArr[i]));
            results.push_back(pair<int,int>(numberArr[j], numberArr[j]));
            j++;
        }
        else
        {
            results.push_back(pair<int,int>(numberArr[i], numberArr[j]));
            results.push_back(pair<int,int>(numberArr[j], numberArr[i]));
            results.push_back(pair<int,int>(numberArr[i], numberArr[i]));
            i++;
        }
    }
    while (i <= mid)
    {
        results.push_back(pair<int,int>(numberArr[i], numberArr[i]));
        ++i;
    }
    while (j <= right)
    {
        results.push_back(pair<int,int>(numberArr[j], numberArr[j]));
        ++j;
    }

}

void findAllPairs(const vector<int>& numberArr, size_t left, size_t right, vector<pair<int,int>>& results)
{
    if (left < right)
    {
        int mid = (left + right)/2;
        findAllPairs(numberArr, left, mid,results);
        findAllPairs(numberArr, mid+1, right, results);
        mergePairs(numberArr, left, mid, right, results);
    }
}
vector<pair<int,int>> findAllPairs(const vector<int>& numberArr)
{
    vector<pair<int,int>> results;

    return results;
 }

int main()
{
    vector<int> numberArr {1, 2};
    findAllPairs(numberArr);
}