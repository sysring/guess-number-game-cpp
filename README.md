# 🎯 Guess Number Game (C++)

A simple and interactive number guessing game written in C++.  
The player must guess a randomly generated number within a limited number of attempts.

---

## 🚀 Features

- Multiple difficulty levels:
  - Easy (1–50, 10 attempts)
  - Medium (1–100, 8 attempts)
  - Hard (1–500, 7 attempts)
- Smart hints:
  - Too high / Too low
  - Hot / Cold system
- Input validation (no crashes on invalid input)
- Score system based on performance and difficulty
- Clean and modular C++ code

---

## 🛠️ Technologies

- C++
- Standard Library (`<iostream>`, `<random>`, `<limits>`, etc.)

---

## ▶️ How to Compile & Run

### Linux / Mac
```bash
g++ main.cpp game.cpp -o guess-game
./guess-game

Windows (MinGW)
g++ main.cpp game.cpp -o guess-game.exe
guess-game.exe
