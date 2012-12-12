#include "audioCl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ao/ao.h>
#include <math.h>

//Affiche la liste des musiques au clients
void liste_musiques(char *son[],int taille)
{
	int i;

	printf("\n******** Voici la liste de musiques disponible ******** \n");
	
	for(i=0;i<taille;i++)
	{
		printf("%d) %s\n",i+1,son[i]);
	}
}

//INUTILE POUR LE MOMENT 
void play_musique(char recv_data[]){


	ao_device *device;
	ao_sample_format format;
	int default_driver;

	/* -- Initialize -- */

	ao_initialize();

	/* -- Setup for default driver -- */

	default_driver = ao_default_driver_id();

        memset(&format, 0, sizeof(format));
	format.bits = 16;
	format.channels = 2;
	format.rate = 44100;
	format.byte_format = AO_FMT_LITTLE;

	/* -- Open driver -- */
	device = ao_open_live(default_driver, &format, NULL /* no options */);
	if (device == NULL) {
		fprintf(stderr, "Error opening device.\n");
		return;
	}


	ao_play(device, recv_data, sizeof(recv_data));

	/* -- Close and shutdown -- */
	ao_close(device);

	ao_shutdown();

}
