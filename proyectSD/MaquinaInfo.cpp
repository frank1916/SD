#include "MaquinaInfo.h"

MaquinaInfo::MaquinaInfo(int desc , struct sockaddr_in infor){
	this->descriptorMaquina = desc;
	this->maquinaInfor = infor;
	this->estado=true;
}

int MaquinaInfo::getId(){
	return this->id;
}

void MaquinaInfo::setId(int id){
 	this->id=id;
}

int MaquinaInfo::getDescriptorMaquina(void){
	return this->descriptorMaquina;
}
struct sockaddr_in MaquinaInfo::getMaquinaInfor(){
	return this->maquinaInfor;
}

bool MaquinaInfo::getEstado(){
	return this->estado;
}

void MaquinaInfo::setEstado(bool estado){
	this->estado=estado;
}