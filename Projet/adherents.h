#ifndef ADHERENTS_H_INCLUDED
#define ADHERENTS_H_INCLUDED

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

char message_alert[255];


void            Remplir_Adherent(char fichier[]);
list_Adherents  Charger_Adherents(char fichier[]);
void            afficherListAdherent(Adherent * A);
void            afficherAdherent(Adherent A);
void            Ajouter_Adherent(list_Adherents* list_adh);
Adherent*       Rechercher_Adherent_num(list_Adherents list_adh,int numero);
Adherent*       Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]);
void            Modifier_Adherent(list_Adherents * list_adh,int numero);
void            Sauvegarder_Adherents(char fichier[], list_Adherents list_adh);
void            Supprimer_Adherent(list_Adherents *list_adh, int numero);

#endif // ADHERENTS_H_INCLUDED
