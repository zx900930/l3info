All: client serveur

client: libaudioCl.so clientTCP.o
	gcc -Wall -lao -ldl -lm clientTCP.o -o client libaudioCl.so 

libaudioCl.so: audioCl.c audioCl.h
	gcc -shared -o libaudioCl.so audioCl.c

clientTCP.o: clientTCP.c
	gcc -c clientTCP.c

serveur: libdiffcomm.so libaudioSD.so serveurTCP.o
	gcc -Wall -lao -ldl -lm -lvorbisfile serveurTCP.o -o serveur libaudioSD.so libdiffcomm.so	

libaudioSD.so: audioSD.c audioSD.h
	gcc -shared -o libaudioSD.so audioSD.c

libdiffcomm.so: diffcomm.c diffcomm.h
	gcc -shared -o libdiffcomm.so diffcomm.c

serveurTCP.o: serveurTCP.c
	gcc -c serveurTCP.c


clean:
	-rm *.o
	-rm *.so
	-rm client
	-rm serveur
