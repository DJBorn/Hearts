#include <string>

#ifndef __RandomPlayer_H__
#define __RandomPlayer_H__

// a RandomPlayer inherits from Player and chooses a valid random card
// in any given situation
class RandomPlayer : public Player {
 private:
  // contains the seed of the player
  PRNG prng;
 public:
  // RandomPlayer constructor
  RandomPlayer(string name, int seed);

  // lead choice
  Card lead();

  // throwOff choice
  Card throwOff();

  // followSuit choice
  Card followSuit(Trick &trick);
};

#endif
