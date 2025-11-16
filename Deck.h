//
// Created by Daniel Kim on 9/12/25.
//

#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

/*
 * The Deck class consists of 52 playing cards
 *
 * Holds all the cards in a vector
 * Shuffle the deck at the start
 * Deal cards one by one to the player or dealer
 */
class Deck {
private:
  // Vector containing all cards
  std::vector<Card> cards;
  // index tracker for top card in the deck
  int currentIndex;

public:
  // Constructor: builds a standard 52 card deck and shuffles it
  Deck();

  // shuffles deck
  void shuffle();

  // deals the next card from the deck
  Card deal();

  // returns number of cards remaining to be dealt in the deck
  int size() const;
};
#endif

