#include "OrderBook.hpp"
#include "Order.hpp"
#include <iostream>
#include <ctime>
using namespace std;

int main(){

    // Cenário 1 — heap de compras organizado
    cout << "=== Cenário 1: Heap de compras ===" << endl;
    OrderBook ob1;
    ob1.submit(Order(1, 'B', 80, 1));
    ob1.submit(Order(2, 'B', 100, 2));
    ob1.submit(Order(3, 'B', 60, 3));
    ob1.printBuyOrders();
    ob1.cancel(0);
    ob1.printBuyOrders();
    ob1.submit(Order(4, 'B', 90, 4));
    ob1.submit(Order(5, 'B', 70, 5));
    ob1.printBuyOrders(); // esperado: 100 no topo

    // Cenário 2 — heap de vendas organizado
    cout << "\n=== Cenário 2: Heap de vendas ===" << endl;
    OrderBook ob2;
    ob2.submit(Order(1, 'S', 80, 1));
    ob2.submit(Order(2, 'S', 60, 2));
    ob2.submit(Order(3, 'S', 100, 3));
    ob2.submit(Order(4, 'S', 70, 4));
    ob2.submit(Order(5, 'S', 50, 5));
    ob2.printSellOrders(); // esperado: 50 no topo

    // Cenário 3 — venda já existe, compra chega e executa
    cout << "\n=== Cenário 3: Transação compra encontra venda ===" << endl;
    OrderBook ob3;
    ob3.submit(Order(1, 'S', 80, 1));
    ob3.submit(Order(2, 'B', 100, 2));
    ob3.printBuyOrders();  // esperado: vazio
    ob3.printSellOrders(); // esperado: vazio
    //ob3.printTransactions(); // esperado: [2, 1, 80.0]

    // Cenário 4 — compra já existe, venda chega e executa
    cout << "\n=== Cenário 4: Transação venda encontra compra ===" << endl;
    OrderBook ob4;
    ob4.submit(Order(1, 'B', 100, 1));
    ob4.submit(Order(2, 'S', 80, 2));
    ob4.printBuyOrders();  // esperado: vazio
    ob4.printSellOrders(); // esperado: vazio
    //ob4.printTransactions(); // esperado: [1, 2, 100.0]

    // Cenário 5 — sem compatibilidade
    cout << "\n=== Cenário 5: Sem compatibilidade ===" << endl;
    OrderBook ob5;
    ob5.submit(Order(1, 'B', 80, 1));
    ob5.submit(Order(2, 'S', 100, 2));
    ob5.printBuyOrders();  // esperado: 80
    ob5.printSellOrders(); // esperado: 100

    // Cenário 6 — melhor contraparte (menor preço, menor timestamp)
    cout << "\n=== Cenário 6: Melhor contraparte ===" << endl;
    OrderBook ob6;
    ob6.submit(Order(1, 'S', 90, 1));
    ob6.submit(Order(2, 'S', 70, 2));
    ob6.submit(Order(3, 'S', 70, 3));
    ob6.submit(Order(4, 'B', 100, 4));
    ob6.printSellOrders();   // esperado: 70(ts=3) e 90 restantes
    ob6.printTransactions(); // esperado: [4, 2, 70.0]

    // Cenário 7 — heap se reorganiza após transação
    cout << "\n=== Cenário 7: Reorganização após transação ===" << endl;
    OrderBook ob7;
    ob7.submit(Order(1, 'B', 100, 1));
    ob7.submit(Order(2, 'B', 90, 2));
    ob7.submit(Order(3, 'B', 80, 3));
    ob7.submit(Order(4, 'B', 70, 4));
    ob7.submit(Order(5, 'B', 60, 5));
    ob7.submit(Order(6, 'S', 50, 6)); // executa com 100
    ob7.printBuyOrders();   // esperado: 90 no topo
    ob7.printTransactions(); // esperado: [1, 6, 100.0]

    // Cenário 8 — cancelamento básico de compra
    cout << "\n=== Cenário 8: Cancel compra ===" << endl;
    OrderBook ob8;
    ob8.submit(Order(1, 'B', 100, 1));
    ob8.submit(Order(2, 'B', 90, 2));
    ob8.submit(Order(3, 'B', 80, 3));
    cout << ob8.cancel(2) << endl; // esperado: 1
    ob8.printBuyOrders(); // esperado: 100 e 80, sem 90

    // Cenário 9 — cancelamento da raiz
    cout << "\n=== Cenário 9: Cancel raiz ===" << endl;
    OrderBook ob9;
    ob9.submit(Order(1, 'B', 100, 1));
    ob9.submit(Order(2, 'B', 90, 2));
    ob9.submit(Order(3, 'B', 80, 3));
    cout << ob9.cancel(1) << endl; // esperado: 1
    ob9.printBuyOrders(); // esperado: 90 no topo

    // Cenário 10 — cancelamento do último elemento
    cout << "\n=== Cenário 10: Cancel último ===" << endl;
    OrderBook ob10;
    ob10.submit(Order(1, 'B', 100, 1));
    ob10.submit(Order(2, 'B', 90, 2));
    ob10.submit(Order(3, 'B', 80, 3));
    cout << ob10.cancel(3) << endl; // esperado: 1
    ob10.printBuyOrders(); // esperado: 100 e 90

    // Cenário 11 — cancelamento de venda
    cout << "\n=== Cenário 11: Cancel venda ===" << endl;
    OrderBook ob11;
    ob11.submit(Order(1, 'S', 50, 1));
    ob11.submit(Order(2, 'S', 60, 2));
    ob11.submit(Order(3, 'S', 70, 3));
    cout << ob11.cancel(1) << endl; // esperado: 1
    ob11.printSellOrders(); // esperado: 60 no topo

    // Cenário 12 — cancelamento inexistente
    cout << "\n=== Cenário 12: Cancel inexistente ===" << endl;
    OrderBook ob12;
    ob12.submit(Order(1, 'B', 100, 1));
    cout << ob12.cancel(99) << endl; // esperado: 0

    // Cenário 13 — cancelamento e nova reserva no lugar
    cout << "\n=== Cenário 13: Cancel e nova ordem ===" << endl;
    OrderBook ob13;
    ob13.submit(Order(1, 'B', 100, 1));
    ob13.submit(Order(2, 'B', 90, 2));
    ob13.cancel(1);
    ob13.submit(Order(3, 'S', 85, 3)); // deve executar com 90
    ob13.printTransactions(); // esperado: [2, 3, 90.0]

    // Cenário 14 — getBuyOrders básico
    cout << "\n=== Cenário 14: getBuyOrders ===" << endl;
    OrderBook ob14;
    ob14.submit(Order(1, 'B', 100, 1));
    ob14.submit(Order(2, 'B', 90, 2));
    ob14.submit(Order(3, 'B', 80, 3));
    int n14;
    Order* buy14 = ob14.getBuyOrders(&n14);
    cout << "n: " << n14 << endl; // esperado: 3
    for(int i = 0; i < n14; i++)
        cout << buy14[i].getId() << " | " << buy14[i].getPrice() << endl;
    delete[] buy14;

    // Cenário 15 — getSellOrders básico
    cout << "\n=== Cenário 15: getSellOrders ===" << endl;
    OrderBook ob15;
    ob15.submit(Order(1, 'S', 50, 1));
    ob15.submit(Order(2, 'S', 60, 2));
    ob15.submit(Order(3, 'S', 70, 3));
    int n15;
    Order* sell15 = ob15.getSellOrders(&n15);
    cout << "n = " << n15 << endl; // esperado: 3
    for(int i = 0; i < n15; i++)
        cout << sell15[i].getId() << " | " << sell15[i].getPrice() << endl;
    delete[] sell15;

    // Cenário 16 — getTransactions básico
    cout << "\n=== Cenário 16: getTransactions ===" << endl;
    OrderBook ob16;
    ob16.submit(Order(1, 'B', 100, 1));
    ob16.submit(Order(2, 'S', 80, 2));
    ob16.submit(Order(3, 'B', 90, 3));
    ob16.submit(Order(4, 'S', 70, 4));
    int n16;
    Transaction* trans16 = ob16.getTransactions(&n16);
    cout << "n = " << n16 << endl; // esperado: 2
    for(int i = 0; i < n16; i++)
        cout << trans16[i].getBuyOrderId() << " | " 
            << trans16[i].getSellOrderId() << " | " 
            << trans16[i].getExecutionPrice() << endl;
    delete[] trans16;

    // Cenário 17 — get com lista vazia
    cout << "\n=== Cenário 17: get vazio ===" << endl;
    OrderBook ob17;
    int n17;
    Order* buy17 = ob17.getBuyOrders(&n17);
    cout << "n = " << n17 << endl;         // esperado: 0
    cout << (buy17 == nullptr) << endl;   // esperado: 1

    // Cenário stress test
    int volumes[] = {100000, 1000000, 10000000, 100000000};

    for(int v = 0; v < 4; v++){
        int vol = volumes[v];
        cout << "\n=== Stress Test: " << vol << " ordens ===" << endl;
        
        OrderBook ob_stress;
        clock_t start = clock();

        for(int i = 1; i <= vol; i++){
            char type = (i % 2 == 0) ? 'B' : 'S';
            ob_stress.submit(Order(i, type, float(rand() % 1000), i));
        }

        clock_t end = clock();
        cout << "Tempo: " << (double)(end-start)/CLOCKS_PER_SEC << "s" << endl;

        int n;
        Order* buys = ob_stress.getBuyOrders(&n);
        cout << "Compras restantes: " << n << endl;
        delete[] buys;

        Order* sells = ob_stress.getSellOrders(&n);
        cout << "Vendas restantes: " << n << endl;
        delete[] sells;

        Transaction* trans = ob_stress.getTransactions(&n);
        cout << "Transações: " << n << endl;
        delete[] trans;
    }
    return 0;
}
