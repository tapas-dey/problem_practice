
#include <map>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;


int main()
{
    unordered_map<string, set<string>> myMap;
    //set<string> mySet{"stockTwo"};
    myMap.insert(make_pair("stockOne", set<string>{"stockTwo"}));
    myMap["stockOne"].insert("stockThree");

    auto mapItr = myMap.find("stockOne");
    auto& pairSet = mapItr->second;
    for (auto& pair : mapItr->second)
    {
      cout << pair << endl;
    }
    return 0;
}