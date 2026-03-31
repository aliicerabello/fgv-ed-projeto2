class Order {

private:
    int id;
    char type; // 'B' ou 'S'
    float price;
    int timestamp;

public:

    Order(int id, char type, float price, int timestamp);
    ~Order();

    int getId();
    char getType();
    float getPrice();
    int getTimestamp();
};