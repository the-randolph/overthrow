// -*- C++ -*-

#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>
#include <utility>

enum class card { baron, executioner, diplomat, commander, bodyguard, empty };

inline std::ostream &operator<<(std::ostream &os, card card) {
  switch (card) {
  case card::baron:
    os << "baron";
    break;
  case card::executioner:
    os << "executioner";
    break;
  case card::diplomat:
    os << "diplomat";
    break;
  case card::commander:
    os << "commander";
    break;
  case card::bodyguard:
    os << "bodyguard";
    break;
  case card::empty:
    os << "empty";
    break;
  }
  return os;
}

using hand = std::pair<card, card>;

class player {
public:
  bool alive;
  hand hand;
  int coin;
  bool isAlive();
};

#endif
