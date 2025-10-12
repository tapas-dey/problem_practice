#include <iostream>
#include <vector>
#include <math.h>
#include <map>

using namespace std;

static const int kStartingCurrencyIndex = 0;//Assume the first index is where we start

void FindPathOfArbitrage(const vector<vector<double>> conversion_table, 
                         vector<int>& path)
{
    //Keep track of the logarithmic conversion sum from the starting currency
    vector<double> log_conversion_sum(conversion_table.size(), numeric_limits<double>::max());
    map<int, int> chain;
    //Conversion sum within the currency- set to zero
    log_conversion_sum[kStartingCurrencyIndex] = 0;
    //Bellman Ford tries all the vertices to find the minimal conversion sum
    for (auto times = 1; times < conversion_table.size(); ++times)
    {
        bool updated = false;
        for(auto ii = 0; ii < conversion_table.size(); ++ii)
        {
            for (auto jj = 0; jj < conversion_table[ii].size(); ++jj)
            {
                double new_path_sum = log_conversion_sum[ii] + conversion_table[ii][jj];
                if (log_conversion_sum[ii] != numeric_limits<double>::max() &&
                    log_conversion_sum[jj] > new_path_sum)
                {
                    updated = true;
                    log_conversion_sum[jj] = new_path_sum; 
                    chain[jj] = ii; 
                }
            }
        }
        //We should be able to find minimal conversion sum for a negative cycle
        //Otherwise we don't have one
        if (!updated)
        {
            return;
        }
    }
    int cycle_vertex= -1;
    //To detect negative cycle do one more round and see still we're updating values
    for(auto ii = 0; ii < conversion_table.size(); ++ii)
    {
        for (auto jj = 0; jj < conversion_table[ii].size(); ++jj)
        {
            double new_path_sum = log_conversion_sum[ii] + conversion_table[ii][jj];
            if (log_conversion_sum[ii] != numeric_limits<float>::max() &&
                log_conversion_sum[jj] > new_path_sum)
            {
                cycle_vertex = jj;
                chain[jj] = ii;
                break;  
            }
        }
    }
    if (cycle_vertex == -1)
    {
        return;
    }

    //Get the parent/root of the cycle_vertex
    for (int i = 0; i < conversion_table.size(); ++i)
    {
        cycle_vertex = chain[cycle_vertex];
    }
    //Move within the cycle to trace the path
    int cur = cycle_vertex;
    while(1)
    {
        path.push_back(cur);
        cur = chain[cur];
        if (cur == cycle_vertex && path.size() > 1)
        {
            //We came back to the cycle_vertex that we started on
            break;
        }
    }
}

int main() {
    //Ref: https://www.ijisrt.com/assets/upload/files/IJISRT20MAY047.pdf
    //currency names for the paper exchange rates table
    vector<string> nameOfCurrencies = {"USD", "EUR", "CHF", "GBP", "JPY"};
    //Currency names for the Bloomberg data table
    //vector<string> nameOfCurrencies = {"USD", "EUR", "CAD", "GBP", "CHF"};

    vector<vector<double>> conversion_table;
    //-----------------------------------------------------
    //currency exchange rates from the paper
    conversion_table.push_back(vector<double> {1.0, 0.908, 0.9598,0.8099, 108.28});
    conversion_table.push_back(vector<double> {1.1012, 1.0, 1.0586,0.892, 119.89});
    conversion_table.push_back(vector<double> {1.0392, 0.9444, 1.0,0.8422, 112.59});
    conversion_table.push_back(vector<double> {1.2335, 1.1205, 1.1866,1.0, 133.67});
    conversion_table.push_back(vector<double> {0.0092, 0.0083, 0.0088,0.0074, 1.0});
    //-----------------------------------------------------
    //currency exchange rates from the Bloomberg
    // conversion_table.push_back(vector<double> {1.0, 1.1717, 1.3830,1.3509, 1.2531});
    // conversion_table.push_back(vector<double> {0.8535, 1.0, 1.6205,1.0695, 0.6171});
    // conversion_table.push_back(vector<double> {0.7231, 0.6164, 1.0,1.8683, 1.7331});
    // conversion_table.push_back(vector<double> {0.7402, 0.8673, 0.5352,1.0, 0.9276});
    // conversion_table.push_back(vector<double> {0.7980, 0.9350, 0.5232,1.0780, 1.0});
    //-----------------------------------------------------

    //Convert all the currency rates to logarithmic value
    for (auto& rowData : conversion_table)
    {
        for (auto& exchange_rate : rowData)
        {
            //Any log base is fine
            exchange_rate = -log10(exchange_rate);
        }
    }
    vector<int> arbitragePath;
    //Run Bellman Ford to detect a negative cycle and the path of that cycle
    FindPathOfArbitrage(conversion_table, arbitragePath); 

    if (!arbitragePath.empty())
    {
        cout << "Arbitrage exists: ";
        //Start iterating in reverse direction to print out the path from the starting currency
        for (auto itr = arbitragePath.rbegin(); itr != arbitragePath.rend(); ++itr)
        {
            cout << nameOfCurrencies[*itr];
            if (itr + 1 != arbitragePath.rend())
            {
                //append arrow after currency name
                cout << " --> ";
            }
        }
    }
    else 
    {
        cout << "Arbitrage doesn't exists." << endl;
    }
}
