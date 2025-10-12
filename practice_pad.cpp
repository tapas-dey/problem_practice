#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <semaphore.h>
#include <set>
using namespace std;

class A{
    public:
    A(){cout << "constructor A" << endl; }
};
class B : public A{
    public:
    B() {cout << "constructor B" << endl;}
};

int main()
{
    A* a = new B;
    delete a;
    return 0;
}