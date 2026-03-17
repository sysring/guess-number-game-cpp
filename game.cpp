#include "game.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <string>

namespace
{
    struct GameSettings
    {
        int maxNumber;
        int maxAttempts;
        int scoreBonus;
        std::string difficultyName;
    };

    int readInteger(const std::string& prompt)
    {
        int value;

        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value)
            {
                return value;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
    }

    GameSettings chooseDifficulty()
    {
        std::cout << "\n=== Select Difficulty ===\n";
        std::cout << "1. Easy   (1 to 50,  10 attempts)\n";
        std::cout << "2. Medium (1 to 100, 8 attempts)\n";
        std::cout << "3. Hard   (1 to 500, 7 attempts)\n\n";

        int choice = 0;

        while (choice < 1 || choice > 3)
        {
            choice = readInteger("Enter your choice (1-3): ");

            if (choice < 1 || choice > 3)
            {
                std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
            }
        }

        switch (choice)
        {
            case 1:
                return {50, 10, 0, "Easy"};
            case 2:
                return {100, 8, 15, "Medium"};
            case 3:
                return {500, 7, 35, "Hard"};
            default:
                return {100, 8, 15, "Medium"};
        }
    }

    int generateRandomNumber(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    void displayTemperatureHint(int difference, int previousDifference)
    {
        if (previousDifference == -1)
        {
            if (difference <= 5)
            {
                std::cout << "Very hot! You are extremely close.\n";
            }
            else if (difference <= 15)
            {
                std::cout << "Hot! You are getting close.\n";
            }
            else if (difference <= 30)
            {
                std::cout << "Cold. You still have some distance to cover.\n";
            }
            else
            {
                std::cout << "Very cold. You are far from the target.\n";
            }

            return;
        }

        if (difference < previousDifference)
        {
            std::cout << "You are getting closer.\n";
        }
        else if (difference > previousDifference)
        {
            std::cout << "You are getting farther away.\n";
        }
        else
        {
            std::cout << "You are at the same distance as before.\n";
        }
    }

    int calculateScore(const GameSettings& settings, int attemptsUsed)
    {
        const int remainingAttempts = settings.maxAttempts - attemptsUsed;
        const int baseScore = (remainingAttempts + 1) * 10;
        return baseScore + settings.scoreBonus;
    }
}

void playGame()
{
    const GameSettings settings = chooseDifficulty();
    const int secretNumber = generateRandomNumber(1, settings.maxNumber);

    int attemptsUsed = 0;
    int previousDifference = -1;

    std::cout << "\n=== Guess the Number ===\n";
    std::cout << "Difficulty: " << settings.difficultyName << '\n';
    std::cout << "Range: 1 to " << settings.maxNumber << '\n';
    std::cout << "Maximum attempts: " << settings.maxAttempts << "\n\n";

    while (attemptsUsed < settings.maxAttempts)
    {
        const int guess = readInteger(
            "Attempt " + std::to_string(attemptsUsed + 1) + "/" +
            std::to_string(settings.maxAttempts) + " - Enter your guess: "
        );

        ++attemptsUsed;

        if (guess < 1 || guess > settings.maxNumber)
        {
            std::cout << "Out of range. Please choose a number between 1 and "
                      << settings.maxNumber << ".\n\n";
            continue;
        }

        if (guess == secretNumber)
        {
            const int score = calculateScore(settings, attemptsUsed);

            std::cout << "\nCongratulations! You guessed the correct number in "
                      << attemptsUsed << " attempt"
                      << (attemptsUsed > 1 ? "s" : "") << ".\n";

            std::cout << "Final score: " << score
                      << " points (difficulty bonus: +" << settings.scoreBonus << ")\n";

            return;
        }

        if (guess < secretNumber)
        {
            std::cout << "Too low.\n";
        }
        else
        {
            std::cout << "Too high.\n";
        }

        const int currentDifference = std::abs(secretNumber - guess);
        displayTemperatureHint(currentDifference, previousDifference);
        previousDifference = currentDifference;

        std::cout << '\n';
    }

    std::cout << "\nGame over. The correct number was: " << secretNumber << '\n';
}
