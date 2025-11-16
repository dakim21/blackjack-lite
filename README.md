# Blackjack

*Name*: Daniel Kim

---

## Summary
This is a simplified game of Blackjack.  
Blackjack is a casino game where the player competes against the dealer to get as close to 21 as possible without going over.

The sequence of the game goes as follows:
1. Deals random cards with values (2–10, JQK = 10, Ace = 11).
2. Player chooses to Hit(draw a card) or Stand.
3. Dealer draws until reaching 17 or higher.
4. Winner is determined by comparing totals.

---

## Module 1 Concepts
*Classes*:
- `Card` (fields: suit, rank, value/num)
- `Deck` (holds vector of cards, deals cards)

*Enumerated type*:
- `Suit {Hearts, Diamonds, Clubs, Spades}`

*Overloaded operator*:
- `<<` for printing `Card` objects to the console

*Input validation*:
- Ensures user enters only `h` (hit) or `s` (stand)

---

## Module 2 Concepts
*Component Class Relationship*:
- `Game` **has-a** `Deck`, `Card`, and hand vectors for both player and dealer.
- Has clear separation of logic: card mechanics (Deck/Card) and gameplay loop (Game).

*File output*:
1. `game_log.txt`:
    - Displays a summary of each round; this is actually slightly redundant right now but I plan on making it useful later.
2. `win_stats.txt`:
    - Shows how many times the player and dealer have won; automatically updates after each round

---

## Module 3 Concepts
*Multiple Languages*:
- C++ handles the gameplay, input validation and file I/O
- Python reads the text logs (win_stats.txt) created by C++ and graphs them using matplotlib.

*Data Passing*:
- Data is passed through shared text files (win_stats.txt, game_log.txt)
- After each blackjack session after the player exits, it writes updated statistics with the option to "View Statistics" from the starting menu. It then automatically launches the python script which parses through the logs and creates a bar chart (results.png).

---

## Known Bugs
- Ace is always counted as 11 (does not switch to 1)
- Dealer only hits until at least 17

---

## Future Work
- Handle Ace values (1 or 11)
- Add chip betting system
- Track multiple players
- Add multi-deck support
- Add features such as splitting, doubling down, insurance, etc.
- Add visual representation of cards, right now its text only

---

## Citations
- https://en.cppreference.com/w/cpp/algorithm/random_shuffle#std::shuffle  
- https://en.cppreference.com/w/cpp/numeric/random/default_random_engine
- https://en.cppreference.com/w/cpp/chrono/c/time (for seeding rng)

---

## Self-Assessment
*Grade I think I earned*: B-
- Didn't go too in depth with the win/loss/tie graph, it only shows win counts and not ties.
- Language interaction is pretty minimal
- Didn't make commits over longer than 3 days