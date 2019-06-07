#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax unreal friendly
#define TMap std::map 
using FText = std::string;
using int32 = int;


FBullCowGame::FBullCowGame(){ Reset(); } // defaut constructor
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const	{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

/* void FBullCowGame::WordLengthChosen()
{
	int32 LengthOfWord;
	std::cin >> LengthOfWord;
	TMap <int32, FString> WordLengthToWord{ {3,"pig"} , {4,"deck"} ,{5,"nurse"} ,{6,"native"} };
	MyHiddenWord = WordLengthToWord[LengthOfWord];

	return;

}  */

int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5, 10}, {6,16} };


	return WordLengthToMaxTries[MyHiddenWord.length()];

}

void FBullCowGame::Reset()
{


	const FString HIDDEN_WORD = "native"; // this MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( Guess.length() != GetHiddenWordLength())// if the guess isn't an isogram,
	{
		return EGuessStatus::Wrong_Length;
	}
	else  if (!IsLowerCase(Guess))  // if the guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase; // 
	}
		
	else if (!IsIsogram(Guess))  // if the word length is wrong
	{
		return EGuessStatus::Not_Isogram;
	}
		
	else // otherwise
	{
		return EGuessStatus::OK;
	}
		
	
}




// receives a valid guess, increaments turn and returns count of bulls and cow
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;

	FBullCowCount BullCowCount;

    // loop through all the letter in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MYHchar = 0; MYHchar < WordLength; MYHchar++)
	{ // compare letters against  the guess ??
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{  // if they match then??	

			if (Guess[GChar] == MyHiddenWord[MYHchar]) 
			{
				if (MYHchar == GChar)  // if they're in the same place
				{
					BullCowCount.Bulls++; // increment bulls
	}
				else 
				{

					BullCowCount.Cows++; // must be cow
				}
			
			}
			
	}
	}
	if (BullCowCount.Bulls == WordLength) 
	{

		bGameIsWon = true;

	}

	else
	{
		bGameIsWon = false;
	}
	
	return BullCowCount;
}
// receive the guess and check if it's an isogram or not
bool FBullCowGame::IsIsogram(FString Guess) const{

   
	// treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1)
	{
		return true;
	}
	
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Guess) 
	{
		Letter = tolower(Letter);
	
		if (LetterSeen[Letter])  // if the letter is in the map
		{
			return false;  // we do NOT have an isogram
		}
		else  // otherwise
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen

		}

	}

	return true; // for exemple in cases where /0 is entered	



}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	

	for(auto Letter : Guess) 
	{
	
	if (!islower(Letter)) // if not a lowercase letter 
	{
	
		return false; 
	}
	
	else {} 
	}

	
	     
	return true; // for exemple in cases where /0 is entered	
}
