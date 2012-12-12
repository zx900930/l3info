#include"automate2.h"

af *af_elague(af *a)
{
  af_etat **tab_etats;
  int n = af_nb_etats(a);
  liste *l = NULL;
  af_etat *e;
  int delta;
  int *accessible;
  af_arc *t;
  int i;
  liste *l2;
  l2 = NULL;

  af_numerote_etats(a);
  tab_etats = malloc(n * sizeof(af_etat*));
  accessible = malloc(n * sizeof(int));

  for(l = af_get_etats(a); l; l = l->suiv){
    e = l->val;
    tab_etats[e->n] = e;
    accessible[e->n]= 0;
  }
  
  accessible[af_get_etat_init(a)->n]  = 1;
  delta = 1;
  while(delta){
    delta = 0;
    for(i=0; i < n; i++){
      if(accessible[i] == 1){
	accessible[i]++;
	for(l= af_get_trans(tab_etats[i]); l; l = l->suiv){
	  t = l->val;
	  if(accessible[t->dest->n] == 0){
	    delta = 1;
	    accessible[t->dest->n] = 1;
	  }
	}
      }
    }
  }
  for(l=af_get_etats(a); l; l = l->suiv){
    e = l->val;
    if(accessible[e->n]== 0)
      af_libere_etat(e); 
    else
      l2 = liste_ajoute_tete(l2, e);
  }
  liste_libere(af_get_etats(a), NULL); 
  a->etats = l2;
  free(accessible);
  free(tab_etats);
  return a;
}

/*---------------------------------------------------------------------------------*/

af *af_cree_reco(void)
{
  af *a;

  a = malloc(sizeof(af));
  if (a == NULL){
    fprintf(stderr, "erreur d'allocation dans af_cree_reco : interruption !!\n");
    exit(1);
  }
  a->etats = NULL;
  a->init = NULL;
  return a;
}

/*---------------------------------------------------------------------------------*/

af_etat *af_cree_etat(void)
{
  af_etat *e;

  e = malloc(sizeof(af_etat));
  if (e == NULL){
    fprintf(stderr, "erreur d'allocation dans af_cree_etat : interruption !!\n");
    exit(1);
  }
  e->trans = NULL;
  e->n = -1;
  e->is_accept = 0;
  return e;
}

/*---------------------------------------------------------------------------------*/

af_arc  *af_cree_arc(af_etat *orig, int in, af_etat *dest)
{
  af_arc *arc;
  arc = malloc(sizeof(af_arc));
  if (arc == NULL){
    fprintf(stderr, "erreur d'allocation dans af_cree_arc : interruption !!\n");
    exit(1);
  }
  arc->orig = orig;
  arc->in = in;
  arc->dest = dest;
  return arc;
}

/*---------------------------------------------------------------------------------*/

af_arc  *af_enleve_arc(af_etat *orig, int in, af_etat *dest)
{
  liste *p_trans;
  af_arc *t;

  for(p_trans=orig->trans; p_trans; p_trans=p_trans->suiv){
    t = p_trans->val;
    if((t->dest == dest) && (t->in == in))
      break;
  }
  if(p_trans != NULL){
    orig->trans = liste_elimine_maillon(orig->trans, p_trans);
    return t;
  }
  return NULL;
}

af_arc  *af_ajoute_arc(af_etat *orig, int in, af_etat *dest)
{
  af_arc *arc;
  liste *l;
  for(l = af_get_trans(orig); l; l = l->suiv){
    arc = l->val;
    if((arc ->in == in) && (arc->dest == dest))
      return arc;
  }
  
  arc = af_cree_arc(orig, in, dest);
  orig->trans = liste_ajoute_tete(orig->trans, arc);
  return arc;
}

liste *af_get_trans(af_etat *e)
{
  return e->trans;
}

/*---------------------------------------------------------------------------------*/

af_etat *af_nouvel_etat(af *a)
{
  af_etat *e;
  
  e = af_cree_etat();
  a->etats = liste_ajoute_tete(a->etats, e);
  return e;
}

/*---------------------------------------------------------------------------------*/

liste *af_get_etats(af *a)
{
  return a->etats;
}

/*---------------------------------------------------------------------------------*/

void af_set_etat_init(af *a, af_etat *e)
{
  a->init = e;
}

/*---------------------------------------------------------------------------------*/

af_etat *af_get_etat_init(af *a)
{
  return a->init;
}

/*---------------------------------------------------------------------------------*/

int af_is_etat_init(af *a, af_etat *e)
{
  return (a->init == e);
}

/*---------------------------------------------------------------------------------*/

void af_set_etat_accept(af_etat *e)
{
  e->is_accept = 1;
}
/*---------------------------------------------------------------------------------*/

void af_unset_etat_accept(af_etat *e)
{
  e->is_accept = 0;
}

/*---------------------------------------------------------------------------------*/

int af_is_etat_accept(af_etat *e)
{
  return e->is_accept;
}

/*---------------------------------------------------------------------------------*/

af *af_numerote_etats(af *a)
{
  int i = 1;
  liste *p;

  if(a == NULL) return NULL;
  a->init->n = 0;
  for(p=a->etats; p; p=p->suiv){
    if(p->val != a->init)
      ((af_etat*)(p->val))->n = i++;
  }
  return a;
}

/*---------------------------------------------------------------------------------*/

int af_ecrit_txt(char *nom_fic, af *a)
{
  liste *p_etat;
  liste *p_trans;
  af_arc *arc;
  FILE *fic;

  if(a == NULL) return 1;
  
  if(nom_fic == NULL)
    fic = stdout;
  else{
    fic = fopen(nom_fic, "w");
    if (fic == NULL){
      fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fic);
      return(0);
    }
  }
  
  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv){
    if (((af_etat*)(p_etat->val)) == a->init){
      for(p_trans=((af_etat*)(p_etat->val))->trans; p_trans; p_trans=p_trans->suiv){
	arc = p_trans->val;
	fprintf(fic, "%d %d %d\n", ((af_etat*)(p_etat->val))->n, arc->dest->n, arc->in); 
      }
    }
  }
  
  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv){
    if (((af_etat*)(p_etat->val)) != a->init){
      for(p_trans=((af_etat*)(p_etat->val))->trans; p_trans; p_trans=p_trans->suiv){
	arc = p_trans->val;
	fprintf(fic, "%d %d %d\n", ((af_etat*)(p_etat->val))->n, arc->dest->n, arc->in); 
      }
    }
  }
  
  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv){
    if(((af_etat*)(p_etat->val))->is_accept){
      fprintf(fic, "%d\n", ((af_etat*)(p_etat->val))->n);
    }
  }   
  
  if(fic != stdout)
    fclose(fic);
  return 0;
}
/*---------------------------------------------------------------------------------*/

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

  fprintf(fic, "digraph fsm {\n");
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

/*-----------------------------------------------------------*/
int af_nb_etats(af *a)
{
  return liste_longueur(a->etats);
}

/*---------------------------------------------------------------------------------*/

void af_libere_etat(af_etat *etat)
{
  if(etat != NULL){
    liste_libere(etat->trans, free);
    free(etat);
  }
}

/*---------------------------------------------------------------------------------*/

void af_libere(af *a)
{
  if(a!= NULL){
    liste_libere(a->etats, af_libere_etat);
    free(a);
  }
}

/*---------------------------------------------------------------------------------*/

af_etat *af_recherche_etat(af *a, int n)
{
  liste *l;
  af_etat *e;

  for(l=a->etats; l; l = l->suiv){
    e = l->val;
    if(e->n == n) return e;
  }
  return NULL;
}

/*---------------------------------------------------------------------------------*/

af *af_clone(af *a)
{
  af *clone;
  int i;
  liste *p_etat;
  liste *p_trans;
  af_etat *etat_original1, *etat_original2;
  af_etat *etat_clone1, *etat_clone2;
  af_arc *arc_original;

  clone = af_cree_reco();
  /* on cree les etats de l'automate clone */
  for(p_etat=a->etats, i=0; p_etat; p_etat=p_etat->suiv, i++)
    {
      etat_original1 = ((af_etat*)(p_etat->val));
      etat_clone1 = af_nouvel_etat(clone);
      etat_clone1->n = etat_original1->n = i;
      if(etat_original1 == a->init)
	af_set_etat_init(clone, etat_clone1);
      if(etat_original1->is_accept)
	af_set_etat_accept(etat_clone1);

    }
  
  /* on cree les transitions de l'automate clone */
  for(p_etat=a->etats; p_etat; p_etat=p_etat->suiv)
    {
      etat_original1 = ((af_etat*)(p_etat->val));
      etat_clone1 = af_recherche_etat(clone, etat_original1->n);
	
	for(p_trans=etat_original1->trans; p_trans; p_trans=p_trans->suiv)
	  {
	    arc_original = ((af_arc*)(p_trans->val));
	    etat_original2 = arc_original->dest;
	    etat_clone2 = af_recherche_etat(clone, etat_original2->n);
	    af_ajoute_arc(etat_clone1, arc_original->in, etat_clone2);
	  }
    }
  return clone;
}


/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

