#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PUERTO 8080
#define TAM_BUF 1024

int main(void){

     int sd = socket(AF_INET, SOCK_STREAM,0);
    if(sd <0){
        perror("Error al crear el socket");
        return EXIT_FAILURE;
    
    }
    printf("Socket creado correctamente.");
    
    struct sockaddr_in dir;
    memset(&dir,0,sizeof(dir));
    dir.sin_family = AF_INET;
    dir.sin_port = htons(PUERTO);
    dir.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sd,(struct sockaddr *)&dir, sizeof(dir)) < 0){
        perror("Error en la funcion connect()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Conectado al servidor %s:%d\n", inet_ntoa(dir.sinaddr), ntohs(dir.sin_port));
    
    const char mensaje = "Hola servidor, este es mi primer mensaje por socket TCP";
    ssize_t write(sd, mensaje, sizeof(mensaje) <0);
    if(write <0){
        perror("Error en la funcion write()");
        close(sd);
        return EXIT_FAILURE;
    }

    
    char buffer[TAM_BUF];
    ssize_t n = read(sd, buffer, sizeof(buffer)-1);
    if(n<0){
        perror("Error en la funcion read()");

        close(sd);
        return EXIT_FAILURE;
    }
    

    close(sd);



}