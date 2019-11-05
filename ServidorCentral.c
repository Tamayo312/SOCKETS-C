#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

struct Mensaje {
	char tipo[15];
	char medida[15];
	char hora[15];
};

int main(int argc, const char * argv[]) {
    
    int fd;
    int i, cont;
    struct sockaddr_in servidor, cliente;
    
    char msg[15];
    socklen_t size;
    
    
    //Incializar estructura UDP
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(23000);
    servidor.sin_addr.s_addr = INADDR_ANY;
    memset(servidor.sin_zero, '\0', 8);
    
    int fdTCP;
    struct sockaddr_in servidorTCP;
    

    //Inicializar estructura TCP
    servidorTCP.sin_family = AF_INET;
    servidorTCP.sin_port = htons(1900);
    inet_aton("127.0.0.1", &servidorTCP.sin_addr);
    memset(&servidorTCP.sin_zero,'\0',8);

    printf("Servidor UDP\n");

    //Socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( fd < 0 )
    {
        perror("Error al crear socket\n");
    }
    
    //Bind
    if( bind(fd, (struct sockaddr *) &servidor, sizeof(struct sockaddr)) < 0 )
    {
        perror("Error en bind\n");
    }
    
for(i=0;i=10;i++){
    cont++;
    //Recvfrom
    if( recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr *) &cliente, &size) < 0 )
    {
        perror("Error al recibir\n");
    }
    
    printf("Mensaje: %s\n",msg);
    printf("Cliente: %s\n", inet_ntoa(cliente.sin_addr) );
    printf("Puerto:%d\n", ntohs(cliente.sin_port));	
    
    
    char tipo[15], medida[15], hora[15];
    strcpy(tipo, strtok(msg, "|"));
    strcpy(medida, strtok(NULL, "|"));
    strcpy(hora, strtok(NULL, "|"));

    /*printf("%s\n", tipo);
    printf("%s\n", medida);
    printf("%s\n", hora);*/
    
    
 //AQUI COMIENZA EL CLIENTE TCP
if(cont == 10){
    struct Mensaje msj;
    strcpy(msj.tipo, tipo);
    strcpy(msj.medida, medida);
    strcpy(msj.hora, hora);

    printf("Mensaje a enviar: %s|%s|\n", msj.tipo, msj.medida);
    char message[15];
    strcat(message, msj.tipo);
    strcat(message, "|");
    strcat(message, msj.medida);
    strcat(message, "|");
    
    printf(" Cliente TCP\n");
    
    //socket
    fdTCP = socket(AF_INET, SOCK_STREAM, 0);
    if( fdTCP < 0 )
    {
        perror("Error. Socket\n");
    }
    
    //Connect
    if( connect(fdTCP, (struct sockaddr *)&servidorTCP, sizeof(struct sockaddr)) < 0)
    {
        perror("Error al conectar\n");
    }
    
    printf("Enviando...%s\n", message);
    
    //Send
    if( send(fdTCP, message, strlen(message)+1, 0) < 0 )
    {
        perror("Error. Send\n");
    }
    cont = 0;
    strcpy(message, "");
 }
}
    //close
    close(fd);
    
    return 0;
}
