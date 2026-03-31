#include "Transaction.hpp"

// constructor
Transaction::Transaction(int buy_order_id_, int sell_order_id_, float execution_price_){
    this->buy_order_id = buy_order_id_;
    this->sell_order_id = sell_order_id_;
    this->execution_price = execution_price_;
}

// destructor
Transaction::~Transaction(){
}

// getters
int Transaction::getBuyOrderId(){
    return buy_order_id;
}

int Transaction::getSellOrderId(){
    return sell_order_id;
}

float Transaction::getExecutionPrice(){
    return execution_price;
}