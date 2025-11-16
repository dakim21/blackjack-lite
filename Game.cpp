//
// Created by dakim on 10/2/2025.
//

#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

// Constructor: initializes and shuffles the deck once when the game is created
Game::Game() {
    // shuffle deck initiaLLy
    deck.shuffle();
}

// reset: resets game state before every round
void Game::reset() {
    // create a fresh new deck
    deck = Deck();
    // reshuffle new deck
    deck.shuffle();
    // clear player's hand
    playerHand.clear();
    // clear dealer's hand
    dealerHand.clear();
}

// updateWinStats: logs cumulative wins to win_stats.txt
void Game::updateWinStats(bool playerWon) {
    int playerWins = 0, dealerWins = 0;

    // open file to read existing win stats
    std::ifstream in("../win_stats.txt"); // <<-- path fixed to match write target
    if (in.is_open()) {
        std::string line;

        // read each line and parse win counts
        while (std::getline(in, line)) {
            if (line.find("PlayerWins:") != std::string::npos)
                // extract and convert player win count
                playerWins = std::stoi(line.substr(line.find(":") + 1));
            else if (line.find("DealerWins:") != std::string::npos)
                // ext ract and convert dealer win count
                dealerWins = std::stoi(line.substr(line.find(":") + 1));
        }
        // close in put file after reading
        in.close();
    }

    // increment appropriate win counter based on game winner
    if (playerWon) ++playerWins;
    else ++dealerWins;

    // open file for writing updated win counts
    std::ofstream out("../win_stats.txt");
    if (out.is_open()) {
        // write updated states to file
        out << "PlayerWins: " << playerWins << "\n";
        out << "DealerWins: " << dealerWins << "\n";

        // close output file
        out.close();
    }
}

// logResult: logs outcome of each game to game_log.txt
void Game::logResult(const std::string& result) const {
    std::ofstream log("../game_log.txt", std::ios::app);
    if (log.is_open()) {
        log << result << "\n";
        log.close();
    }
}

// play: main game loop that handles a round of blackjack
void Game::play() {
    // bool to control main game loop
    bool playing = true;

    while (playing) {
        // reset game state for a new round
        reset();
        // deal two cards to player and dealer
        dealInitialCards();
        // show player hand
        printHand(playerHand, "Your");
        // show dealer hand
        printHand(dealerHand, "Dealer", true);

        // handle player decision (hit or stand)
        playerTurn();

        // calculate player total
        int playerTotal = calculateHandTotal(playerHand);
        // if player didnt bust, go to dealer's turn
        if (playerTotal <= 21) {
            dealerTurn();
        }

        // calculate dealer total
        int dealerTotal = calculateHandTotal(dealerHand);

        // final score summary
        std::cout << "Final totals -> You: " << playerTotal << " | Dealer: " << dealerTotal << "\n";

        // determine winner logic
        if (playerTotal > 21) {
            std::cout << "You busted. Dealer wins!\n";
            logResult("Result: Dealer wins (player busted)");
            updateWinStats(false);
        } else if (dealerTotal > 21 || playerTotal > dealerTotal) {
            std::cout << "You win!\n";
            logResult("Result: Player wins");
            updateWinStats(true);
        } else if (dealerTotal > playerTotal) {
            std::cout << "Dealer wins!\n";
            logResult("Result: Dealer wins");
            updateWinStats(false);
        } else {
            std::cout << "It's a tie!\n";
            logResult("Result: Tie game");
        }

        // prompt player to play again
        playing = askPlayAgain();
    }

    // goodbye message
    std::cout << "Thanks for playing!\n";

    // show win stats
    std::ifstream stats("../win_stats.txt"); // <<-- path fixed to match updateWinStats
    if (stats.is_open()) {
        std::string line;
        std::cout << "\nWin Summary:\n";
        while (std::getline(stats, line)) {
            std::cout << line << "\n";
        }
        stats.close();
    }
}

// dealInitialCards: deals two cards to player and dealer
void Game::dealInitialCards() {
    playerHand.push_back(deck.deal());
    dealerHand.push_back(deck.deal());
    playerHand.push_back(deck.deal());
    dealerHand.push_back(deck.deal());
}

// playerTurn: handles player actions (hit or stand)
void Game::playerTurn() {
    // loop as long as playe ris under 21 and chooses to hit
    while (calculateHandTotal(playerHand) < 21 && askPlayerHit()) {
        playerHand.push_back(deck.deal());
        printHand(playerHand, "Your");
    }
}

// dealerTurn: shows dealer's hidden card and hits until at least 17
void Game::dealerTurn() {
    // reveal hidden card
    std::cout << "Dealer's hidden card: " << dealerHand[1] << "\n";

    // loop until dealer hits at least 17
    while (calculateHandTotal(dealerHand) < 17) {
        // deal a card
        Card c = deck.deal();
        // add to dealer's hand
        dealerHand.push_back(c);
        std::cout << "Dealer draws " << c << ". Total now " << calculateHandTotal(dealerHand) << "\n";
    }
}

// calculateHandTotal: returns bj value of a hand
int Game::calculateHandTotal(const std::vector<Card>& hand) const {
    int total = 0, aces = 0;

    // sum card values and count aces
    for (const auto& card : hand) {
        total += card.getValue();
        // track number of aces
        if (card.getRank() == "A") aces++;
    }

    // downgrade aces from 11 to 1 if over 21
    while (total > 21 && aces--) {
        total -= 10;
    }
    return total;
}

// printHand: displays the hand of either the player or dealer
// If hideFirstCard is true, first card is hidden (used for dealer)
void Game::printHand(const std::vector<Card>& hand, const std::string& who, bool hideFirstCard) const {
    std::cout << who << " cards: ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (i == 0 && hideFirstCard) {
            std::cout << "Hidden, ";
        } else {
            // use overloaded << for Card
            std::cout << hand[i];
            if (i != hand.size() - 1) std::cout << ", ";
        }
    }

    // print total if not hiding the total
    if (!(who == "Dealer" && hideFirstCard)) {
        std::cout << " (Total: " << calculateHandTotal(hand) << ")";
    }

    std::cout << "\n";
}

// askPlayerHit: prompts the player whether they want to hit or stand
bool Game::askPlayerHit() const {
    std::string input;

    while (true) {
        std::cout << "Hit (h) or Stand (s)? ";
        // get full line input
        std::getline(std::cin, input);
        // parse input
        std::stringstream ss(input);
        char ch;
        ss >> ch;
        // player chooses to hit
        if (ch == 'h' || ch == 'H') return true;
        // player chooses to stand
        if (ch == 's' || ch == 'S') return false;

        // input validation
        std::cout << "Invalid input. Please enter h or s.\n";
    }
}

// askPlayAgain: prompts the player whether they want to play again
bool Game::askPlayAgain() const {
    std::string input;
    while (true) {
        std::cout << "Would you like to play again? (y/n): ";
        // get full line input
        std::getline(std::cin, input);
        // parse input
        std::stringstream ss(input);
        char ch;
        ss >> ch;
        // play again
        if (ch == 'y' || ch == 'Y') return true;
        // exit
        if (ch == 'n' || ch == 'N') return false;

        // input validation
        std::cout << "Invalid input. Please enter y or n.\n";
    }
}