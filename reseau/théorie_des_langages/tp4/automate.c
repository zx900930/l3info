#include "automate.h"
#include <stdlib.h>
#include <stdio.h>


automate_t * creer_automate(int n, int k, char *d){  	//n nombres d'états, k nombre de lettres, d 
	
	int i,j;
	automate_t *a;
	a =(automate_t*)malloc(sizeof(automate_t));
	a->n = n;
	a->k= k;
	a->alpha = d;
	a->etats_term = (int*)malloc(n * sizeof(int));
	a->transition= (int **)malloc(n*sizeof(int*));
	for(i = 0; i < n; ++i){
		a->transition[i]=(int*)malloc(k*sizeof(int));
		a->etats_term[i] =0;
		for(j =0; j < k; j++)
			a->transition[i][j] =-1;
	}
return a;
}

void rendre_etat_final(automate_t*a, int p){
	if( p > a->n)
	{
		fprintf(stderr,"erreur valeur supp a %d\n",a->n);
		exit(1);
	}
	a->etats_term[p] = 1;
}

int etat_est_final(automate_t *a, int p){
	if(a->etats_term[p] == 1)
		return 1;
	return 0;

}
void init_transition(automate_t *a, int depart, int arrive, int lettre){
	
	if( a->transition[depart][lettre] == -1)
		a->transition[depart][lettre] = arrive;

}
	
int arrivee_transition(automate_t *a, int depart, int lettre){
	return a->transition[depart][lettre];

}	
void detruire_automate(automate_t* a){
	int i;
	free(a->etats_term);
	for(i = 0; i < a->n; ++i){
		free(a->transition[i]);		
	}
	free(a->transition);
	free(a);
}

void affiche_auto(automate_t *t) {
	int i,j;
	for(i=0;i<t->n; i++) {
		for(j=0;j<t->k; j++) {
			printf("%d ",arrivee_transition(t, i, j));
		}
		printf("\n");
	}

}


int af_dessine(af *a) {
  liste *p_etat;
  liste *p_trans;
  af_arc *arc;
  FILE *fic;
  
  if(a == NULL) return 1;

  fic = fopen(".tmp", "w");
  if (fic == NULL){
      fprintf(stderr, "impossible d'ouvrir le fichier .tmp\n");
      return(0);
  }

  fprintf(fic, "digraph automate {\n");
  fprintf(fic, "graph [margin=\"0,0\"];\n");
  fprintf(fic, "node [shape = circle];\n");
  fprintf(fic, "rankdir=LR;\n");

  
  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv){
      for(p_trans=((af_etat*)(p_etat->val))->trans; p_trans; p_trans=p_trans->suiv){
          arc = p_trans->val;
          fprintf(fic, "%d -> %d [label=\"%d\"];\n", ((af_etat*)(p_etat->val))->n, arc->dest->n, arc->in); 
      }
  }

  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv){
    if(((af_etat*)(p_etat->val))->is_accept){
      if (((af_etat*)(p_etat->val)) == a->init)
	fprintf(fic, "%d [shape=doublecircle style=bold];\n", ((af_etat*)(p_etat->val))->n);
      else
	fprintf(fic, "%d [shape=doublecircle style=solid];\n", ((af_etat*)(p_etat->val))->n);
    }
  }

  
  if(a->init && (a->init->is_accept == 0))
    fprintf(fic, "%d [shape=circle style=bold];\n", a->init->n);
  

  fprintf(fic, "}\n");
  if(fic != stdout)
      fclose(fic);

 if(system("dot .tmp | xdot - &") != 0) {
      fprintf(stderr, "impossible de dessiner l'automate");
      return 0;
  }

  return 1;
}
