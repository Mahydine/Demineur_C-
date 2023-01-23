#include "commandes.h"

int main() {

    Grille g;
    Item** item;

    unsigned int Commande = 0, lignes = 0, colonnes = 0, nombre_de_mines = 0;

    cin >> Commande;
        assert(Commande <= 5 && Commande >= 1 ); // Verifie que le numéro de commande entré est entre 1 et 5
    cin >> lignes;
        assert(lignes >= 2); // Vérifie un minimum de 2 ou + lignes
    cin >> colonnes;
        assert(colonnes >= 2); // Vérifie un minimum de 2 ou + colonnes
    cin >> nombre_de_mines;
        assert(nombre_de_mines >= 1); // Vérifie un minimum de 1 ou + mines

    if (Commande == 1) Commande1(lignes, colonnes, nombre_de_mines);
    else if (Commande == 2) Commande2(g, item, lignes, colonnes, nombre_de_mines);
    else if (Commande == 3) Commande3(g, lignes, colonnes, nombre_de_mines);
    else if (Commande == 4) Commande4(g, lignes, colonnes, nombre_de_mines);
    else if (Commande == 5) Commande5(g, item, lignes, colonnes, nombre_de_mines);

    return 0;
}