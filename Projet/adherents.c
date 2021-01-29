#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "adherents.h"
#include "emprunts.h"

void Remplir_Adherent(char fichier[]){/*
Fonction : Remplir Adherents
Variables : 
---------
	- fichier : chaine de characteres representant le nom du fichier
Fonctionnement :
---------------
Il s'agit de creer une liste des Adherents a partir de donnes fournis dans l'entree 
	- on definie les variable de donné liée a chaque adherent  
	- on boucle jusqu'a atteindre le fin du saisie (jusqua ce que numero = EOF(-1))
	- on ferme le fichier 
*/
        FILE* fadh = fopen(fichier, "a");
        if(fadh == NULL) exit(0);
        int numero;
        char nom[14];
        char prenom[14];
        char email[30];
        char address[30];
        int emprunt = 0;
        do{
                printf("entrez les donnees d' Adherent:\n");
                printf("numero \t nom prenom \t email \t address \t emprunt \n") ;
                scanf("%d %s %s %s %s %d",&numero,nom,prenom,email,address,&emprunt);
                fprintf(fadh, "\n%d %s %s %s %s %d", numero,nom,prenom,email ,address,emprunt);
                puts("entrez 0 pour sortir: ");
                scanf("%d", &numero);
        }while(numero != 0);
        fclose(fadh);
}


list_Adherents Charger_Adherents(char fichier[]){/*
Fonction : Charger Adherents
Variables : 
---------
	- fichier : chaine de characteres representant le nom du fichier
Fonctionnement :
---------------
Il s'agit de creer une liste des Adherents a partir de donnes fournis dans la fichier 
	- on verfiie l'existance du fichier 
	- initialisation du liste chainée de Adherents 
	- on definie les variable de donné liée a chaque Adherent 
	- on boucle jusqu'a atteindre le fin du fichier (jusqua ce que numero = EOF(-1))
	- on ferme le fichier 
*/
        FILE* fadh = fopen(fichier, "r");
        if(fadh == NULL) exit(0);
        list_Adherents ladh = NULL;
        Adherent* prec = NULL;
        rewind(fadh);
        while(!feof(fadh)){
                Adherent* ptAdh = Malloc(Adherent);
                fscanf(fadh, "%d %s %s %s %s %d", &(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh,ptAdh->don_adh.email , ptAdh->don_adh.adresse , &(ptAdh->don_adh.emprunt));
                ptAdh->suiv = NULL;
                if(prec != NULL) prec->suiv = ptAdh;
                prec= ptAdh;
                if(ladh == NULL) ladh  = ptAdh;
        }
        fclose(fadh);
        return ladh;
}

void afficherAdherent(Adherent * Adh){
/*
Fonction : Afficher Liste Adherents

Variables : 
---------

	- Adh : liste chainé des Adherents 

Fonctionnement :
---------------

Il s'agit d'afficher la liste des Adherents
*/
        Adherent *ptAdh;
        ptAdh = Adh;
        while(ptAdh !=NULL){
                printf("%d %s %s %s %s %d\n", ptAdh->don_adh.num_adh, ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, ptAdh->don_adh.emprunt);
                ptAdh = ptAdh->suiv;
        }
}

void Ajouter_Adherent(list_Adherents* list_adh){
/*
Fonction : Ajouter Livre

Variables : 
---------

	- list_adh : pointeur sur une list chainée de adherents

Fonctionnement :
---------------

Il s'agit de la lecture d'un livre a partir de l'enrtée et ajouter a la liste 
*/
        Adherent* ptAdh = *list_adh;
        if(ptAdh == NULL){
                ptAdh = Malloc(Adherent);
                printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
                scanf("%d %s %s %s %s %d", &(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
                *list_adh = ptAdh;
        }else{
                while(ptAdh->suiv != NULL){
                        ptAdh = ptAdh->suiv;
                }
                Adherent *prec = ptAdh;
                ptAdh=Malloc(Adherent) ;
                printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
                scanf("%d %s %s %s %s %d",&(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
                prec->suiv = ptAdh;
        }
}
Adherent* Rechercher_Adherent_num(list_Adherents list_adh,int numero){
/*
Fonction : Rechercher adherent par numero (index)

Variables : 
---------

	- list_adh : list chainée des adherents
	- numero : le numero (index) d'adherent 

Fonctionnement :
---------------

Il s'agit de la recherche iterative du livre en utilisant son numero : 
	- on teste si la liste est vide 
	- un pointeur (temporaire) de recherche
	- une boucle qui s'arrete lorsque la liste est fini (on a attend le dernier element (de suivant = NULL))
	- si l'adherent est trouve on sort de la fonction et le retourne
*/
        if(list_adh == NULL){
                puts("liste vide");
                return NULL;
        }
        Adherent *ptAdh = list_adh;
        while(ptAdh->suiv != NULL){
                if(ptAdh->don_adh.num_adh == numero){
                        return ptAdh;
                }
                ptAdh = ptAdh->suiv;
        }
        printf("Adherent non trouv?e\n");
        return NULL;
}


Adherent * Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]){
/*
Fonction : Rechercher adherents par nom

Variables : 
---------

	- list_adh : list chainée de adherents
	- nom : de l'adherent

Fonctionnement :
---------------

Il s'agit de la recherche iterative du adherents en utilisant son nom : 
	- on teste si la liste est vide 
	- un pointeur (temporaire) de recherche
	- une boucle qui s'arrete lorsque la liste est fini (on a attend le dernier element (de suivant = NULL))
	- si l'adherent est trouve on sort de la fonction et retourne l'adherent 
*/
        if(list_adh == NULL){
                puts("liste vide");
                return NULL;
        }
        Adherent *ptAdh = list_adh;
        while(ptAdh->suiv != NULL){
                if(!strcmp(ptAdh->don_adh.nom_adh , nom)){
                        return ptAdh;
                }
                ptAdh = ptAdh->suiv;
        }
        printf("Adherent non trouv?e\n");
        return NULL;
}




void Modifier_Adherent(list_Adherents * list_adh,int numero){
/*
Fonction : Modifier Adherent 

Variables : 
---------

	- list_adh : list chainée des adherents
	- numero : le numero (index) d'adherent

Fonctionnement :
---------------

Il s'agit de modifier un livre au sein de la liste des adherents  : 
	- on teste si la liste est vide 
	- on cherche le poiteur sur la donne de adherent
	- on lit les nouvelles données 
	- on change les donnes 
*/
        Adherent* ptAdh;
        if(ptAdh=Rechercher_Adherent_num(*list_adh,numero)){
                puts("entrez les nouvelle donnees:");
                puts("numero nom prenom email address emprunt\n");
                scanf("%d %s %s %s %s %d",&(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
        }
}



void Supprimer_Adherent(list_Adherents *list_adh, int numero){
/*
Fonction : Supprimer adherent 

Variables : 
---------

	- list_adh : list chainée d'adherents
	- numero : le numero (index) d'adherent 

Fonctionnement :
---------------

Il s'agit de supprimer un livre au sein de la liste des adherents : 
	- on teste si la liste est vide 
	- si le livre à supprimer est au début de la liste on fait pointer la tete au enregistrement qui le suit et en efface le courant
        - sinon, on fait pointer le precédent sur le suivant en guardant reference sur le courant, et on l'efface après (libèrer l'espace mem).
*/
        if(*list_adh == NULL){
                printf("liste vide\n");
                return;
        }else{
                if((*list_adh)->don_adh.num_adh == numero){
                        Adherent* ptAdh = *list_adh;
                        *list_adh = (*list_adh)->suiv;
                        free(ptAdh);
                }
                else{
                        Adherent * ptAdh = *list_adh;
                        while(ptAdh->suiv != NULL){
                                if(ptAdh->suiv->don_adh.num_adh == numero){
                                        Adherent* t = ptAdh->suiv;
                                        ptAdh->suiv = ptAdh->suiv->suiv;
                                        free(t);
                                        break;
                                }
                                ptAdh = ptAdh->suiv;
                        }
                }
        }
}

void Sauvegarder_Adherents(char fichier[], list_Adherents list_adh){
/*
Fonction : Sauvegarder Adherents

Variables : 
---------

	- list_adh : list chainée de livres .
	- fichier : le nom de fichier . 

Fonctionnement :
---------------

Il s'agit de sauvegarder la liste des adherents  : 
	- on teste si la liste est vide 
*/
        FILE* fadh = fopen(fichier, "w+");
        if(list_adh == NULL){
                puts("liste vide\n");
                return;
        }
        Adherent *ptAdh = list_adh;
        int i=0;
        while(ptAdh){
                if(i==0) i++;
                else fprintf(fadh, "\n");
                fprintf(fadh, "%d %s %s %s %s %d" ,ptAdh->don_adh.num_adh, ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, ptAdh->don_adh.emprunt);
                ptAdh = ptAdh->suiv;
        }
        fclose(fadh);
}

