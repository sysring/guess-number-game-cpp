#include "game.h"
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <cmath>

// -----------------------------
// Helpers (propre et réutilisable)
// -----------------------------
static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entree invalide. Mets un nombre.\n";
    }
}

struct Settings {
    int maxNumber;
    int maxTries;
    int difficultyBonus; // bonus de score selon difficulté
    std::string name;
};

static Settings chooseDifficulty() {
    std::cout << "\nChoisis une difficulte :\n";
    std::cout << "1) Facile    (1-50,  10 essais)\n";
    std::cout << "2) Moyen     (1-100, 8 essais)\n";
    std::cout << "3) Difficile (1-500, 7 essais)\n";

    int choice = 0;
    while (choice < 1 || choice > 3) {
        choice = readInt("Ton choix (1-3) : ");
        if (choice < 1 || choice > 3) {
            std::cout << "Choix invalide. Reessaie.\n";
        }
    }

    if (choice == 1) return {50, 10, 0,  "Facile"};
    if (choice == 2) return {100, 8,  15, "Moyen"};
    return {500, 7,  35, "Difficile"};
}

static int randomBetween(int min, int max) {
    // RNG moderne (meilleure qualité que rand)
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

static void printHotColdHint(int secret, int guess, int previousDiff) {
    int diff = std::abs(secret - guess);

    if (previousDiff == -1) {
        // premier essai : juste un état
        if (diff <= 5)      std::cout << "🔥 Tres chaud !\n";
        else if (diff <= 15) std::cout << "🌡️  Chaud.\n";
        else if (diff <= 30) std::cout << "🧊 Froid.\n";
        else                 std::cout << "🥶 Tres froid.\n";
        return;
    }

    if (diff < previousDiff) std::cout << "📈 Tu te rapproches !\n";
    else if (diff > previousDiff) std::cout << "📉 Tu t'eloignes !\n";
    else std::cout << "😐 Pareil.\n";
}

// -----------------------------
// Game entry point
// -----------------------------
void playGame() {
    Settings s = chooseDifficulty();
    const int secret = randomBetween(1, s.maxNumber);

    int tries = 0;
    int previousDiff = -1;

    std::cout << "\n=== Devine le nombre (1 a " << s.maxNumber << ") ===\n";
    std::cout << "Difficulte: " << s.name << " | Essais: " << s.maxTries << "\n\n";

    while (tries < s.maxTries) {
        int guess = readInt("Essai " + std::to_string(tries + 1) + "/" +
                            std::to_string(s.maxTries) + " - Ton nombre : ");

        tries++;

        if (guess < 1 || guess > s.maxNumber) {
            std::cout << "⚠️  Hors limite. Choisis entre 1 et " << s.maxNumber << ".\n";
            continue; // on compte l'essai (à toi de décider, c'est plus "strict")
        }

        if (guess < secret) {
            std::cout << "Plus grand !\n";
            printHotColdHint(secret, guess, previousDiff);
        } else if (guess > secret) {
            std::cout << "Plus petit !\n";
            printHotColdHint(secret, guess, previousDiff);
        } else {
            // Score : base selon essais restants + bonus difficulté
            int base = (s.maxTries - tries + 1) * 10;
            int score = base + s.difficultyBonus;

            std::cout << "\n✅ Bravo !! Tu as gagne en " << tries << " essais.\n";
            std::cout << "🎯 Score : " << score << " points (bonus difficulte: +" << s.difficultyBonus << ")\n";
            return;
        }

        previousDiff = std::abs(secret - guess);
        std::cout << "\n";
    }

    std::cout << "\n❌ Perdu… Le nombre etait : " << secret << "\n";
}
