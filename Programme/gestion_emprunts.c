#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include<signal.h>
#include <windows.h>

#include "adherents.h"
#include "emprunts.h"
#include "livres.h"

#define Malloc(type) (type *)malloc(sizeof(type))
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define clear() system("clear");
#define NC   "\e[0m"
#define RED  "\e[0;31m"
#define GRN  "\e[0;32m"
#define CYN  "\e[0;36m"
#define REDB "\e[41m"
void color(char a[]) {
        printf("%s" , a);
}
#endif

#if defined(_WIN32) || defined(_WIN64)
#define clear() ;system("cls");
#define RED  "color 1"
#define GRN  "color 2"
#define CYN  "color 3"
#define REDB "color 5"

#include "adherents.h"
#include "livres.h"
#include "emprunts.h"
#include "structures.h"

void color(char a[]) {
        system(a);
}
#endif




void            Menu(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Livres(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv);

void Resize_win(int width, int heigh){
	SMALL_RECT windowSize = {0 , 0 , width , heigh}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

int main(){
    Resize_win(55,20);
	strcpy(message_alert, "");
    list_livres ma_liste_lv = NULL;
    list_Adherents ma_liste_adh = NULL;
    ma_liste_lv = Charger_Livres("Livres.txt");
    ma_liste_adh = Charger_Adherents("Adherents.txt");
    Menu(&ma_liste_adh , &ma_liste_lv);
	return 0;
}


void Menu(list_Adherents * list_adh, list_livres * list_lv) {
        char c;
        do {
                clear() ;
                printf("| message: ");
                if(strcmp(message_alert,"")){
        			printf("%s", message_alert);
        			strcpy(message_alert, "");
				}
				printf("\n");
                printf("___________________________________________________\n\n");
                printf("|   Choisissez entre : \n");
                printf("|\t1. Gestion Adherent.\n");
                printf("|\t2. Gestion livres.\n");
                printf("|\t3. Gestion Emprunt.\n");
                printf("|\tq. Quitter.\n");
                printf("|\n|\n|\n|\n|\n|\n");
                printf("___________________________________________________\n\n");
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


void Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv) {
        char c;
        do {
                clear();
                printf("| message: ");
                if(strcmp(message_alert,"")){
        			printf("%s", message_alert);
        			strcpy(message_alert, "");
				}
				printf("\n");
				printf("___________________________________________________\n\n");
                printf("|   Choisissez entre : \n");
                printf("|\t1. Remplir Liste Adherent\n");
                printf("|\t2. Charger Liste Adherent\n");
                printf("|\t3. Ajouter Adherent\n");
                printf("|\t4. Rechercher Adherent\n");
                printf("|\t5. Modifier Adherent\n");
                printf("|\t6. Supprimer Adherent\n");
                printf("|\t7. Sauvegarder Liste Adherent\n");
                printf("|\tq. Quitter\n");
                printf("|\tr. Retourner\n");
                printf("|\n");
                printf("___________________________________________________\n\n");
                c = getch();
                char fichier[20];
                char nom[14];
                int  numero;

                switch(c) {
                    case '1':// Remplir Adherents
                        printf("Entrer le nom du fichier: ");
                        signal(2, Interruption);
                        if(scanf("%s" , fichier) == 1);
                        Remplir_Adherent(fichier);
                        break;
                    case '2':// Charger Adherents
                        printf("Entrer le nom du fichier: ");
                        signal(2, Interruption);
                        if(scanf("%s" , fichier) == 1);
                        *list_adh = Charger_Adherents(fichier);
                        break;
                    case '3':// ajouter du Adherent ;
                        Ajouter_Adherent(list_adh);
                        break;
                    case '4':// rechercher Adherent ;
                		puts("entrez le nom d'adherent");
                		signal(2, Interruption);
                		if(scanf("%s",nom) == 1){;
                            while(nom == "\n")scanf("%s",nom);
                            Adherent* adh = Rechercher_Adherent_nom(*list_adh ,nom);
                            if(adh != NULL)
                                afficherAdherent(*adh);
                            puts("cliquer un boutton pour continuer:");
                            getch();
						}
                        break;
                    case '5':// Modifier
                        printf("Enter le numero de l'Adherent a modifier: ");
                        signal(2, Interruption);
                        if(scanf("%d" , &numero) == 1);
                        Modifier_Adherent(list_adh , numero);
                        break;
                    case '6':// Supprimer Adherent
                        printf("Entrer le numero: ");
                        signal(2, Interruption);
                        if(scanf("%d" , &numero) == 1);
                        Supprimer_Adherent(list_adh ,numero );
                        break;
                    case '7':// Sauvegarder
                        printf("Entrer le nom du fichier de souvegarde: ");
                        signal(2, Interruption);
                        if(scanf("%s" , fichier) == 1);
                        Sauvegarder_Adherents(fichier , *list_adh);
                        break;
                    case 'q':// quitter
                    	printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}
void Menu_Livres(list_Adherents * list_adh,list_livres * list_lv) {
        char c;
        do {
                clear();
                printf("| message: ");
                if(strcmp(message_alert,"")){
        			printf("%s", message_alert);
        			strcpy(message_alert, "");
				}
				printf("\n");
				printf("___________________________________________________\n\n");
                printf("|   Choisissez entre : \n");
                printf("|\t1. Remplir liste livre\n");
                printf("|\t2. Charger liste livre\n");
                printf("|\t3. Ajouter livre\n");
                printf("|\t4. Rechercher livre\n");
                printf("|\t5. Modifier livre\n");
                printf("|\t6. Supprimer livre\n");
    			printf("|\t7. Ordonner livre\n");
                printf("|\t8. Sauvegarder liste livre\n");
    			printf("|\tq. Quitter\n");
				printf("|\tr. Retourner\n");
				printf("___________________________________________________\n\n");
                c = getch();
                //printf("%c" , c);
                char fichier[20];
                char nom[14];
				char cat[14], titre[14];
                int  numero;
                switch(c) {
                    case '1':// Remplir Livre
                        printf("Entrer le nom du fichier: ");
                        signal(2, Interruption);
                        if(scanf("%s" , fichier == 1));
                        Remplir_Livres(fichier);
                        break;
                    case '2':// Charger Livre
                		printf("Entrer le nom du fichier: ");
                		signal(2, Interruption);
                        if(scanf("%s" , fichier) == 1);
                        *list_lv = Charger_Livres(fichier);
                        break;
                    case '3':// ajouter du Livre ;
                        Ajouter_Livre(list_lv);
                        break;
                    case '4':// rechercher Livre ;
						printf("Entrer: titre et categorie: ");
						signal(2, Interruption);
						if(scanf("%s %s" , titre , cat) == 1);
                        Livre *lv = Rechercher_Livre_cat(*list_lv ,cat , nom);
                        if(lv != NULL)
                        	afficherLivre(*lv);
                        printf("cliquer un boutton pour continuer:");
						getch();
						break;
                    case '5':// Modifier livre
                        printf("Enter le numero de la livre a modifier: ");
                        signal(2, Interruption);
                        if(scanf("%d" , &numero) == 1);
                    	Modifier_Livre(list_lv , numero);
                		break;
                    case '6':// Supprimer Livre
                        printf("Entrer le numero: ");
                        signal(2, Interruption);
                        if(scanf("%d" , &numero) == 1);
                        Supprimer_Livre(list_lv ,numero );
                        break;
					case '7': //Ordonner la liste des livre
							Ordonner_Livres_Categorie(list_lv);
							break;
                    case '8':// Sauvegarder
                        printf("Entrer le nom du fichier ou a sauvegarder: ");
                        signal(2, Interruption);
                        if(scanf("%s" , fichier) == 1);
                        Sauvegarder_Livres(fichier , *list_lv);
                        getch();
                        break;
                    case 'q':// quitter
                        printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}
void Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv) {
        char c;
        do {
                clear();
                printf("| message: ");
                if(strcmp(message_alert,"")){
        			printf("%s", message_alert);
        			strcpy(message_alert, "");
				}
				printf("\n");
				printf("___________________________________________________\n\n");
                printf("|   Choisissez entre : \n");
                printf("|\t1. Emprunter\n");
                printf("|\t2. Afficher livre emprunte\n");
                printf("|\t3. Afficher Adherents emprunteur\n");
                printf("|\t4. Rendre livre\n");
	       		printf("|\tq. Quitter\n");
				printf("|\tr. Retourner\n");
				printf("|\n|\n|\n|\n");
				printf("___________________________________________________\n\n");

                c = getch();
                //printf("%c" , c);
                char fichier[20];
                char nom[14];
                int  numero;
                switch(c) {
                    case '1':// Remplir Adherents
						printf("Entrer le numero de l'Adherent et du livre:");
						int numero_liv;
						signal(2, Interruption);
						if(scanf("%d %d" , &numero , &numero_liv) == 1);
                        Emprunter(numero , numero_liv, list_lv , list_adh);
                    	break;
					case '2':
						Afficher_livres_Empruntes(*list_lv);
						puts("cliquer un boutton pour continuer:");
						getch();
                        break;
                    case '3':
						Afficher_Adherents_emprunteurs(*list_lv , *list_adh);
						puts("cliquer un boutton pour continuer:");
						getch();
                        break;
                    case '4':
						printf("Entrer numero du livre: ");
						signal(2, Interruption);
						if(scanf("%d" , &numero) == 1);
						Rendre_livre(list_lv  , list_adh , numero);
                            break;
                    case 'q':// quitter
                        printf("Au revoir");
                        exit(0);
                        break;
                }
        }while(c!='r');
}

