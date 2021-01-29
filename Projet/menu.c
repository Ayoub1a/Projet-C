#include <stdio.h>    // bibliotheque d'interaction avec le sysytem entré/sortie
#include <stdlib.h>   // bibliotheque de definition des fonctions standards (free , malloc , realloc ..)
#include <strings.h>  // bibliotheque de manipulation de chaine de lettres
#include <signal.h>   // detection des signal (Ctrl-C , Ctrl-Z ..)

// des fonctions definis pour le systems d'exploitation linux/Unix/apple
#define Malloc(type) (type *)malloc(sizeof(type))
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define clear() system("clear");
#define NC   "\e[0m"
#define RED  "\e[0;31m"
#define GRN  "\e[0;32m"
#define CYN  "\e[0;36m"
#define REDB "\e[41m"
void color(char a[]) {printf("%s" , a);}
#endif
// des fonctions definis pour le systems d'exploitation linux/Unix/apple
#if defined(_WIN32) || defined(_WIN64)
#define clear() ;system("cls");
#define RED  "color 1"
#define GRN  "color 2"
#define CYN  "color 3"
#define REDB "color 5"
void color(char a[]) {system(a);}
#endif
// inclusion des fichiers .h (headers)
#include "adherents.h"
#include "livres.h"
#include "emrunts.h"

// Prototypes des fonctions
void            Menu(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Livres(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv);

void main(){
	strcpy(message_alert, "");                                                         // Message alert permet de tracer les erreur
        list_livres ma_liste_lv = NULL;                                                    // Initiaisation des liste chaine
        list_Adherents ma_liste_adh = NULL;
        ma_liste_lv = Charger_Livres("Livres.txt");					   // Chargement des listes a partir des fichiers
        ma_liste_adh = Charger_Adherents("Adherents.txt");
        Menu(&ma_liste_adh , &ma_liste_lv);
	return 0;
}


void Menu(list_Adherents * list_adh, list_livres * list_lv) {/*
Fonction : Menu

Variables :
----------

	- Liste_adherants : liste chaine des adherants
	- Liste_Livres : liste chaine des livres

Fonctionnment : 
--------------

Il affiche un menu : 
	- Menu de gestion Adherants
	- Menu de gestion Livres
	- Menu de gestion d'Emprunt
Tant que l'utilisateur n'a pas tappe le lettre 'q' qui veux dire quitter .*/
        char c;
        do {
                clear() ;
                printf("Bonjour !!\n");
                printf("Choisissez entre : \n");
                printf("1. Gestion Adherent.\n");
                printf("2. Gestion livres.\n");
                printf("3. Gestion Emprunt.\n");
                printf("q. Quitter.\n");
            	c = getch();
                //printf("%c" , c);
                switch(c) {
                        case '1':
                                Menu_Adherent(list_adh , list_lv);
                                break;
                        case '2':
                                Menu_Livres(list_adh , list_lv);
                                break;
                        case '3':
                                Menu_Emprunt(list_adh , list_lv);
                                break;
                        case 'q':
                                exit(0);
                                break;
                }
        }while(1);
}


void Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv) {/*
Fonction : Menu

Variables : 
----------
	- Liste_adherants : liste chaine des adherants
	- Liste_Livres : liste chaine des livres

Fonctionnment : 
--------------

Il affiche un menu : 
		Remplir Liste Adherent.
                Charger Liste Adherent.
                Ajouter Adherent.
                Rechercher Adherent.
                Modifier Adherent.
                Supprimer Adherent.
                Sauvegarder Liste Adherent.
                Retourner.
Tant que l'utilisateur n'a pas tappe le lettre 'q' qui veux dire quitter .*/
        char c;
        int z=0;
        do {
                clear();
                if(strcmp(message_alert,"")){
        			printf("message: %s\n", message_alert);
        			strcpy(message_alert, "");
				}
				printf("___________________________________________\n\n");
                printf("Bonjour !!\n");
                printf("Choisissez entre : \n");
                printf("1. Remplir Liste Adherent\n");
                printf("2. Charger Liste Adherent\n");
                printf("3. Ajouter Adherent\n");
                printf("4. Rechercher Adherent\n");
                printf("5. Modifier Adherent\n");
                printf("6. Supprimer Adherent\n");
                printf("7. Sauvegarder Liste Adherent\n");
                printf("q. Quitter.\n");
                printf("r. Retourner.\n");
                c = getch();
                char fichier[20];
                char nom[14];
                int  numero;

                switch(c) {
                    case '1':// Remplir Adherents
                        printf("Entrer le nom du fichier: ");
                        scanf("%s" , fichier);
                        Remplir_Adherent(fichier);
                        break;
                    case '2':// Charger Adherents
                        printf("Entrer le nom du fichier: ");
                        scanf("%s" , fichier);
                        *list_adh = Charger_Adherents(fichier);
                        break;
                    case '3':// ajouter du Adherent ;
                        Ajouter_Adherent(list_adh);
                        break;
                    case '4':// rechercher Adherent ;
                		puts("entrez le nom d'adherent");
                		scanf("%s",nom);
                		while(nom == "\n")scanf("%s",nom);
						Adherent* adh = Rechercher_Adherent_nom(*list_adh ,nom);
						if(adh != NULL)
                        	afficherAdherent(*adh);
						puts("cliquer un botton pour continuer:");
						getch();
                        break;
                    case '5':// Supprimer
                        printf("Enter le numero de l'Adherent a modifier: ");
                        scanf("%d" , &numero);
                        Modifier_Adherent(list_adh , numero);
                        break;
                    case '6':// Supprimer Adherent
                        printf("Entrer le numero: ");
                        scanf("%d" , &numero);
                        Supprimer_Adherent(list_adh ,numero );
                        break;
                    case '7':// Sauvegarder
                        printf("Entrer le nom du fichier de souvegarde: ");
                        scanf("%s" , fichier);
                        Sauvegarder_Adherents(fichier , *list_adh);
                        break;
                    case 'q':// quitter
                    	printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}
void Menu_Livres(list_Adherents * list_adh,list_livres * list_lv) {/*
Fonction : Menu Livres

Variables : 
-----------
	- Liste_adherants : liste chaine des adherants
	- Liste_Livres : liste chaine des livres

Fonctionnment : 
---------------

Il affiche un menu : 
		Remplir Liste livre.
                Charger Liste livre.
                Ajouter livre.
                Rechercher livre.
                Modifier livre.
                Supprimer livre.
                Sauvegarder Liste livre.
		Ordonner livre
                Retourner.
Tant que l'utilisateur n'a pas tappe le lettre 'q' qui veux dire quitter .*/
        char c;
        do {
                clear();
                if(strcmp(message_alert,"")){
        			printf("message: %s\n", message_alert);
        			strcpy(message_alert, "");
				}
				printf("___________________________________________\n\n");
                printf("Bonjour !!\n");
                printf("Choisissez entre \n");
                printf("1. Remplir liste livre\n");
                printf("2. Charger liste livre\n");
                printf("3. Ajouter livre\n");
                printf("4. Rechercher livre\n");
                printf("5. Modifier livre\n");
                printf("6. Supprimer livre\n");
    		printf("7. Ordonner livre\n");
                printf("8. Sauvegarder liste livre.\n");
    		printf("q. Quitter\n");
		printf("r. Retourner\n");
                c = getch();
                //printf("%c" , c);
                char fichier[20];
                char nom[14];
				char cat[14], titre[14];
                int  numero;
                switch(c) {
                    case '1':// Remplir Livre
                        printf("Entrer le nom du fichier: ");
                        scanf("%s" , fichier);
                        Remplir_Livres(fichier);
                        break;
                    case '2':// Charger Livre
                		printf("Entrer le nom du fichier: ");
                        scanf("%s" , fichier);
                        *list_lv = Charger_Livres(fichier);
                        break;
                    case '3':// ajouter du Livre ;
                        Ajouter_Livre(list_lv);
                        break;
                    case '4':// rechercher Livre ;
						printf("Entrer: titre et categorie: ") ;
						scanf("%s %s" , titre , cat);
                        Livre *lv = Rechercher_Livre_cat(*list_lv ,cat , nom);
                        if(lv != NULL)
                        	afficherLivre(*lv);
                        printf("cliquer un botton pour continuer:");
						getch();
						break;
                    case '5':// Modifier livre
                        printf("Enter le numero de la livre a modifier: ");
                        scanf("%d" , &numero);
                    	Modifier_Livre(list_lv , numero);
                		break;
                    case '6':// Supprimer Livre
                        printf("Entrer le numero: ");
                        scanf("%d" , &numero);
                        Supprimer_Livre(list_lv ,numero );
                        break;
					case '7': //Ordonner la liste des livre
							Ordonner_Categorie(list_lv);
							break;
                    case '8':// Sauvegarder
                        printf("Entrer le nom du fichier ou a sauvegarder: ");
                        scanf("%s" , fichier);
                        Sauvegarder_Livres(fichier , *list_lv);
                        break;
                    case 'q':// quitter
                        printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}
void Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv) {/*
Fonction : Menu Emprunt

Variables : 
----------

	- Liste_adherants : liste chaine des adherants
	- Liste_Livres : liste chaine des livres

Fonctionnment : 
--------------

Il affiche un menu : 
		Emprunter.
                Afficher livre emprunte.
                Afficher Adherents emprunteur.
		Rendre livre
                Retourner.
Tant que l'utilisateur n'a pas tappe le lettre 'q' qui veux dire quitter .*/
        char c;
        do {
                clear();
                if(strcmp(message_alert,"")){
        			printf("message: %s\n", message_alert);
        			strcpy(message_alert, "");
				}
				printf("___________________________________________\n\n");
                printf("Bonjour !!\n");
                printf("Choisissez entre : \n");
                printf("1. Emprunter.\n");
                printf("2. Afficher livre emprunte.\n");
                printf("3. Afficher Adherents emprunteur.\n");
                printf("4. Rendre livre.\n");
	       		printf("q. Quitter.\n");
				printf("r. Retourner.\n");
                c = getch();
                //printf("%c" , c);
                char fichier[20];
                char nom[14];
                int  numero;
                switch(c) {
                    case '1':// Remplir Adherents
						printf("Entrer le numero de l'Adherent et du livre:");
						int numero_liv;
						scanf("%d %d" , &numero , &numero_liv);
                        Emprunter(numero , numero_liv, list_lv , list_adh);
                    	break;
					case '2':
						Afficher_livres_Empruntes(*list_lv);
						puts("cliquer un botton pour continuer:");
						getch();
                        break;
                    case '3':
						Afficher_Adherents_emprunteurs(*list_lv , *list_adh);
						puts("cliquer un botton pour continuer:");
						getch();
                        break;
                    case '4':
						printf("Entrer numero du livre: ");
						scanf("%d" , &numero);
						Rendre_livre(list_lv  , list_adh , numero);
                            break;
                    case 'q':// quitter
                        printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}

