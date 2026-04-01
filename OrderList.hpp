#include "Order.hpp"
#ifndef ORDERLIST_HPP
#define ORDERLIST_HPP

struct OrderNode{
    Order order;
    OrderNode *next;

    OrderNode();
};

class OrderList{
    OrderNode *head;
    int size;

public:

    OrderList(); //inicializada vazia
    ~OrderList(); //destrutor

    bool add(Order o); //adiciona no final
    bool remove(int id);
    Order getMax();
    Order getMin(); //seller

};


#endif