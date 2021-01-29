#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))
#include "livres.h"

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
  int emprunteur; 
};

typedef struct _livre {
  struct donne_livre don_lv;
  struct _livre *suiv;
}Livre;


typedef Adherent* list_Adherents;
typedef Livre * list_livres;

char message_alert[255];

void Remplir_Livres(char fichier[]){/*
Fonction : Remplir livres

Variables : 
---------

	- fichier : chaine de characteres representant le nom du fichier

Fonctionnement :
---------------

Il s'agit de creer une liste des Livres a partir de donnes fournis dans la fichier 
	- on definie les variable de donné liée a chaque livre 
	- on boucle jusqu'a atteindre le fin du saisie (jusqua ce que numero = EOF(-1))
	- on ferme le fichier 
*/
        FILE* fLivre = fopen(fichier, "a"); 								
        int numero = -1;										        
        char titre[30];										                 
        char categorie[12];										        
        char nom[14];										                
        char prenom[14];										         
        printf("---- Entrez les donnees du livre: ");
        printf("		Cliquez ctrl+c pour sortir \n");
	printf("numero | titre | categorie | nomAuteur | prenomAuteur \n");
        do{													
                numero = -1;
                signal(2, Interruption);
		scanf("%d %s %s %s %s", &numero, titre, categorie, nom, prenom);
                if(numero != -1) fprintf(fLivre, "\n%d %s %s %s %s %d", numero, titre, categorie, nom, prenom, -1); //emprunteur initialise à -1
        }while(numero != -1);
        fclose(fLivre);
}

list_livres Charger_Livres(char fichier[]){/*
Fonction : Charger livres

Variables : 
---------

	- fichier : chaine de characteres representant le nom du fichier

Fonctionnement :
---------------

Il s'agit de creer une liste des Livres a partir de donnes fournis dans la fichier 
	- on verfiie l'existance du fichier 
	- initialisation du liste chainée de livres 
	- on definie les variable de donné liée a chaque livre 
	- on boucle jusqu'a atteindre le fin du fichier (jusqua ce que numero = EOF(-1))
	- on ferme le fichier 
*/
        FILE* fLivres = fopen(fichier, "r");
        if(fLivres == NULL){
        	strcpy(message_alert, "fichier livres non trouve");
        	return;
		}
        list_livres livre = NULL; 
        Livre* prec = NULL;
        rewind(fLivres); //positionner le pointeur du fichier au debut
        while(!feof(fLivres)){ 
                Livre *ptLivre = (Livre*)malloc(sizeof(Livre));
                fscanf(fLivres, "%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                ptLivre->suiv = NULL;
                if(prec != NULL) prec->suiv = ptLivre; 
                prec = ptLivre;
                if(livre == NULL) livre  = ptLivre; // la list point sur la premiere case memoire du ptLivre  
        }
        fclose(fLivres);
        strcpy(message_alert, "liste chargee");
        return livre;
}

void afficherListeLivres(Livre* List){ 
/*
Fonction : Afficher Liste Livres

Variables : 
---------

	- L : liste chainé des livres 

Fonctionnement :
---------------

Il s'agit d'afficher la liste des livres
*/
		Livre *ptLivre;
		ptLivre = List;
        while(ptLivre !=NULL){
                printf("%d %s %s %s %s %d\n", ptLivre->don_lv.num_lv, ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, ptLivre->don_lv.emprunteur);
                ptLivre = ptLivre->suiv;
        }
}

void afficherLivre(Livre L){ 
/*
Fonction : Afficher Livre

Variables : 
---------

	- L : un livre 

Fonctionnement :
---------------

Il s'agit d'afficher un livre pointée par le variable L
*/
    printf("%d %s %s %s %s %d\n", L.don_lv.num_lv, L.don_lv.titre, L.don_lv.categorie, L.don_lv.auteur.nom_aut, L.don_lv.auteur.prenom_aut, L.don_lv.emprunteur);
}

void Ajouter_Livre(list_livres* list_lv){
/*
Fonction : Ajouter Livre

Variables : 
---------

	- list_lv : pointeur sur une list chainée de livres

Fonctionnement :
---------------

Il s'agit de la lecture d'un livre a partir de l'enrtée et ajouter a la liste 
*/
        Livre *prec, *ptLivre = *list_lv;
        if(ptLivre == NULL){ 											//si liste est vide
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                *list_lv = ptLivre;
        }else{ 													//ajout dans une liste non vide
                while(ptLivre->suiv != NULL){
                        ptLivre = ptLivre->suiv;
                }
                prec = ptLivre; 										//souvegarder la position precedente pour faire la liaison
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                scanf("%d %s %s %s %s", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut);
                ptLivre->don_lv.emprunteur = -1;
		prec->suiv = ptLivre;
        }
}
Livre* Rechercher_Livre_num(list_livres list_lv,int numero){ 
/*
Fonction : Rechercher Livre par numero (index)

Variables : 
---------

	- list_lv : list chainée de livres
	- numero : le numero (index) du livre 

Fonctionnement :
---------------

Il s'agit de la recherche iterative du livre en utilisant son numero : 
	- on teste si la liste est vide 
	- un pointeur (temporaire) de recherche
	- une boucle qui s'arrete lorsque la liste est fini (on a attend le dernier element (de suivant = NULL))
	- si le livre est trouve on sort de la fonction et retourne le livre 
*/
	if(list_lv == NULL){ 						 
                strcpy(message_alert,"liste des livres est vide");
                return NULL;
        }
        Livre *ptLivre = list_lv;
        while(ptLivre->suiv != NULL){
                if(ptLivre->don_lv.num_lv == numero){
                        return ptLivre;
                }
                ptLivre = ptLivre->suiv;
        }
        strcpy(message_alert,"livre non trouve");
        return NULL;
}

void Modifier_Livre(list_livres* list_lv, int numero){ 
/*
Fonction : Modifier livre 

Variables : 
---------

	- list_lv : list chainée de livres
	- numero : le numero (index) du livre 

Fonctionnement :
---------------

Il s'agit de modifier un livre au sein de la liste des livres  : 
	- on teste si la liste est vide 
	- on cherche le poiteur sur la donne de livre 
	- on lit les nouvelles données 
	- on change les donnes 
*/
        Livre* ptLivre;
        if(*list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return;
        }
        if(ptLivre = Rechercher_Livre_num(*list_lv, numero)){
                puts("Entrez les nouvelle donnees:\n	numero | titre | categorie | nomAuteur | prenomAuteur | numAdherent\n");
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
        }
}

void Supprimer_Livre(list_livres* list_lv, int numero){
/*
Fonction : Supprimer livre 

Variables : 
---------

	- list_lv : list chainée de livres
	- numero : le numero (index) du livre 

Fonctionnement :
---------------

Il s'agit de supprimer un livre au sein de la liste des livres  : 
	- on teste si la liste est vide 
	- si le livre à supprimer est au début de la liste on fait pointer la tete au enregistrement qui le suit et en efface le courant
        - sinon, on fait pointer le precédent sur le suivant en guardant reference sur le courant, et on l'efface après (libèrer l'espace mem).
*/
        if(*list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return;
        }else{
                Livre* ptLivre = *list_lv;
                if(ptLivre->don_lv.num_lv == numero){
                        *list_lv = (*list_lv)->suiv;
                        free(ptLivre);
                }
                else{
                        while(ptLivre->suiv != NULL){
                                if(ptLivre->suiv->don_lv.num_lv == numero){
                                        Livre* t = ptLivre->suiv;
                                        ptLivre->suiv = ptLivre->suiv->suiv;
                                        free(t);
                                        break;
                                }
                                ptLivre = ptLivre->suiv;
                        }
                }
        }
}


void Ordonner_Categorie(list_livres* list_lv){ //tri à bulles par catégorie de la liste des livres
/*
Fonction : Ordonner par Categorie 

Variables : 
---------

	- list_lv : list chainée de livres

Fonctionnement :
---------------

Il s'agit d' ordonner la liste des livres par categorie   : 
	- on teste si la liste est vide 
	- premier parcours pour faire un premier travers et calculer la taille de la liste.
	- une deuxiemme parcours :  on fait les autres travers maintenant on décrementant le size pour ne pas faire des opérations sur les donnees déja ordonnees.
*/
		if(*list_lv == NULL){
			strcpy(message_alert,"liste des livres est vide");
			return;
		}
        Livre *prec, *courant= *list_lv;
        int size = 0;
        prec = courant;
        while(courant->suiv != NULL){ 									//on traversant la liste des livres
                if(strcmp(courant->don_lv.categorie, courant->suiv->don_lv.categorie) > 0){ 		//si il y'a mauvais positionnement
                        if(prec == courant){								//si on est dans le début de la liste, le precedent et suiv pointent initialement sur la meme position
                                prec = courant->suiv;
                                courant->suiv = courant->suiv->suiv;
                                prec->suiv = courant;
                                *list_lv = prec;
                        }
                        else{ 										//sinon, prec, et suiv pointent sur des positions consécutives
                                prec->suiv = courant->suiv;
                                courant->suiv = courant->suiv->suiv;
                                prec->suiv->suiv = courant;
                                prec = prec->suiv;
                        }
                }
                else{ 											//après chaque itération on décale les deux pointeurs
                        prec = courant;
                        courant = courant->suiv;
                }
                size++;											//on incrément la taille
        }
        while(size > 0){
                courant = *list_lv;
                prec = courant;
                int i=0;
                while(i < size){ //de 0 jusqu'a size..
                        if(strcmp(courant->don_lv.categorie, courant->suiv->don_lv.categorie) > 0){
                                if(prec == courant){
                                        prec = courant->suiv;
                                        courant->suiv = courant->suiv->suiv;
                                        prec->suiv = courant;
                                        *list_lv = prec;
                                }
                                else{
                                        prec->suiv = courant->suiv;
                                        courant->suiv = courant->suiv->suiv;
                                        prec->suiv->suiv = courant;
                                        prec = prec->suiv;
                                }
                        }
                        else{
                                prec = courant;
                                courant = courant->suiv;
                        }
                        i++;
                }
                size--;
                strcpy(message_alert,"liste des livres ordonee");
        }
}


Livre* Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]){ //on suppose que la liste des ordonnees est trié par categorie
/*
Fonction : Rechercher Livre par categorie

Variables : 
---------

	- list_lv : list chainée de livres
	- categorie : la categorie qu'on cherche
	- titre : le nom du livre a chercher 

Fonctionnement :
---------------

Il s'agit de la recherche iterative du livre en utilisant son numero : 
	- on teste si la liste est vide 
	- un pointeur (temporaire) de recherche
	- une boucle qui s'arrete lorsque la liste est fini (on a attend le dernier element (de suivant = NULL))
	- si le livre est trouve on sort de la fonction et retourne le livre 
*/
	if(list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return NULL;
        }
        Livre* ptLivre = list_lv;
        while(ptLivre->suiv != NULL){
                if(!strcmp(ptLivre->don_lv.categorie, categorie)){
                        /**comme la liste est trié par catégorie, tout les livres de la meme categorie
                         * sont dans des positions consécutives*/
                        if(!strcmp(ptLivre->don_lv.titre, titre)){
                                return ptLivre;
                        }else{
                                ptLivre = ptLivre->suiv;
                                while(!strcmp(ptLivre->don_lv.categorie, categorie)){
                                        if(!strcmp(ptLivre->don_lv.titre, titre))
                                                return ptLivre;
                                        else
                                                ptLivre = ptLivre->suiv;
                                }
                        }
                }
                ptLivre = ptLivre->suiv;
        }
        strcpy(message_alert,"livre non trouve");
        return NULL;
}

void Sauvegarder_Livres(char fichier[], list_livres list_lv){ //charger les donnees de la liste dans un fichier
        FILE* fLivre = fopen(fichier, "w+");
        if(list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return;
        }
        Livre *ptLivre = list_lv;
        int i=0;
        while(ptLivre){
                if(i==0) i++;
                else fprintf(fLivre, "\n");
                fprintf(fLivre, "%d %s %s %s %s %d", ptLivre->don_lv.num_lv, ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, ptLivre->don_lv.emprunteur);
                ptLivre = ptLivre->suiv;
        }
        fclose(fLivre);
}

void Interruption()
{
    return;
}
