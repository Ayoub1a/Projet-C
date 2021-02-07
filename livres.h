#ifndef LIVRES_H_INCLUDED
#define LIVRES_H_INCLUDED

#include "structures.h"

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
void 	Interruption();


#endif // LIVRES_H_INCLUDED
