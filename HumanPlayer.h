#include <string>

#ifndef __HumanPlayer_H__
#define __HumanPlayer_H__

// a HumanPlayer inherits from Player and contains test cases
// for which cards are valid to play in a givfen situation
class HumanPlayer : public Player {
 public:
  // HumanPlayer constructor
  HumanPlayer(string name);

  // lead conditions
  Card lead();

  // throwOff conditions
  Card throwOff();

  // followSuit conditions
  Card followSuit(Trick &trick);
};


#endif
