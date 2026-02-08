#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int secret = (std::rand() % 100) + 1;

    int guess = 0;
    int tries = 0;

    std::cout << "=== Devine le nombre (1 a 100) ===\n";

    while (guess != secret) {
        std::cout << "Ton nombre : ";
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entree invalide. Essaie un nombre.\n";
            continue;
        }

        tries++;

        if (guess < secret) std::cout << "Plus grand !\n";
        else if (guess > secret) std::cout << "Plus petit !\n";
        else std::cout << "Bravo ! Trouve en " << tries << " essais.\n";
    }

    return 0;
}
