//
// Created by Daniel Kim on 9/11/25.
//

#include "Card.h"

// constructor: initialize card with given rank and value
Card::Card(Suit s, const std::string& r, int n)
    : suit(s), rank(r), num(n) {}

// overloaded constructor: sets value automatically based on rank
Card::Card(Suit s, const std::string& r) : suit(s), rank(r) {
  if (r == "J" || r == "Q" || r == "K") {
    num = 10;
  } else if (r == "A") {
    num = 11;
  } else {
    // converts "2-10" to int
    num = std::stoi(r);
  }
}

// Getters for num rank suit, will return respective value
int Card::getValue() const {
  return num;
}

std::string Card::getRank() const {
  return rank;
}

Suit Card::getSuit() const {
  return suit;
}

/*
 * operator<<: makes it easy to use "std::cout << card;"
 * Overload stream insertion operator
 * Example: "10 of Clubs" or "Ace of Hearts".
 */
std::ostream& operator<<(std::ostream& os, const Card& c) {
  std::string suitName;
  switch (c.suit) {
  case Suit::Hearts:   suitName = "Hearts"; break;
  case Suit::Diamonds: suitName = "Diamonds"; break;
  case Suit::Clubs:    suitName = "Clubs"; break;
  case Suit::Spades:   suitName = "Spades"; break;
  }
  os << c.rank << " of " << suitName;
  return os;
}