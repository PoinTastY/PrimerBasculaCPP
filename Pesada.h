#ifndef PESADA_H
#define PESADA_H
#include <iostream>
#include <string>
#include <time.h>
#include <cstring>

using namespace std;


class Pesada{
private:
    int folio;
    bool estado;
    char fecha[sizeof("dd/mm/aaaa hh:mm:ss")];
    int peso;
    int pesoNeto;
    int costales;

public:
    Pesada();
    void capturarInfo(int, int, int);
    void mostrarInfo();
    int returnFolio();
    string returnFecha();
    int returnPesoNeto();
    int returnCostales();
    int returnestado();
    bool operator ! ();

};

#endif
