#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
void clear(); 
int Menu();
void Menu_Adherant();
void Menu_Livres();
void Menu_Emprunt();
int main() {
    Menu();
	return 0 ;
}
int Menu() {
	char c; 
	do {
		clear() ;
		printf("Bonjour !!\n");
		printf("Choisissez nentre : \n");
		printf("1. Gestion adherant.\n");
		printf("2. Gestion livres.\n");
		printf("3. Gestion Emprunt.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
				Menu_Adherant();
				break;
			case 50: 
				Menu_Livres();
				break;
			case 51:
				Menu_Emprunt();
				break;
		}
	}while(c!=113);
	return 0 ;
}
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
void Menu_Adherant() {
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
		printf("4. Afficher Adherant.\n");
		printf("5. Ajouter Adherant.\n");
		printf("6. Rechercher Adherant.\n");
		printf("7. Modifier Adherant.\n");
		printf("8. Sauvegarder Adherant.\n");
		printf("9. Supprimer Adherant.\n");
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
				
				break;
			case 50:
				break;
			case 51:
				break;
		}
	}while(c!=113);
}
void Menu_Livres() {
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
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
				
				break;
			case 50:
				break;
			case 51:
				break;
		}
	}while(c!=113);
}
void Menu_emprunt() {
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
		c = getchar();
		//printf("%c" , c);
		switch(c) {
			case 49:
				
				break;
			case 50:
				break;
			case 51:
				break;
		}
	}while(c!=113);
}
//color 
