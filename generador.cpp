#include <iostream>
#include <string>
#include <fstream>
#include "Pesada.h"

using namespace std;

int main () {
    //crear un archivo de acceso aleatorio
    ofstream archivo("Folios.dat", ios::out | ios::binary);

    //verificar que el archivo se creo correctamente
    if (!archivo) {
        cerr << "No se pudo crear el archivo" << endl;
        exit(1);
    }

    //escribir 100 registros en el archivo, del tamaño de un objeto pesada
    Pesada p;
    for (int i = 0; i < 100; i++) {
        archivo.write(reinterpret_cast<const char *>(&p), sizeof(Pesada));
    }

    //cerrar el archivo
    archivo.close();
    system("pause");
    return 0;
}
