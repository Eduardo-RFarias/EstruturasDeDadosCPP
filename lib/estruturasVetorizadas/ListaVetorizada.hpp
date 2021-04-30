#ifndef LISTAVETORIZADA
#define LISTAVETORIZADA

#include <iostream>
using namespace std;

class ListaVetorizada
{
private:
    int *array;
    int size;
    int MAXSIZE;
    bool isSorted;

public:
    ListaVetorizada(int size = 0);
    ListaVetorizada(int *array, int size);
    ~ListaVetorizada();

    int getSize();
    int getMaxSize();

    int get(int index);
    int search(int value);

    void remove(int index);
    void append(int value);
    void remove_noReplace(int index);
    void append_noReplace(int value);
    void insertIn(int value, int index);

    void sort();
    int binarySearch(int value);
};

#endif