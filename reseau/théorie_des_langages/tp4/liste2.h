#ifndef __LISTE__
#define __LISTE__

typedef struct _liste
{
  void *val;
  struct _liste *suiv;
} liste;

liste *liste_cree(void *val, liste *suiv);
liste *liste_ajoute_tete(liste *l, void *val);
liste *liste_ajoute_queue(liste *l, void *val);
liste *liste_duplique(liste *l);
int liste_longueur(liste *l);
void liste_libere(liste *l, void (*libere_val)(void *));
liste *liste_concatene(liste *l1, liste*l2);
liste *liste_elimine_maillon(liste *l, liste *maillon);


#endif
