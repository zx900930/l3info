#ifndef __AF__
#define __AF__

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"liste2.h"

#define EPSILON 0
#define NOSYM -1

typedef struct 
{
  int n;          /* numéro de l'état */
  liste *trans;   /* liste des transitions sortantes */
  int est_final;  /* est ce un état d'acceptation ? */
} af_etat;

typedef struct
{
  int in;        /* le symbole */
  af_etat *orig; /* l'état origine */
  af_etat *dest; /* l'état destination */
} af_arc;

typedef struct
{
  liste *etats;  /* la liste des états */
  af_etat *init; /* l'état initial */
} af;

af      *af_cree_reco(void);
af_etat *af_cree_etat(void);
af_arc  *af_cree_arc(af_etat *orig, int in, af_etat *dest);
af_arc  *af_ajoute_arc(af_etat *orig, int in, af_etat *dest);
af_arc  *af_enleve_arc(af_etat *orig, int in, af_etat *dest);
void     af_set_etat_accept(af_etat *e);
void     af_unset_etat_accept(af_etat *e);
af_etat *af_nouvel_etat(af *a);
liste   *af_get_etats(af *a);
liste   *af_get_trans(af_etat *e);
void     af_set_etat_init(af *a, af_etat *e);
af_etat *af_get_etat_init(af *a);
int      af_is_etat_init(af *a, af_etat *e);
void     af_ajoute_etat_accept(af *a, af_etat *e);
af      *af_numerote_etats(af *a);
int      af_ecrit_txt(char *nom_fic, af *a);
int      af_dessine(af *a);
int      af_nb_etats(af *a);
void     af_libere_etat(af_etat *etat);
void     af_libere(af *a);
af      *af_clone(af *a);
af_etat *af_recherche_etat(af *a, int n);
int      af_is_etat_accept(af_etat *e);
af      *af_elague(af *a);

#endif


















/*-----------------------------------------------------------*/

af      *af_cree_reco(void);
af_etat *af_cree_etat(void);
af_arc  *af_cree_arc(af_etat *orig, int in, af_etat *dest);
af_arc  *af_ajoute_arc(af_etat *orig, int in, af_etat *dest);
af_arc  *af_enleve_arc(af_etat *orig, int in, af_etat *dest);
void     af_set_etat_accept(af_etat *e);
void     af_unset_etat_accept(af_etat *e);
af_etat *af_nouvel_etat(af *a);
liste   *af_get_etats(af *a);
liste   *af_get_trans(af_etat *e);
void     af_set_etat_init(af *a, af_etat *e);
af_etat *af_get_etat_init(af *a);
int      af_is_etat_init(af *a, af_etat *e);
void     af_ajoute_etat_accept(af *a, af_etat *e);
af      *af_numerote_etats(af *a);
int      af_ecrit_txt(char *nom_fic, af *a);
int      af_dessine(af *a);
int      af_nb_etats(af *a);
void     af_libere_etat(af_etat *etat);
void     af_libere(af *a);
af      *af_clone(af *a);
af_etat *af_recherche_etat(af *a, int n);
int      af_is_etat_accept(af_etat *e);
af      *af_elague(af *a);


#endif
