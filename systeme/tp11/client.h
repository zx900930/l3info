#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int creer_socket(int type, int *ptr_port, char *adresse, struct sockaddr_in *ptr_adresse);
void client_lit_stdin(int socket);


