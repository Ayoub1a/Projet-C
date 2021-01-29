#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "adherents.h"
#include "emrunts.h"


void color(char a[]) {
        system(a);
}
#endif
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


void Afficher_livres_Empruntes(list_livres list_lv){
/* 
Fonction : Afficheer liste des livres Empruntes 

Variables: 
---------
	- list_lv : liste des livres 
Fonctionnement: 
--------------

il s'agit de lister les livre empruntes cad le numero d'adherant emprunteur est != -1
*/
  Livre * ptr = list_lv;
  while(ptr->suiv != NULL) {
    if (ptr->don_lv.emprunteur != -1) {
     		printf("%d %s %s %s %s %d\n", ptr->don_lv.num_lv, ptr->don_lv.titre, ptr->don_lv.categorie, ptr->don_lv.auteur.nom_aut, ptr->don_lv.auteur.prenom_aut, ptr->don_lv.emprunteur);
    }
    ptr = ptr->suiv;
  }
  return;
}

void Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh ) {
/* 
Fonction : Emprunter Livre 

Variables: 
---------

	- list_lv : liste des livres
	- list_adh : listedes adherents
	- numero_Adherant : numero d'adherants
	- numero_livre : numero de livre
	
Fonctionnement: 
--------------

il s'agit d'emprunter le livre (changer l'attribut emprunteur au numero de cette adherant) a l'adherant (incrementer le nombre des livres empruntes)
	- recherche du livre
	- recherche d'adherant
	- tester si le livre est deja emprunter (l'attribut eprunteur != -1)
	- tester si l'adherant a depasser le nombre maximum (3) des livres
	- emprunter sinon
*/
  Livre* livre =  Rechercher_Livre_num(*list_lv,numero_livre);
  Adherent* adh = Rechercher_Adherent_num(*list_adh,numero_Adherent);
	if (livre->don_lv.emprunteur != -1) {
    	printf("le livre n_%d est deja emprunte\n", numero_livre);
    	return;
	}else {
    if (adh->don_adh.emprunt == 3) {
   		printf("le client n_%d a deja emprunte 3 livres\n", numero_Adherent);
    	return;
    }
    livre->don_lv.emprunteur = numero_Adherent;
	adh->don_adh.emprunt += 1;
	}
	return;
}

void Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv){
/* 
Fonction : Rendre livre  

Variables: 
---------

	- list_lv : liste des livres
	- list_adh : listedes adherents
	- numero_lv : numero de livre
	
Fonctionnement: 
--------------

il s'agit de rendre le livre : 
	- recheche du livre et adherent 
	- decrementer le nombre des livres emprunte par l'adherent
	- changer l'eprunteur de livre a -1
*/
	Livre* ptLivre = Rechercher_Livre_num(*list_lv, numero_lv);
	Adherent* adh = Rechercher_Adherent_num(*list_adh, ptLivre->don_lv.emprunteur);
	adh->don_adh.emprunt -= 1;
	ptLivre->don_lv.emprunteur = -1;
}


void Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh){
/* 
Fonction : Afficher Adherents emprunteurs 

Variables: 
---------

	- list_lv : liste des livres
	- list_adh : listedes adherents

Fonctionnement: 
--------------

il s'agit d'afficher les Adherents emprunteur : 
	  on crée une matrice d'indexes dans laquelle on vas enregistrer chaque emprunteur avec les numeros des livres
	  qu'il a emprunté et par la suite on vas traverser cette matrice en affichant chaque emprunteur avec les livres
	  qu'il a emprunté
*/.
	Livre* ptLivre = list_lv;
	int **index; 							// la matrice 
	int i, j, taille=0; 						//taille actuelle de la matrice d'indexes
	while(ptLivre != NULL){ 					//pour chaque instance de livre
		if(ptLivre->don_lv.emprunteur != -1){ 			//si le livre est emprunté
			i=0;
			while(i<taille){ 				//on traverse la matrice des indexes
				if(ptLivre->don_lv.emprunteur == index[i][0]){ //si le numero d'emprunteur existe deja dans la matirice
					j=1;
					while(j<4 && index[i][j] != 0) j++; //on se deplace à une case vide(initisé par 0 avec calloc)
					index[i][j] = ptLivre->don_lv.num_lv;
					break;
				}
				i++;
			}
			if(i==taille){ 									//si on est a une position vide (emprunteur pas encore ajouté)
				if(taille == 0) index = (int**)malloc((taille+1)*sizeof(int*)); 	//si le premier ligne a ajouter on fait malloc
				else index = (int**)realloc(index, (taille+1)*sizeof(int*)); 		//sinon on fait realloc
				index[i] = (int*)calloc(4, sizeof(int));				//on alloue 4 emplacement pour chaque emprunteur, 1 pour son numero et 3 pour les livres empruntés (max), calloc initiale a 0
				index[i][0] = ptLivre->don_lv.emprunteur; 				//on assigne le numero d'emprunteur
				index[i][1] = ptLivre->don_lv.num_lv; 					//on ajout le livre comme premier livre empunté
				taille++; 								//la taille de la matrice est augmenté par une ligne
			}
		}
		ptLivre = ptLivre->suiv; 								//livre suivant
	}
	i=0;
	while(i<taille){ 										//affichage en utilisant la matrice des indexes
		j=1;
		Adherent* ptAdh = Rechercher_Adherent_num(list_adh, index[i][0]); //
		printf("%s %s:\n",ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh);
		while(j<4 && index[i][j] != 0){
			Livre* lv = Rechercher_Livre_num(list_lv,index[i][j]);
			printf("\t%s\n",lv->don_lv.titre);
			j++;
		}
		i++;
	}
	for(i=0;i<taille;i++){
		free(index[i]);
	};
	free(index);
}

