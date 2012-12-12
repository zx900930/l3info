#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "audioSD.h"
#include <string.h>
#include <sys/socket.h>
#include <ao/ao.h>


//Decode la musique
void decoder(int connected,char recv_data[],char contenu[])
{
	ao_device *device;
	ao_sample_format format;
	int default_driver;

long ret;





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

	char pcmout[4096];
	char musique[1000];
	//on declare un pointeur sur un fichier
	FILE* fichier=NULL;
	
	//on ouvre le fichier ou est le contenu du serveur
	strcpy(musique, "/export/home/users1/licence/licence3/l3info2012/10905775/dm/Liste/");
	strcat(musique, contenu);
	fichier = fopen(musique,"r");
	//si ca a echouer on dit
	if (fichier == NULL) 
	{
		printf("ERREUR FICHIER\n");
		exit(-1);
	}

	OggVorbis_File vf;
	int eof=0;
	int current_section;

	//copie .ogg dans vf
	if(ov_open_callbacks(fichier, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0)
	{
		fprintf(stderr,"Input does not appear to be an Ogg bitstream.\n");
		exit(1);
	}

	


	char **ptr=ov_comment(&vf,-1)->user_comments;
	//vorbis_info *vi=ov_info(&vf,-1);
	

	while(*ptr)
	{
		fprintf(stderr,"%s\n",*ptr);
		++ptr;
	}

	//fprintf(stderr,"\nBitstream is %d channel, %ldHz\n",vi->channels,vi->rate);
	//fprintf(stderr,"Encoded by: %s\n\n",ov_comment(&vf,-1)->vendor);
	

	bzero(recv_data,sizeof(recv_data));

	while(!eof)
	{
		ret=ov_read(&vf,pcmout,sizeof(pcmout),0,2,1,&current_section);
		if (ret == 0) 
		{
			/* EOF */

			eof=1;
		} 
		else if (ret < 0) 
		{
			/* error in the stream.  Not a problem, just reporting it in
			 case we (the app) cares.  In this case, we don't. */
		} 
		else 
		{
		/* we don't bother dealing with sample rate changes, etc, but
		 you'll have to */
	

		
		//fwrite(pcmout,1,ret,stdout);
		ao_play(device,pcmout,ret);

		//fprintf(stderr,"2**************.\n");
		//send(fils_sock, pcmout,ret, 0);
		//printf("%s",pcmout);
		//ao_play(device, pcmout, sizeof(pcmout));
			
		}

	}



	ov_clear(&vf);
	fprintf(stderr,"FIN DU DECODAGE.\n");
}
