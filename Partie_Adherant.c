#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Malloc(type) (type*) malloc(sizeof(type))
struct donne_adherant {
  int numero; 
  char nom[14];
  char prenom[14];
  char email[30]; 
  char address[30];
  int emprunt;
};

typedef struct _Adherant{
  struct donne_adherant don_adh;
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
// Prototypes : 
typedef Adherant* list_adherant;
typedef Livre * list_livre;
void Remplir_Adherant(char fichier[]);
list_adherant Charger_Adherant(char fichier[]);
void afficherAdherant(Adherant * A);
void Ajouter_Adherant(list_adherant* liste);
Adherant* Rechercher_Adherant_num(list_adherant list,int numero); 
Adherant* Rechercher_Adherant(list_adherant list,char nom[]); 
void Modifier_Adherant(list_adherant * list,int numero);
void Sauvegarder_Adherant(char fichier[], list_adherant list);
void Supprimer_Adherant(list_adherant *list, int numero);
void main(){
	//Remplir_Adherant("Adherants.txt");
	list_adherant Adherant_liste = Charger_Adherant("Adherants.txt");
	//Rechercher_Adherant_num(Adherant_liste , 2)
	//Supprimer_Adherant(&Adherant_liste ,2) ;
	Modifier_Adherant(&Adherant_liste , 3);
	//afficherAdherant(Adherant_liste);
	Sauvegarder_Adherant("Adherants.txt", Adherant_liste);
}
void Remplir_Adherant(char fichier[]){
	FILE* fadh = fopen(fichier, "a");
	if(fadh == NULL) exit(0);
	int numero;
	char nom[14];
	char prenom[14];
	char email[30]; 
	char address[30]; 
	int emprunt = 0;
	do{
		printf("entrez les donnees d' adherant:\n");
		printf("\t numero \t nom prenom \t email \t address \t emprunt \n") ;
		scanf("%d %s %s %s %s %d",&numero,nom,prenom,email,address,&emprunt);
		fprintf(fadh, "\n%d %s %s %s %s %d", numero,nom,prenom,email ,address,emprunt);
		puts("entrez 0 pour sortir: ");
		scanf("%d", &numero);
	}while(numero != 0);
	fclose(fadh);
}

list_adherant Charger_Adherant(char fichier[]){
	FILE* fadh = fopen(fichier, "r");
	if(fadh == NULL) exit(0);
	list_adherant ladh = NULL;
	Adherant* prec = NULL;
	rewind(fadh);
	while(!feof(fadh)){
		Adherant* tmp = Malloc(Adherant);
		fscanf(fadh, "%d %s %s %s %s %d", &(tmp->don_adh.numero), tmp->don_adh.nom, tmp->don_adh.prenom,tmp->don_adh.email , tmp->don_adh.address , &(tmp->don_adh.emprunt));
		tmp->next = NULL;
		if(prec != NULL) prec->next = tmp;
		prec= tmp;
		if(ladh == NULL) ladh  = tmp;
	}
	fclose(fadh);
	return ladh;
}

void afficherAdherant(Adherant * A){
	Adherant *tmp;
	tmp = A;
	while(tmp !=NULL){
		printf("%d %s %s %s %s %d\n", tmp->don_adh.numero, tmp->don_adh.nom, tmp->don_adh.prenom, tmp->don_adh.email, tmp->don_adh.address, tmp->don_adh.emprunt);
		tmp = tmp->next;
	}
}

void Ajouter_Adherant(list_adherant* liste){
	Adherant* tmp = *liste;
	if(tmp == NULL){
		tmp = Malloc(Adherant); 
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d", &(tmp->don_adh.numero), tmp->don_adh.nom, tmp->don_adh.prenom, tmp->don_adh.email, tmp->don_adh.address, &(tmp->don_adh.emprunt));
		*liste = tmp;
	}else{
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		Adherant *prec = tmp;
		tmp=Malloc(Adherant) ; 
		printf("entrez les donnees de la livre:\nnumero titre categorie nomAuteur prenomAuteur numAdherent\n");
		scanf("%d %s %s %s %s %d",&(tmp->don_adh.numero), tmp->don_adh.nom, tmp->don_adh.prenom, tmp->don_adh.email, tmp->don_adh.address, &(tmp->don_adh.emprunt));
		prec->next = tmp;
	}
}

Adherant* Rechercher_Adherant_num(list_adherant list,int numero){
	if(list == NULL){
		puts("liste vide");
		return NULL;
	}
	Adherant *pt = list;
	while(pt->next != NULL){
		if(pt->don_adh.numero == numero){
			return pt;
		}
		pt = pt->next;
	}
	printf("Adherant non trouvée\n");
	return NULL;
}
Adherant * Rechercher_Adherant(list_adherant list,char nom[]){
	if(list == NULL){
		puts("liste vide");
		return NULL;
	}
	Adherant *pt = list;
	while(pt->next != NULL){
		if(!strcmp(pt->don_adh.nom , nom)){
			return pt;
		}
		pt = pt->next;
	}
	printf("Adherant non trouvée\n");
	return NULL;
}



void Modifier_Adherant(list_adherant * list,int numero){
	Adherant* tmp;
	if(tmp=Rechercher_Adherant_num(*list,numero)){
		puts("entrez les nouvelle donnees:\n");
		puts("\t nom prenom email address emprunt \n");
		scanf("%d %s %s %s %s %d",&(tmp->don_adh.numero), tmp->don_adh.nom, tmp->don_adh.prenom, tmp->don_adh.email, tmp->don_adh.address, &(tmp->don_adh.emprunt));
	}
}

void Supprimer_Adherant(list_adherant *list, int numero){
	if(*list == NULL){
		printf("liste vide\n");
		return;
	}else{
		if((*list)->don_adh.numero == numero){
			Adherant* tmp = *list;
			*list = (*list)->next;
			free(tmp);
		}
		else{
			Adherant * tmp = *list;
			while(tmp->next != NULL){
				if(tmp->next->don_adh.numero == numero){
					Adherant* t = tmp->next;
					tmp->next = tmp->next->next;
					free(t);
					break;
				}
				tmp = tmp->next;
			}
		}
	}
}
void Sauvegarder_Adherant(char fichier[], list_adherant list){
	FILE* fadh = fopen(fichier, "w+");
	if(list == NULL){
		puts("liste vide\n");
		return;
	}
	Adherant *tmp = list;
	int i=0;
	while(tmp){
		if(i==0) i++;
		else fprintf(fadh, "\n");
		fprintf(fadh, "%d %s %s %s %s %d" ,tmp->don_adh.numero, tmp->don_adh.nom, tmp->don_adh.prenom, tmp->don_adh.email, tmp->don_adh.address, tmp->don_adh.emprunt);
		tmp = tmp->next;
	}
	fclose(fadh);
}


