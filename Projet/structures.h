#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


struct donne_Adherent {
  int num_adh;
  char nom_adh[14];
  char prenom_adh[14];
  char email[30];
  char adresse[30];
  int emprunt;
};

typedef struct _Adherent{
  struct donne_Adherent don_adh;
  struct _Adherent *suiv;
}Adherent;

struct Auteur {
  char nom_aut[14];
  char prenom_aut[14];
};

struct donne_livre{
  int num_lv;
  char titre[30];
  char categorie[12];
  struct Auteur auteur;
  int emprunteur; // a intialiser par -1
};

typedef struct _livre {
  struct donne_livre don_lv;
  struct _livre *suiv;
}Livre;


typedef Adherent* list_Adherents;
typedef Livre * list_livres;

extern char message_alert[255];


#endif // STRUCTURES_H_INCLUDED
