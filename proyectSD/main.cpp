#include <iostream>
#include "Servidor.h"
#include "Cliente.h"
#include "Maquina.h"

int main(int argc, char ** argv) {

    int tipo = 0;
    int puerto = 0;
    cout << "Seleccione el tipo: 1:Servidor, 2:Cliente Cual?:  ";
    cin >> tipo;
    cin.get();

    cout << "Puerto: ";
    cin >> puerto;
    cin.get();

    int val = tipo;

    if (val == 1) {
        Servidor servidor;
        servidor.setPuerto(puerto);
        servidor.inicializarServidor();
        servidor.ejecutarServidor();
        while (1);
    }
    if (val == 2) {
        cout << "Nombre del Host o ip: ";
        string host;
        getline(cin, host);
        Cliente *cliente = new Cliente(puerto, host);
        cliente->conectarServidor();
        int accion;
        while (true) {
            cout << "\n Seleccione una accion a realizar: \n 1:Enviar Mensage."<<endl;
            cin >> accion;
            cin.get();
            if (accion == 1) {
                cout << "Escriba un mensaje para enviar " << endl;
                char texto[128];
                cin>>texto;
                cin.get();
                char msg[128];
                sprintf(msg, texto);
                int i = send(cliente->getDescriptor(), (void *) msg, sizeof (msg), 0);
            }
            if (accion == 2) {
                int maquina;
                cout << "Seleccione la maquina de la cual quiere ver los archivos [1][2][3][4][5][6].";
                cin >> maquina;
                cin.get();
                cout << "Archivos de la Maquina " << maquina << endl;
            }
            if (accion == 3) {
                cout << "Selecciono 3.";
            }
            if (accion == 4) {
                cout << "Selecciono 4.";
            }            
        }
    }
    return 0;
}
