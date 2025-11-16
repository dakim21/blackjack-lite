//
// Created by Daniel Kim on 9/11/25.
//

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

// enum for the four suits in a standard deck of cards
enum class Suit {Hearts, Diamonds, Clubs, Spades};

/* Card class represents a single card in blackjack.
 * Fields include:
 * Suit (hearts diamonds spades clubs)
 * Rank (type of card (2-10, JQKA)
 * Value (or num, bj value, so 2-11)
 *
 * Also includes the overloaded operator << so cards can be printed in a readable manner.
 */
class Card {
private:
  Suit suit;
  std::string rank;
  int num;

public:
  // Constructor, creates a card witha  suit, rank and num
  Card(Suit s, const std::string& r, int n);

  // Constructor with default value mapping from rank (for testgin)
  Card(Suit s, const std::string& r);

  // getters
  int getValue() const;
  std::string getRank() const;
  Suit getSuit() const;

  // Overloaded operator to make card readable
  friend std::ostream& operator<<(std::ostream& os, const Card& c);
};
#endif //CARD_H
