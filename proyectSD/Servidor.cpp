#include "servidor.h"
#include "Maquina.h"

int cont;


Servidor::Servidor(){
	this->puerto=9000;
}


Servidor::Servidor(int puerto){
	this->puerto=puerto;
}
 
void Servidor::inicializarServidor(){

	descriptorSer= socket(AF_INET,SOCK_STREAM,0);
	servidorInfo.sin_family=AF_INET;
	servidorInfo.sin_addr.s_addr=htonl(INADDR_ANY);
	servidorInfo.sin_port=htons(puerto);
	idBind=bind(descriptorSer,(struct sockaddr *)&servidorInfo, sizeof(servidorInfo));
	
	listen(descriptorSer, maxMaquinas);

	if(descriptorSer==-1 && idBind==-1)
		cout<<"Error iniciando el servidor."<<endl;

}

void Servidor::cerrarServidor(){
	exit(EXIT_SUCCESS);
}
void * recibirCliente(void *cli){
    ClienteInfo * cliente =(ClienteInfo *) cli;
    char mensajeDeCliente[128];
    while(cliente->getEstado()){
        int i = recv(cliente->getDescriptorCliente(), (void *)&mensajeDeCliente,128,0);
        sleep(1);
        if(i!=0){
            cout<<"El cliente con ip: "<<inet_ntoa(cliente->getClienteInfor().sin_addr)<<" envio: "<<mensajeDeCliente<<endl;
            char mensajeACliente[128];
           //sprintf(mensajeACliente,"chao %d",cliente->getId());
           send(cliente->getDescriptorCliente(),(void *)mensajeACliente,sizeof(mensajeACliente),0);
        }else{        
            	cout<<"Se desconecto el cliente con ip: " <<inet_ntoa(cliente->getClienteInfor().sin_addr)<<" con error"<<endl;
		cliente->setEstado(false);
		close(cliente->getDescriptorCliente());
        }
    }
}

void * recibirMaquina(void * maq){
	MaquinaInfo * maquina=(MaquinaInfo *) maq;
	char mensajeDeMaquina[128];
	while(maquina->getEstado()){
		int i=recv(maquina->getDescriptorMaquina(),(void *)&mensajeDeMaquina,128,0);
		sleep(1);
		if(i!=0){
			cout<<"La maquina con ip: "<<inet_ntoa(maquina->getMaquinaInfor().sin_addr)<<" envio: "<<mensajeDeMaquina<<endl;
			char mensajeAMaquina[128];			
			//sprintf(mensajeAMaquina,"Chao %d",maquina->getId());
			send(maquina->getDescriptorMaquina(),(void *)mensajeAMaquina,sizeof(mensajeAMaquina),0);
		}else{
			cout<<"Se desconecto la maquina con ip: "<<inet_ntoa(maquina->getMaquinaInfor().sin_addr)<<" con error"<<endl;
			maquina->setEstado(false);
			close(maquina->getDescriptorMaquina());
		}
	}
}
void Servidor::aceptarCliente(){
    int descriptorCliente;
    cont=0;	
    while(cont<1){
        struct sockaddr_in clienteInfor;
        int tamano= sizeof(struct sockaddr_in);
	cout<<"Aceptando Cliente"<<endl;
        descriptorCliente=accept(this->descriptorSer,(struct sockaddr *)&clienteInfor,(socklen_t*) &tamano);
        if(descriptorCliente!=-1){
            cout<< "Cliente Conectado"<<endl;
            clienteDescriptor = new ClienteInfo(descriptorCliente,clienteInfor);
            pthread_t clientesHilos;
            pthread_create(&clientesHilos,NULL,&recibirCliente,(void *) clienteDescriptor);
            clienteDescriptor->setId(cont);
            cont++;
	}
    }
}

void Servidor::aceptarMaquinas(){
    int descriptorMaquina;
    cont=0;
    while(cont<maxMaquinas){
        struct sockaddr_in maquinaInfor;
        int tamano= sizeof(struct sockaddr_in);
        cout<<"Aceptando Maquinas"<<endl;
        descriptorMaquina=accept(this->descriptorSer,(struct sockaddr *)&maquinaInfor,(socklen_t*) &tamano);
        if(descriptorMaquina!=-1){
            cout<< "Maquina Conectada"<<endl;
            maquinaDescriptor.push_back(new MaquinaInfo(descriptorMaquina,maquinaInfor));
            pthread_t clientesHilos;
            pthread_create(&clientesHilos,NULL,&recibirMaquina,(void *) maquinaDescriptor[cont]);
            maquinaDescriptor[cont]->setId(cont);
            cont++;
        }
    }
}

void * Servidor::comenzarServidor(void * servidor){
    Servidor * server=(Servidor *) servidor;
    server->aceptarCliente();
    server->aceptarMaquinas();

}

void Servidor::ejecutarServidor(){
    pthread_t hilo;
    pthread_create(&hilo,NULL,&comenzarServidor,(void *) this);
}

void Servidor::setDescriptorServidor(int descriptor){
	this->descriptorSer=descriptor;
}

void Servidor::setIdBin(int bind){
	this->idBind=bind;
}
void Servidor::setPuerto(int puerto){
	this->puerto=puerto;
}
void Servidor::setServidorInfo(struct sockaddr_in info){
	this->servidorInfo = info;
}

int Servidor::getDescriptorServidor(){
	return this->descriptorSer;
}
int Servidor::getIdBin(){
	return this->idBind;
}
int Servidor::getPuerto(){
	return this->puerto;
}
struct sockaddr_in Servidor::getServidorInfo(){
	return this->servidorInfo;
}

vector<MaquinaInfo *> Servidor::getMaquinas(){
	return this->maquinaDescriptor;
}