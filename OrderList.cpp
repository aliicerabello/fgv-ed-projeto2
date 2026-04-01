#include "OrderList.hpp"
#include <stdio.h>

OrderNode::OrderNode(){
    this->order = order;
    this->next = next;
}
//construtor
OrderList::OrderList(){ 
    head = nullptr;
    size = 0;
}

//destrutor
OrderList::~OrderList(){
    OrderNode *atual = head;

    while (atual != nullptr){
        OrderNode* temp = atual;
        atual = atual->next;
        delete temp;

    }

}

bool OrderList::add(Order o){
    OrderNode *novo = new OrderNode();
    novo->order = o;
    novo->next = this->head;
    this->head = novo;
    this->size++;
    return true;

};

bool OrderList::remove(int id){
    OrderNode *atual = this->head;
    OrderNode *anterior = nullptr;

    if (atual == nullptr){
        return false;
    } // lista vazia

    if (atual->order.getId() == id) {
        this->head = atual->next;
        delete atual;
        this->size--;
        return true;
    } //id a remover é o head

    while(atual != nullptr){
        int id_atual = atual->order.getId();
        if (id_atual == id){
            anterior->next = atual->next;
            atual->next = nullptr;
            delete atual;
            this->size--;
            return true;
        }
        anterior = atual;
        atual = atual->next;
    } // id tá no meio ou fim

    return false;

}