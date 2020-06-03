// -*- C++ -*-

#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>
#include <utility>

enum class Card { baron, executioner, diplomat, commander, bodyguard, empty };

inline std::ostream &operator<<(std::ostream &os, Card card) {
  switch (card) {
  case Card::baron:
    os << "baron";
    break;
  case Card::executioner:
    os << "executioner";
    break;
  case Card::diplomat:
    os << "diplomat";
    break;
  case Card::commander:
    os << "commander";
    break;
  case Card::bodyguard:
    os << "bodyguard";
    break;
  case Card::empty:
    os << "empty";
    break;
  }
  return os;
}

using Hand = std::pair<Card, Card>;

class Player {
  friend class gameState;

  std::string name;
  bool alive;
  Hand hand;
  int coin;

public:
  Player(std::string userName);
  bool isAlive() const { return alive; }
  void setAlive(bool val) { alive = val; }
  Hand getHand() const { return hand; }
  void setHand(Hand newHand) { hand = newHand; }
  int getCoin() const { return coin; }
  void setCoin(int val) { coin = val; }
};

#endif
