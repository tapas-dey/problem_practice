#include <vector>
#include <limits>

using namespace std;

double buySellTwice(const vector<double> prices){
    double min_price = std::numeric_limits<double>::max();
    double max_profit = std::numeric_limits<double>::min();
    vector<double> forward_pass;(prices.size(), 0.0);
    for (int ii = 0; ii < prices.size(); ++ii){
        min_price = min(min_price, prices[ii]);
        max_profit = max(max_profit, prices[ii] - min_price);
        forward_pass[ii] = max_profit;
    }
    double max_price = std::numeric_limits<double>::min();
    for (int ii = prices.size() - 1; ii >= 0; --ii){
        max_price = max(max_price, prices[ii]);
        max_profit = max(max_profit, max_price - prices[ii] + forward_pass[ii - 1]);
    }
    return max_profit;
}
int main(){
    return 0;
}