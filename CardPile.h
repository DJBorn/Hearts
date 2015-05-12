#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : private vector<Card*> {
 public:
  // Constructors and destructor
  CardPile ();
  virtual ~CardPile ();

  // remove a card from the cardpile
  void removeCard(Card &card);

  // remove all cards for the cardpile
  void emptyCardPile();

  virtual void print();

  // return total hearts value to a cardpile, including queen of spades
  int heartsValue();

  void setSeed(uint32_t seed);

  // shuffles deck
  void shuffle();

  // promote certain vector functions
  using vector<Card*>::begin;
  using vector<Card*>::back;
  using vector<Card*>::size;
  using vector<Card*>::at;
  using vector<Card*>::push_back;
  using vector<Card*>::pop_back;
  using vector<Card*>::clear;
  using vector<Card*>::erase;

 private:
  PRNG prng;
  static const uint32_t DefaultRandomSeed;

};

#endif
