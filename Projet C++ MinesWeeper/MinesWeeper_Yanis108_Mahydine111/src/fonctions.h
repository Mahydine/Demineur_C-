#pragma once
#include"entete.h"

void Commande1(unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines) {

    srand(time(NULL)); // initialise la fonction srand sur le temps actuel.

    // Calcul des dimensions de la grille pour pouvoir choisir des positions aléatoires sans débordé en dehors
    unsigned int dimensions = lignes * colonnes;

    // Affiche le nombre de lignes, de colonnes et de mines.
    cout << lignes << " " << colonnes << " " << nombre_de_mines << " ";

    // Boucle affichant une position aléatoire dans l'intervale 0:Dimensions
    // autant de fois qu'il y a de mines.
    for(int i = 0 ; i < nombre_de_mines ; i++){
        cout << rand() % dimensions << " ";
    }
}

void initialisation_jeu(Grille& g, unsigned int lignes, unsigned int colonnes, unsigned int nombre_de_mines) {

    // Entre les informations de lignes, colonnes, mines, dans la structure Grille
    g.lignes = lignes;    
    g.colonnes = colonnes;
    g.nombre_de_mines = nombre_de_mines;

    // Choix et placement des mines stockées dans le tableau positionMines
    for (int i = 0 ; i < nombre_de_mines ; ++i) cin >> g.positionMines[i];

    // Stock le nombre de coups a effectuer souhaiter
    cin >> g.nombre_de_coups;
    assert(g.nombre_de_coups <= (lignes* colonnes));

    // Enregistrer les coups effectués autant de fois qu'il y a de coups a faire (nombre_de_coups)
    for (int m = 0 ; m < g.nombre_de_coups ; ++m) {
        cin >> g.coups[m]; // Stock l'origine du coup (marquage ou démasquage de case)
        cin >> g.positionCoups[m]; // Stock la position a laquelle effectué le coup (numero de la case)
    }
}

void triage_mines(Grille& g) {

    unsigned int temp;
    // Boucle s'executant autant de fois qu'il y a de mines
    for (int i = 0; i < g.nombre_de_mines; i++) {
        // Boucle s'executant autant de fois qu'il y a de mines²
        for (int j = 0; j < g.nombre_de_mines; j++) {
            // Interverti les valeurs si la première est inferieure a la deuxieme
            if (g.positionMines[i] < g.positionMines[j]) {
                temp = g.positionMines[i];
                g.positionMines[i] = g.positionMines[j];
                g.positionMines[j] = temp;
            }
        }
    }

}

void triage_historique(Grille& g) {

    unsigned int temp = 0, temp_lettre = 0;

    for (int i = 0; i < g.nombre_de_coups; ++i) { // Boucle s'executant autant de fois qu'il y a de coups
        for (int j = 0; j < g.nombre_de_coups; ++j) { // Boucle s'executant autant de fois qu'il y a de coups²
            if (g.positionCoups[i] < g.positionCoups[j]) { // si la première position du coup est inferieure a la suivante
                // Inverse la première position avec la deuxieme
                temp = g.positionCoups[i];
                g.positionCoups[i] = g.positionCoups[j];
                g.positionCoups[j] = temp;
                // Inverse la première lettre du coups avec la deuxieme
                temp_lettre = g.coups[i];
                g.coups[i] = g.coups[j];
                g.coups[j] = temp_lettre;
            }
        }
    }
}

void initialisation_grille(Item*** it, Grille& g) {

    // Crée un tableau de caractère en allocation dynamique
    *it = new Item * [g.lignes];

    // Boucle qui se répète autant de fois qu'il y a de colonnes
    for (int x = 0 ; x < g.colonnes; ++x) {
        (*it)[x] = new Item[g.colonnes];
    }

    // Boucle qui se répète autant de fois qu'il y a de lignes
    for (int x = 0; x < g.lignes; x++) {
        // Boucle qui se répète autant de fois qu'il y a de colonnes
        for (int y = 0; y < g.colonnes; y++) {
            // Masque toute les cases de la grille
            (*it)[x][y] = '.';
        }
    }
}

void placage_des_mines(Grille& g, Item** it) {

    unsigned int compteur = 0; // variable qui va servir de compteur
    unsigned int position = 0; // variable qui va servir d'indicateur de position

    // Boucle s'executant autant de fois qu'il y a de lignes
    for (int x = 0 ; x < g.lignes; ++x) {
        // Boucle s'executant autant de fois qu'il y a de colonnes
        for (int y = 0; y < g.colonnes; ++y) {
            // Si le numéro de case de la mine à l'indice compteur correspond a celui de la position alors
            if (g.positionMines[compteur] == position) {
                // marquer la case d'un 'm' aux positions en deux dimensions : (x,y) sur la grille
                it[x][y] = MINE;
                // incrémenté le compteur pour vérifier le reste des cases
                compteur++;
                // incrémenté la position pour vérifier le reste des cases
                position++;
            }
            // Sinon, la position actuelle sur la grille ne contient pas de mines donc..
            else {
                // incrémenté la position pour vérifier le reste des cases
                position++;
            }
        }
    }
}

void effectuer_coup(Grille& g, Item** it) {

    unsigned int compteur = 0; // variable qui va servir de compteur
    unsigned int position = 0; // variable qui va servir d'indicateur de position

    // Boucle s'executant autant de fois qu'il y a de lignes
    for (int x = 0; x < g.lignes; x++) {
        // Boucle s'executant autant de fois qu'il y a de colonnes
        for (int y = 0; y < g.colonnes; y++) {
            // Si le caractère du coup effectué à l'indice du compteur correspond a M
            // ET que la position du coup effectué à l'indice du compteur correspond a la position sur laquelle on vérifie
            if (g.coups[compteur] == MARQUER && g.positionCoups[compteur] == position) {
                // effectue le coup sur la case aux positions en deux dimensions : (x,y) sur la grille
                it[x][y] = MARQUE;
                // incrémenté la position pour vérifier le reste des cases
                position++;
                // incrémenté le compteur pour vérifier le reste des cases
                compteur++;
            }
            // Sinon si le caractère du coup effectué à l'indice du compteur correspond a D
            // ET que la position du coup effectué à l'indice du compteur correspond a la position sur laquelle on vérifie
            else if (g.coups[compteur] == DEMASQUER && g.positionCoups[compteur] == position) {
                // Si la case est masquée
                if (it[x][y] == MASQUE) {
                    // on l'a démasque
                    it[x][y] = VIDE;
                    // incrémenté la position pour vérifier le reste des cases
                    position++;
                    // incrémenté le compteur pour vérifier le reste des cases
                    compteur++;
                }
            }
            // Sinon la position actuelle ne subit aucun coups de la part du joueur donc
            else {
                // incrémenté la position pour vérifier le reste des cases
                position++;
            }
        }
    }
}

void cases_adjacentes(Grille& g, Item** it) {

    unsigned int zero = 48; // 48 correspond au zéro en ASCII, servira en tant que caractère

    // Boucle qui s'execute autant de fois qu'il y a de lignes
    for (int l = 0; l < g.lignes; ++l) {
        // Boucle qui s'execute autant de fois qu'il y a de colonnes
        for (int c = 0; c < g.colonnes; ++c) {
            // Si cet emplacement correspond a une mine, placer une mine
            if (it[l][c] == MINE) {
                it[l][c] = MINE;
                // Si a la fois, "l" est compris entre 1 et le nombre de lignes
                // ET "c" est compris entre 1 et le nombre de colonnes
                if (l > 0 && l < g.lignes && c > 0 && c < g.colonnes) {
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] = zero;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] = zero;
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                    if (it[l][c + 1] != MINE) it[l][c + 1] = zero;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] = zero;
                }

                if (l == 0 && c == 0) {
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] = zero;
                    if (it[l][c + 1] != MINE) it[l][c + 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                }

                if (l == 0 && c > 0 && c < g.colonnes) {
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] = zero;
                    if (it[l][c + 1] != MINE) it[l][c + 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] = zero;
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                }

                if (l == 0 && c == g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                    if (it[l - 1][c + 1] != MINE) it[l][c + 1] = zero;
                }

                if (l > 0 && l < g.lignes && c == 0) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] = zero;
                    if (it[l][c + 1] != MINE) it[l][c + 1] = zero;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                }

                if (l == g.lignes && c == 0) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] = zero;
                    if (it[l][c + 1] != MINE) it[l][c + 1] = zero;
                }

                if (l == g.lignes && c > 0 && c < g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] = zero;
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] = zero;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] = zero;
                }

                if (l == g.lignes && c == g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] = zero;
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                }

                if (c == g.colonnes && l > 0 && l < g.lignes) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] = zero;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] = zero;
                    if (it[l][c - 1] != MINE) it[l][c - 1] = zero;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] = zero;
                    if (it[l + 1][c] != MINE) it[l + 1][c] = zero;
                }
            }
        }
    }

    for (int l = 0; l < g.lignes; ++l) {
        for (int c = 0; c < g.colonnes; ++c) {
            if (it[l][c] == MINE) {
                it[l][c] = MINE;
                if (l >= 1 && l < g.lignes && c >= 1 && c < g.colonnes) {
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] += 1;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] += 1;
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                    if (it[l][c + 1] != MINE) it[l][c + 1] += 1;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] += 1;
                }

                if (l == 0 && c == 0) {
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] += 1;
                    if (it[l][c + 1] != MINE) it[l][c + 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                }

                if (l == 0 && c > 0 && c < g.colonnes) {
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] += 1;
                    if (it[l][c + 1] != MINE) it[l][c + 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] += 1;
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                }

                if (l == 0 && c == g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                    if (it[l - 1][c + 1] != MINE) it[l][c + 1] += 1;
                }

                if (l > 0 && l < g.lignes && c == 0) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] += 1;
                    if (it[l][c + 1] != MINE) it[l][c + 1] += 1;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                }

                if (l == g.lignes && c == 0) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] += 1;
                    if (it[l][c + 1] != MINE) it[l][c + 1] += 1;
                }

                if (l == g.lignes && c > 0 && c < g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] += 1;
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                    if (it[l - 1][c + 1] != MINE) it[l - 1][c + 1] += 1;
                    if (it[l + 1][c + 1] != MINE) it[l + 1][c + 1] += 1;
                }

                if (l == g.lignes && c == g.colonnes) {
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] += 1;
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                }

                if (c == g.colonnes && l > 0 && l < g.lignes) {
                    if (it[l - 1][c] != MINE) it[l - 1][c] += 1;
                    if (it[l - 1][c - 1] != MINE) it[l - 1][c - 1] += 1;
                    if (it[l][c - 1] != MINE) it[l][c - 1] += 1;
                    if (it[l + 1][c - 1] != MINE) it[l + 1][c - 1] += 1;
                    if (it[l + 1][c] != MINE) it[l + 1][c] += 1;
                }
            }
        }
    }
}

void affichage_grille(Grille& g, Item** it) {

    cout << g.lignes << " " << g.colonnes << endl;

    for (int k = 0 ; k < g.colonnes ; k++){ // Crée la première délimitation de ligne, celle qui fait le toit de la grille
        cout << " ---";
    }

    cout << endl;

    for(int i = 0; i < g.lignes ; i++){ // Boucle Principale
        // Boucle ligne de mine et de séparations
        for(int j = 0; j < g.colonnes ; j++){
            cout << "| " << it[i][j] << " ";
        }
        // barre fermant la dernière case de chaque ligne
        cout << "|" << endl;
        // Boucle de délimitations lignes
        for (int x = 0 ; x < g.colonnes ; x++){
            cout << " ---";
        }
        // Saute une ligne après les delimitations
        cout << endl;
    }
}

void is_won(Grille& g) {

    bool win = false; // Booleen si la partie est gagnée (true) ou non (false)
    unsigned int dimensions = g.lignes * g.colonnes;

    if (g.nombre_de_coups != dimensions - g.nombre_de_mines) win = false;
    else {  
        // Boucle s'executant autant de fois qu'il y a de mines
        for (int i = 0; i < g.nombre_de_mines; ++i) {
            // Boucle s'executant autant de fois qu'il y a de mines²
            for (int j = 0; j < g.nombre_de_mines; ++j) { 
                // Si aucun coup ne démasque une mine 
                if (g.coups[i] == DEMASQUER && g.positionCoups[i] != g.positionMines[j]) win = true;
                // Sinon si un coup démasque une mine
                else win = false;
            }
        }
    }
    // Si win vaut false alors la partie est perdue
    if (win == false) cout << "game not won";
    // Sinon la partie est gagnée
    else cout << "game won";
}

void is_lost(Grille& g) {

    bool win = false; // Booleen si la partie est gagnée (true) ou non (false)

    // Boucle s'executant autant de fois qu'il y a de mines
    for (int i = 0 ; i < g.nombre_de_mines; i++) {
        if (g.coups[g.nombre_de_coups - 1] == MARQUER && g.positionCoups[g.nombre_de_coups - 1] != g.positionMines[i]) win = false; // game lost
        if (g.coups[g.nombre_de_coups - 1] == DEMASQUER && g.positionCoups[g.nombre_de_coups - 1] == g.positionMines[i]) win = false; // game lost
        if (g.coups[g.nombre_de_coups - 1] == DEMASQUER && g.positionCoups[g.nombre_de_coups - 1] != g.positionMines[i]) win = true; // game not lost
        if (g.coups[g.nombre_de_coups - 1] == MARQUER && g.positionCoups[i] == g.positionMines[i]) win = true; // game not lost
    }

    // Si win vaut false alors la partie est perdue
    if (win == 0) cout << "game lost" << endl;
    // Sinon la partie est gagnée
    else cout << "game not lost" << endl;
}

void nouveau_coup(Grille& g) {
    
    char coup;
    int position_coup;

    cin >> coup >> position_coup;
    cout << coup << position_coup << endl;

    // Ajoute le coup effectué dans la liste, une case après la dernière
    g.coups[g.nombre_de_coups + 1] = coup;
    // Ajoute la position du coup effectué dans la liste, une case après la dernière
    g.positionCoups[g.nombre_de_coups + 1] = position_coup;
    // Incrémente le nombre de coups total de 1
    g.nombre_de_coups++;

    // Affiche la position qui vien d'être ajoutée
    cout << "la position que vous avez choisit est : " << position_coup << endl;
}