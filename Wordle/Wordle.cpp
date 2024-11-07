/*
	Wordle.cpp
	Matthew Bersalona 
	CSCI 123 C
	11/05/2024
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> words{ "sigma", "alpha", "omega", "white", "green", "phone" };

string selectWord(vector<string>& wordsList);
void guessWord(string guess, bool& correct, string word);
bool checkLetter(char letter, const vector<int>& correctIndexes,  vector<int>& usedIndexes, string word);

int main() {
	char gameState;

	do {
		string guessedWord;
		string wordToGuess = selectWord(words);
		int guessesLeft = 6;
		bool guessCorrect = false;

		cout << "Welcome to Wordle!" << endl << "e - letter is in the correct place" 
			<< endl << "(e) - letter appears in the word but in a different place" 
			<< endl << "{e} - letter does not appear in the word" << endl << endl;

		while (guessesLeft > 0 && !guessCorrect) {
			cout << "Enter a guess: ";
			cin >> guessedWord;

			while (guessedWord.length() != 5) {
				cout << "Guess must be a 5 letter word." << endl << endl;
				cout << "Enter a guess: ";
				cin >> guessedWord;
			}
			guessWord(guessedWord, guessCorrect, wordToGuess);
			cout << endl;
			guessesLeft--;
		}
		if (guessesLeft > 0 && guessCorrect) {
			cout << "Congratualtions! You guessed correctly." << endl;
		}
		else if (guessesLeft == 0 && !guessCorrect) {
			cout << "You're out of guesses. " << endl << "The word was " << words[0] << endl;
		}

		cout << "Do you want to play again (Y or N)? ";
		cin >> gameState;
		cout << endl;
	} while (gameState == 'Y' || gameState == 'y');

	return 0; 
}

string selectWord(vector<string>& wordsList) {
	srand(time(0));
	int randomIndex = rand() % wordsList.size();
	return wordsList[randomIndex];
}

void guessWord(string guess, bool& correct, string word) {
	vector<int> correctIndexes;
	vector<int> usedIndexes;
	for (int i = 0; i < guess.length(); i++) {
		if (guess[i] == word[i]) {
			correctIndexes.push_back(i);
		}
	}

	for (int i = 0; i < guess.length(); i++) {
		if (guess[i] == word[i]) {
			cout << guess[i];
		}
		else if (checkLetter(guess[i], correctIndexes, usedIndexes, word)) {
			cout << "(" << guess[i] << ")";
		} else if (!checkLetter(guess[i], correctIndexes, usedIndexes, word)) {
			cout << "{" << guess[i] << "}";
		}
	}
	cout << endl;

	if (guess == word) {
		correct = true;
	}
}

bool checkLetter(char letter, const vector<int>& correctIndexes, vector<int>& usedIndexes, string word){
	for (int i = 0; i < word.length(); i++) {
		if (letter == word[i] &&
			find(correctIndexes.begin(), correctIndexes.end(), i) == correctIndexes.end() &&
			find(usedIndexes.begin(), usedIndexes.end(), i) == usedIndexes.end()) {
			usedIndexes.push_back(i); 
			return true;
		}
	}
	return false;
}

