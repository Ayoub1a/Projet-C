# Projet-C

typdef struct _Adherant {
  int numero; 
  char nom[14];
  char prenom[14];
  char email[30]; 
  char address{30];
  int emprunt;
} Adherant ;
struct Auteur {
  char nom[14]; 
  char prenom[14];
}
typdef struct _livre {
  int numero;
  char titre[30];
  char categorie[12];
  struct Auteur auteur;
  int num_adherant;
}Livre;
