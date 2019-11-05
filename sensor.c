
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    srand(getpid());
    int i;
    int fd;
    int ret;
    struct sockaddr_in servidor;
    char msg[40];
    char tipo[15];
    int temp;
    char tempChar[5];
    printf("Sensor UDP\n");
    printf("------------------------------------------\n");
while(1){
    //TIMESTAMP
    time_t t;
    struct tm *tm;
    char hora[25];
    t = time(NULL);
    tm = localtime(&t);
    strftime(hora, 25, "%H:%M", tm);

    
    
    struct sockaddr_in serv_respuesta;
    socklen_t size;
    
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(23000);
    //inet_aton("192.168.17.133", &servidor.sin_addr);
    inet_aton("127.0.0.1", &servidor.sin_addr);
    memset(&servidor.sin_zero,'\0',8);
    
    
    //socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( fd < 0 )
    {
        perror("Error al crear el socket\n");
    }
    
    //sendto
    printf("Introduce el tipo de sensor (abcdID): \n");
    scanf("%s", &tipo);
    printf("Temperatura medida: \n");
    //scanf("%s", &temp);
    //Medida aleatoria
    temp = rand()%31+0;
    printf("%d\n", temp);
    snprintf(tempChar, sizeof tempChar, "%d", temp);

    strcat(msg, tipo);
    strcat(msg, "|");
    strcat(msg, tempChar);
    strcat(msg, "|");
    strcat(msg, hora);

    printf("\tEnviando... %s\n", msg);
    
    ret = sendto(fd, msg, strlen(msg) , 0, (struct sockaddr *)&servidor, sizeof(struct sockaddr) );
    if( ret < 0 )
    {
        perror("Error al enviar\n");
    }
    printf("Ok\n");
    strcpy(msg, "");
    }
    
    //Close
    close(fd);
    
    
    
    return 0;
}
