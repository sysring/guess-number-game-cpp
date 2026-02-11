#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

static int askDifficulty() {
    int choice = 0;
    std::cout << "\nChoisis une difficulte :\n";
    std::cout << "1) Facile   (1-50,  10 essais)\n";
    std::cout << "2) Moyen    (1-100, 8 essais)\n";
    std::cout << "3) Difficile(1-500, 7 essais)\n";
    std::cout << "Ton choix (1-3) : ";

    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Choix invalide. Reessaie (1-3) : ";
    }
    return choice;
}

void playGame() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int choice = askDifficulty();

    int maxNumber = 100;
    int maxTries = 8;

    if (choice == 1) { maxNumber = 50;  maxTries = 10; }
    if (choice == 2) { maxNumber = 100; maxTries = 8;  }
    if (choice == 3) { maxNumber = 500; maxTries = 7;  }

    int secret = (std::rand() % maxNumber) + 1;

    int guess = 0;
    int tries = 0;

    std::cout << "\n=== Devine le nombre (1 a " << maxNumber << ") ===\n";
    std::cout << "Tu as " << maxTries << " essais.\n\n";

    while (tries < maxTries) {
        std::cout << "Essai " << (tries + 1) << "/" << maxTries << " - Ton nombre : ";

        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entree invalide. Mets un nombre.\n";
            continue; // ne compte pas comme un essai
        }

        tries++;

        if (guess < secret) std::cout << "Plus grand !\n";
        else if (guess > secret) std::cout << "Plus petit !\n";
        else {
            std::cout << "Bravo !! Tu as gagne en " << tries << " essais.\n";
            return;
        }
    }

    std::cout << "\nPerdu 😈 Le nombre etait : " << secret << "\n";
}
