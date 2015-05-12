#include <string>

#ifndef __SmartPlayer_H__
#define __SmartPlayer_H__

// a SmartPlayer inherits from Player and contains algorithms for which
// cards they should play in certain situations
class SmartPlayer : public Player {
 public:
  // SmartPlayer constructor
  SmartPlayer(string name);

  // lead algorithm
  Card lead();

  // throwOff algorithm
  Card throwOff();

  // followSuit algorithm
  Card followSuit(Trick &trick);
};

#endif
