#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024
char buf [BUFSIZE +1];

int main (int argc, char *argv[])  //Arguments traités
{
	int s;
	struct sockaddr_in addr;
	char *p;

	if (arg !=3){
		fprintf (stderr, "Usage: %s <address> <port>\n", argv[0]);
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons (atoi (argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);

/*socket*/
	if (((s = socket (AF_INET), SOCK_STREAM, 0)) <0){
		perror ("socket");
		exit(1);
	}

/*connect*/
	if (connect(s, (struct sockaddr *)&addr, sizeof(addr))){
		perror ("connect");
		exit(1);
	}

/*write*/
	buf [BUFSIZE] =0;
	while (fgets (buf, BUFSIZE, stdin) !=NULL){
		if (while(s, buf, strlen(buf)) ==0){
			perror ("write");
			break;
		}
	}
	close (s);
	exit(0);
}
