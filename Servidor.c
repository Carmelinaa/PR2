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

    struct sockaddr_in direcc;
    memset(&direcc,0,sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PUERTO);
    direcc.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sd, (struct sockaddr *) &direcc, sizeof(direcc)) <0){
        perror("Error en la función bind()");
        close(sd);
        return EXIT_FAILURE;

    }

    if(listen(sd, SOMAXCONN) <0){
        perror("Error en la función listen()");
        close(sd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in cliente;
    socklen_t = sizeof(cliente);
    int sd_cliente = accept(sd, (struct sockaddr *)&cliente, &len);
    if(sd_cliente <0){
        perror("Error en la función accept()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Cliente conectado desde %s:%d/n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));

    char buffer[TAM_BUF];
    ssize_t n = read(sd_cliente, buffer, sizeof(buffer)-1);
    if(n<0){
        perror("Error en la funcion read()");
        close(sd_cliente);
        close(sd);
        return EXIT_FAILURE;
    }

    const char respuesta = "mensaje recibido";
    if(write(sd_cliente, respuesta,strlen(respuesta)) < 0){
        perror("Error en la funcion write()");
        close (sd_cliente);
        close(sd);
        return EXIT_FAILURE;

    }
    

    close(sd);
    close(sd_cliente);



}