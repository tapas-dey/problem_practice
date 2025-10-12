#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    string str("493929");
    reverse(str.begin(), str.end());
    string result;
    for (int ii = 0; ii < str.length(); ii += 2){
        result += static_cast<char>((stoi(str.substr(ii, 2)) - 92 + 'A'));        
    }
    cout << result.c_str() << endl;
    return 0;
}