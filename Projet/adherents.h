#ifndef ADHERENTS_H_INCLUDED
#define ADHERENTS_H_INCLUDED

#include "structures.h"

void            Remplir_Adherent(char fichier[]);
list_Adherents  Charger_Adherents(char fichier[]);
void            afficherListAdherent(Adherent * A);
void            afficherAdherent(Adherent A);
void            Ajouter_Adherent(list_Adherents* list_adh);
Adherent*       Rechercher_Adherent_num(list_Adherents list_adh,int numero);
Adherent*       Rechercher_Adherent_nom(list_Adherents list_adh,char nom[]);
void            Modifier_Adherent(list_Adherents * list_adh,int numero);
void            Sauvegarder_Adherents(char fichier[], list_Adherents list_adh);
void            Supprimer_Adherent(list_Adherents *list_adh, int numero);

#endif // ADHERENTS_H_INCLUDED
