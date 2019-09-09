#include "gameState.h"
#include <iostream>
#include <random>

gameState::gameState(int numPlayers)
    : numPlayers(numPlayers),
      players(numPlayers, player()), deck{card::baron,       card::baron,
                                          card::baron,       card::executioner,
                                          card::executioner, card::executioner,
                                          card::diplomat,    card::diplomat,
                                          card::diplomat,    card::commander,
                                          card::commander,   card::commander,
                                          card::bodyguard,   card::bodyguard,
                                          card::bodyguard} {

  for (size_t i = 0; i < deck.size(); i++) {
    std::cout << deck[i] << "\n";
  }

  // Shuffle deck
  std::cout << "-- Shuffle Deck Begin -- \n";
  auto rng = std::default_random_engine(time(0));
  std::shuffle(deck.begin(), deck.end(), rng);
  for (size_t i = 0; i < deck.size(); i++) {
    std::cout << deck[i] << "\n";
  }

  // Create X numbers of players and distribute cards
  // Push top of deck into each players hands

  for (int i = 0; i < numPlayers; i++) {
    std::cout << "Player " << i << " added. \n";
    card first, second;
    first = deck.back();
    deck.pop_back();
    second = deck.back();
    deck.pop_back();
    players.at(i).hand = hand(first, second);
    std::cout << "Player " << i << " : <" << players.at(i).hand.first << ","
              << players.at(i).hand.second << "> \n";
  }
}

void gameState::mainLoop() {
  // Loop through the player array and get them to do actions
  // Probability is just randomized.
 while (1) {
    if (players.size() == 1) {
      break;
    }

    for (int i = 0; i < players.size(); i++) {
      if (i == 0) {
        // Player's choice
      }
      else {
        // Computer generated choice  
      }
    }
    break;
  }
}

// bool gameState::checkCard(player *p, card c) {
//   for (player &otherPlayer : players) {
//     if (p == &otherPlayer)
//       continue;
//     if (otherPlayer.doYouContest(p, c)) {
//       if (p->hasCard(c))
//         otherPlayer.loseCard();
//       else
//         p->loseCard(c);
//       return true;
//     }
//   }
//   return false;
// }

// // in gamestate.cpp:
// void gameState::performExecution(player *from, player *to) {
//   if (checkCard(player, card::executioner))
//     return;
// }
