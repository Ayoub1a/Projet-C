# Projet-C
typdef struct _Adherant {
  int numero; 
  char nom[14];
  char prenom[14];
  char email[30]; 
  char address{30];
  int emprunt;
}Adherant ;
struct Auteur {
  char nom[14]; 
  char prenom[14];
}
typdef struct _livre {
  int numero;
  char titre[30];
  char categorie[12];
  struct Auteur auteur;
  int num_adherant; // a intialiser par -1
}Livre;
#######Structure de fichiers ###########################
            Numero nom Prenom 
#############################################
typedef Adherant* list_adherant;
typedef Livre * list_livre;
list_adherant Charger_Adherant(char fichier[]); // charger le fichier dans une liste chainée
list_livre Charger_Livres(char fichier[]);
void Ajouter_Adherant(list_dherant *list);
void Ajouter_Livre(list_livre* list);
void Modifier_Adherant(list_adherant* list,int numero);
void Modifier_Livre(list_livre* list,int numero);
void Supprimer_Adherant(list_adherant* list,int numero);
void Supprimer_Livre(list_livre* list,int numero);
void Rechercher_Adherant(list_adherant list,char nom[]);
void Rechercher_Livre(list_livre list,char categorie[],char titre[]);
void Ordonner_Categorie(list_livre list);
void Emprunter(int numero_adherant , int numero_livre); // donner le numero d'adherant  , rechercher par nom le livre
void Afficher_livre_Emprunte(list_livre list);
void Afficher_adherant_emprunteur(list_livre list); // eliminer la redendance des emprunteurs
void Rendre_livre(list_livre list,int numero);
void Menu();
