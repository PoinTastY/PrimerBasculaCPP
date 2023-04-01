#include "Pesada.h"

Pesada::Pesada(){
    folio = 1;
    memcpy(fecha, "dd/mm/aaaa hh:mm:ss", sizeof(fecha));
    estado = false;
    peso = 0;
    pesoNeto = 0;
    costales = 0;
}

void Pesada :: capturarInfo(int peso, int folio, int costales){
    this->peso = peso;
    this->folio = folio;
    this->costales = costales;
    this->pesoNeto = peso * costales;
    time_t now = time(0);
    char* dt = ctime(&now);
    strftime(dt, 26, "%d/%m/%Y %H:%M:%S", localtime(&now));
    memcpy(fecha, dt, sizeof(fecha));
    this-> estado = true;
}


void Pesada::mostrarInfo(){
    cout << "Folio: " << folio << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Peso de costal: " << peso << endl;
    cout << "Costales: " << costales << endl;
    cout << "Peso neto: " << pesoNeto << endl;
}

bool Pesada::operator ! (){
    return estado;
}

int Pesada :: returnFolio(){
    return folio;
}

string Pesada :: returnFecha(){
    return fecha;
}

int Pesada :: returnPesoNeto(){
    return pesoNeto;
}

int Pesada :: returnCostales(){
    return costales;
}

int Pesada :: returnestado(){
    return estado;
}
