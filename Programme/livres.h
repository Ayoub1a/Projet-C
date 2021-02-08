#ifndef LIVRES_H_INCLUDED
#define LIVRES_H_INCLUDED

#include "structures.h"

void            Remplir_Livres(char fichier[]);
list_livres     Charger_Livres(char fichier[]);
void            Ajouter_Livre(list_livres* list_lv);
Livre*          Rechercher_Livre_num(list_livres list_lv,int numero);
void            Modifier_Livre(list_livres* list_lv,int numero);
void            Supprimer_Livre(list_livres* list_lv,int numero);
Livre*           Rechercher_Livre_cat(list_livres list_lv,char categorie[],char titre[]);
void            Ordonner_Livres_Categorie(list_livres* list_lv);
void            Sauvegarder_Livres(char fichier[] , list_livres);
void            afficherListeLivres(Livre* L);
void			afficherLivre(Livre L);
void 	        Interruption();

#endif // LIVRES_H_INCLUDED
