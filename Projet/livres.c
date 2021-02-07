#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

#include "livres.h"


void Remplir_Livres(char fichier[]){
        /**remplir le fichier des livres manuellement */
        FILE* fLivre = fopen(fichier, "a"); /*ajouter a la fin du fichier*/
        if(fLivre == NULL) exit(0);
        int numero = -1;
        char titre[30];
        char categorie[12];
        char nom[14];
        char prenom[14];
                printf("entrez les donnees du livre:\n");
                puts("cliquez ctrl+c pour sortir: ");
				printf("numero titre categorie nomAuteur prenomAuteur\n");
        do{
                numero = -1;
                signal(2, Interruption);
				scanf("%d %s %s %s %s", &numero, titre, categorie, nom, prenom);
                if(numero != -1) fprintf(fLivre, "\n%d %s %s %s %s %d", numero, titre, categorie, nom, prenom, -1); //emprunteur initialise à -1
        }while(numero != -1);
        fclose(fLivre);
}

list_livres Charger_Livres(char fichier[]){
        /**charger la liste des livres a partir d'un fichier*/
        FILE* fLivres = fopen(fichier, "r");
        if(fLivres == NULL){
        	strcpy(message_alert, "fichier livres non trouve");
        	return;
		}
        list_livres lvr = NULL; //poiteur sur la debut de la liste
        Livre* prec = NULL;
        rewind(fLivres); //positionner le pointeur du fichier au debut
        while(!feof(fLivres)){ //tant que on est pas arrivé a la fin du fichier
                Livre *ptLivre = (Livre*)malloc(sizeof(Livre));
                fscanf(fLivres, "%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                ptLivre->suiv = NULL;
                if(prec != NULL) prec->suiv = ptLivre; //prec doit etre non null pour que prec->next existe
                prec = ptLivre;
                if(lvr == NULL) lvr  = ptLivre; //si lvr est null, ont est entrain de charger le premier livre
        }
        fclose(fLivres);
        strcpy(message_alert, "liste chargee");
        return lvr;
}

void afficherListeLivres(Livre* L){ //afficher une liste des livres ligne par ligne
		Livre *ptLivre;
		ptLivre = L;
        while(ptLivre !=NULL){
                printf("%d %s %s %s %s %d\n", ptLivre->don_lv.num_lv, ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, ptLivre->don_lv.emprunteur);
                ptLivre = ptLivre->suiv;
        }
}

void afficherLivre(Livre L){ //afficher une liste des livres ligne par ligne
    printf("%d %s %s %s %s %d\n", L.don_lv.num_lv, L.don_lv.titre, L.don_lv.categorie, L.don_lv.auteur.nom_aut, L.don_lv.auteur.prenom_aut, L.don_lv.emprunteur);
}

void Ajouter_Livre(list_livres* list_lv){
        /**lit et ajoute une instance de livre dans la liste des livres*/
        Livre *prec, *ptLivre = *list_lv;
        if(ptLivre == NULL){ //si liste est vide
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
                *list_lv = ptLivre;
        }else{ //ajout dans une liste non vide
                while(ptLivre->suiv != NULL){
                        ptLivre = ptLivre->suiv;
                }
                prec = ptLivre; //souvegarder la position precedente pour faire la liaison
                ptLivre = (Livre*) malloc(sizeof(Livre));
                printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur\n");
                scanf("%d %s %s %s %s", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut);
                ptLivre->don_lv.emprunteur = -1;
				prec->suiv = ptLivre;
        }
}

Livre* Rechercher_Livre_num(list_livres list_lv,int numero){ //recherche un livre par numero
        if(list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return NULL;
        }
        Livre *ptLivre = list_lv;
        while(ptLivre->suiv != NULL){
                if(ptLivre->don_lv.num_lv == numero){
                        return ptLivre; //dès qu'on a trouvé le livre on retourne
                }
                ptLivre = ptLivre->suiv;
        }
        strcpy(message_alert,"livre non trouve");
        return NULL;
}

void Modifier_Livre(list_livres* list_lv, int numero){ //modifier les donnees d'un livre dans liste, recherche par nom
        Livre* ptLivre;
        if(*list_lv == NULL){
                strcpy(message_alert,"liste des livres est vide");
                return;
        }
        if(ptLivre = Rechercher_Livre_num(*list_lv, numero)){
                puts("entrez les nouvelle donnees:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
                scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
        }
}

void Supprimer_Livre(list_livres* list_lv, int numero){
        /**supprimer un livre de la liste, recherche par nom
         * si le livre à supprimer est au début de la liste on fait pointer la tete au enregistrement qui le suit et en efface le courant
         * sinon, on fait pointer le precédent sur le suivant en guardant reference sur le courant, et on l'efface après (libèrer l'espace mem).
         * */
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
		if(*list_lv == NULL){
			strcpy(message_alert,"liste des livres est vide");
			return;
		}
        Livre *prec, *courant= *list_lv;
        int size = 0;
        prec = courant;
        /**cette premier boucle while est pour le premier travers et aussi pour calculer la taille de la liste pour l'utiliser après*/
        while(courant->suiv != NULL){ //on traversant la liste des livres
                if(strcmp(courant->don_lv.categorie, courant->suiv->don_lv.categorie) > 0){ //si il y'a mauvais positionnement
                        if(prec == courant){//si on est dans le début de la liste, le precedent et suiv pointent initialement sur la meme position
                                prec = courant->suiv;
                                courant->suiv = courant->suiv->suiv;
                                prec->suiv = courant;
                                *list_lv = prec;
                        }
                        else{ //sinon, prec, et suiv pointent sur des positions consécutives
                                prec->suiv = courant->suiv;
                                courant->suiv = courant->suiv->suiv;
                                prec->suiv->suiv = courant;
                                prec = prec->suiv;
                        }
                }
                else{ //après chaque etération on décale les deux pointeurs
                        prec = courant;
                        courant = courant->suiv;
                }
                size++;
                //on incrément la taille
        }
        //afficherListeLivres(*list_lv);
        while(size > 0){
                /**on fait les autres travers maintenant on décrementant le size
                 * pour ne pas faire des opérations sur les donnees déja ordonnees
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
                //afficherListeLivres(*list_lv);
                //puts("______\n");
        }
}


Livre* Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]){ //on suppose que la liste des ordonnees est trié par categorie
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
