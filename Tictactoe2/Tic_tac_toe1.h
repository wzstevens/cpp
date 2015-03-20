#include <iostream>
#include <vector>
using namespace std;

class TicTacToe{
private:

	//player number
	int playerNumber = 0;
	//assign a sign for each user
	char sign[50];//50 should be playerNumber!!!!!
	char signOfPlayer = 0;
	//all sign could be used
	string symbol = "XOABCDEFGHIJKLMNPQRSTUVWYZ";
	//chess piece number
	int winChessNumber;
	//ask user for board size
	int boardSize = 2;
	vector<vector<char>> vect;
	//get user inputx and inputy
	int inputx, inputy;
	//save winning sign[i] to winningSign
	char winningSign;

public:
	//user's choice for start a new game or resume last game
	string startOrResume = "";
	TicTacToe();
	//estimate if this is the first time playing this game by check if the savedState.txt is null
	bool savedState();
	//ask if the user wants to start a new game or resume last game.
	bool userChoice(string startOrResume);
	//start a new game
	void newStarter();
	//resume last game
	void resumeGame();
	//read game setup and state from savedState.txt
	void setupGameState();
	//player number and sign for each of them
	void gameSetup();
	//check for winning possibility
	bool winningPossibility();
	bool getEvenResult();
	//draw board according to board size
	void drawBoard(int boardSize);
	//save user sign and couple of position(x,y) to file savedState.txt
	void saveFile(char sign,int inputx,int inputy);
	//input row and column number or quit or quit and save
	void getUserInput(ofstream& fileout);
	void saveAndExit();
	bool empty(int i, int j);
	bool findWinner();
	void printOutResult();
	void timedelay(long long timeuse);

};
