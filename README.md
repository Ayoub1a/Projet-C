#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include<signal.h> 


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


void            Remplir_Livres(char fichier[]);//done
list_livres     Charger_Livres(char fichier[]); //done
void            Ajouter_Livre(list_livres* list_lv); //done
Livre*          Rechercher_Livre_num(list_livres list_lv,int numero);//done
void            Modifier_Livre(list_livres* list_lv,int numero);//done
void            Supprimer_Livre(list_livres* list_lv,int numero);//done
Livre*           Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]);
void            Ordonner_Categorie(list_livres* list_lv);//done
void            Sauvegarder_Livres(char fichier[] , list_livres);//done
void            afficherListeLivres(Livre* L);//done
void			afficherLivre(Livre L);
void 			Interruption();

void            Remplir_Adherent(char fichier[]); //
list_Adherents  Charger_Adherents(char fichier[]); //
void            afficherListAdherent(Adherent * A); //
void            afficherAdherent(Adherent A);
void            Ajouter_Adherent(list_Adherents* list_adh); //
Adherent*       Rechercher_Adherent_num(list_Adherents list_adh,int numero); //
Adherent*       Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]);//
void            Modifier_Adherent(list_Adherents * list_adh,int numero); //
void            Sauvegarder_Adherents(char fichier[], list_Adherents list_adh); //
void            Supprimer_Adherent(list_Adherents *list_adh, int numero); //

void            Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh ); //
// donner le numero d'Adherent  , rechercher par nom le livre
void            Afficher_livres_Empruntes(list_livres list_lv); //
void            Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh);//
// eliminer la redendance des emprunteurs
void            Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv);//
void            Menu(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Livres(list_Adherents * list_adh,list_livres * list_lv);
void            Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv);
int main() {
	strcpy(message_alert, "");
        list_livres ma_liste_lv = NULL;
        list_Adherents ma_liste_adh = NULL;
        ma_liste_lv = Charger_Livres("Livres.txt");
        ma_liste_adh = Charger_Adherents("Adherents.txt");
        Menu(&ma_liste_adh , &ma_liste_lv);
	return 0;
}
//##########################################
/*void main(){

        puts("hello");
        //Remplir_Livres("Livres.txt");
        list_livres ma_Liste_lv = Charger_Livres("Livres.txt");
        //list_livres ma_Liste_lv = Charger_Livres("LivresRO.txt");
        //Ajouter_Livre(&ma_Liste_lv);
        //afficherListeLivres(ma_Liste_lv);
        //printf("\n");
        //Supprimer_Livre(&ma_Liste_lv, 111);
        //afficherListeLivres(ma_Liste_lv);
        //puts("\n");
        //Ordonner_Categorie(&ma_Liste_lv);
        //afficherListeLivres(ma_Liste_lv);
        //printf("\n");
        Livre lv = Rechercher_Livre_cat(ma_Liste_lv,"hyjgh","titre8");
        lv.next = NULL;
        afficherListeLivres(&lv);
        printf("\n");
        //Modifier_Livre(&ma_Liste_lv,222);
        //afficherListeLivres(ma_Liste_lv);
        //printf("\n");
        //Sauvegarder_Livres("Livres_output.txt", ma_Liste_lv);

        //Remplir_Adherent("Adherents.txt");
        list_Adherents ma_liste_adh = Charger_Adherents("Adherents.txt");
        //afficherListAdherent(ma_liste_adh);
        //Ajouter_Adherent(&ma_liste_adh);
        //afficherListAdherent(ma_liste_adh);
        //printf("\n");
        //Supprimer_Adherent(&ma_liste_adh, 1);
        //afficherListAdherent(ma_liste_adh);
        //puts("\n");
        //odifier_Adherent(&ma_liste_adh, 3);
        afficherListAdherent(ma_liste_adh);
        Adherent *newadh = Rechercher_Adherent(ma_liste_adh,"nom66");
        newadh->next = NULL;
        puts("\n");
        afficherListAdherent(newadh);
        //Sauvegarder_Adherent("Adherents_output.txt", ma_liste_adh);
        Emprunter(66 , 55 , &ma_Liste_lv, &ma_liste_adh );
        Emprunter(33 , 77 , &ma_Liste_lv, &ma_liste_adh );
        Emprunter(33 , 60 , &ma_Liste_lv, &ma_liste_adh );
        Emprunter(33 , 55 , &ma_Liste_lv, &ma_liste_adh );
        Emprunter(44 , 10 , &ma_Liste_lv, &ma_liste_adh );
        Emprunter(44 , 11 , &ma_Liste_lv, &ma_liste_adh );
        afficherListeLivres(ma_Liste_lv);
        puts("\n");
        afficherListAdherent(ma_liste_adh);
        puts("\n");
        Afficher_livres_Empruntes(ma_Liste_lv);
        puts("\n****************");
        Afficher_Adherent_emprunteur(ma_Liste_lv, ma_liste_adh);
        Rendre_livre(&ma_Liste_lv ,&ma_liste_adh ,60);
        puts("\n********************\n");
        Afficher_livres_Empruntes(ma_Liste_lv);
        puts("\n********\n");
        afficherListeLivres(ma_Liste_lv);
        afficherListAdherent(ma_liste_adh);

}*/
//##########################################




//#################################################################  Livres ################################################################

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

//#################################################################  Adherents ################################################################
void Remplir_Adherent(char fichier[]){ // Remplir les Adherent a du standard  input a un fichier 
        FILE* fadh = fopen(fichier, "a");
        if(fadh == NULL) exit(0);
        int numero=-1;
        char nom[14];
        char prenom[14];
        char email[30]; 
        char address[30];
        int emprunt = 0;
        printf("entrez les donnees d' Adherent :\n");
        puts("cliquez ctrl+c pour sortir");
        printf("numero \t nom prenom \t email \t address \t emprunt \n");
        do{
        		numero = -1;
                signal(2, Interruption);
                scanf("%d %s %s %s %s %d",&numero,nom,prenom,email,address,&emprunt);
                if(numero != -1) fprintf(fadh, "\n%d %s %s %s %s %d", numero,nom,prenom,email ,address,emprunt);
        }while(numero != -1);
        fclose(fadh);
}



list_Adherents Charger_Adherents(char fichier[]){ // charger la liste des Adherent 
        /*
         * la listie ladh pointeur sur un liste chainée des adhaerant 
         */
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
        strcpy(message_alert, "liste charge");
        return ladh;
}

void afficherListAdherent(Adherent *A){ // afichages des Adherents 
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

void Ajouter_Adherent(list_Adherents* list_adh){ // ajout d'un Adherent a une liste 
        Adherent* ptAdh = *list_adh;
        if(ptAdh == NULL){
                ptAdh = Malloc(Adherent); 
                printf("entrez les donnees de l'adherent:\nnumero nom prenom email address emprunt\n");
                scanf("%d %s %s %s %s %d", &(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
                *list_adh = ptAdh;
        }else{
                while(ptAdh->suiv != NULL){
                        ptAdh = ptAdh->suiv;
                }
                Adherent *prec = ptAdh;
                ptAdh=Malloc(Adherent) ; 
                printf("entrez les donnees de l'adherent:\nnumero nom prenom email address emprunt\n");
                scanf("%d %s %s %s %s %d",&(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
                prec->suiv = ptAdh;
        }
}

Adherent* Rechercher_Adherent_num(list_Adherents list_adh,int numero){ // rechercher un Adherent dans la liste
        /*
         * la recherche est de complexite O(n) ou n le nombres des Adherents
         */
        if(list_adh == NULL){
                strcpy(message_alert ,"liste des adherents est vide");
                return NULL;
        }
        Adherent *ptAdh = list_adh;
        while(ptAdh->suiv != NULL){
                if(ptAdh->don_adh.num_adh == numero){
                        return ptAdh;
                }
                ptAdh = ptAdh->suiv;
        }
        strcpy(message_alert,"Adherent non trouve\n");
        return NULL;
}


Adherent * Rechercher_Adherent_nom(list_Adherents list_adh, char nom[]){ // recherche par nom d'un Adherent
        /*
         * la recherche est lineare on return la premier Adherent trouve de meme nom 
         * */
        if(list_adh == NULL){
                strcpy(message_alert, "liste des adherents est vide");
                return NULL;
        }
        Adherent *ptAdh = list_adh;
        while(ptAdh->suiv != NULL){
                if(!strcmp(ptAdh->don_adh.nom_adh , nom)){
                        return ptAdh;
                }
                ptAdh = ptAdh->suiv;
        }
       	strcpy(message_alert,"Adherent non trouve\n");
        return NULL;
}




void Modifier_Adherent(list_Adherents * list_adh,int numero){ // modifier l'Adherent dans la liste 
        Adherent* ptAdh;
        if(ptAdh=Rechercher_Adherent_num(*list_adh,numero)){
                puts("entrez les nouvelle donnees:");
                puts("numero nom prenom email address emprunt\n");
                scanf("%d %s %s %s %s %d",&(ptAdh->don_adh.num_adh), ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, &(ptAdh->don_adh.emprunt));
        }
}



void Supprimer_Adherent(list_Adherents *list_adh, int numero){ // suppresion par numero d'Adherent
        if(*list_adh == NULL){
                strcpy(message_alert, "liste des adherents est vide");
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

void Sauvegarder_Adherents(char fichier[], list_Adherents list_adh){ // suavegarder l'Adherent
        FILE* fadh = fopen(fichier, "w+");
        if(list_adh == NULL){
            	strcpy(message_alert, "liste des adherents est vide");
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

//============================================ emprunts=============================================================

void Afficher_livres_Empruntes(list_livres list_lv){
	if(list_lv == NULL){
		strcpy(message_alert,"liste des livres est vide\n");
		return;
	}
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
	if(*list_lv == NULL){
		strcpy(message_alert,"liste des livres est vide\n");
		return;
	}
	if(*list_adh == NULL){
		strcpy(message_alert, "liste des adherents est vide\n");
		return;
	}
	Livre* livre =  Rechercher_Livre_num(*list_lv,numero_livre);
	Adherent* adh = Rechercher_Adherent_num(*list_adh,numero_Adherent);
	printf("dn empr = %d\n", livre->don_lv.emprunteur);
        if (livre->don_lv.emprunteur != -1) {
        puts("If1");
        sprintf(message_alert, "le livre n_%d est deja emprunte\n", numero_livre);
        puts("If2");
        return;
        }else {
        	puts("else1");
    		if (adh->don_adh.emprunt == 3) {
    			puts("else2");
            	sprintf(message_alert, "le client n_%d a deja emprunte 3 livres\n", numero_Adherent);
        		puts("else3");
				return;
    		}
    		livre->don_lv.emprunteur = numero_Adherent;
        	adh->don_adh.emprunt += 1;
        }
        return;
}

void Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv){
	if(list_lv == NULL){
		strcpy(message_alert,"liste des livres est vide\n");
		return;
	}
	if(list_adh == NULL){
		strcpy(message_alert,"liste des adherents est vide\n");
		return;
	}
	Livre* ptLivre = Rechercher_Livre_num(*list_lv, numero_lv);
	Adherent* adh = Rechercher_Adherent_num(*list_adh, ptLivre->don_lv.emprunteur);
    adh->don_adh.emprunt -= 1;
    ptLivre->don_lv.emprunteur = -1;
}


void Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh){
        /**on crée une matrice d'indexes dans laquelle on vas enregistrer chaque emprunteur avec les numeros des livres
         * qu'il a emprunté et par la suite on vas traverser cette matrice en affichant chaque emprunteur avec les livres
         * qu'il a emprunté.*/
	if(list_lv == NULL){
		strcpy(message_alert,"liste des livres est vide\n");
		return;
	}
	if(list_adh == NULL){
		strcpy(message_alert,"liste des adherents est vide\n");
		return;
	}
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
void Menu(list_Adherents * list_adh, list_livres * list_lv) {
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
void Menu_Adherent(list_Adherents * list_adh,list_livres * list_lv) {
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
void Menu_Livres(list_Adherents * list_adh,list_livres * list_lv) {
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
void Menu_Emprunt(list_Adherents * list_adh,list_livres * list_lv) {
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
