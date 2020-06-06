#include "gameState.h"
#include <iostream>
#include <random>
#include <algorithm>

gameState::gameState(std::vector<std::unique_ptr<Player>> playerList)
  : players(std::move(playerList)),
                                     deck{Card::baron,       Card::baron,
                                          Card::baron,       Card::executioner,
                                          Card::executioner, Card::executioner,
                                          Card::diplomat,    Card::diplomat,
                                          Card::diplomat,    Card::commander,
                                          Card::commander,   Card::commander,
                                          Card::bodyguard,   Card::bodyguard,
                                          Card::bodyguard} {

  // Shuffle deck
  std::cout << "-- Shuffle Deck Begin -- \n";
  auto rng = std::default_random_engine(time(0));
  std::shuffle(deck.begin(), deck.end(), rng);

  // Create X numbers of players and distribute cards
  // Push top of deck into each players hands

  for (size_t i = 0; i < playerList.size(); i++) {
    std::cout << "Player " << i << " added. \n";
    Card first, second;
    first = deck.back();
    deck.pop_back();
    second = deck.back();
    deck.pop_back();
    players.at(i)->setHand(Hand(first, second));
  }
}

Player *gameState::getPlayer(std::string name) {
  for (auto &player : players)
    if (player->name == name)
      return player.get();
  return nullptr;
}

void gameState::generalIncome(std::string name) {
  getPlayer(name)->setCoin(getPlayer(name)->getCoin() + 1);
}

void gameState::generalAid(std::string name) {
  //request();
  getPlayer(name)->setCoin(getPlayer(name)->getCoin() + 2);
}

// [General Actions]
void gameState::generalOverthrow(std::string name, std::string target, int pos) {
  if (getPlayer(target)->isAlive()) {
    if (getPlayer(target)->hand.first == Card::empty)
      {
        deckGraveyard.push_back(getPlayer(target)->hand.second);
        getPlayer(target)->setAlive(false);
      }
    else if (getPlayer(target)->hand.second == Card::empty)
      {
        deckGraveyard.push_back(getPlayer(target)->hand.first);
        getPlayer(target)->setAlive(false);
      }
    else
      {
        if (pos == 0)
          {
            Hand temp = getPlayer(target)->getHand();
            deckGraveyard.push_back(getPlayer(target)->hand.first);
            temp.first = Card::empty;
            getPlayer(target)->setHand(temp);
          }
        if (pos == 1)
          {
            Hand temp = getPlayer(target)->getHand();
            deckGraveyard.push_back(getPlayer(target)->hand.second);
            temp.second = Card::empty;
            getPlayer(target)->setHand(temp);
          }
      }
  }
}

// [Baron]
void gameState::baronTax(std::string name) {
  // request();
  getPlayer(name)->setCoin(getPlayer(name)->getCoin() + 3);
}

void gameState::baronBlockAid(std::string name, std::string target) {
  // request()
}

// [Executioner]
void gameState::executionerExecute(std::string name, std::string target, int pos) {
  // request();
  if (getPlayer(target)->isAlive()) {
    if (getPlayer(target)->hand.first == Card::empty)
      {
        deckGraveyard.push_back(getPlayer(target)->hand.second);
        getPlayer(target)->setAlive(false);
      }
    else if (getPlayer(target)->hand.second == Card::empty)
      {
        deckGraveyard.push_back(getPlayer(target)->hand.first);
        getPlayer(target)->setAlive(false);
      }
    else
      {
        if (pos == 0)
          {
            Hand temp = getPlayer(target)->getHand();
            deckGraveyard.push_back(getPlayer(target)->hand.first);
            temp.first = Card::empty;
            getPlayer(target)->setHand(temp);
          }
        if (pos == 1)
          {
            Hand temp = getPlayer(target)->getHand();
            deckGraveyard.push_back(getPlayer(target)->hand.second);
            temp.second = Card::empty;
            getPlayer(target)->setHand(temp);
          }
      }
  }
}

// [Diplomat]
void gameState::diplomatExchange(std::string name) {
    // request();
    Card tempFirst = deck.back();
    deck.pop_back();
    Card tempSecond = deck.back();
    deck.pop_back();

    Hand tempHand = getPlayer(name)->getHand();

    int cardChosen = 0;
      // cardChosen = Display cards(); function will poll for users choice
      if (cardChosen == 0)
      {
          return;
      }
      else if (cardChosen == 1)
      {
        int replaceCard = 0;
        // replaceCard = chooseCard() getPlayer(name)->getHand();
        if (replaceCard == 0)
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.first = tempFirst;
            deck.insert(deck.begin(), tempSecond);
            getPlayer(name)->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.second);
            tempHand.second = tempFirst;
            deck.insert(deck.begin(), tempSecond);
            getPlayer(name)->setHand(tempHand);
          }
      }
      else {
        int replaceCard = 0;
        // replaceCard = chooseCard() getPlayer(name)->getHand();
        if (replaceCard == 0)
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.first = tempSecond;
            deck.insert(deck.begin(), tempFirst);
            getPlayer(name)->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.second = tempSecond;
            deck.insert(deck.begin(), tempFirst);
            getPlayer(name)->setHand(tempHand);
          }
      }
  }

void gameState::diplomatBlockLoot(std::string name) {
  // request ();
}

// [Admiral]
void gameState::admiralLoot(std::string name, std::string target) {
   // request ();
  if (getPlayer(target)->getCoin() > 2) {
    getPlayer(target)->setCoin(getPlayer(target)->getCoin() - 2);
    getPlayer(name)->setCoin(getPlayer(name)->getCoin() + 2);
  }
  else
  {
    abort();
  }
}

void gameState::admiralBlockLoot(std::string name) {
  // request();
}

// [Bodyguard]
void gameState::bodyguardBlockExecute(std::string name) {
  // request();
}

// [Magician] --- not implemented
void gameState::magicianExamine(std::string name, std::string target)
{
  // request ();
  Card temp;
  int chosenCard = 0;
  if (getPlayer(target)->getHand().first == Card::empty) {
    // display(getPlayer(target)->getHand().second);
    temp = getPlayer(target)->getHand().second;
    chosenCard = 1;
  }
  else if (getPlayer(target)->getHand().second == Card::empty)
    {
      // display(getPlayer(target)->getHand().first);
      temp = getPlayer(target)->getHand().first;
      chosenCard = 0;
    }
  else
    {
      // cardChosen select card from target
      if (chosenCard == 0)
        {
        // display(getPlayer(target)->getHand().first);
          temp = getPlayer(target)->getHand().first;
      }
      else // cardChosen == 1
        {
          // display(getPlayer(target)->getHand().second);
          temp = getPlayer(target)->getHand().second;
        }
    }
  int response = 0;
  // response = requestKeep();
  if (response = 0)
    {
      // keep
      return;
    }
  else // response 1 - discard
    {
      Hand tempHand = getPlayer(target)->getHand();
      Card newCard = deck.back();
      deck.pop_back();
      deck.insert(deck.begin(), temp);
      if (chosenCard == 0)
      {
        tempHand.first = newCard;
      }
      else
        {
          tempHand.second = newCard;
        }
      getPlayer(target)->setHand(tempHand);
    }
}

void gameState::magicianExchange(std::string name) {
    // request();
    Card tempFirst = deck.back();
    deck.pop_back();
    Card tempSecond = deck.back();
    deck.pop_back();

    Hand tempHand = getPlayer(name)->getHand();

    int cardChosen = 0;
      // cardChosen = Display cards(); function will poll for users choice
      if (cardChosen == 0)
      {
          return;
      }
      else if (cardChosen == 1)
      {
        int replaceCard = 0;
        // replaceCard = chooseCard() getPlayer(name)->getHand();
        if (replaceCard == 0)
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.first = tempFirst;
            deck.insert(deck.begin(), tempSecond);
            getPlayer(name)->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.second);
            tempHand.second = tempFirst;
            deck.insert(deck.begin(), tempSecond);
            getPlayer(name)->setHand(tempHand);
          }
      }
      else {
        int replaceCard = 0;
        // replaceCard = chooseCard() getPlayer(name)->getHand();
        if (replaceCard == 0)
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.first = tempSecond;
            deck.insert(deck.begin(), tempFirst);
            getPlayer(name)->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.second = tempSecond;
            deck.insert(deck.begin(), tempFirst);
            getPlayer(name)->setHand(tempHand);
          }
      }
}

void gameState::magicianBlockLoot(std::string name) {
  // request ();
}
