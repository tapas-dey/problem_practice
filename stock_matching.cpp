#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <algorithm>
#include <forward_list>

using namespace std;

enum Operation {
    BUY,
    SELL,
    MODIFY,
    CANCEL,
    PRINT
};

string operationStr[] = {"BUY", "SELL", "MODIFY", "CANCEL", "PRINT"};

struct Order{
    Operation op;
    string orderType;
    int price;
    int quantity;  
    string orderId;
    Operation modifyOp;
};

struct OrderCompare {
    bool operator() (Order& a, Order& b) { return a.price < b.price; }
};

struct OrderCompareS {
    bool operator() (string& a, string& b) { return a.size() < b.size(); }
};

unordered_map<string, list<Order>::iterator> buyOrders;
unordered_map<string, list<Order>::iterator> sellOrders;

list<Order> buyOrderList;
list<Order> sellOrderList;

void addBuyOrders(Order& order){    
    if (buyOrders.find(order.orderId) == buyOrders.end()){
        auto itr = buyOrderList.begin();
        bool addedToList = false;
        for (; itr != buyOrderList.end(); ++itr){
            if (order.price > (*itr).price){
                buyOrders.insert(make_pair(order.orderId, buyOrderList.insert(itr, order)));
                addedToList = true;
                break;
            }
        }
        if (addedToList == false){
            buyOrderList.push_back(order);
            buyOrders.insert(make_pair(order.orderId, --buyOrderList.end()));
        } 
    }
    //See if there's a matching sell order
    auto sellItr = sellOrderList.rbegin();
    auto buyItr = buyOrderList.begin();
    while (buyItr != buyOrderList.end()){ 
        if (sellItr == sellOrderList.rend()){
            break;//Nothing to sell
        }       
        if (buyItr->price >= sellItr->price){
            //Trade
            bool isFullBuyOrder = true;
            bool isFullSellOrder = true;
            int buyQunatity = buyItr->quantity;
            int sellQuantity = sellItr->quantity;
  
            if (buyItr->quantity > sellItr->quantity)
            {
                buyQunatity = sellItr->quantity;
                buyItr->quantity = buyItr->quantity - sellItr->quantity;
                isFullBuyOrder = false;
            }
            else if (sellItr->quantity > buyItr->quantity)
            {
                sellQuantity = buyItr->quantity;
                sellItr->quantity = sellItr->quantity - buyItr->quantity;
                isFullSellOrder = false;
            }
            
            if (buyItr->orderType == "IOC"){
                isFullBuyOrder = true;
            }
            if (sellItr->orderType == "IOC"){
                isFullSellOrder = true;
            }
            //Print trade execution message  
            cout << "TRADE " 
            << buyItr->orderId 
            << " " << buyItr->price << " "<< buyQunatity <<" " 
            << sellItr->orderId 
            << " " << sellItr->price << " "<< sellQuantity << endl;
            //Now update the data
            auto buyMapItr = buyOrders.find(buyItr->orderId);                
            auto sellMapItr = sellOrders.find(sellItr->orderId);
            if (isFullBuyOrder)
            {
                buyOrders.erase(buyMapItr);
                buyOrderList.erase(buyItr);
                buyItr = buyOrderList.begin();
            }
            if (isFullSellOrder)
            {
                sellOrders.erase(sellMapItr);
                //sellOrderList.erase(sellItr);
                sellOrderList.pop_back(); 
                sellItr = sellOrderList.rbegin();
            }   
        }
        else {
            break;
        }
    }
}

void addSellOrders(Order& order){    
    if (sellOrders.find(order.orderId) == sellOrders.end()){
        auto itr = sellOrderList.begin();
        bool addedToList = false;
        for (; itr != sellOrderList.end(); ++itr){
            if (order.price < (*itr).price){
                sellOrders.insert(make_pair(order.orderId, sellOrderList.insert(itr, order)));
                addedToList = true;
                break;
            }
        }
        if (addedToList == false){
            sellOrderList.push_back(order);
            sellOrders.insert(make_pair(order.orderId, --sellOrderList.end()));
        } 
    }
    //See if there's a matching buy order
    auto buyItr = buyOrderList.begin();
    auto sellItr = sellOrderList.begin();            
    while (sellItr != sellOrderList.end()){
        if (buyItr == buyOrderList.end()){
            break;//Nothing to buy
        }
        if (buyItr->price >= sellItr->price){
            //Trade
            bool isFullBuyOrder = true;
            bool isFullSellOrder = true;
            int buyQunatity = buyItr->quantity;
            int sellQuantity = sellItr->quantity;
            if (buyItr->quantity > sellItr->quantity)
            {
                buyQunatity = sellItr->quantity;
                buyItr->quantity = buyItr->quantity - sellItr->quantity;
                isFullBuyOrder = false;
            }
            else if (sellItr->quantity > buyItr->quantity)
            {
                sellQuantity = buyItr->quantity;
                sellItr->quantity = sellItr->quantity - buyItr->quantity;
                isFullSellOrder = false;
            }
            
            if (buyItr->orderType == "IOC"){
                isFullBuyOrder = true;
            }
            if (sellItr->orderType == "IOC"){
                isFullSellOrder = true;
            }
            //Print trade execution message  
            cout << "TRADE " 
            << buyItr->orderId 
            << " " << buyItr->price << " "<< buyQunatity <<" " 
            << sellItr->orderId 
            << " " << sellItr->price << " "<< sellQuantity << endl;
            //Now update the data
            auto buyMapItr = buyOrders.find(buyItr->orderId);                
            auto sellMapItr = sellOrders.find(sellItr->orderId);
            if (isFullBuyOrder)
            {
                buyOrders.erase(buyMapItr);
                buyOrderList.erase(buyItr);
                buyItr = buyOrderList.begin();
            }
            if (isFullSellOrder)
            {
                sellOrders.erase(sellMapItr);
                sellOrderList.erase(sellItr);
                //sellOrderList.pop_back();
                sellItr = sellOrderList.begin();
            }       
        }
        else {
            break;
        }
    }
   
}

void CancelOrders(Order& order){
    auto itr = sellOrders.find(order.orderId);
    if (itr != sellOrders.end()){
        sellOrderList.erase(itr->second);
        sellOrders.erase(itr);
    }
    itr = buyOrders.find(order.orderId);
    if (itr != buyOrders.end()){
        buyOrderList.erase(itr->second);
        buyOrders.erase(itr);
    }
}

void ModifyOrders(Order& order){  

    auto itr = buyOrders.find(order.orderId);
    if (itr != buyOrders.end()){
        //itr->second--;
        if ((itr->second)->orderType == "IOC"){
            return;
        }
    }
    itr = sellOrders.find(order.orderId);
    if (itr != sellOrders.end()){
            //itr->second--;
            if ((itr->second)->orderType == "IOC"){
                return;
            }
    }
    CancelOrders(order);
    if (order.modifyOp == Operation::BUY){
        addBuyOrders(order);
    }
    else if (order.modifyOp == Operation::SELL){
        addSellOrders(order);
    }
}

void PrintOrders(){
    cout << "SELL:" << endl;
    auto itr = sellOrderList.begin();
    for (; itr != sellOrderList.end();){
        int price = (*itr).price;
        int q = (*itr).quantity;
        cout << price << " ";
        auto nextItr =  next(itr);
        if ((*nextItr).price == price)
        {
            while ((*nextItr).price == price && nextItr != sellOrderList.end()){
                q += (*nextItr).quantity;
                ++nextItr;
            }
            itr = nextItr ;
        }
        else {
            ++itr;
        }
        cout << q << endl; 
    }
    cout << "BUY:" << endl;
    itr = buyOrderList.begin();
    for (; itr != buyOrderList.end();){
        int price = (*itr).price;
        int q = (*itr).quantity;
        cout << price << " ";
        auto nextItr =  next(itr);
        if ((*nextItr).price == price)
        {
            while ((*nextItr).price == price && nextItr != buyOrderList.end()){
                q += (*nextItr).quantity;
                ++nextItr;
            }
            itr = nextItr ;
        }
        else {
            ++itr;
        }
        cout << q << endl;  
    }
}

int main()
{
    string token;
    while(std::getline(cin, token, '\n'))
    {
        stringstream ss(token);
        string orderInfo;      
        Order order;
        int tokenIdx = 0;
        while (getline(ss, orderInfo, ' ')){
            if (tokenIdx == 0)
            {
                if (orderInfo == operationStr[Operation::BUY]){
                    order.op = Operation::BUY;
                }
                else if (orderInfo == operationStr[Operation::SELL]){
                    order.op = Operation::SELL;
                }
                else if (orderInfo == operationStr[Operation::MODIFY]){
                    order.op = Operation::MODIFY;
                }
                else if (orderInfo == operationStr[Operation::PRINT]){
                    order.op = Operation::PRINT;
                    break;
                }
                else if (orderInfo == operationStr[Operation::CANCEL]){
                    order.op = Operation::CANCEL;
                }
            }
            else if (tokenIdx == 1){
                if (order.op == Operation::BUY || order.op == Operation::SELL)
                {
                    order.orderType = orderInfo;
                }
                else if (order.op == Operation::CANCEL){
                    order.orderId = orderInfo;
                    break;
                }
                else if (order.op == Operation::MODIFY){
                    order.orderId = orderInfo;
                }
            }
            else if (tokenIdx == 2){
                if (order.op == Operation::BUY || order.op == Operation::SELL)
                {
                    order.price = stoi(orderInfo);
                }
                else if (order.op == Operation::MODIFY){                    
                    if (orderInfo == operationStr[Operation::BUY]){
                        order.modifyOp = Operation::BUY;
                    }
                    else if (orderInfo == operationStr[Operation::SELL]){
                        order.modifyOp = Operation::SELL;
                    }
                    else if (orderInfo == operationStr[Operation::CANCEL]){
                        order.modifyOp = Operation::CANCEL;
                    }
                }
            }
            else if (tokenIdx == 3){
                if (order.op == Operation::BUY || order.op == Operation::SELL){
                        order.quantity = stoi(orderInfo);
                } 
                else if (order.op == Operation::MODIFY){
                        order.price = stoi(orderInfo);
                } 
            }
            else if (tokenIdx == 4){
                if (order.op == Operation::BUY || order.op == Operation::SELL){
                        order.orderId = orderInfo;
                } 
                else if (order.op == Operation::MODIFY){
                        order.quantity = stoi(orderInfo);
                } 
            }
            tokenIdx++;
        }
        
        //cout << operationStr[order.op] << endl;
        //cout << order.orderType << endl;
        //cout << order.orderId << endl;
        //cout << order.price << endl;
        //cout << order.quantity << endl;
        //cout << order.modifyOp << endl;

        if (order.op == Operation::BUY){
            addBuyOrders(order);
        }
        else if (order.op == Operation::SELL){
            addSellOrders(order);
        }
        else if (order.op == Operation::MODIFY){
            ModifyOrders(order);
        }
        else if (order.op == Operation::PRINT){
            PrintOrders();
        }
        else if (order.op == Operation::CANCEL){
            CancelOrders(order);
        }

    }

    return 0;
}