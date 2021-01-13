#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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
#define clear() system("cls");
#define RED  "color 1"
#define GRN  "color 2"
#define CYN  "color 3"
#define REDB "color 5"
void color(char a[]) {
	system(a);
}
#endif
int Menu();
void Menu_Adherant();
void Menu_Livres();
void Menu_Emprunt();
int main() {
	list_livres ma_Liste_lv;
	list_Adherents ma_liste_adh;
        Menu(&ma_liste_adh , &ma_liste_lv);
}
int Menu(list_Adherants * list_adh,list_livres * list_lv) {
	char c;
	do {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez entre : \n");
		printf("1. Gestion adherant.\n");
		printf("2. Gestion livres.\n");
		printf("3. Gestion Emprunt.\n");
    		printf("q. Quitter.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case '1':
				Menu_Adherant();
				break;
			case '2': 
				Menu_Livres();
				break;
			case '3':
				Menu_Emprunt();
				break;
			case 'q': 
				exit(0);
				break;
		}
	}while(1);
	return 0 ;
}
void Menu_Adherant(list_Adherants * list_adh,list_livres * list_lv) {
	/*
void Remplir_Adherent(char fichier[]); //
list_Adherents Charger_Adherents(char fichier[]); //
void afficherAdherent(Adherent * A); //
void Ajouter_Adherent(list_Adherents* list_adh); //
Adherent* Rechercher_Adherent_num(list_Adherents list_adh,int numero); //
Adherent* Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]);//
void Modifier_Adherent(list_Adherents * list_adh,int numero); //
void Sauvegarder_Adherents(char fichier[], list_Adherents list_adh); //
void Supprimer_Adherent(list_Adherents *list_adh, int numero); //
	*/
	char c; 
	do {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez entre : \n");
		printf("1. Remplir adherant.\n");
		printf("2. Charger adherant.\n");
		printf("3. Ajouter Adherant.\n");
		printf("4. Rechercher Adherant.\n");
		printf("5. Modifier Adherant.\n");
		printf("6. Sauvegarder Adherant.\n");
		printf("7. Supprimer Adherant.\n");
    		printf("q. Quitter.\n");
    		printf("r. Retourner.\n");
		c = getchar();
		//printf("%c" , c);
		char fichier[20];
		char nom[14];
		int  numero; 
		switch(c) {
			case '1':// Remplir Adherants
				printf("Entrer le nom du fichier: ")
				scanf("%s" , fichier);
				Remplir_Adherent(fichier);
				break;
			case '2':// Charger Adherants
          			*list_adh = Charger_Adherents(char fichier[]);
				break;
			case '3':// ajouter du Adherant ;
				Ajouter_Adherent(list_adh);
				break;
			case '4':// rechercher Adherant ;
				Rechercher_Adherent_nom(*list_adh ,nom);
				break;
			case '5':// Supprimer
				printf("Enter le numero de l'adherant a modifier: ");
				scanf("%d" , &numero);
				Modifier_Adherent(list_adh , numero);
				break;
			case '6':// Sauvegarder
				printf("Entrer le nom du fichier ou a sauvegarder: ");
				printf("%s" , fichier);
				Sauvegarder_Adherents(fichier , *list_adh);
				break;
			case '7':// Supprimer Adherant
				printf("Entrer le numero: "); 
				scanf("%d" , &numero);
				Supprimer_Adherent(list_adh , )
				break;
			case 'q':// quitter
			        printf("Au revoir");
				exit(0);
		       		break;	       

		}
	}while(c!='r');
}
void Menu_Livres(list_Adherants * list_adh,list_livres * list_lv) {
	/*
void Remplir_Livres(char fichier[]);//done
list_livres Charger_Livres(char fichier[]); //done
void Ajouter_Livre(list_livres* list_lv); //done
Livre* Rechercher_Livre_num(list_livres list_lv,int numero);//done
void Modifier_Livre(list_livres* list_lv,int numero);//done
void Supprimer_Livre(list_livres* list_lv,int numero);//done
Livre Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]);
void Ordonner_Categorie(list_livres* list_lv);//done
void Sauvegarder_Livres(char fichier[] , list_livres);//done
void afficherListeLivres(Livre* L);//done
	*/
	char c; 
	do {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez entre : \n");
		printf("1. Remplir livre.\n");
		printf("2. Charger livre.\n");
		printf("3. Afficher livre.\n");
		printf("4. Ajouter livre.\n");
		printf("5. Rechercher livre.\n");
		printf("6. Modifier livre.\n");
		printf("7. Sauvegarder livre.\n");
		printf("8. Supprimer livre.\n");
    printf("9. Ordonner livre.\n");
    printf("q. Quitter.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
        	break;
			case 50:
					break;
			case 51:
					break;
      case 51:
					break;
      case 51:
					break;
      case 51:
					break;
      case 51:
					break;
		}
	}while(c!=113);
}
void Menu_emprunt(list_Adherants * list_adh,list_livres * list_lv) {
	/*
void Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh ); //
// donner le numero d'Adherent  , rechercher par nom le livre
void Afficher_livres_Empruntes(list_livres list_lv); //
void Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh);//
// eliminer la redendance des emprunteurs
void Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv);//
	*/
	char c; 
	do {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez entre : \n");
		printf("1. Emprunter.\n");
		printf("2. Afficher livre emprunte.\n");
		printf("3. Afficher adherants emprunteur.\n");
		printf("4. Rendre livre.\n");
    printf("q. Quitter.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
					break;
			case 50:
					break;
			case 51:
					break;
      case 52: 
        	break;
		}
	}while(c!=113);
}
//color 
