#pragma one
#include "fonctions.h"

void Commande2(Grille& g, Item**item, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines){
        initialisation_jeu(g, lignes, colonnes, nombre_de_mines);
        triage_mines(g);
        triage_historique(g);
        initialisation_grille(&item, g);
        placage_des_mines(g,item);
        effectuer_coup(g,item);
        cases_adjacentes(g,item);
        affichage_grille(g,item);
}
void Commande3(Grille& g, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines){
        initialisation_jeu(g, lignes, colonnes, nombre_de_mines);
        is_won(g);
}
void Commande4(Grille& g, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines){
        initialisation_jeu(g, lignes, colonnes, nombre_de_mines);
        is_lost(g);
}
void Commande5(Grille& g, Item**item, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines){
        initialisation_jeu(g, lignes, colonnes, nombre_de_mines);
        triage_mines(g);
        triage_historique(g);
        initialisation_grille(&item, g);
        placage_des_mines(g,item);
        effectuer_coup(g,item);
        cases_adjacentes(g,item);
        affichage_grille(g,item);
        nouveau_coup(g);
        triage_historique(g);
        initialisation_grille(&item, g);
        placage_des_mines(g,item);
        effectuer_coup(g,item);
        cases_adjacentes(g,item);
        affichage_grille(g,item);
}