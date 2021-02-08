#ifndef EMPRUNTS_H_INCLUDED
#define EMPRUNTS_H_INCLUDED

#include "structures.h"


void            Emprunter(int numero_Adherent , int numero_livre ,list_livres * list_lv , list_Adherents *list_adh );
void            Afficher_livres_Empruntes(list_livres list_lv);
void            Afficher_Adherents_emprunteurs(list_livres list_lv, list_Adherents list_adh);
void            Rendre_livre(list_livres *list_lv ,list_Adherents* list_adh ,int numero_lv);

#endif // EMPRUNTS_H_INCLUDED
