
#include <iostream>
#include "Card.h"
#include "Player.h"
#include "Trick.h"



// create the player with the given name and set the heart score to 0 intially
Player::Player(string name): name(name)
{
  heartScore = 0;
}

// add the trick value to the Player's hearts value
void Player::addTrickValue(CardPile &trick)
{
  heartScore += trick.heartsValue();
}

// call the emptyCardPile function on the players hand to remove their cards
Player::~Player()
{
  hand.emptyCardPile();
}

// returns the hearscore of the player
int Player::getHeartScore()
{
  return heartScore;
}

// removes the two of clubs
bool Player::Remove2C()
{
  // search through the players hand
  for(int i = 0; i < (int)hand.size(); i++)
    {
      // check if the current card is the two of clubs
      if(hand.at(i)->getRank() == Card::Two && hand.at(i)->getSuit() == Card::Clubs)
	{
	  // delete the card
	  delete(hand.at(i));

	  // erase it from the vector
	  hand.erase(hand.begin()+i);

	  // return true
	  return true;
	}
    }

  // if the card was not found then return false
  return false;
}

// print the players hand
void Player::showCards()
{
  // loop through the player's hand
  for(int i = 0; i < (int)hand.size(); i++)
    {
      // output the rank then suit followed by a space
      cout << Card::RankName.at(hand.at(i)->getRank());
      cout << Card::SuitName.at(hand.at(i)->getSuit());
      cout << " ";
    }
}

// return the name of the player
string Player::showName()
{
  return name;
}

// insert a card into the players hand
void Player::insertCard(Card *card)
{
  // call the push_back function on the hand with the card
  hand.push_back(card);
}

// check if the player can follow the suit
bool Player::canFollowSuit(Trick &trick)
{
  // loop through the player's hand
  for(int i = 0; i < (int)hand.size(); i++)
    {
      // if the current card's suit is equal to the trick's leading card suit return true
      if( hand.at(i)->getSuit() == trick.getLeadingCard().getSuit() )
	return true;
    }

  // if no such card is found then return false
  return false;
}

// determine which card the player should pick
Card Player::playCard(Trick &trick)
{
  // if the size of the trick is 0 then the player will use their leading technique
  if((int)trick.size() == 0)
    {
      return lead();
    }
  // if the player can follow the suit then the player will use their followSuit technique
  else if(canFollowSuit(trick))
    {
      return followSuit(trick);
    }
  // otherwise they use their throwOff technique
  else
    return throwOff();
}
