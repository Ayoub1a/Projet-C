#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "adherents.h"
#include "emprunts.h"



//#################################################################  Adherents ################################################################
void Remplir_Adherent(char fichier[]){
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


list_Adherents Charger_Adherents(char fichier[]){
        FILE* fadh = fopen(fichier, "r");
        if(fadh == NULL){
        	strcpy(message_alert, "fichier adherents non trouve");
        	return;
		}
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

void afficherListAdherent(Adherent* A){
        Adherent *ptAdh;
        ptAdh = A;
        while(ptAdh !=NULL){
                printf("%d %s %s %s %s %d\n", ptAdh->don_adh.num_adh, ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, ptAdh->don_adh.emprunt);
                ptAdh = ptAdh->suiv;
        }
}

void afficherAdherent(Adherent A){ // afichages un adherent
    printf("%d %s %s %s %s %d\n", A.don_adh.num_adh, A.don_adh.nom_adh, A.don_adh.prenom_adh, A.don_adh.email, A.don_adh.adresse, A.don_adh.emprunt);
}

void Ajouter_Adherent(list_Adherents* list_adh){
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
        Adherent* ptAdh;
        if(ptAdh = Rechercher_Adherent_num(*list_adh,numero)){
                puts("entrez les nouvelle donnees:");
                puts("numero nom prenom email address emprunt\n");
                scanf("%d %s %s %s %s %d",&(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
        }
}



void Supprimer_Adherent(list_Adherents *list_adh, int numero){
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


