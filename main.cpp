#include "player.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main(int arc, char *argv[]) {
  // Initializing deck
  std::vector<card> deck = {
      card::baron,       card::baron,       card::baron,     card::executioner,
      card::executioner, card::executioner, card::diplomat,  card::diplomat,
      card::diplomat,    card::commander,   card::commander, card::commander,
      card::bodyguard,   card::bodyguard,   card::bodyguard};

  for (size_t i = 0; i < deck.size(); i++) {
    std::cout << deck[i] << "\n";
  }

  // Shuffle deck
  std::cout << "-- Shuffle Deck Begin -- \n";
  auto rng = std::default_random_engine{};
  std::shuffle(deck.begin(), deck.end(), rng);
  for (size_t i = 0; i < deck.size(); i++) {
    std::cout << deck[i] << "\n";
  }
}
