#include <string>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "Card.h"

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

// We'll give you this one.
Card::Card() : rank(Ace), suit(Spades) {}

// Now you do the rest.

// Card Destructor
Card::~Card()
{
}

// Get value of card
int Card::getHeartsValue() const
{
  // return 1 if the card is a hearts
  if ( suit == Hearts )
    return 1;

  // return 13 if the cark is the queen of spades
  else if ( suit == Spades && rank == Queen )
    return 13;

  // all other cards return 0
  return 0;
}

// Check if a string is a legal card
bool Card::stringIsALegalCard(string s)
{
  // return true if the string is of length 2, the first character in the string is an element in RankName and the
  // second element is in SuitName
  return( s.length() == 2 && (int)RankName.find(s.at(0)) >= 0 && (int)SuitName.find(s.at(1)) >= 0);
}

// return the rank of a card
Card::Rank Card::getRank() const
{
  return rank;
}

// return the suit of a card
Card::Suit Card::getSuit() const
{
  return suit;
}

// check if the left card has lower value than the right card
bool operator< (const Card& c1, const Card& c2)
{
  // if the rank of c1 is less than the rank of c2, then return true
  if ( c1.getRank() < c2.getRank() )
    return true;
  if ( c1.getRank() > c2.getRank() )
    return false;
  // if they're the same, then if the suit of c1 is less than the suit of c2, return true
  return ( c1.getSuit() < c2.getSuit() );
}

// check if two cards are the same
bool operator== (const Card& c1, const Card& c2)
{
  // return true if the rank and suit of c1 and c2 are the same
  return ( c1.getRank() == c2.getRank() && c1.getSuit() == c2.getSuit() );
}

// output a card to standard output
ostream& operator<< (ostream &out, const Card &c)
{
  // output the rank first and then the suit
  return out << c.RankName.at(c.getRank()) << c.SuitName.at(c.getSuit());
}

// get a card from standard input
istream& operator>> (istream& in, Card& c)
{
  // create a new string
  string card;

  // input that string
  in >> card;

  // if the card is not a legal card then terminate program with error message
  if ( !Card::stringIsALegalCard( card ) )
    {
      cerr << "Error, " << card << " is not a legal card.  Aborting." << endl;
      exit(1);
    }

  // create a rank by taking the first character of the inputted string and finding it's index in RankName then converting it to
  // the rank enum. Do the same for suit by finding it in SuitName
  Card::Rank rank = (Card::Rank)c.RankName.find(card[0]);
  Card::Suit suit = (Card::Suit)c.SuitName.find(card[1]);

  // create a new card with the rank and suit values and set the given card to the new card
  Card newCard(rank, suit);
  c = newCard;

  // return
  return in;
}

// Card constructor with given rank and suit
Card::Card(Card::Rank r, Card::Suit s)
{
  // set the rank and suit to the given variables
  rank = r;
  suit = s;
}

Card::Card(string sCard)
{
  // if the card is not a legal card then terminate program with error message
  if ( !Card::stringIsALegalCard( sCard ) )
    {
      cerr << "Error, " << sCard << " is not a legal card.  Aborting." << endl;
      exit(1);
    }

  // create a rank by taking the first character of the inputted string and finding it's index in RankName then converting it to
  // the rank enum. Do the same for suit by finding it in SuitName
  rank = (Card::Rank)Card::RankName.find(sCard.at(0));
  suit = (Card::Suit)Card::SuitName.find(sCard.at(1));

}
