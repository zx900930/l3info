#ifndef __SOCKET__
#define __SOCKET__

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int creer_socket(int, int, SOCKADDR_IN *);

void client_service(SOCKET );


#endif
