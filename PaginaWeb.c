#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, const char * argv[])
{
    int fd, fdCLiente;
    struct sockaddr_in servidor, cliente;
    socklen_t sizeCliente;
    
    char msg[15];
    
    
    //Incializar estructura
    //Datos del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(1900);
    servidor.sin_addr.s_addr = INADDR_ANY;
    memset(servidor.sin_zero, '\0', 8);
    
    printf("Pagina Web\n");
    
    //Socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if( fd < 0)
    {
        perror("Error. Socket\n");
    }
    
    //Bind
    if (bind(fd, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) < 0 )
    {
        perror("Error. Bind\n");
    }
while(1){
    //Listen
    if( listen(fd, 1) < 0 )
    {
         perror("Error. Listen\n");
    }
    
    //Accept
    printf("Esperando conexiones...\n");
    fdCLiente = accept(fd, (struct sockaddr *)&cliente, &sizeCliente);
    if( fdCLiente < 0)
    {
        perror("Error. Accept\n");
    }
    printf("Conexion establecida con %s\n",inet_ntoa(cliente.sin_addr));
    
    
    //recv
    if( recv(fdCLiente, msg, sizeof(msg), 0) < 0 )
    {
        perror("Error. Recv\n");
    }
    
    printf("Mensaje:%s\n",msg);
    
}
    //Close
    close(fd);
    
    return 0;
}
