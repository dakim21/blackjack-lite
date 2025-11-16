//
// Created by dakim on 10/1/2025.
//

#ifndef M2OEP_GAME_H
#define M2OEP_GAME_H

#include "Deck.h"
#include <fstream>

class Game {
private:
    Deck deck;
    std::vector<Card> playerHand;
    std::vector<Card> dealerHand;
    void updateWinStats(bool playerWon);
    void logResult(const std::string& result) const;

public:
    // constructor: initializes and shuffles deck
    Game();

    // starts and controls the main gameplay loop
    void play();

    // resets the game state: clears hands and reshuffles the deck
    void reset();

    // deals two cards to player and dealer
    void dealInitialCards();

    // manages player actions (hit or stand) until player stands or busts
    void playerTurn();

    // dealer draws cards until their hand total is at least 17
    void dealerTurn();

    // calculate bj score of hand
    int calculateHandTotal(const std::vector<Card>& hand) const;

    // print the cards in a hand, dealer's first should be hidden
    void printHand(const std::vector<Card>& hand, const std::string& who, bool hideFirstCard = false) const;

    // prompt player to hit or stand
    bool askPlayerHit() const;

    // prompt player to play again
    bool askPlayAgain() const;
};

#endif //M2OEP_GAME_H