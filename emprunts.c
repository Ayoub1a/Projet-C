#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "emprunts.h"

void Afficher_livres_Empruntes(list_livres list_lv){
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
	Livre* ptLivre = Rechercher_Livre_num(*list_lv, numero_lv);
	Adherent* adh = Rechercher_Adherent_num(*list_adh, ptLivre->don_lv.emprunteur);
	adh->don_adh.emprunt -= 1;
	ptLivre->don_lv.emprunteur = -1;
}


void Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh){
	/**on crée une matrice d'indexes dans laquelle on vas enregistrer chaque emprunteur avec les numeros des livres
	 * qu'il a emprunté et par la suite on vas traverser cette matrice en affichant chaque emprunteur avec les livres
	 * qu'il a emprunté.*/
	Livre* ptLivre = list_lv;
	int **index;
	int i, j, taille=0; //taille actuelle de la matrice d'indexes
	while(ptLivre != NULL){ //pour chaque instance de livre
		if(ptLivre->don_lv.emprunteur != -1){ //si le livre est emprunté
			i=0;
			while(i<taille){ //on traverse la matrice des indexes
				if(ptLivre->don_lv.emprunteur == index[i][0]){ //si le numero d'emprunteur existe deja dans la matirice
					j=1;
					while(j<4 && index[i][j] != 0) j++; //on se deplace à une case vide(initisé par 0 avec calloc)
					index[i][j] = ptLivre->don_lv.num_lv;
					break;
				}
				i++;
			}
			if(i==taille){ //si on est a une position vide (emprunteur pas encore ajouté)
				if(taille == 0) index = (int**)malloc((taille+1)*sizeof(int*)); //si le premier ligne a ajouter on fait malloc
				else index = (int**)realloc(index, (taille+1)*sizeof(int*)); //sinon on fait realloc
				index[i] = (int*)calloc(4, sizeof(int));
				//on alloue 4 emplacement pour chaque emprunteur, 1 pour son numero et 3 pour les livres empruntés (max), calloc initiale a 0
				index[i][0] = ptLivre->don_lv.emprunteur; //on assigne le numero d'emprunteur
				index[i][1] = ptLivre->don_lv.num_lv; //on ajour le livre comme premier livre empunté
				taille++; //la taille de la matrice est augmenté par une ligne
			}
		}
		ptLivre = ptLivre->suiv; //livre suivant
	}
	i=0;
	while(i<taille){ //affichage en utilisant la matrice des indexes
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

