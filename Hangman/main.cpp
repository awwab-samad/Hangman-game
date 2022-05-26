#include "Functions.h"

using namespace std;

int main() //driver code
{
    char letter; //declare variables
    int wordLength;
    int guesses = 0;
    int tries = 6;

    bool winFlag = false; //winFlag is initialized to false
    bool gameRun = true; //gameRun is initialized to true

    string word;
    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //string of alphabets

    welcomeHangman(); //call welcome() function
    gameContinueHM(); //call gameContinue() function

    //loop only runs if gameRun is true
    while (gameRun)
    {
        word = gameStart(); //get the random word from file
        wordLength = word.length() - 1; //calculate word length

        char *fileWord = new char[wordLength]; //dynamically allocate memory for 2 arrays of size wordLength
        char *blankWord = new char[wordLength];

        for (int i = 0; i < wordLength; i++) //loop wordLength number of times
        {
            *(fileWord + i) = toupper(word[i]); //converts each letter to uppercase
            *(blankWord + i) = '_'; //puts underscore (blank space) to each index location
        }

        //loop runs only if 0 <= tries <= 6 and winFlag = false
        while ((tries <= 6 and tries > 0) and (winFlag == false))
        {
            cout << "\nPlease guess a letter: "; //ask user to guess letter
            cin >> letter;

            letter = checkLetter(letter, alphabets); //call checkLetter() function
            alphabets = removeLetter(letter, alphabets); //call removeLetter() function
            tries = checkGuess(letter, fileWord, blankWord, wordLength, tries); //call checkGuess() function
            winFlag = refreshDisplay(blankWord, wordLength, alphabets, guesses++, tries); //call refreshDisplay() function
        }

        gameOver(winFlag, word, guesses, tries); //call gameOver() function

        delete[] fileWord; //deallocate memory for the 2 arrays
        delete[] blankWord;

        gameRun = playAgain(gameRun); //call playAgain function

        alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //initialize variables again
        guesses = 0;
        tries = 6;
        winFlag = false;
    }

    return 0; //program end
}
