#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderList.hpp"

class OrderBook {

private:

    OrderList buyOrders;
    OrderList sellOrders;
    // Estruturas internas escolhidas pelos alunos
    // para armazenar ordens de compra, venda e transações

public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};