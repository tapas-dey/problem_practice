#include <vector>
using namespace std;

int gas_station_journey(vector<int>&gas, vector<int>&cost)
{
    int sumCost = 0, sumGas = 0;
    //Make sure we've enough gas to go through all the stations
    for (auto i = 0; i < gas.size(); ++i)
    {
        sumCost += cost[i];
        sumGas += gas[i];
    }
    //If we're spending more gas then we ca get
    //we can't make the whole trip 
    if (sumCost > sumGas) 
        return -1;             

    int current_gas = 0, starting_index = 0;

    for (auto i = 0; i < gas.size(); ++i)
    {
        current_gas = current_gas + (gas[i] - cost[i]);
        if (current_gas < 0){
            current_gas = 0;
            starting_index = i + 1;
        }
    }  
    return starting_index;
}
   
    

int main() {

    //Find the index of the gas station in the integer array gas 
    //such that if we start from that index we may return to the same index 
    //by traversing through all the elements, 
    //collecting gas[i] and consuming cost[i].
    vector<int> gas = {1, 1, 1, 1, 10};
    vector<int> cost = {2, 2, 1, 3, 1};

    int return_index = gas_station_journey(gas, cost);
    if (return_index != -1 )
    {
        cout << "We can start from station with index: " << return_index << endl;
    }
    else
    {
        cout <<"Can't complete the trip" << endl;
    }
    
    return 0;
}