//
// Created by dakim on 10/4/2025.
//

#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include <iostream>
#include <cassert>

void testCard() {
    // create a King of Hearts card
    Card c(Suit::Hearts, "K");

    // test suit retrieval
    assert(c.getSuit() == Suit::Hearts);
    // test rank retrieval
    assert(c.getRank() == "K");
    // test bj value of King
    assert(c.getValue() == 10);

    // test success
    std::cout << "Card test passed.\n";
}

void testDeck() {
    // create a fresh deck
    Deck d;

    // test if deck = 52 cards
    assert(d.size() == 52);

    // deal one card from the top
    Card top = d.deal();
    // test if deck now has 51 cards
    assert(d.size() == 51);

    // shuffle remaining cards
    d.shuffle();

    // test success
    std::cout << "Deck test passed.\n";
}

// testBlackjackTotal: for testing bj hand totals but mostly Ace handling
void testBlackjackTotal() {
    // create a game instance to use calculateHandTotal() method
    Game game;

    // test 1: A + 9 should be 20
    std::vector<Card> hand = {Card(Suit::Spades, "A"), Card(Suit::Clubs, "9")};
    assert(game.calculateHandTotal(hand) == 20);

    // test 2: A + A + 9 should be 21
    hand = {Card(Suit::Spades, "A"), Card(Suit::Clubs, "A"), Card(Suit::Diamonds, "9")};
    assert(game.calculateHandTotal(hand) == 21);


    // test3: A + K + 9 should be 20
    hand = {Card(Suit::Spades, "A"), Card(Suit::Clubs, "K"), Card(Suit::Diamonds, "9")};
    assert(game.calculateHandTotal(hand) == 20);

    // test success
    std::cout << "Blackjack hand total tests passed.\n";
}

// main: run all test methods
int main() {
    testCard();
    testDeck();
    testBlackjackTotal();

    // test success
    std::cout << "All tests passed.\n";
    return 0;
}
