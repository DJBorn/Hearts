
#ifndef __Player_H__
#define __Player_H__

#include <iostream>
#include <string>
#include "PRNG.h"
#include "CardPile.h"
#include "Trick.h"

using namespace std;

// A Player is a virtual function that holds the player's name, heartScore, their hand
// and has functions that determine which card the player should play depending on
// their hand and the trick. It also has functions that check certain conditions
// and return or output certain values of the Player.
class Player {
 private:
  // create pure virtual lead, throwOff, followSuit functions
  virtual Card lead() = 0;
  virtual Card throwOff() = 0;
  virtual Card followSuit(Trick &trick) = 0;

 protected:
  // store heartScore, name of the player, and the player's hand
  int heartScore;
  string name;
  CardPile hand;

 public:
  // create a function that takes in a trick and adds the trick hearts value
  void addTrickValue(CardPile &trick);

  // check if the player can follow the suit
  bool canFollowSuit(Trick &trick);

  // decides which card the player should use
  Card playCard(Trick &trick);

  // removes every card
  ~Player();

  // removes the two of clubs and returns true if one existed, false otherwise
  bool Remove2C();

  // outputs the cards
  void showCards();

  // gets the heartscore of the player
  int getHeartScore();

  // outputs the name of the player
  string showName();

  // inserts a card to the player's hand
  void insertCard(Card *card);

  // player constructor with their name
  Player(string name);
};

#endif
