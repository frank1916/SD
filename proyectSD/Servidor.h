#include "MaquinaInfo.h"
#include "ClienteInfo.h"
#define maxMaquinas 5

class Servidor{
	private:
		int descriptorSer;
		int idBind;
		int puerto;
		struct sockaddr_in servidorInfo;
		vector<MaquinaInfo *> maquinaDescriptor;
                ClienteInfo *clienteDescriptor;
		bool state;

	public:
		Servidor(void);
		Servidor(int);

		void inicializarServidor(void);
		void aceptarMaquinas(void);
                void aceptarCliente(void);
		void cerrarServidor(void);
		static void *comenzarServidor(void *);
		void ejecutarServidor(void);

		void setDescriptorServidor(int);
		void setIdBin(int);
		void setPuerto(int);
		void setServidorInfo(struct sockaddr_in);
                
                
		int getDescriptorServidor(void);
		int getIdBin(void);
		int getPuerto(void);
		struct sockaddr_in getServidorInfo(void);
		vector<MaquinaInfo *> getMaquinas(void);
                ClienteInfo* getCliente(void);
};
