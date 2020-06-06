// -*- C++ -*-

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <memory>
#include "player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

class gameState {
  std::vector<std::unique_ptr<Player>> players;
  std::vector<Card> deck;
  std::vector<Card> deckGraveyard;
  // deck, etc

  // check when a player contests a card played
  bool checkCard(Player *p, Card c);

public:
  gameState(std::vector<std::unique_ptr<Player>> playerList);

  // access player info
  Player *getPlayer(std::string name);

  // General Actions
  void generalIncome(std::string name);
  void generalAid(std::string name);
  void generalOverthrow(std::string name, std::string target, int pos);
  // Baron (Duke)
  void baronTax(std::string name);
  void baronBlockAid(std::string name, std::string target);
  // Executioner (Assasin)
  void executionerExecute(std::string name, std::string target, int pos);
  // Diplomat (Ambassador)
  void diplomatExchange(std::string name);
  void diplomatBlockLoot(std::string name);
  // Admiral (Captain)
  void admiralLoot(std::string name, std::string target);
  void admiralBlockLoot(std::string name);
  // Bodyguard (Contessa)
  void bodyguardBlockExecute(std::string name);
  // Magician (Inquisitor)
  void magicianExamine(std::string name, std::string target);
  void magicianExchange(std::string name);
  void magicianBlockLoot(std::string name);
  // check deck graveyad

};


#endif
