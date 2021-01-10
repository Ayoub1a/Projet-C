#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct donne_adherant {
  int numero; 
  char nom[14];
  char prenom[14];
  char email[30]; 
  char address[30];
  int emprunt;
};

typedef struct _Adherant{
  struct donne_adherant;
  struct _Adherant *next;
}Adherant;

struct Auteur {
  char nom[14]; 
  char prenom[14];
};

struct donne_livre{
  int numero;
  char titre[30];
  char categorie[12];
  struct Auteur auteur;
  int num_adherant; // a intialiser par -1
};

typedef struct _livre {
  struct donne_livre d;
  struct _livre *next; 
}Livre;

typedef Adherant* list_adherant;
typedef Livre * list_livre;
void Remplir_Livres(char fichier[]);//done
list_livre Charger_Livres(char fichier[]); //done
void Ajouter_Livre(list_livre* list); //done
Livre* Rechercher_Livre(list_livre list,int numero);//done
void Modifier_Livre(list_livre* list,int numero);//done
void Supprimer_Livre(list_livre* list,int numero);//done
Livre Rechercher_Livre_cat(list_livre list,char categorie[],char titre[]);//done
void Ordonner_Categorie(list_livre* list);//done
void Emprunter(int numero_adherant,int numero_livre); //donner le numero d'adherant  , rechercher par num le livre
void Afficher_livres_Empruntes(list_livre list);
void Rendre_livre(list_livre list,int numero);
void Sauvegarder_Livres(char fichier[] , list_livre);//done
void afficherLivre(Livre* L);//done

//##########################################
void main(){
	Remplir_Livres("Livres.txt");
	list_livre monLivre = Charger_Livres("Livres.txt");
	//Ajouter_Livre(&monLivre);
	//afficherLivre(monLivre);
	printf("\n");
	//Supprimer_Livre(&monLivre, 111);
	//afficherLivre(monLivre);
	//puts("\n");
	Ordonner_Categorie(&monLivre);
	afficherLivre(monLivre);
	printf("\n");
	/*Livre lv = Rechercher_Livre_cat(monLivre,"hyjgh","titre8");
	lv.next = NULL;
	afficherLivre(&lv);
	printf("\n");*/
	//Modifier_Livre(&monLivre,222);
	//afficherLivre(monLivre);
	//printf("\n");
	Sauvegarder_Livres("Livres_output.txt", monLivre);
}
//##########################################

void Remplir_Livres(char fichier[]){
	FILE* fLivre = fopen(fichier, "a");
	if(fLivre == NULL) exit(0);
	int numero;
	char titre[30];
	char categorie[12];
	char nom[14]; 
	char prenom[14];
	int num_adherant;
	do{
		printf("entrez les donnees du livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &numero, titre, categorie, nom, prenom, &num_adherant);
		fprintf(fLivre, "\n%d %s %s %s %s %d", numero, titre, categorie, nom, prenom, num_adherant);
		puts("entrez -1 pour sortir: ");
		scanf("%d", &numero);
	}while(numero != -1);
	fclose(fLivre);
}

list_livre Charger_Livres(char fichier[]){
	FILE* fLivres = fopen(fichier, "r");
	if(fLivres == NULL) exit(0);
	list_livre lvr=NULL;
	Livre* prec = NULL;
	rewind(fLivres);
	while(!feof(fLivres)){
		Livre *tmp = (Livre*)malloc(sizeof(Livre));
		fscanf(fLivres, "%d %s %s %s %s %d", &(tmp->d.numero), tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, &(tmp->d.num_adherant));
		tmp->next = NULL;
		if(prec != NULL) prec->next = tmp; //prec doit etre non null pour que prec->next existe
		prec = tmp;
		if(lvr == NULL) lvr  = tmp;
	}
	afficherLivre(lvr);
	fclose(fLivres);
	return lvr;
}

void afficherLivre(Livre* L){
	Livre *tmp;
	tmp = L;
	while(tmp !=NULL){
		printf("%d %s %s %s %s %d\n", tmp->d.numero, tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, tmp->d.num_adherant);
		tmp = tmp->next;
	}
}

void Ajouter_Livre(list_livre* list){
	Livre* tmp = *list;
	if(tmp == NULL){
		tmp = (Livre*) malloc(sizeof(Livre));
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(tmp->d.numero), tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, &(tmp->d.num_adherant));
		*list = tmp;
	}else{
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		Livre *prec = tmp;
		tmp = (Livre*) malloc(sizeof(Livre));
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(tmp->d.numero), tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, &(tmp->d.num_adherant));
		prec->next = tmp;
	}
}

Livre* Rechercher_Livre(list_livre list,int numero){
	if(list == NULL){
		puts("liste vide");
		return;
	}
	Livre *pt = list;
	while(pt->next != NULL){
		if(pt->d.numero == numero){
			return pt;
		}
		pt = pt->next;
	}
	printf("livre non trouve\n");
	return;
}

void Modifier_Livre(list_livre* list,int numero){
	Livre* tmp;
	if(tmp=Rechercher_Livre(*list,numero)){
		puts("entrez les nouvelle donnees:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(tmp->d.numero), tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, &(tmp->d.num_adherant));
	}
}

void Supprimer_Livre(list_livre* list, int numero){
	if(*list == NULL){
		printf("liste vide\n");
		return;
	}else{
		if((*list)->d.numero == numero){
			Livre* tmp = *list;
			*list = (*list)->next;
			free(tmp);
		}
		else{
			Livre* tmp = *list;
			while(tmp->next != NULL){
				if(tmp->next->d.numero == numero){
					Livre* t = tmp->next;
					tmp->next = tmp->next->next;
					free(t);
					break;
				}
				tmp = tmp->next;
			}
		}
	}
}


void Ordonner_Categorie(list_livre* list){
	Livre *prec, *tmp= *list;
	int size = 0;
	prec = tmp;
	while(tmp->next != NULL){
		if(strcmp(tmp->d.categorie, tmp->next->d.categorie) > 0){
			if(prec == tmp){
				prec = tmp->next;
				tmp->next = tmp->next->next;
				prec->next = tmp;
				*list = prec;
			}
			else{
				prec->next = tmp->next;
				tmp->next = tmp->next->next;
				prec->next->next = tmp;
				prec = prec->next;
			}
		}
		else{
			prec = tmp;
			tmp = tmp->next;
		}
		size++;
		//
	}
	//afficherLivre(*list);
	while(size > 0){
		tmp = *list;
		prec = tmp;
		int i=0;
		while(i < size){
			if(strcmp(tmp->d.categorie, tmp->next->d.categorie) > 0){
				if(prec == tmp){
					prec = tmp->next;
					tmp->next = tmp->next->next;
					prec->next = tmp;
					*list = prec;
				}
				else{
					prec->next = tmp->next;
					tmp->next = tmp->next->next;
					prec->next->next = tmp;
					prec = prec->next;
				}
			}
			else{
				prec = tmp;
				tmp = tmp->next;
			}
			i++;
		}
		size--;
		//afficherLivre(*list);
		//puts("______\n");
	}
}


Livre Rechercher_Livre_cat(list_livre list,char categorie[],char titre[]){ //on suppose que la liste des ordonné par categorie
	Livre* pt = list;
	if(pt == NULL){
		puts("list vide\n");
		return;
	}
	while(pt->next != NULL){
		if(!strcmp(pt->d.categorie, categorie)){
			if(!strcmp(pt->d.titre, titre)){
				return *pt;
			}else{
				pt = pt->next;
				while(!strcmp(pt->d.categorie, categorie)){
					if(!strcmp(pt->d.titre, titre))
						return *pt;
					else
						pt = pt->next;
				}
			}	
		}
		pt = pt->next;
	}
	puts("livre non trouve\n");
}

void Sauvegarder_Livres(char fichier[], list_livre list){
	FILE* fLivre = fopen(fichier, "w+");
	if(list == NULL){
		puts("liste vide\n");
		return;
	}
	Livre *tmp = list;
	int i=0;
	while(tmp){
		if(i==0) i++;
		else fprintf(fLivre, "\n");
		fprintf(fLivre, "%d %s %s %s %s %d", tmp->d.numero, tmp->d.titre, tmp->d.categorie, tmp->d.auteur.nom, tmp->d.auteur.prenom, tmp->d.num_adherant);
		tmp = tmp->next;
	}
	fclose(fLivre);
}


