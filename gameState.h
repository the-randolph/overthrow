// -*- C++ -*-

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include "player.h"

class gameState {
  int numPlayers;
  std::vector<player> players;
  std::vector<card> deck;
  // deck, etc

  void performExecution(player *from, player *to);

  bool checkCard(player *p, card c);

public:
  gameState(int numPlayers = 2);

  void mainLoop();
};


#endif
