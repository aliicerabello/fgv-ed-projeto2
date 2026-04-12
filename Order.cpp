#include "Order.hpp"
using namespace std;

// constructor
Order::Order(){
}

Order::Order(int id_, char type_, float price_, int timestamp_){
    this->id = id_;
    this->type = type_;
    this->price = price_;
    this->timestamp = timestamp_;
}

// destructor
Order::~Order(){
}

int Order::getId(){
    return id;
}

char Order::getType(){
    return type;
}

float Order::getPrice(){
    return price;
}

int Order::getTimestamp(){
    return timestamp;
}
