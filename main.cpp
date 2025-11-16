//
// Created by Daniel Kim on 9/14/25.
//

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <limits>

int main() {
  // main Game object controlling all game logic
  Game game;
  // stores user manu selection
  char choice;

  // main menu loop runs until user chooses to exit
  do {
    std::cout << "\n=== Blackjack ===\n";
    std::cout << "1. Play Blackjack\n";
    std::cout << "2. View Statistics\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option (1-3): ";

    // take input for the menu option
    std::cin >> choice;

    // avoids leftover characters breaking future inputs
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // option 1: new blackjack session
    if (choice == '1') {
      game.play();
    }

    // option 2: view statistics
    else if (choice == '2') {
#ifdef _WIN32
      system("python ../statistics.py");
#else
      system("python3 analytics.py");
#endif
    }

    // option 3: exit
    else if (choice == '3') {
      std::cout << "Thanks for playing!\n";
    }

    // input validation
    else {
      std::cout << "Invalid input.";
    }
  }

  // menu repeats until user selects 3 to exit
  while (choice != '3');
  return 0;
}
