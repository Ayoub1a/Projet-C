#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))

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


void Remplir_Adherent(char fichier[]); //
list_Adherents Charger_Adherents(char fichier[]); //
void afficherAdherent(Adherent * A); //
void Ajouter_Adherent(list_Adherents* list_adh); //
Adherent* Rechercher_Adherent_num(list_Adherents list_adh,int numero); //
Adherent* Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]);//
void Modifier_Adherent(list_Adherents * list_adh,int numero); //
void Sauvegarder_Adherents(char fichier[], list_Adherents list_adh); //
void Supprimer_Adherent(list_Adherents *list_adh, int numero); //

void Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh ); //
// donner le numero d'Adherent  , rechercher par nom le livre
void Afficher_livres_Empruntes(list_livres list_lv); //
void Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh);//
// eliminer la redendance des emprunteurs
void Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv);//
void Menu();



//##########################################
void main(){
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
	/*Livre lv = Rechercher_Livre_cat(ma_Liste_lv,"hyjgh","titre8");
	lv.next = NULL;
	afficherListeLivres(&lv);
	printf("\n");*/
	//Modifier_Livre(&ma_Liste_lv,222);
	//afficherListeLivres(ma_Liste_lv);
	//printf("\n");
	//Sauvegarder_Livres("Livres_output.txt", ma_Liste_lv);
	
	//Remplir_Adherent("Adherents.txt");
	list_Adherents ma_liste_adh = Charger_Adherents("Adherents.txt");
	//afficherAdherent(ma_liste_adh);
	//Ajouter_Adherent(&ma_liste_adh);
	//afficherAdherent(ma_liste_adh);
	//printf("\n");
	//Supprimer_Adherent(&ma_liste_adh, 1);
	//afficherAdherent(ma_liste_adh);
	//puts("\n");
	//odifier_Adherent(&ma_liste_adh, 3);
	/*afficherAdherent(ma_liste_adh);
	Adherent *newadh = Rechercher_Adherent(ma_liste_adh,"nom66");
	newadh->next = NULL;
	puts("\n");
	afficherAdherent(newadh);*/
	//Sauvegarder_Adherent("Adherents_output.txt", ma_liste_adh);
	Emprunter(66 , 55 , &ma_Liste_lv, &ma_liste_adh );
	Emprunter(33 , 77 , &ma_Liste_lv, &ma_liste_adh );
	Emprunter(33 , 60 , &ma_Liste_lv, &ma_liste_adh );
	Emprunter(33 , 55 , &ma_Liste_lv, &ma_liste_adh );
	Emprunter(44 , 10 , &ma_Liste_lv, &ma_liste_adh );
	Emprunter(44 , 11 , &ma_Liste_lv, &ma_liste_adh );
	afficherListeLivres(ma_Liste_lv);
	puts("\n");
	afficherAdherent(ma_liste_adh);
	puts("\n");
	Afficher_livres_Empruntes(ma_Liste_lv);
	/*puts("\n****************");
	Afficher_Adherent_emprunteur(ma_Liste_lv, ma_liste_adh);*/
	Rendre_livre(&ma_Liste_lv ,&ma_liste_adh ,60);
	puts("\n********************\n");
	Afficher_livres_Empruntes(ma_Liste_lv);
	puts("\n********\n");
	afficherListeLivres(ma_Liste_lv);
	afficherAdherent(ma_liste_adh);
	
}
//##########################################




//#################################################################  Livres ################################################################

void Remplir_Livres(char fichier[]){
	/**remplir le fichier des livres manuellement */
	FILE* fLivre = fopen(fichier, "a"); /*ajouter a la fin du fichier*/
	if(fLivre == NULL) exit(0);
	int numero;
	char titre[30];
	char categorie[12];
	char nom[14]; 
	char prenom[14];
	int num_Adherent;
	do{
		printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &numero, titre, categorie, nom, prenom, &num_Adherent);
		fprintf(fLivre, "\n%d %s %s %s %s %d", numero, titre, categorie, nom, prenom, num_Adherent);
		puts("entrez -1 pour sortir: ");
		scanf("%d", &numero);
	}while(numero != -1);
	fclose(fLivre);
}

list_livres Charger_Livres(char fichier[]){
	/**charger la liste des livres a partir d'un fichier*/
	FILE* fLivres = fopen(fichier, "r");
	if(fLivres == NULL) exit(0);
	list_livres lvr = NULL; //poiteur sur la debut de la liste
	Livre* prec = NULL;
	rewind(fLivres); //positionner le pointeur du fichier au debut
	while(!feof(fLivres)){ //tant que on est pas arriv� a la fin du fichier
		Livre *ptLivre = (Livre*)malloc(sizeof(Livre));
		fscanf(fLivres, "%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
		ptLivre->suiv = NULL;
		if(prec != NULL) prec->suiv = ptLivre; //prec doit etre non null pour que prec->next existe
		prec = ptLivre;
		if(lvr == NULL) lvr  = ptLivre; //si lvr est null, ont est entrain de charger le premier livre
	}
	fclose(fLivres);
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

void Ajouter_Livre(list_livres* list_lv){
	/**lit et ajoute une instance de livre dans la liste des livres*/
	Livre *prec, *ptLivre = *list_lv;
	if(ptLivre == NULL){ //si liste est vide
		ptLivre = (Livre*) malloc(sizeof(Livre));
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
		*list_lv = ptLivre;
	}else{ //ajout dans une liste non vide
		while(ptLivre->suiv != NULL){
			ptLivre = ptLivre->suiv;
		}
		prec = ptLivre; //souvegarder la position precedente pour faire la liaison
		ptLivre = (Livre*) malloc(sizeof(Livre));
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
		prec->suiv = ptLivre;
	}
}

Livre* Rechercher_Livre_num(list_livres list_lv,int numero){ //recherche un livre par numero
	if(list_lv == NULL){
		puts("liste vide\n");
		return;
	}
	Livre *ptLivre = list_lv;
	while(ptLivre->suiv != NULL){
		if(ptLivre->don_lv.num_lv == numero){
			return ptLivre; //d�s qu'on a trouv� le livre on retourne
		}
		ptLivre = ptLivre->suiv;
	}
	printf("livre non trouve\n");
}

void Modifier_Livre(list_livres* list_lv, int numero){ //modifier les donnees d'un livre dans liste, recherche par nom
	Livre* ptLivre;
	if(ptLivre=Rechercher_Livre_num(*list_lv,numero)){
		puts("entrez les nouvelle donnees:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(ptLivre->don_lv.num_lv), ptLivre->don_lv.titre, ptLivre->don_lv.categorie, ptLivre->don_lv.auteur.nom_aut, ptLivre->don_lv.auteur.prenom_aut, &(ptLivre->don_lv.emprunteur));
	}
}

void Supprimer_Livre(list_livres* list_lv, int numero){
	/**supprimer un livre de la liste, recherche par nom
	 * si le livre � supprimer est au d�but de la liste on fait pointer la tete au enregistrement qui le suit et en efface le courant
	 * sinon, on fait pointer le prec�dent sur le suivant en guardant reference sur le courant, et on l'efface apr�s (lib�rer l'espace mem).
	 * */
	if(*list_lv == NULL){
		printf("liste vide\n");
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


void Ordonner_Categorie(list_livres* list_lv){ //tri � bulles par cat�gorie de la liste des livres
	Livre *prec, *courant= *list_lv;
	int size = 0;
	prec = courant;
	/**cette premier boucle while est pour le premier travers et aussi pour calculer la taille de la liste pour l'utiliser apr�s*/
	while(courant->suiv != NULL){ //on traversant la liste des livres
		if(strcmp(courant->don_lv.categorie, courant->suiv->don_lv.categorie) > 0){ //si il y'a mauvais positionnement
			if(prec == courant){//si on est dans le d�but de la liste, le precedent et suiv pointent initialement sur la meme position
				prec = courant->suiv;
				courant->suiv = courant->suiv->suiv;
				prec->suiv = courant;
				*list_lv = prec;
			}
			else{ //sinon, prec, et suiv pointent sur des positions cons�cutives
				prec->suiv = courant->suiv;
				courant->suiv = courant->suiv->suiv;
				prec->suiv->suiv = courant;
				prec = prec->suiv;
			}
		}
		else{ //apr�s chaque et�ration on d�cale les deux pointeurs
			prec = courant;
			courant = courant->suiv;
		}
		size++; 
		//on incr�ment la taille
	}
	//afficherListeLivres(*list_lv);
	while(size > 0){
		/**on fait les autres travers maintenant on d�crementant le size
		 * pour ne pas faire des op�rations sur les donnees d�ja ordonnees
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
		//afficherListeLivres(*list_lv);
		//puts("______\n");
	}
}


Livre Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]){ //on suppose que la liste des ordonnees est tri� par categorie
	Livre* ptLivre = list_lv;
	if(ptLivre == NULL){
		puts("list vide\n");
		return;
	}
	while(ptLivre->suiv != NULL){
		if(!strcmp(ptLivre->don_lv.categorie, categorie)){
			/**comme la liste est tri� par cat�gorie, tout les livres de la meme categorie
			 * sont dans des positions cons�cutives*/
			if(!strcmp(ptLivre->don_lv.titre, titre)){
				return *ptLivre;
			}else{
				ptLivre = ptLivre->suiv;
				while(!strcmp(ptLivre->don_lv.categorie, categorie)){
					if(!strcmp(ptLivre->don_lv.titre, titre))
						return *ptLivre;
					else
						ptLivre = ptLivre->suiv;
				}
			}	
		}
		ptLivre = ptLivre->suiv;
	}
	puts("livre non trouve\n");
}

void Sauvegarder_Livres(char fichier[], list_livres list_lv){ //charger les donnees de la liste dans un fichier
	FILE* fLivre = fopen(fichier, "w+");
	if(list_lv == NULL){
		puts("liste vide\n");
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

void afficherAdherent(Adherent * A){
        Adherent *ptAdh;
        ptAdh = A;
        while(ptAdh !=NULL){
                printf("%d %s %s %s %s %d\n", ptAdh->don_adh.num_adh, ptAdh->don_adh.nom_adh, ptAdh->don_adh.prenom_adh, ptAdh->don_adh.email, ptAdh->don_adh.adresse, ptAdh->don_adh.emprunt);
                ptAdh = ptAdh->suiv;
        }
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
        if(ptAdh=Rechercher_Adherent_num(*list_adh,numero)){
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

//============================================ emprunts=============================================================

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
	/**on cr�e une matrice d'indexes dans laquelle on vas enregistrer chaque emprunteur avec les numeros des livres
	 * qu'il a emprunt� et par la suite on vas traverser cette matrice en affichant chaque emprunteur avec les livres
	 * qu'il a emprunt�.*/
	Livre* ptLivre = list_lv;
	int **index;
	int i, j, taille=0; //taille actuelle de la matrice d'indexes
	while(ptLivre != NULL){ //pour chaque instance de livre
		if(ptLivre->don_lv.emprunteur != -1){ //si le livre est emprunt�
			i=0;
			while(i<taille){ //on traverse la matrice des indexes
				if(ptLivre->don_lv.emprunteur == index[i][0]){ //si le numero d'emprunteur existe deja dans la matirice
					j=1;
					while(j<4 && index[i][j] != 0) j++; //on se deplace � une case vide(initis� par 0 avec calloc)
					index[i][j] = ptLivre->don_lv.num_lv;
					break;
				}
				i++;
			}
			if(i==taille){ //si on est a une position vide (emprunteur pas encore ajout�)
				if(taille == 0) index = (int**)malloc((taille+1)*sizeof(int*)); //si le premier ligne a ajouter on fait malloc
				else index = (int**)realloc(index, (taille+1)*sizeof(int*)); //sinon on fait realloc
				index[i] = (int*)calloc(4, sizeof(int));
				//on alloue 4 emplacement pour chaque emprunteur, 1 pour son numero et 3 pour les livres emprunt�s (max), calloc initiale a 0
				index[i][0] = ptLivre->don_lv.emprunteur; //on assigne le numero d'emprunteur
				index[i][1] = ptLivre->don_lv.num_lv; //on ajour le livre comme premier livre empunt�
				taille++; //la taille de la matrice est augment� par une ligne
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

