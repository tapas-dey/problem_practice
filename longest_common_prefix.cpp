#include <iostream>
#include <vector>

using namespace std;

string longestCommonPrefix_Naive(const vector<string>& stringArr)
{
    if (stringArr.size() == 0)
    {
        return "";
    }
    //start with the full length string of the first item in the stringArr
    string prefix = stringArr[0];
    for (int ii = 1; ii < stringArr.size(); ++ii)
    {
        //If we find the prefix "find" will return 0 since we're looking for prefix
        //ex: if we look for "fl" in "flight" it'll return 0 but -1 if we look for "flo"
        //So keep trying until we find something.
        while(stringArr[ii].find(prefix) != 0)
        {
            //reduce prefix size by 1 char if we can't find
            prefix = prefix.substr(0, prefix.length() - 1);
        }
        // we can immediately return here since we didn't find anything common for string at i
        if (prefix.empty()){ return "";} 
    }
    return prefix;
}

int main()
{
    //Given a set of string find the longest common prefix among them
    vector<string> stringArr {"flower","flow","flight"};
    cout << "Longest Common Prefix using naive: " << longestCommonPrefix_Naive(stringArr) << endl;
    return 0;
}