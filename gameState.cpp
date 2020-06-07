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
  Player *p = getPlayer(name);
  p->setCoin(p->getCoin() + 1);
}

void gameState::generalAid(std::string name) {
  //request();
  Player *p = getPlayer(name);
  p->setCoin(p->getCoin() + 2);
}

void gameState::removeCard(std::string target, int pos){
  Player *t = getPlayer(target);
  if (t->isAlive()) {
    if (t->hand.first == Card::empty)
      {
        deckGraveyard.push_back(t->hand.second);
        t->setAlive(false);
      }
    else if (t->hand.second == Card::empty)
      {
        deckGraveyard.push_back(t->hand.first);
        t->setAlive(false);
      }
    else
      {
        if (pos == 0)
          {
            Hand temp = t->getHand();
            deckGraveyard.push_back(t->hand.first);
            temp.first = Card::empty;
            t->setHand(temp);
          }
        if (pos == 1)
          {
            Hand temp = t->getHand();
            deckGraveyard.push_back(t->hand.second);
            temp.second = Card::empty;
            t->setHand(temp);
          }
      }
  }
}

// [General Actions]
void gameState::generalOverthrow(std::string name, std::string target, int pos) {
  Player *p = getPlayer(name);
  if (p->getCoin() >= 7)
  {
    p->setCoin(p->getCoin() - 7);
    removeCard(target, pos);
  }
}

// [Baron]
void gameState::baronTax(std::string name) {
  // request();
  Player *p = getPlayer(name);
  p->setCoin(p->getCoin() + 3);
}

void gameState::baronBlockAid(std::string name, std::string target) {
  // request()
}

// [Executioner]
void gameState::executionerExecute(std::string name, std::string target, int pos) {
  // request();
  Player *p = getPlayer(name);
  Player *t = getPlayer(target);

  if (p->getCoin() >= 3)
    {
       p->setCoin(p->getCoin() - 3);
       removeCard(target, pos);
    }
}

// [Diplomat]
void gameState::diplomatExchange(std::string name) {
    Player *p = getPlayer(name);
    // request();

    if (deck.size() >= 2)
      {
        Card tempFirst = deck.back();
        deck.pop_back();
        Card tempSecond = deck.back();
        deck.pop_back();

        Hand tempHand = p->getHand();

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
                p->setHand(tempHand);
              }
            else
              {
                deck.insert(deck.begin(), tempHand.second);
                tempHand.second = tempFirst;
                deck.insert(deck.begin(), tempSecond);
                p->setHand(tempHand);
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
              p->setHand(tempHand);
            }
          else
            {
              deck.insert(deck.begin(), tempHand.first);
              tempHand.second = tempSecond;
              deck.insert(deck.begin(), tempFirst);
              p->setHand(tempHand);
            }
        }
      }
    else if (deck.size() == 1)
      {
        Card tempCard = deck.back();
        deck.pop_back();

        Hand tempHand = p->getHand();
        int cardChosen = 0;
        // displayCard() to choose whether or not to replace or not;
        if (cardChosen == 0)
          {
            return;
          }
        else if (cardChosen == 1)
          {
            if (p->getHand().first == Card::empty) {
              deck.insert(deck.begin(), tempHand.second);
              tempHand.second = tempCard;
              p->setHand(tempHand);
            }
            if (p->getHand().second == Card::empty) {
              deck.insert(deck.begin(), tempHand.first);
              tempHand.first = tempCard;
              p->setHand(tempHand);
            }
            // replaceCard() to request which to swap;
          }
      }
    else {
      return; // this needs to not skip the user's turn after
    }
  }

void gameState::diplomatBlockLoot(std::string name) {
  // request ();
}

// [Admiral]
void gameState::admiralLoot(std::string name, std::string target) {
  Player *p = getPlayer(name);
  Player *t = getPlayer(target);
  // request ();
  if (t->getCoin() > 2) {
    t->setCoin(t->getCoin() - 2);
    p->setCoin(p->getCoin() + 2);
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
  Player *p = getPlayer(name);
  Player *t = getPlayer(target);
  // request ();
  Card temp;
  int chosenCard = 0;
  if (t->getHand().first == Card::empty) {
    // display(getPlayer(target)->getHand().second);
    temp = t->getHand().second;
    chosenCard = 1;
  }
  else if (t->getHand().second == Card::empty)
    {
      // display(getPlayer(target)->getHand().first);
      temp = t->getHand().first;
      chosenCard = 0;
    }
  else
    {
      // cardChosen select card from target
      if (chosenCard == 0)
        {
        // display(getPlayer(target)->getHand().first);
          temp = t->getHand().first;
      }
      else // cardChosen == 1
        {
          // display(getPlayer(target)->getHand().second);
          temp = t->getHand().second;
        }
    }
  int response = 0;
  // response = requestKeep();
  if (response == 0)
    {
      // keep
      return;
    }
  else // response 1 - discard
    {
      Hand tempHand = t->getHand();
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
      t->setHand(tempHand);
    }
}

void gameState::magicianExchange(std::string name) {
    Player *p = getPlayer(name);
    // request();
    Card tempFirst = deck.back();
    deck.pop_back();
    Card tempSecond = deck.back();
    deck.pop_back();

    Hand tempHand = p->getHand();

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
            p->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.second);
            tempHand.second = tempFirst;
            deck.insert(deck.begin(), tempSecond);
            p->setHand(tempHand);
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
            p->setHand(tempHand);
          }
        else
          {
            deck.insert(deck.begin(), tempHand.first);
            tempHand.second = tempSecond;
            deck.insert(deck.begin(), tempFirst);
            p->setHand(tempHand);
          }
      }
}

void gameState::magicianBlockLoot(std::string name) {
  // request ();
}
