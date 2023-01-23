#include<iostream>  // Bibliothèque input output stream permettant la gestion du flux d'entrée sortie
#include<ctime>     // Bibliothèque ctime permettant de generer des nombres aléatoires
#include<cassert>   // Bibliothèque cassert pour verifier des conditions et stopper le programme si elle ne sont pas respectée

using namespace std; // permet de ne pas avoir à écrire "std::" à chaque utilisation d'une fonction iostream

#define TAILLE 100

typedef char Item;   // Le nouveau type "Item" correspond a un caractère unique et permettra une meilleure lisibilitée du code

enum Coup { MARQUER = 'M', DEMASQUER = 'D' }; // Enumération des coups possible d'une case dans une structure "Case"

enum Case { MINE = 'm', VIDE = ' ', MASQUE = '.', MARQUE = 'x'}; // Enumération des état possible d'une case dans une structure "Case"


// Structure Grille qui va contenir les informations relative a la grille
struct Grille {
    unsigned int lignes = 0;
    unsigned int colonnes = 0;
    unsigned int nombre_de_mines = 0;
    unsigned int nombre_de_coups = 0;
    int positionMines[TAILLE]; // Tableau d'entier qui contient la position de chaque mine
    int positionCoups[TAILLE];  // Tableau d'entier qui contient le/les numéro.s des cases que l'on marque ou démasque
    char coups[TAILLE]; // Tableau de caractère qui contient les lettres des coups que l'on souhaite faire, M ou D
};



/*
* @brief Renvoie une liste d'entier correspondand respectivement aux nombre de lignes, de colonnnes, de mines et génère aléatoirement leurs position
* @param [in] lignes, colonnes, nombre de mines
* @param [out] nombre de ligne, de colonne et de mine ainsi que leurs positions générée
*/
void Commande1(unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines);


/*
* @brief Initialise la structure Grille avec le nombre de lignes, de colonnes, de mines et leurs positions
* @param [in] Grille& g, lignes, colonnes, nombre de mines
*/
void initialisation_jeu(Grille& g, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines);


/*
* @brief Trie les coups dans l'ordre croissant par rapport a la case visée.
* @param [in] Grille& g
*/
void triage_historique(Grille& g);


/*
* @brief Crée la base de la grille en initialisant une matrice
* @param [in] Item** it, Grille& g
*/
void initialisation_grille(Item*** it, Grille& g);


/*
* @brief Trie les mines dans l'ordre du plus petit au plus grand
* @param [in] Grille& g
*/
void triage_mines(Grille& g);


/*
* @brief Place les mines dans la grille de jeu
* @param [in] Grille& g, Structure Item
*/
void placage_des_mines(Grille& g, Item** it);


/*
* @brief Fonction permettant de marquer ou demasquer une case
* @param [in] Grille& g, Strucutre Item
*/
void effectuer_coup(Grille& g, Item** it);


/*
* @brief Affiche autour d'une case les informations des cases adjacentes
* @param [in] Grille& g, Structure Item
*/
void cases_adjacentes(Grille& g, Item** it);


/*
* @brief Affiche la grille, les lignes les colonnes avec les séparations ect..
* @param [in/out] Grille&, structure item
* @param [out] Grille visuelle
*/
void affichage_grille(Grille& g, Item** it);


/*
* @brief Determine si une partie est perdue ou pas
* @param [in] Structure grille
* return "game lost" ou "game not lost"
*/
void is_lost(Grille& g);


/*
* @brief Determine si une partie est gagnée ou pas
* @param [in] Structure grille
* @return "game won" ou "game not won"
*/
void is_won(Grille& g);


/*
* @brief Sert, comme son nom l'indique, a générer un nouveau coup
* @param [in] Grille& g, Strcture Item
*/
void nouveau_coup(Grille& g);