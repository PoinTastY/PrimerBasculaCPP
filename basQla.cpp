#include <iostream>
#include <string>
#include "Pesada.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main(){
    Pesada p;
    int peso = 30 + rand() % 21;//Por ahora el peso es aleatorio, hasta que se disponga de una bascula
    int folio = 1, costales;
    //abre el archivo de acceso aleatorio
    fstream archivo("Folios.dat", ios::in | ios::out | ios::binary);

    //si no se pudo abrir el archivo
    if(!archivo){
        cerr << "No se pudo abrir el archivo :c" << endl;
        exit(1);
    }

    //menu de opciones en un bucle
    int opcion;
    do{
        archivo.clear();
        cout << "\nBienvenido al sistema de pesada" << endl;
        cout << "1. Pesar" << endl;
        cout << "2. Consultar folio" << endl;
        cout << "3. Leer todos los folios" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            //pesar
            peso = 30 + rand() % 21;
            cout << "\n\nPeso(automatico): " << peso << endl;//Si hay bascula, se implementara una funcion que lea el peso
            
            //capturar folio
            cout << "Folio(1 - 100): ";
            cin >> folio;
            while (folio < 1 || folio > 100){//validar que haya datos validos
                if(folio < 1 || folio > 100){
                    cout << "\nError, ingrese un folio valido" << endl;
                    cout << "Folio(1 - 100): ";
                    cin >> folio;
                }else{
                    cout << "\nAlgo salio mal :c" << endl;
                }
            }
            //capturar costales
            cout << "\nCostales cargados: ";
            cin >> costales;
            while (costales < 1){//validar que haya datos validos
                if(costales < 1){
                    cout << "\nError, ingrese un numero valido" << endl;
                    cout << "Costales cargados: ";
                    cin >> costales;
                }else{
                    cout << "\nAlgo salio mal :c" << endl;
                }
            }

            //lectura del archivo para confirmar que el folio no este ocupado
            archivo.seekg((folio-1)*sizeof(Pesada));//posicionamos el puntero de lectura en el registro que queremos leer
            archivo.read(reinterpret_cast<char *>(&p), sizeof(Pesada));//leemos el registro del archivo
            if (!p){//si el folio ya esta ocupado
                cout << "\nEl folio ya esta ocupado, quiere sobreescribirlo?\n1. Si, 2. No" << endl;
                cin >> opcion;
                if (opcion == 2){
                    cout << "\nNo se ha sobreescrito el folio" << endl;
                    break;
                }else if (opcion == 1){
                    cout << "\nSobreescribiendo..." << endl;
                    p.capturarInfo(peso, folio, costales);
                    cout << "\nSe ha capturado la siguiente informacion: " << endl;
                    p.mostrarInfo();
                    //escritura en el archivo
                    archivo.seekp(0);//posicionamos el puntero de escritura al inicio del archivo
                    archivo.seekp((folio - 1) * sizeof(Pesada));//posicionamos el puntero de escritura en el registro que queremos modificar
                    archivo.write(reinterpret_cast<const char *>(&p), sizeof(Pesada));//escribimos el registro en el archivo
                }else{
                    cout << "\nOpcion invalida" << endl;
                    break;
                }
            }else{//si el folio esta libre
                p.capturarInfo(peso, folio, costales);
                cout << "\nSe ha capturado la siguiente informacion: " << endl;
                p.mostrarInfo();
                //escritura en el archivo
                archivo.seekp(0);//posicionamos el puntero de escritura al inicio del archivo
                archivo.seekp((folio - 1) * sizeof(Pesada));//posicionamos el puntero de escritura en el registro que queremos modificar
                archivo.write(reinterpret_cast<const char *>(&p), sizeof(Pesada));//escribimos el registro en el archivo
            }
            system("pause");    

            
            break;
        case 2:
            //consultar folio
            cout << "\n\nFolio para buscar(1 - 100): ";
            cin >> folio;
            while (folio < 1 || folio > 100){//validar los datos
                if(folio < 1 || folio > 100){
                    cout << "\nError, ingrese un folio valido" << endl;
                    cout << "Folio(1 - 100): ";
                    cin >> folio;
                }else{
                    cout << "\nAlgo salio mal :c" << endl;
                }
            }
            archivo.seekg(0);//posicionamos el puntero de lectura al inicio del archivo
            archivo.seekg((folio - 1) * sizeof(Pesada));//posicionamos el puntero de lectura en el registro que queremos leer
            archivo.read(reinterpret_cast<char *>(&p), sizeof(Pesada));//leemos el registro del archivo
            if(!(!p)){
                cout << "\nEl folio no existe" << endl;
            }else{
                cout << "\nSe ha consultado la siguiente informacion: " << endl;
                p.mostrarInfo();
            }
            system("pause");
            break;
        case 3:
            //leer todos los folios
            cout << "\n\nSe ha consultado la siguiente informacion: " << endl;
            cout << left << setw(10) << "Folio" << setw(20) << "Fecha" << setw(10) <<  "Peso neto" << setw(15) << "Costales" << endl;
            archivo.seekg(0);//posicionamos el puntero de lectura al inicio del archivo
            archivo.read(reinterpret_cast<char *>(&p), sizeof(Pesada));//leemos el registro del archivo
            while(archivo && !archivo.eof()){//mientras no sea el final del archivo
                if(!p){//para que no imprima toooodos los registros inicializados
                    cout << left << setw(10) << p.returnFolio() << setw(20) << p.returnFecha() << setw(10) << p.returnPesoNeto() << setw(15) << p.returnCostales() << endl;
                }
                archivo.read(reinterpret_cast<char *>(&p), sizeof(Pesada));//leemos el registro del archivo

            }
            

            system("pause");
            break;

        case 4:
            //salir
            cout << "\n\nGracias por usar el sistema de pesada" << endl;
            break;

        default:
            cout << "\n\nOpcion invalida, try again\n" << endl;
            opcion = 0;
            break;
        }


    }while (opcion >= 0 && opcion < 4);

    //cerramos el archivo
    archivo.close();
    return 0;
}