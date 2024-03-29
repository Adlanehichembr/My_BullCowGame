/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction, For game logic, see the FBullCowGame class

*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly 
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game which we re-use across plays 
void PrintGameSummary();

// the entry point for our application
int main() 
{	
	bool bPlayAgain = false;
	do {
	PrintIntro();
	PlayGame();
	bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	
	return 0; // exit the application
}


void PrintIntro()
{

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;

}

// plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	

	//	loop asking for guesses while the game
	//	is NOT won and there are still tries remaining

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		FText Guess = GetValidGuess();

		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << " Cows= " << BullCowCount.Cows << "\n\n";

		if (BullCowCount.Bulls == 5 || BullCowCount.Bulls == 4)
		{
			std::cout << "You're almost there!\n\n";
		}
	}

	PrintGameSummary();
	
	return; // good practice to always return even if void
}
// loop continually until the user gives  a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << "/" << BCGame.GetMaxTries();
		std::cout <<". Enter your guess: ";
		
		std::getline(std::cin, Guess);

	    Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter without repeating letters word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assuming the guess is valid	
			
			break;

		}
	} while (Status!=EGuessStatus::OK);
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n) ? ";
	FText Response = "";
	std::getline(std::cin, Response); 

	return (Response[0] == 'y') || (Response[0] == 'Y'); 
}

 void PrintGameSummary() {
    
	 
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WON!\n\n";
	}
	else
	{
		std::cout << "Good luck Next time!\n\n";
	}
	return;
} 


