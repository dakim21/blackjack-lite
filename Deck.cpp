//
// Created by Daniel Kim on 9/12/25.
//

#include "Deck.h"
#include <ctime>
#include <algorithm>
#include <random>

/*
 * Constructor, creates a deck of 52 cards.
 * Each card has a suit, a rank string, and a value in blackjack
 * After creating the deck, it is shuffled using std::random_shuffle from the algorithm library
 */
Deck::Deck() : currentIndex(0) {
  // all blackjack rank and values
  std::vector<std::string> ranks = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
  std::vector<int> values = {2,3,4,5,6,7,8,9,10,10,10,10,11};

  // create cards for each suit and each rank
  for (int s = 0; s < 4; s++) {
    for (size_t i = 0; i < ranks.size(); i++) {
      cards.emplace_back(static_cast<Suit>(s), ranks[i], values[i]);
    }
  }
}

/*
 * shuffle: Randomly shuffles the deck of cards
 * resets currentIndex to 0 so dealing starts from the top
 * uses std::shuffle with a default_random_engine seeded by the current time to make sure shuffle order is different each time
 */
void Deck::shuffle() {
  currentIndex = 0;
  auto rng = std::default_random_engine(std::time(nullptr));
  std::shuffle(cards.begin(), cards.end(), rng);
}

/*
 * dealCard: returns the next card from the deck
 * if the deck ends, reshuffle and start over
 * currentIndex++ to keep track of next card
 */
Card Deck::deal() {
  if (currentIndex >= static_cast<int>(cards.size())) {
    currentIndex = 0;
    auto rng = std::default_random_engine(std::time(nullptr));
    std::shuffle(cards.begin(), cards.end(), rng);
  }
  return cards[currentIndex++];
}

/*
 * size: returns the number of remaining cards in the deck
 */
int Deck::size() const {
  return static_cast<int>(cards.size()) - currentIndex;
}