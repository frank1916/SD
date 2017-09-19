#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include <vector>

using namespace std;

class Maquina {

private:
	int descriptorMaquina;
	struct sockaddr_in servidorInfo;
	int puertoServidor;
	string ipServidor;
	bool estado;    

public:
	Maquina(void);
	Maquina(int, string);
	void conectarServidor(void);
	static void * escucharServidor(void*);
	static void * escribirServidor(void*);
	int getDescriptor(void);
	void setDescriptor(int);
	bool getEstado(void);
	void setEstado(bool);

};
