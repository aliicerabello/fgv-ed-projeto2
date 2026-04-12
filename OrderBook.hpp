#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "Order.hpp" 
#include "Transaction.hpp"

class OrderBook {

private:

    int buy_size, buy_capacity;
    Order** buy_orders;

    int sell_size, sell_capacity;
    Order** sell_orders;

    int transaction_size, transaction_capacity;
    Transaction** transactions; /*ponteiro de ponteiro pois ao criar a lista
                                de orders/transactions eu teria que inicializa-los*/

    // aux methods
    void insertBuy(Order* order_); 
    bool priorityBuy(Order* child, Order* parent);
    void siftUpBuy(int buy_size_);
    void siftDownBuy(int buy_size_, int start_i);
    
    void insertSell(Order* order_);
    bool prioritySell(Order* child, Order* parent);
    void siftUpSell(int sell_size_);
    void siftDownSell(int sell_size_, int start_i);     
    
    void insertTransaction(Transaction* transaction_);

public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order_);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif