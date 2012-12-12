#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>

#define NIPQUAD (addr) \
	((unsigned char*)&addr) [0], \
	((unsigned char*)&addr) [1], \
	((unsigned char*)&addr) [2], \
	((unsigned char*)&addr) [3]

#define BUFSIZE 1024
char buf [BUFSIZE +1];

void *sighandler (int dummy)
{
	wait(NULL);
}

/* function de manipulation du client */

void serve(int s, struct sockaddr_in *peer)
{
	int space, n;
	char *p, *q;
	q = p = buf ; space = BUFSIZE;
	while (1){
		if((n = read (s, p, space)) <=0)
			break;
		p += n; space -=n;
		while ((q < p) && (*q != '\n'))
			q++;
		while ((q < p) || !space){
			*q = 0;
			printf("message from %d.%d.%d.%d %d: %s\n",
					NIPQUAD(peer->sin_addr.s_addr), ntohs(peer->sin_port), buf);
			if (q < p) q++;
			memmove(buf, q, p - q);
			n = q - buf; // Nombre de caractÃres traitÃs
			p -= n;
			space += n;
			q = buf;
			while ((q < p) && (*q != '\n'))
				q++; 	
		}
	}

	if (n < 0) perror("read");
	else if (p > buf) {
		*p = 0;
		printf("message from %d.%d.%d.%d %d: %s\n",
				NIPQUAD(peer->sin_addr.s_addr), ntohs(peer->sin_port), buf);
	}
}

int main (int argc, char *argv[])
{
	int s;
	struct sockaddr_in myaddr;
	int optval;

	if (arg !=2){
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(1);

		/*Option du socket SO_REUSEADDR: Autorise bind()
		  utilise les anciennes adresses de protocole de l'adresse */

		optval = 1;
		if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optival, sizeof(optival))){
			perror("setsockopt");
			exit(1);
		}

		memset(&myaddr, 0, sizeo(myaddr));
		myaddr.sin_family = AF_INET;
		myaddr.sin_port = htons(atoi(argv[1]));
		myaddr.sin_addr.s_addr = INADDR_ANY;

		if (bind(s,(struct sockaddr *) &myaddr, sizeof(myaddr))){
			perror("bind");
			exit(1);

			if (lesten(s, SOMAXCONN)){
				perror("lesten");
				exit(1);

				/* Installer le gestionnaire de signal pour signal SIGCHLD */
				if (signal(SIGCHLD, (sig_t) sighandler) == SIG_ERR) {
					perror("signal");
					exit(1);
				}

				while (1){
					int new_s;
					struct sockaddr_in claddr;
					int claddrlen;

					claddrlen = sizeof (claddr);
					if ((new_s = accept(s, (struct sockaddr *) &claddr, &claddrlen)) < 0){
						perror("accept");
						continue;
					}

					if (fork()) {/*parent*/
						close(s); /*nouveau socket uniquement utilisÃ©par le processus enfant*/ 
					}
					else {
						close(s);
						printf("connexion de %d.%d.%d.%d %d closed\n",
								NIPQUAD(claddr.sin_addr.s_addr), ntohs(claddr.sin_port));
						exit(0);
					}
				}
			}
