#include <iostream>
#include "Card.h"
#include "Player.h"
#include "Trick.h"
#include "HumanPlayer.h"


// Human Player constructor calls player constructor with h appended to the given name
HumanPlayer::HumanPlayer(string name): Player("h" + name) {}

// human player's lead algorithm
Card HumanPlayer::lead()
{
	// create a new string of the card choice
	string strCard = "";

	// display the human player's name and their cards
	cout << "Human player " << showName() << " has these cards:" << endl;
	cout << "	";
	showCards();
	cout << endl;

	// ask for cards until a valid one is given
	for(;;)
	{
		// ask the user which card they would like to play
		cout << "What card would you like to play, " << showName() << "? ";

		// input the card string
		cin >> strCard;

		// check if it is a legal card, if it is then break the loop
		if( Card::stringIsALegalCard(strCard) )
			break;

		// output that the card is not a legal card and ask again
		cout << strCard << " is not a card" << endl;
	}

	// create a new card with the given string
	Card play(strCard);

	// remove that card from their hand
	hand.removeCard(play);

	// output their name and which card they played
	cout << "  " << showName() << " led " << play << endl;

	// return the card they played
	return play;
}

// human player's throwOff algorithm
Card HumanPlayer::throwOff()
{
	// create a new string of the card chocie
	string strCard = "";

	// display the user and their cards
	cout << "Human player " << showName() << " has these cards:" << endl;
	cout << "	";
	showCards();
	cout << endl;

	// ask for cards until a valid one is given
	for(;;)
	{
		// ask the user which card they would like to play
		cout << "What card would you like to play, " << showName() << "? ";

		// input the card string
		cin >> strCard;

		// check if it is a legal card, if it is then break the loop
		if( Card::stringIsALegalCard(strCard) )
			break;

		// output that the card is not a legal card and ask again
		cout << strCard << " is not a card" << endl;
	}

	// output the player's name and the card they played
	cout << "  " << showName() << " threw off " << strCard << endl;


	// create a new card with the given string
	Card play(strCard);

	// remove that card from their hand
	hand.removeCard(play);

	// return the card they played
	return play;
}

// human player's followSuit algorithm
Card HumanPlayer::followSuit(Trick &trick)
{
	// create a new string of the card chocie
	string strCard = "";

	// create a suit and set it the to the trick's leading card suit
	Card::Suit suit = trick.getLeadingCard().getSuit();

	// output the player and their cards
	cout << "Human player " << showName() << " has these cards:" << endl;
	cout << "	";
	showCards();
	cout << endl;

	// continue asking for cards until a valid one is given
	for(;;)
	{
		// ask the user which card they would like to play
		cout << "What card would you like to play, " << showName() << "? ";
		cin >> strCard;
		// check if the player played a proper card
		if( Card::stringIsALegalCard(strCard) )
		{
			// set the boolean of checking if the inputted card is not in their hand to true
			bool notInHand = true;

			// check if the player played the proper suit
			if ( (Card::Suit)Card::SuitName.find((strCard.at(1))) != suit )
			{
				// display the suit the player must play and reset the loop
				cout << "You have at least one " << Card::SuitName.at(suit) << "; you must follow that suit!" << endl;
				continue;
			}

			// loop through the player's hand
			for(int i = 0; i < (int)hand.size() ; i++)
			{
				// if the inputted card is in the player's hand then set the boolean notInHand to false
				if(hand.at(i)->getRank() == (Card::Rank)Card::RankName.find((strCard.at(0))) &&
					hand.at(i)->getSuit() == (Card::Suit)Card::SuitName.find((strCard.at(1))))
					notInHand = false;
			}

			// check if the given player card is not in their hand
			if(notInHand)
			{
				// output that the card is not in their hand and reset the loop
				cout << strCard << " is not in your hand" << endl;
				continue;
			}

			// break the loop otherwise
			break;
		}

		// if the loop did not break then the player did not play a proper card
		cout << strCard << " is not a card" << endl;
	}

	// output the user and the card they played
	cout << "  " << showName() << " followed suit with " << strCard << endl;

	// create a new card with the given input card
	Card play(strCard);

	// remove that card from the player's hand
	hand.removeCard(play);

	// return the card they played
	return play;
}
