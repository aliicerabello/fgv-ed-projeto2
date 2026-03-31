class Transaction {

private:
    int buy_order_id;
    int sell_order_id;
    float execution_price;

public:

    Transaction(int buy_order_id, int sell_order_id, float execution_price);
    ~Transaction();

    int getBuyOrderId();
    int getSellOrderId();
    float getExecutionPrice();
};