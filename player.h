#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
class Player {
  bool alive;
  std::pair<int, int> hand;
  int coin;
  public bool isAlive();
};

#endif
