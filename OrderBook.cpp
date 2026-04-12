#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"
#include <iostream>
using namespace std;

/*================================================
            constructor and destructor
==================================================*/

OrderBook::OrderBook(){
    buy_capacity = 8; buy_size = 0;
    sell_capacity = 8; sell_size = 0;
    transaction_capacity = 8; transaction_size = 0;

    buy_orders = new Order*[buy_capacity];
    sell_orders = new Order*[sell_capacity];
    transactions = new Transaction*[transaction_capacity];
}

OrderBook::~OrderBook(){
    for(int i = 0; i < buy_size; i++)
        delete buy_orders[i];
    delete[] buy_orders;
    
    for(int i = 0; i < sell_size; i++)
        delete sell_orders[i];
    delete[] sell_orders;
    
    for(int i = 0; i < transaction_size; i++)
        delete transactions[i];
    delete[] transactions;
}

void OrderBook::insertTransaction(Transaction* transaction_){
    // double size
    if(transaction_size == transaction_capacity){
        transaction_capacity *= 2;
        Transaction** transactions_copy = new Transaction*[transaction_capacity];

        for(int i = 0; i < transaction_size; i++){
            transactions_copy[i] = transactions[i];
            transactions[i] = nullptr;
        }
        delete[] transactions;
        transactions = transactions_copy;
    }
    // insert transaction
    transactions[transaction_size] = transaction_;
    transaction_size++;
}

/*================================================
               submit() aux methods
==================================================*/

void OrderBook::insertBuy(Order* order_){
    // double size
    if(buy_size == buy_capacity){
        buy_capacity *= 2;
        Order** buy_orders_copy = new Order*[buy_capacity];

        for(int i = 0; i < buy_size; i++){
            buy_orders_copy[i] = buy_orders[i];
            buy_orders[i] = nullptr;
        }
        delete[] buy_orders;
        buy_orders = buy_orders_copy;
    }

    // insert buy
    buy_orders[buy_size] = order_;
    buy_size++; siftUpBuy(buy_size);
}

void OrderBook::siftUpBuy(int buy_size_){
    int child_i = buy_size_ - 1;
    int parent_i = (buy_size_ - 1)/2;

    Order* child = buy_orders[child_i];
    Order* parent = buy_orders[parent_i];

    while(priorityBuy(child, parent) && child_i != 0){
        // sift up buy orders
        Order* temp_parent = buy_orders[parent_i];
        buy_orders[parent_i] = buy_orders[child_i];
        buy_orders[child_i] = temp_parent;
        temp_parent = nullptr;

        // sift up index
        child_i = parent_i; child = buy_orders[child_i];
        parent_i = (child_i - 1)/2; parent = buy_orders[parent_i];
    }
}

bool OrderBook::priorityBuy(Order* child, Order* parent){
    float child_price = child->getPrice();
    int child_timestamp = child->getTimestamp();
    
    float parent_price = parent->getPrice();
    int parent_timestamp = parent->getTimestamp();

    if(child_price > parent_price)
        return true;

    if(child_price == parent_price && child_timestamp < parent_timestamp)
        return true;
    
    return false;   
}

void OrderBook::siftDownBuy(int buy_size_, int start_i){
    
    int parent_i = start_i;
    int left_child_i = 2*start_i + 1; int right_child_i = 2*start_i + 2;

    buy_orders[parent_i] = buy_orders[buy_size_ - 1]; 
    buy_orders[buy_size_ - 1] = nullptr; 
    buy_size_--; 

    while(left_child_i < buy_size_){ 
        
        Order* left_child = buy_orders[left_child_i];
        Order* right_child = buy_orders[right_child_i];
        Order* parent = buy_orders[parent_i];
        Order* parent_copy = buy_orders[parent_i];

        if(right_child_i < buy_size_ && priorityBuy(right_child, left_child)){
            if(priorityBuy(right_child, parent)){
            // sift down buy orders
            Order* right_child_copy = buy_orders[right_child_i];
            buy_orders[right_child_i] = parent_copy;
            buy_orders[parent_i] = right_child_copy; 
            right_child_copy = nullptr;           
            
            //sift down index
            parent_i = right_child_i;
            }
            else
                break;
        }
        else{
            if(priorityBuy(left_child, parent)){
            // sift down buy orders
            Order* left_child_copy = buy_orders[left_child_i];      
            buy_orders[left_child_i] = parent_copy;
            buy_orders[parent_i] = left_child_copy; 
            left_child_copy = nullptr;   
         
            //sift down index
            parent_i = left_child_i; 
            }

            else
                break;
        }
        parent_copy = nullptr; 
        right_child_i = 2*parent_i + 2; right_child = nullptr;
        left_child_i = 2*parent_i + 1; left_child = nullptr;
    }
}

void OrderBook::insertSell(Order* order_){
    // double size
    if(sell_size == sell_capacity){
        sell_capacity *= 2;
        Order** sell_orders_copy = new Order*[sell_capacity];

        for(int i = 0; i < sell_size; i++){
            sell_orders_copy[i] = sell_orders[i];
            sell_orders[i] = nullptr;
        }
        delete[] sell_orders;
        sell_orders = sell_orders_copy;
    }

    // insert sell
    sell_orders[sell_size] = order_;
    sell_size++; siftUpSell(sell_size);
}

void OrderBook::siftUpSell(int sell_size_){
    int child_i = sell_size_ - 1;
    int parent_i = (sell_size_ - 1)/2;

    Order* child = sell_orders[child_i];
    Order* parent = sell_orders[parent_i];

    while(prioritySell(child, parent) && child_i != 0){
        // sift up sell orders
        Order* temp_parent = sell_orders[parent_i];
        sell_orders[parent_i] = sell_orders[child_i];
        sell_orders[child_i] = temp_parent;
        temp_parent = nullptr;

        // sift up index
        child_i = parent_i; child = sell_orders[child_i];
        parent_i = (child_i - 1)/2; parent = sell_orders[parent_i];
    }
}

bool OrderBook::prioritySell(Order* child, Order* parent){
    float child_price = child->getPrice();
    int child_timestamp = child->getTimestamp();
    
    float parent_price = parent->getPrice();
    int parent_timestamp = parent->getTimestamp();

    if(child_price < parent_price)
        return true;

    if(child_price == parent_price && child_timestamp < parent_timestamp)
        return true;
    
    return false;   
}

void OrderBook::siftDownSell(int sell_size_, int start_i){

    int parent_i = start_i;
    int left_child_i = 2*start_i + 1; int right_child_i = 2*start_i + 2;

    sell_orders[parent_i] = sell_orders[sell_size_ - 1];
    sell_orders[sell_size_ - 1] = nullptr; // first sell points to last
    sell_size_--; 

    while(left_child_i < sell_size_){ 
        
        Order* left_child = sell_orders[left_child_i];
        Order* right_child = sell_orders[right_child_i];
        Order* parent = sell_orders[parent_i];
        Order* parent_copy = sell_orders[parent_i];

        if(right_child_i < sell_size_ && prioritySell(right_child, left_child)){
            
            if(prioritySell(right_child, parent)){
            Order* right_child_copy = sell_orders[right_child_i];
            
            sell_orders[right_child_i] = parent_copy;
            sell_orders[parent_i] = right_child_copy; 
            
            right_child_copy = nullptr;           
            parent_i = right_child_i;
            }
            else
                break;
        }
        else{
            if(prioritySell(left_child, parent)){
            Order* left_child_copy = sell_orders[left_child_i];
            
            sell_orders[left_child_i] = parent_copy;
            sell_orders[parent_i] = left_child_copy; 
            
            left_child_copy = nullptr;   
            parent_i = left_child_i; 
            }
            else
                break;
        }
        parent_copy = nullptr; 
        left_child_i = 2*parent_i + 1; left_child = nullptr;
        right_child_i = 2*parent_i + 2; right_child = nullptr;
    }
}

/*================================================
                public methods
==================================================*/

bool OrderBook::submit(Order order_){
    Order* order = new Order(order_.getId(), order_.getType(), 
    order_.getPrice(), order_.getTimestamp());
    
    char order_type = order->getType();
    float order_price = order->getPrice();
    int order_id = order->getId();

    if(order_type == 'B'){
        if(sell_size == 0)
            insertBuy(order);
        else{
            Order* top_sell = sell_orders[0];
            float top_sell_price = top_sell->getPrice();
            int top_sell_id = top_sell->getId();

            if(order_price >= top_sell_price){
                Transaction* transaction = new Transaction(order_id, top_sell_id, top_sell_price);
                insertTransaction(transaction);
                siftDownSell(sell_size, 0); sell_size--;
                order = nullptr; transaction = nullptr;
                return true;
            }
            else
                insertBuy(order);
        }
    }
    else{
        if(buy_size == 0)  
            insertSell(order);
        else{
            Order* top_buy = buy_orders[0];
            float top_buy_price = top_buy->getPrice();
            int top_buy_id = top_buy->getId();

            if(order_price <= top_buy_price){
                Transaction* transaction = new Transaction(top_buy_id, order_id, top_buy_price);
                insertTransaction(transaction);
                siftDownBuy(buy_size, 0); buy_size--; 
                order = nullptr; transaction = nullptr;
                return true;
            }
            else
                insertSell(order);
        }
    }
    order = nullptr;
    return false;
}

bool OrderBook::cancel(int id){
    for(int i = 0; i < buy_size; i++){
        if(id == buy_orders[i]->getId()){
            buy_orders[i] = nullptr;
            siftDownBuy(buy_size, i); buy_size--;
            siftUpBuy(buy_size);
            return true;
        }
    }

    for(int i = 0; i < sell_size; i++){
        if(id == sell_orders[i]->getId()){
            sell_orders[i] = nullptr;
            siftDownSell(sell_size, i); sell_size--;
            siftUpSell(sell_size);
            return true;
        }
    }
    return false;
}

/*================================================
                get() methods
==================================================*/

Order* OrderBook::getBuyOrders(int* n){ 
    *n = buy_size;
    Order* buy_orders_copy = new Order[*n]; 

    if(buy_size == 0){
        *n = 0;
        cout << "n = " << *n << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < *n; i++)
            buy_orders_copy[i] = *buy_orders[i];          
        return buy_orders_copy;
    }
}

Order* OrderBook::getSellOrders(int* n){
    *n = sell_size;
    Order* sell_orders_copy = new Order[*n]; 
    
    if(sell_size == 0){
        *n = 0;
        cout << "n = " << *n << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < *n; i++)
            sell_orders_copy[i] = *sell_orders[i];          
        return sell_orders_copy;
    }
}

Transaction* OrderBook::getTransactions(int* n){
    *n = transaction_size;
    Transaction* transaction_copy = new Transaction[*n]; 
    
    if(transaction_size == 0){
        *n = 0;
        cout << "n = " << *n << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < *n; i++)
            transaction_copy[i] = *transactions[i];           
        return transaction_copy;
    }
}

/*================================================
                print() methods
==================================================*/

void OrderBook::printBuyOrders(){
    cout << "Buy Orders:" << endl;

    if(buy_size == 0)
        cout << "(empty)" << endl;
    else{
        for(int i = 0; i < buy_size; i++)
            cout << '['
            << buy_orders[i]->getId() << " | " 
            << buy_orders[i]->getPrice() << " | "
            << buy_orders[i]->getTimestamp() << ']' << endl;
    }
}

void OrderBook::printSellOrders(){
    cout << "Sell Orders:" << endl;

    if(sell_size == 0)
        cout << "(empty)" << endl;
    else{
        for(int i = 0; i < sell_size; i++)
            cout << '['
            << sell_orders[i]->getId() << " | " 
            << sell_orders[i]->getPrice() << " | "
            << sell_orders[i]->getTimestamp() << ']' << endl;
    }
}

void OrderBook::printTransactions(){
    cout << "Transactions:" << endl;

    if(transaction_size == 0)
        cout << "(empty)" << endl;
    else{
        for(int i = 0; i < transaction_size; i++)
            cout << '['
            << transactions[i]->getBuyOrderId() << ", " 
            << transactions[i]->getSellOrderId() << ", "
            << transactions[i]->getExecutionPrice() << ']' << endl;
    }
}