#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <time.h>
#include <cstdio>

using namespace std;


class MaquinaInfo {

    private:
        int descriptorMaquina;
        struct sockaddr_in maquinaInfor; 
        bool estado;
        int id;
    
    public:
        MaquinaInfo(int ,struct sockaddr_in);
        int getId(void);
        void setId(int);
        int getDescriptorMaquina(void);
        struct sockaddr_in getMaquinaInfor();
        bool getEstado(void);
        void setEstado(bool);
    
};

