#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "Trick.h"

using namespace std;

int main (int argc, char* argv[])
{
	// set the current command line input to the first command
	// set the seed for the deck to 37 as default
	// set the maxScore to 40 as default
	int input = 0, seed = 37, maxScore = 40;

	// create the main deck
	Deck mainDeck;

	// create the players
    Player **players = new Player*[4];

	// createa boolean to check whether an input deck is used and input players is used
	bool usedInputDeck = false;
    bool usedInputPlayers = false;

	// create the filename of the file that will contain the input deck
	char *inputFileName;

	// loop while the input has not reached the end of the command line arguments
	while ( input != argc )
	{
		// create a string to store the next command
		string command = argv[input];

		// check if the command is "-r" which sets the seed
		if (command.compare("-r") == 0)
		{
			// increase the input by 1
			input++;

			// check if the next argument exists
			if(input > argc - 1)
			{
				cerr << "Error, -r requires another argument.  Aborting." << endl;
				exit(1);
			}

			// set the seed to the current input
			seed = atoi(argv[input]);

			// set the maind ecks random seed to the given seed
			mainDeck.setSeed(seed);
		}
		
		// check if the command is "-s" which sets the max score
		else if (command.compare("-s") == 0)
		{
			// increase the input by 1
			input++;

			// check if there are no more arguments then output error and exit
			if(input > argc - 1)
			  {
			    cerr << "Error, -s requires another argument.  Aborting." << endl;
			    exit(1);
			  }

			// set the maxscore to the current input
			maxScore = atoi(argv[input]);
			
			// check if the maxscore is 0 or less
			if ( maxScore <= 0 )
			{
				cerr << "Error, maxScore must be positive." << endl;
				exit(1);
			}
		}

		// check if the command is -d which inputs a deck
		else if (command.compare("-d") == 0)
		{
			// increase the input by 1
			input++;

			// check if there are no more arguments then output error and exit
			if(input > argc - 1)
			  {
			    cerr << "Error, -d requires another argument.  Aborting." << endl;
			    exit(1);
			  }

			// set the input deck value to true
            usedInputDeck = true;

			// set the filename to the current input command
			inputFileName = argv[input];

			// create a test ifstream to see if the file exists
			ifstream testFile(inputFileName);
			
			// if the file does not exist then output error to standard error, close the stream and exit
			if(!testFile.good())
			{
				cerr << "Error, couldn't open card deck input file \"" << inputFileName << "\"" << endl;
				testFile.close();
				exit(1);
			}
		}

		// check if the command is -p which gives 4 players
		else if (command.compare("-p") == 0)
		{
			// increase the input by 1
            input++;

			// set the boolean of using input players to true
            usedInputPlayers = true;

			// create a name string and the kind of player string
            string name;
            string kind;
            
			// loop 4 times for each player
            for (int i = 0; i < 4; i++)
			{
				// check if there are no more arguments then output error and exit
				if(input > argc - 1)
				{
					cerr << "Error, -p requires another argument.  Aborting." << endl;
					exit(1);
				}

				// set the name of the next player to the command input
                name = argv[input];

				// increase the input by 1
                input++;

				// check if there are no more arguments then output error and exit
				if(input > argc - 1)
				{
					cerr << "Error, -p requires another argument.  Aborting." << endl;
					exit(1);
				}

				// set the kind of player to the command input
                kind = argv[input];
                
				// check if the kind of player is human
                if (kind.compare("H") == 0)
				{
					// create a new human player with the given name
                    players[i] = new HumanPlayer(name);
                }
				// check if the kind of player is smart
                else if(kind.compare("S") == 0)
				{
					// create a new human player with a given name
                    players[i] = new SmartPlayer(name);
                }
				// check if the kind of player is random
                else if(kind.compare("R") == 0)
				{
					// increase the input by 1
                    input++;

					// check if there are no more arguments then output error and exit
					if(input > argc - 1)
					{
						cerr << "Error, -p requires another argument.  Aborting." << endl;
						exit(1);
					}

					// create a new integer for the random players seed and set it to the next argument
                    int playerSeed = atoi(argv[input]);

					// create a new random player with the given name and seed
                    players[i] = new RandomPlayer(name, playerSeed);
                }

				// if the given player kind is none of the above then output error and exit
				else
				{
					cerr << "Illegal player kind: \"" << kind << "\"" << endl;
					exit(1);
				}

				// increase the input if it is not less than 3
				if(i < 3)
					input++;
            }
		}
		// increase the input by 1
		input++;
	}

	// if there is no input deck then generate a default deck
    if (!usedInputDeck) {
        mainDeck.generate();
    }
	// if there is an input deck then create an ifstream with the filename and input the deck then close the stream
	else
	{
		ifstream givenDeck(inputFileName);
		givenDeck >> mainDeck;
		givenDeck.close();
	}

	// if there is no input players set default players
    if (!usedInputPlayers) {
        players[0] = new SmartPlayer("Alice");
        players[1] = new SmartPlayer("Bob");
        players[2] = new SmartPlayer("Carole");
        players[3] = new SmartPlayer("Ted");
    }
    
    //shuffle the deck
    mainDeck.shuffle();
    
	// set the hand to the first one
	int hand = 1;

	// create a boolean that checks if someoen has reached max score
	bool isLoser = false;

	// create the main trick
	Trick mainTrick;

	// while no player has reached maxScore yet
	while( !isLoser )
	{
		// declare a new game of hearts
		cout << "Starting a new game of Hearts. The MaxPoints is " << maxScore << ".\n\n\n";

		// declare the beginning of the hand and output the deck
		cout << "At the beginning of hand " << hand << ", here is the deck:" << endl;
		cout << "    ";
		mainDeck.print();
		cout << "\n\n\n";

		// deal out the cards to each player
		for (int j = 0; j < 13; j++) {
			players[(0+hand-1)%4]->insertCard(mainDeck.back());
			mainDeck.pop_back();
	        
			players[(1+hand-1)%4]->insertCard(mainDeck.back());
			mainDeck.pop_back();
	        
			players[(2+hand-1)%4]->insertCard(mainDeck.back());
			mainDeck.pop_back();
	        
			players[(3+hand-1)%4]->insertCard(mainDeck.back());
			mainDeck.pop_back();
		}

		// output the hand of each player
		cout << "Here are the hands for each player at the start of hand number " << hand << "\n\n";
		for(int i = 0; i < 4; i++)
		{
			// display the current players name and their cards
			cout << players[i]->showName() << " has these cards:" << endl;
			cout << "    ";
			players[i]->showCards();
			cout << "\n\n";
		}
		cout << endl;

		// set the boolean of the two of clubs being played as false
		bool TwoClubsPlayed = false;

		// initialize the current player
		int currentPlayer;

		// begin all 13 rounds
		for(int i = 1; i <= 13; i++)
		{
			cout << "Now starting round " << i << " of hand " << hand << endl;
			for(int j = 0; j < 4; j++)
			{
				// check if the two of clubs has been played yet
				if(!TwoClubsPlayed)
				{
					// go through each player until the one with holding the two of clubs is found
					for(int i = 0; i < 4; i++)
					{
						// if the player is holding the two of clubs, delete it from their hand
						if(players[i]->Remove2C())
						{
							// set the initial current player to the person who played the two of clubs
							currentPlayer = i;

							// insert the two of clubs into the trick
							mainTrick.insertCard(Card::TwoOfClubs, i);

							// output the player who played the two of clubs
							cout << "  " << players[i]->showName() << " has 2C and leads with it" << endl;
						}
					}
					// set the the value of the two of clubs being played to true
					TwoClubsPlayed = true;
				}
				// if no one held the two of clubs, proceed as normal
				else
				{
					// determine the card the current player will play
					Card playedCard = players[currentPlayer]->playCard(mainTrick);

					// insert that card into the trick
					mainTrick.insertCard(playedCard, currentPlayer);
				}
				// rotate to the next player
				currentPlayer = ( currentPlayer + 1 ) % 4;
			}
			
			// output the player who has the trump card and the cards they put into their hearts value
			cout << "  " << players[mainTrick.getTrumpPlayer()]->showName() << " won the trick and added the following cards:" << endl;
			cout << "    ";
			mainTrick.print();
			cout << "\n\n";

			// get the trump player from mainTrick, and add the hearts value of mainTrick to that player's total hearts value
			players[mainTrick.getTrumpPlayer()]->addTrickValue(mainTrick);

			// set the next rounds lead player to the current rounds trump player
			currentPlayer = mainTrick.getTrumpPlayer();

			// empty the trick
			mainTrick.emptyCardPile();
		}

		// output the score at the end of the hand
		cout << "At the end of hand " << hand << ", the score is:" << endl;
		cout << "    " << players[0]->showName() << "  " << players[0]->getHeartScore() << endl;
		cout << "    " << players[1]->showName() << "  " << players[1]->getHeartScore() << endl;
		cout << "    " << players[2]->showName() << "  " << players[2]->getHeartScore() << endl;
		cout << "    " << players[3]->showName() << "  " << players[3]->getHeartScore() << endl;
		
		// increase the hand count
		hand++;

		// generate a new deck
		mainDeck.generate();
		
		// shuffle the deck
		mainDeck.shuffle();

		// declare and initialize worst player and winner player to be first player
		int worstPlayer = 0;
		int winner = 0;

		// if the first player has reached maxScore then the game is over
		if( players[0]->getHeartScore() >= maxScore )
			isLoser = true;

		// check through each player to see who is worst and best
		for(int i = 0; i < 4; i++)
		{
			// if the heart score of the current player is greater than the max score and greater than the player
			// with the leading maxScore then set him as the worst player and declare a loser
			if ( players[i]->getHeartScore() >= maxScore && players[i]->getHeartScore() > players[worstPlayer]->getHeartScore())
			{
				worstPlayer = i;
				isLoser = true;
			}
			// if the current player has a lower score than the winner player, then set them as the winner
			if ( players[i]->getHeartScore() < players[winner]->getHeartScore() )
				winner = i;
		}

		// if there is a loser then output the end of the game and output who exceeded the maxPoints and who won the game
		if(isLoser)
		{
			cout << "\nThe game is over." << endl;
			cout << players[worstPlayer]->showName() << " has exceeded " << maxScore << " points." << endl;
			cout << "The winner is " << players[winner]->showName() << endl;
		}
	}

	// delete the players and their cards
	for(int i = 0; i < 4; i++)
	{
		delete(players[i]);
	}

	// delete the array of players
	delete [] players;
}
