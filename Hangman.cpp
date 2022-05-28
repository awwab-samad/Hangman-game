#include "Functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//function for welcome & instructions
void welcomeHangman()
{
    cout << "\n\n=================================<INSTRUCTIONS>=================================" << endl;
    cout << "\nWelcome to Hangman!" << endl;
    cout << "\nYou will be given a random blank word." << endl;
    cout << "Your job is to guess it by guessing letters you think is in the word." << endl;
    cout << "You have 6 tries for any incorrect guess." << endl;
    cout << "Any incorrect guess and a hangman will begin to appear!" << endl;
    cout << "No more tries left and you lose!" << endl;
    cout << "Goodluck!" << endl;
}

void gameContinue() //function to continue game
{
    char start;
    bool gameRun = true; //gameRun initialized to true

    cout << "\nPress any key to continue, press q to quit: "; //begin game
    cin >> start;

    if (start == 'q') //user wants to quit
    {
        gameRun = false; //gameRun becomes false
        gameQuit(gameRun); //call gameQuit() function
    }
}

//function to start the game
string gameStart()
{
    string word; //declare variables
    int wordLength;

    cout << "\n====================================<NEWGAME>===================================" << endl;

    word = getWord(); //call getWord() function
    wordLength = word.length() - 1; //calculate wordLength

    cout << "\nHere is a " << wordLength << " letter word for you to guess." << endl;
    cout << "\nYou have 6 incorrect guesses remaining." << endl;
    cout << "\n";

    drawHangman(6); //call drawHangman() function

    cout << "\n";
    for (int i = 0; i < wordLength; i++) //print blank spaces for the mystery word
        cout << "_ ";

    cout << "\n\nLetter Bank:" << endl;
    for (int i = 'A'; i <= 'Z'; i++) //loop from A to Z
    {
        cout << char(i) << " "; //print alphabet

        if (i == 'J') //newline condition
            cout << "\n";
        else if (i == 'T') //newline condition
            cout << "\n    ";
    }
    cout << "\n";

    return word; //return random word from file
}

//function to get a random word from hangman words file
string getWord()
{
    string word; //declare variables
    int lineCounter = 0;

    ifstream hmFile; //create file handler to read the file
    hmFile.open("hangman words.txt"); //open file

    while (!hmFile.eof()) //read through entire file from top to bottom
    {
        getline(hmFile, word); //get each line
        lineCounter++; //increment lineCounter
    }

    srand(time(NULL)); //get seed from computer's internal clock
    int randNum = 1 + rand() % lineCounter; //seed the random number generator to generate random number from 1 to lineCounter

    hmFile.close(); //close file

    hmFile.open("hangman words.txt"); //open file
    for (int i = 1; i <= randNum; i++) //loop randNum number of times
        getline(hmFile, word); //get word on the random line number

    hmFile.close(); //close file

    //cout << randNum << endl; //testing purposes
    //cout << word << endl;

    return word; //return random word from file
}

//function to check the letter input
char checkLetter(char letter, string alphabets)
{
    int asciiCode; //declare variable

    while (!(letter >= 'a' and letter <='z') and !(letter >= 'A' and letter <= 'Z')) //input not letter
    {
        cout << "\nInvalid guess\nTry again: ";
        cin >> letter;
    }

    letter = toupper(letter); //convert letter to uppercase
    asciiCode = int(letter); //get ascii code of letter
    while (alphabets[asciiCode - 65] != letter) //letter has been guessed before
    {
        cout << "\nThat letter has already been guessed\nTry again: ";
        cin >> letter;

        while (!(letter >= 'a' and letter <='z') and !(letter >= 'A' and letter <= 'Z')) //input not letter
        {
            cout << "\nInvalid guess\nTry again: ";
            cin >> letter;
        }

        letter = toupper(letter); //convert letter to uppercase
        asciiCode = int(letter); //get ascii code of letter
    }

    return letter; //return correct letter
}

//function to remove the letter from alphabets string
string removeLetter(char letter, string alphabets)
{
    int asciiCode; //declare variable

    asciiCode = int(letter); //get ascii code of letter
    alphabets[asciiCode - 65] = ' '; //replace letter from alphabets with blank space

    return alphabets; //return alphabets
}

//function to check the user's guess
int checkGuess(char letter, const char *fileWord, char *blankWord, int wordLength, int tries)
{
    bool flag = false; //declare variable

    for (int i = 0; i < wordLength; i++) //loop wordLength number of times
    {
        if (*(fileWord + i) == letter) //condition for right letter
        {
            *(blankWord + i) = letter; //update blankWord to include letter
            flag = true; //flag becomes true
        }
    }
    if (flag == true) //right letter, flag is true
        cout << "\nGood guess! That letter was in the word!" << endl;

    if (flag == false) //wrong letter, flag is still false
    {
        cout << "\nBad guess! Now a part of the hangman has been drawn!" << endl;
        tries--; //tries decrements
    }

    return tries; //return tries remaining
}

//function to display hangman, blank word, letter bank, guesses, and tries
bool refreshDisplay(const char *blankWord, int wordLength, string alphabets, int guesses, int tries)
{
    bool winFlag = true; //declare variable

    drawHangman(tries); //calls drawHangman() function

    cout << "\n";
    for (int i = 0; i < wordLength; i++) //loop wordLength number of times
    {
        cout << *(blankWord + i) << ' '; //prints updated blankWord

        if (*(blankWord + i) == '_') //if blank word still has an underscore
            winFlag = false; //winFlag becomes false
    }

    cout << "\n\nLetter Bank:" << endl;
    for (int i = 0; i < 26; i++) //loop 26 times
    {
        cout << alphabets[i] << " "; //prints alphabets in "Letter Bank"

        if (i == 9) //newline condition
            cout << "\n";
        else if (i == 19) //newline condition
            cout << "\n    ";
    }

    cout << "\n\nGuesses made: " << guesses; //display guesses
    cout << "\nIncorrect guesses remaining: " << tries << endl; //display tries

    return winFlag; //return winFlag
}

//function to draw hangman
void drawHangman(int tries)
{
    switch(tries) //switch condition
    {
        case 6: //6 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |        " << endl;
            cout << "  |        " << endl;
            cout << "  |        " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 5: //5 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |        " << endl;
            cout << "  |        " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 4: //4 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |    |   " << endl;
            cout << "  |        " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 3: //3 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |   /|   " << endl;
            cout << "  |        " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 2: //2 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |   /|\\ " << endl;
            cout << "  |        " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 1: //1 try left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |   /|\\ " << endl;
            cout << "  |   /    " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
        case 0: //0 tries left
        {
            cout << "\n";
            cout << "  |----|   " << endl;
            cout << "  |    0   " << endl;
            cout << "  |   /|\\ " << endl;
            cout << "  |   / \\ " << endl;
            cout << " / \\      " << endl;
            cout << "===========" << endl;
            break;
        }
    }
}

//function to check game win or lose
void gameOver(bool win, string word, int guesses, int tries)
{
    if (win == true) //win condition
    {
        cout << "\n\nYOU WIN!" << endl;
        cout << "\nYay! You guessed the word! Now the man is free!";
    }
    if (win == false) //lose condition
        cout << "\n\nGAME OVER! You Lose!";

    displayStats(word, guesses, tries); //calls displayStats() function
}

//function to display game stats
void displayStats(string word, int guesses, int tries)
{
    cout << "\n\n===================================<GAMEOVER>===================================" << endl;
    cout << "\nGame statistics:" << endl;
    cout << "\nWord: " << word << endl; //display actual word
    cout << "Total guesses: " << guesses << endl; //display total guesses
    cout << "Total incorrect guesses: " << 6 - tries << endl; //display total incorrect guesses
}

//function to play again
bool playAgain(bool gameRun)
{
    char play; //declare variable

    cout << "\n\nWant to play again? y/n "; //ask to play again
    cin >> play;

    while (play != 'y' and play != 'Y' and play != 'n' and play != 'N') //check invalid input
    {
        cout << "\nInvalid input\nWant to play again? y/n "; //prompt user for input again
        cin >> play;
    }

    if (play == 'y' or play == 'Y') //yes condition
        gameRun = true; //gameRun becomes true
    if (play == 'n' or play == 'N') //no condition
        gameRun = gameQuit(gameRun); //calls gameQuit() function

    return gameRun; //return gameRun
}

//function to quit game
bool gameQuit(bool gameRun)
{
    cout << "\nThank you for playing! Have a nice day!";
    gameRun = false; //gameRun becomes false
    return gameRun; //return gameRun
}
