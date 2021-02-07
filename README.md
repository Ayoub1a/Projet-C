#Gestion d'une Bibliotheque version Linux/Macos/Unix
##Structures
- Structure Adherent :
	Contient les donnes d'un aderents : index , nom , prenom ,email n adresse , emprunt (nombre des livres empruntés) .
- Structure Livres : 
	Contient les donnes d'un livre : index , titre , autheur , emprunteur .
```c
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
```
##Organisation
l'orginsation du projets se fait sur 4 fichiers : 
- gestion\_emprunt.c: il s'agit du programme principale liant les autres partie
- emprunts.c: contient l'ensembles des fonction de manipulation des empunts ,a savoir : rendre , emprunter , Afficher liste emprunteur.
- Adherents.c: contient l'ensemble des fonction de manipulation des adherents.
- Livres.c:  contient l'ensemble des fonctions de manipulation des Livres.
###Adherents
###Livres 
###Emprunts
##Execution
