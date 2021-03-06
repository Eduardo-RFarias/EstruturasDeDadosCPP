#ifndef LISTAENCADEADA
#define LISTAENCADEADA

#include <iostream>
using namespace std;

class ListaEncadeada
{
private:
    class Node
    {
    public:
        int valor;
        Node *next;
    };

    Node *first;
    int size;

public:
    ListaEncadeada();
    ~ListaEncadeada();

    bool isEmpty();
    void clear();

    int getSize();
    int get(int index);
    int search(int value);

    void addFirst(int valor);
    void addBeforeKey(int chave, int valor);
    void addLast(int valor);
    void removeFirst();
    void removeValue(int chave);
    void removeLast();
};

#endif
