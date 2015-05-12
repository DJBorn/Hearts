#include <iostream>
#include "Card.h"
#include "Player.h"
#include "Trick.h"
#include "SmartPlayer.h"


// smart player constructor calls player constructor with s appended to the beginning of their given name
SmartPlayer::SmartPlayer(string name): Player("s" + name) {}

// smart player's lead algorithm
Card SmartPlayer::lead()
{
	// set the cardIndex to 0
	int cardIndex = 0;

	// loop through the player's hand
	for(int i = 0; i < (int)hand.size(); i++)
	{
		// set the current card's index to the cardIndex only if EITHER:
		// - the rank of the current card is lower than the rank of the cardIndex
		// - the rank of the current card and the cardIndex is the same and the suit of the current card is lower than the
		//   suit of the cardIndex
		if(hand.at(i)->getRank() < hand.at(cardIndex)->getRank() ||
			(hand.at(i)->getRank() == hand.at(cardIndex)->getRank() && hand.at(i)->getSuit() < hand.at(cardIndex)->getSuit()))
			cardIndex = i;
	}

	// create a new card with the cardIndex's rank and suit
	Card play(hand.at(cardIndex)->getRank(), hand.at(cardIndex)->getSuit());

	// remove the card from the player's hand
	hand.removeCard(play);

	// output the player's name and which card they played
	cout << "  " << showName() << " led " << play << endl;

	// return the card they played
	return play;
}

// smart player's throwOff algorithm
Card SmartPlayer::throwOff()
{
	// set the highestHearts index to -1
	int highestHearts = -1;

	// set the highestGeneral index to 0
	int highestGeneral = 0;

	// create a new rank and suit
	Card::Rank rank;
	Card::Suit suit;

	// create a boolean that checks if the queen of spades is found
	bool QSFound = false;

	// loop through the player's hand
	for(int i = 0; i < (int)hand.size(); i++)
	{
		// if the current card is the queen of spades then set the boolean to check if it exists to true
		if(hand.at(i)->getRank() == Card::Queen && hand.at(i)->getSuit() == Card::Spades)
		{
			QSFound = true;
		}

		// if a hearts card has not been picked yet then pick the first hearts as the current highest hearts
		// if the heart has been picked then check if the current card is a hearts and its rank is greater than the current
		// highest hearts card
		if( (highestHearts == -1 && hand.at(i)->getSuit() == Card::Hearts) ||
			(hand.at(i)->getSuit() == Card::Hearts && hand.at(i)->getRank() > hand.at(highestHearts)->getRank()))
			highestHearts = i;
		
		// check if the rank of the current card is higher than the rank of the general card and if the rank is equal, check the suit
		if( hand.at(i)->getRank() > hand.at(highestGeneral)->getRank() )
			highestGeneral = i;
		else if( hand.at(i)->getRank() == hand.at(highestGeneral)->getRank() && 
			     hand.at(i)->getSuit() > hand.at(highestGeneral)->getSuit() )
			highestGeneral = i;
	}

	// if the queen of spades was found then set the rank and suit to the queen of spades
	if(QSFound)
	{
		rank = Card::Queen;
		suit = Card::Spades;
	}

	// if the queen of spades was not found and a hearts was found, then set the rank and suit to that card
	else if(highestHearts >= 0)
	{
		rank = hand.at(highestHearts)->getRank();
		suit = hand.at(highestHearts)->getSuit();
	}

	// if neither were found then set the rank and suit to the highest general card found
	else
	{
		rank = hand.at(highestGeneral)->getRank();
		suit = hand.at(highestGeneral)->getSuit();
	}

	// create a new card with the rank and suit
	Card play(rank, suit);

	// display the player's name and which card they played
	cout << "  " << showName() << " threw off " << play << endl;

	// remove the card from the player's hand
	hand.removeCard(play);

	// return the card they played
	return play;
}

// smart player's followSuit algorithm
Card SmartPlayer::followSuit(Trick &trick)
{
	// declare a suit that is set to the trick's leading suit
	Card::Suit suit = trick.getLeadingCard().getSuit();

	// create a new rank and suit
	Card::Rank playRank;
	Card::Suit playSuit;

	// create a bestCard and lowestCard both set to -1 
	// bestCard is the card which has a rank closest to the trump card's rank but be less than it
	// lowestCard is the card which has a rank closest to the trump card's rank but be greater than it
	int bestCard = -1;
	int lowestCard = -1;

	// loop through the player's hand
	for(int i = 0; i < (int)hand.size(); i++)
	{
		// check if the current card's suit is equal to the trick's leading suit
		if(hand.at(i)->getSuit() == suit)
		{
			// if the bestCard has not been found yet and the current card has lower rank than the trump card's rank then set the
			// bestCard to the current card
			if(bestCard == -1 && hand.at(i)->getRank() < trick.getTrumpCard().getRank())
				bestCard = i;

			// if a bestCard has been found and the current card has greater rank than the bestCard and lower rank than the trump
			// card's rank, then set the besCard to the current card
			else if(bestCard != -1 && hand.at(bestCard)->getRank() < hand.at(i)->getRank() && hand.at(i)->getRank() < trick.getTrumpCard().getRank())
				bestCard = i;

			// if the lowestCard has not been found yet and the current card has higher rank than the trump card's rank then set the
			// lowestCard to the current card
			if(lowestCard == -1 && hand.at(i)->getRank() > trick.getTrumpCard().getRank())
				lowestCard = i;

			// if a lowestCard has been found and the current card has lower rank than the lowestCard and higher rank than the trump
			// card's rank, then set the lowestCard to the current card
			else if(lowestCard != -1 && trick.getTrumpCard().getRank() < hand.at(i)->getRank() && hand.at(i)->getRank() < hand.at(lowestCard)->getRank())
				lowestCard = i;
		}
	}

	// if the bestCard has been found then set the rank and suit to that card
	if(bestCard >= 0)
	{
		playRank = hand.at(bestCard)->getRank();
		playSuit = hand.at(bestCard)->getSuit();
	}

	// if the bestCard has not been found then set the rank and suit to the lowestCard
	else
	{
		playRank = hand.at(lowestCard)->getRank();
		playSuit = hand.at(lowestCard)->getSuit();
	}

	// create a new card with the rank and suit
	Card play(playRank, playSuit);

	// output the player's name and the card they played
	cout << "  " << showName() << " followed suit with " << play << endl;

	// remove that card from their hand
	hand.removeCard(play);

	// return the card they played
	return play;
}
