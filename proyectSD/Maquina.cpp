#include "Maquina.h"

Maquina::Maquina() {
    this->puertoServidor = 9000;
    this->ipServidor = "192.168.1.50";
    this->estado = true;
}

Maquina::Maquina(int puerto, string ip) {
    this->puertoServidor = puerto;
    this->ipServidor = ip;
    this->estado = true;
}

void * Maquina::escucharServidor(void * maq) {
    Maquina* maquina = (Maquina *) maq;
    char mensajeDeServidor[60];
    while (1) {
        recv(maquina->getDescriptor(), (void *) &mensajeDeServidor, 60, 0);
        cout << mensajeDeServidor << endl;
    }
}

void * Maquina::escribirServidor(void * maq) {
    Maquina* maquina = (Maquina *) maq;
    int conectado = 1;
    while (conectado) {
        char msg[128];
        sprintf(msg, "Hola");
        int i = send(maquina->getDescriptor(), (void *) msg, sizeof (msg), 0);
        sleep(1);
        if (i == -1) {
            conectado = 0;
            cout << "se desconecto del servidor" << endl;
            close(maquina->getDescriptor());
            exit(EXIT_SUCCESS);
        }
    }
}

void Maquina::conectarServidor() {
    descriptorMaquina = socket(AF_INET, SOCK_STREAM, 0);
    servidorInfo.sin_family = AF_INET;
    inet_pton(AF_INET, ipServidor.c_str(), &servidorInfo.sin_addr);
    servidorInfo.sin_port = htons(puertoServidor);
    int conn = connect(descriptorMaquina, (struct sockaddr *) &servidorInfo, sizeof (servidorInfo));
    if (conn != -1) {
        pthread_t hiloEscucha;
        pthread_create(&hiloEscucha, NULL, escucharServidor, (void *) this);
        pthread_t hiloEscribe;
        pthread_create(&hiloEscribe, NULL, escribirServidor, (void *) this);
        while (1);
    } else {
        cout << "No se pudo conectar con el servidor" << endl;
    }
}

int Maquina::getDescriptor() {
    return this->descriptorMaquina;
}

void Maquina::setDescriptor(int descriptor) {
    this->descriptorMaquina = descriptor;
}

bool Maquina::getEstado() {
    return this->estado;
}

void Maquina::setEstado(bool estado) {
    this->estado = estado;
}