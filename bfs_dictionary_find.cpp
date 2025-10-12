//Ref:Elements of Programming interviews: Problem: 18.7(Page:355)
//Transform one string to another

#include <map>
#include <queue>
#include <vector>
#include <string>
#include <set>

using namespace std;

int TransfromString(unordered_set<string> D, const string& s, const string& t)
{
    struct stringWithDistance{
        string candidate_string;
        int distance;
    };
    queue<stringWithDistance> q;
    D.erase(s);
    q.emplace(stringWithDistance{q, 0});

    while(!q.empty())
    {
        stringWithDistance f(q.front());
        if (f.candidate_string == t)
        {
            return f.distance;
        }
        string str = f.candidate_string;
        for (int i = 0; i < str.size(); ++i)
        {
            for (int c = 0; c < 26; ++c)
            {
                //Try a different character and see if that exists in the dictionary
                str[i] = 'a' + c;
                auto it (D.find(str));
                if (it != D.end())
                {
                    D.erase(it);
                    q.emplace(stringWithDistance{str, f.distance + 1});
                }
            }
            //Revert back the change of the string
            str[i] = f.candidate_string[i];
        }
        q.pop();
    }
}

int main()
{
    
    return 0;
}