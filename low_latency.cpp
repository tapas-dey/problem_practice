
#include<iostream>

using namespace std;


//Regular gcd implementation
// int gcd(int a, int b)
// {
//     if (b == 0)
//     {
//         return a;
//     }
//     return gcd(b, a % b);
// }

//template implementation of gcd
template <int a, int b>
struct gcd{
    inline static constexpr int value = gcd<b, a%b> :: value;
};

template <int a>
struct gcd<a, 0>{
    inline static constexpr int value = a;
};

int main()
{
    //Regular gcd implementation
    //cout << "gcd(10, 15): " << gcd(10, 15) << endl;
    //cout << "gcd(15, 5): " << gcd(15, 5) << endl;
    
    //template implementation of gcd
    cout << "gcd(10, 15): " << gcd<10, 15>::value << endl;
    cout << "gcd(15, 5): " << gcd<15, 5>::value << endl;
}
