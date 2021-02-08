#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "livres.h"


void Remplir_Livres(char fichier[]){
    /*
            Fonction : Remplir livres
    Variables :
    ---------
        - fichier : chaine de characteres representant le nom du fichier
    Fonctionnement :
    ---------------
    Il s'agit de creer une liste des Livres a partir de donnes fournis dans l'entree
        - on definie les variable de donn?li? a chaque livre
        - on boucle jusqu'a atteindre le fin du saisie (jusqua ce que numero = EOF(-1))
        - on ferme le fichier
    */
        FILE* fLivre = fopen(fichier, "a"); /*ajouter a la fin du fichier*/
        if(fLivre == NULL) exit(0);
        int numero = -1;
        char titre[30];
        char categorie[12];
        char nom[14];
        char prenom[14];
                printf("entrez les donnees du livre:\n");
				printf("numero titre categorie nomAuteur prenomAuteur\n");
        do{
                numero = -1;
                signal(2, Interruption);
				scanf("%d %s %s %s %s", &numero, titre, categorie, nom, prenom);
                if(numero != -1) fprintf(fLivre, "\n%d %s %s %s %s %d", numero, titre, categorie, nom, prenom, -1); //emprunteur initialise ?-1
        }while(numero != -1);
        strcpy(message_alert,"remplissage termine");
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
        - initialisation du liste chain? de livres
        - on definie les variable de donn?li? a chaque livre
        - on boucle jusqu'a atteindre le fin du fichier (jusqua ce que numero = EOF(-1))
        - on ferme le fichier
    */
        FILE* fLivres = fopen(fichier, "r");
        if(fLivres == NULL){
        	strcpy(message_alert, "fichier livres non trouve");
        	return;
		}
        list_livres lvr = NULL;
        Livre* prec = NULL;
        rewind(fLivres); //positionner le pointeur du fichier au debut
        while(!feof(fLivres)){
                Livre *ptLivre = (Livre*)malloc(sizeof(Livre));
                fscanf(fLivres, "%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                ptLivre->suiv = NULL;
                if(prec != NULL) prec->suiv = ptLivre;
                prec = ptLivre;
                if(lvr == NULL) lvr  = ptLivre; // la list point sur la premiere case memoire du ptLivre
        }
        fclose(fLivres);
        strcpy(message_alert, "liste chargee");
        return lvr;
}

void afficherListeLivres(Livre* L){ /*
    Fonction : Afficher Liste Livres
    Variables :
    ---------
        - List : liste chain?des livres
    Fonctionnement :
    ---------------
    Il s'agit d'afficher la liste des livres
    */
		Livre *ptLivre;
		ptLivre = L;
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
    Il s'agit d'afficher un livre point? par le variable L
    */
    printf("%d %s %s %s %s %d\n", L.don_lv.num_lv, L.don_lv.titre, L.don_lv.categorie, L.don_lv.auteur.nom_aut, L.don_lv.auteur.prenom_aut, L.don_lv.emprunteur);
}

void Ajouter_Livre(list_livres* list_lv){
           /*
    Fonction : Ajouter Livre
    Variables :
    ---------
        - list_lv : pointeur sur une list chain? de livres
    Fonctionnement :
    ---------------
    Il s'agit de la lecture d'un livre a partir de l'enrt? et ajouter a la liste
    */
        Livre *prec, *ptLivre = *list_lv;
        if(ptLivre == NULL){ //si liste est vide
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                signal(2, Interruption);
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                *list_lv = ptLivre;
                ptLivre->suiv = NULL;
        }else{ //ajout dans une liste non vide
                while(ptLivre->suiv != NULL){
                        ptLivre = ptLivre->suiv;
                }
                prec = ptLivre; //souvegarder la position precedente pour faire la liaison
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                signal(2, Interruption);
                scanf("%d %s %s %s %s", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut);
                ptLivre->don_lv.emprunteur = -1;
				prec->suiv = ptLivre;
				ptLivre->suiv = NULL;
        }
        strcpy(message_alert, "livre ajoute");
}

Livre* Rechercher_Livre_num(list_livres list_lv,int numero){ /*
    Fonction : Rechercher Livre par numero (index)
    Variables :
    ---------
        - list_lv : list chain? de livres
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
        while(ptLivre != NULL){
                if(ptLivre->don_lv.num_lv == numero){
                        return ptLivre; //si on trouve le livre on retourne
                }
                ptLivre = ptLivre->suiv;
        }
        strcpy(message_alert,"livre non trouve");
        return NULL;
}

void Modifier_Livre(list_livres* list_lv, int numero){ /*
    Fonction : Modifier livre
    Variables :
    ---------
        - list_lv : list chain? de livres
        - numero : le numero (index) du livre
    Fonctionnement :
    ---------------
    Il s'agit de modifier un livre au sein de la liste des livres  :
        - on teste si la liste est vide
        - on cherche le poiteur sur la donne de livre
        - on lit les nouvelles donn?s
        - on change les donnes
    */
        Livre* ptLivre;
        if(*list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return;
        }
        if(ptLivre = Rechercher_Livre_num(*list_lv, numero)){
                puts("entrez les nouvelle donnees:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
                signal(2, Interruption);
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
        }
        strcpy(message_alert, "livre modifie");
}

void Supprimer_Livre(list_livres* list_lv, int numero){
    /*
    Fonction : Supprimer livre
    Variables :
    ---------
        - list_lv : list chain? de livres
        - numero : le numero (index) du livre
    Fonctionnement :
    ---------------
    Il s'agit de supprimer un livre au sein de la liste des livres  :
        - on teste si la liste est vide
        - si le livre ?supprimer est au d?ut de la liste on fait pointer la tete au enregistrement qui le suit et en efface le courant
            - sinon, on fait pointer le prec?ent sur le suivant en guardant reference sur le courant, et on l'efface apr? (lib?er l'espace mem).
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
                strcpy(message_alert, "livre supprime");
        }
}


void Ordonner_Livres_Categorie(list_livres* list_lv){/*
    Fonction : Ordonner par Categorie
    Variables :
    ---------
        - list_lv : list chain? de livres
    Fonctionnement :
    ---------------
    Il s'agit d' ordonner la liste des livres par categorie   :
        - on teste si la liste est vide
        - premier parcours pour faire un premier travers et calculer la taille de la liste.
        - une deuxiemme parcours :  on fait les autres travers maintenant on d?rementant le size pour ne pas faire des op?ations sur les donnees d?a ordonnees.
    */
		if(*list_lv == NULL){
			strcpy(message_alert,"liste des livres est vide");
			return;
		}
        Livre *prec, *courant= *list_lv;
        int size = 0;
        prec = courant;
        /**cette premiere boucle while est pour le premier travers et aussi pour calculer la taille de la liste pour l'utiliser apr?*/
        while(courant->suiv != NULL){ //on traversant la liste des livres
                if(strcmp(courant->don_lv.categorie, courant->suiv->don_lv.categorie) > 0){ //si il y'a mauvais positionnement
                        if(prec == courant){//si on est dans le d?ut de la liste, le precedent et suiv pointent initialement sur la meme position
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
                size++;
        }
        while(size > 0){
                /**on fait les autres travers maintenant on d?rementant le size
                 * pour ne pas faire des op?ations sur les donnees d?a ordonnees
                 * */
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


Livre* Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]){
        /*
    Fonction : Rechercher Livre par categorie
    Variables :
    ---------
        - list_lv : list chain? de livres
        - categorie : la categorie qu'on cherche
        - titre : le nom du livre a chercher
    Fonctionnement :
    ---------------
    Il s'agit de la recherche iterative d'un livre en utilisant son categorie et titre :
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
                        /**comme la liste est tri?par cat?orie, tout les livres de la meme categorie
                         * sont dans des positions cons?utives*/
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

void Sauvegarder_Livres(char fichier[], list_livres list_lv){ /*
    Fonction : sauvegarder Livres
    Variables :
    ---------
        - list_lv : list chain? de livres .
        - fichier : le nom de fichier .
    Fonctionnement :
    ---------------
    Il s'agit de sauvegarder la liste des livres  :
        - on teste si la liste est vide
    */
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
        strcpy(message_alert,"souvegarde termine");
        fclose(fLivre);
}

void Interruption()
{
    return;
}
