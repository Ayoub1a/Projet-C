# Gestion d'une Bibliotheque version Linux/Macos/Unix
## Structures:
- **Structure Adherent** :
	Contient les donnes d'un aderents : index , nom , prenom ,email n adresse , emprunt (nombre des livres empruntés) .
- **Structure Livres** : 
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
## Organisation:
l'orginsation du projets se fait sur 4 fichiers : 
- **Gestion_emprunt.c**: il s'agit du programme principale liant les autres partie
- **Emprunts.c**: contient l'ensembles des fonction de manipulation des empunts ,a savoir : rendre , emprunter , Afficher liste emprunteur.
- **Adherents.c**: contient l'ensemble des fonction de manipulation des adherents.
- **Livres.c**:  contient l'ensemble des fonctions de manipulation des Livres.
### Adherents:
```c
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
```
### Livres:
```c
void            Remplir_Livres(char fichier[]);//done
list_livres     Charger_Livres(char fichier[]); //done
void            Ajouter_Livre(list_livres* list_lv); //done
Livre*          Rechercher_Livre_num(list_livres list_lv,int numero);//done
void            Modifier_Livre(list_livres* list_lv,int numero);//done
void            Supprimer_Livre(list_livres* list_lv,int numero);//done
Livre*           Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]);
void            Ordonner_Categorie(list_livres* list_lv);//done
void            Sauvegarder_Livres(char fichier[] , list_livres);//done
void            afficherListeLivres(Livre* L);//done
void                    afficherLivre(Livre L);
void    Interruption();
```
### Emprunts:
```c
void            Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh );
void            Afficher_livres_Empruntes(list_livres list_lv);
void            Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh);
void            Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv);
```
### Gestion\_Emprunt:
```c
void            Menu(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Livres(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv);
```
### Dependances:
```make
output: gestion_emprunts.o emprunts.o adherents.o livres.o *.h
        gcc gestion_emprunts.o emprunts.o adherents.o livres.o -o output
livres.o: livres.c livres.h
        gcc -c livres.c
emprunts.o: emprunts.c emprunts.h
        gcc -c emprunts.c
adherents.o: adherents.c adherents.h
        gcc -c adherents.c
gestion_emprunts.o: gestion_emprunts.c *.h
        gcc -c gestion_emprunts.c
```
## Execution
Afin d'esxuter ce programme dans votre terminal : 
```bash
git clone https://github.com/Ayoub-2/Projet-C.git
cd Projet_c 
make 
./ouput
```
