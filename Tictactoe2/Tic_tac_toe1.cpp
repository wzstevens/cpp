#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <time.h>
#include "windows.h"
#include "Tic_tac_toe1.h"
using namespace std;

TicTacToe::TicTacToe(){
}

bool TicTacToe::savedState(){
	ifstream in1("savedState.txt");
	string str;
	in1 >> str;
	in1.close();
	if (str.empty()){//str.empty() == 1
		if (str.empty()){
			return 0;//empty file
		}
	}
	else{
		return 1;//file with state
	}
}
bool TicTacToe::userChoice(string startOrResume){
	if (startOrResume == "no" || startOrResume == "n"){
		//if no, start new game
		return 0;
	}
	else if (startOrResume == "yes" || startOrResume == "y"){
		return 1;
	}
	//why there must have a return? and how should I write?
	return 0;
}

void TicTacToe::newStarter(){
	//get user number and assign each user a sign, and ask for a win sequence
	gameSetup();
	//check winning possibility
	while (winningPossibility() == 0){//0 means nobody could win
		cout << "No one will win, please set up the game again"<<endl;
		gameSetup();
	}

	drawBoard(boardSize);
	//user input interrupted only if input is q or qw
	ofstream fileout2("savedState.txt");
	do{
		getUserInput(fileout2);
	} while (1);
	fileout2.close();
	saveAndExit();
}

void TicTacToe::resumeGame(){
	setupGameState();
	drawBoard(boardSize);
}

void TicTacToe::gameSetup(){
	cout << "Please input user number:";
	cin >> playerNumber;
	while (cin.fail() || playerNumber<2 || playerNumber > 26){
		cout << "Players should be at least 2 and not exceed 26 players, please input user number: " << endl;
		cin.clear();
		cin.sync();
		cin >> playerNumber;
	}
	for (int i = 0; i < playerNumber; i++){
		sign[i] = symbol.at(i);
	}
	cout << "Please input the win sequence:\n";
	cout << "how many same chess pieces in a line:";
	cin >> winChessNumber;
	while (cin.fail()){
		cout << "Please input winning chess number: " << endl;
		cin.clear();
		cin.sync();
		cin >> winChessNumber;
	}
	cout << "how large the board is:";
	cin >> boardSize;
	while (cin.fail()){
		cout << "Please input board size: " << endl;
		cin.clear();
		cin.sync();
		cin >> winChessNumber;
	}
	ofstream fileout1("savedSetup.txt");
	fileout1 << playerNumber << " " << winChessNumber << " "
		 << boardSize << " ";
	fileout1.close();
	vect.resize(boardSize);
	for (int i = 0; i < vect.size(); i++){
		vect[i].resize(boardSize);
	}
	for (int i = 0; i < vect.size(); i++){
		for (int j = 0; j < vect.size(); j++){
			vect[i][j] = '   ';
		}
	}
}

void TicTacToe::drawBoard(int boardSize){
	// line 0 is always like this
	cout << "  1";
	for (int i = 2; i <= boardSize; i++){
		cout << "   " << i;
	}
	cout << endl;

	for (int i = 1; i <= boardSize; i++){
		cout << i;
		for (int j = 1; j <= boardSize; j++){
			cout << " " << vect[i - 1][j - 1] << " ";
			if (j != boardSize){
				cout << "|";
			}
		}
		cout << endl;
		if (i != boardSize){
			cout << " ";
			for (int j = 0; j < boardSize - 1; j++){//get the column number
				cout << "---+";
			}
			cout << "---" << endl;
		}
	}
}

//not used
//save user sign and couple of position(x,y) to file savedState.txt
void TicTacToe::saveFile(char sign, int inputx, int inputy){
}

void TicTacToe::setupGameState(){
	ifstream filein1("savedSetup.txt");
	ifstream filein2("savedState.txt");

	if (filein1.good()){
		filein1 >> playerNumber>> winChessNumber >> boardSize;
	}
	else{
		cout << "sorry, file not found." << endl;
	}
	for (int i = 0; i < playerNumber; i++){
		sign[i] = symbol.at(i);
	}
	vect.resize(boardSize+1);
	for (int i = 0; i < vect.size(); i++){
		vect[i].resize(boardSize+1);
	}
	for (int i = 0; i < vect.size(); i++){
		for (int j = 0; j < vect.size(); j++){
			vect[i][j] = '   ';
		}
	}
	int k = 0, s = 0;
	char sign = 0;
	double time_span = 0.0;

	while (filein2 >> k >> s >> sign >> time_span){
		inputx = k + 1;
		inputy = s + 1;
		signOfPlayer = sign;
		if (findWinner() == true){
			printOutResult();
			cout << "restart game:" << endl;
		}
		vect[k][s] = sign;
		timedelay(time_span);
		drawBoard(boardSize);
	}
	if (findWinner() == true){
		gameSetup();
	}

	//check winning possibility
	while (winningPossibility() == false){//0 means nobody could win
		cout << "No one win the game, restart game:"<<endl;
		gameSetup();
	}
	
	cout << "Continue last game:" << endl;
	//user input interrupted only if input is q or qw
	ofstream fileout2("savedState.txt");
	do{
		getUserInput(fileout2);
	} while (inputx != 'q' || inputx != 'qw');
	fileout2.close();
	saveAndExit();
}

void TicTacToe::getUserInput(ofstream& fileout2){
	//define inputx1--inputxn and inputy1--inputyn for users and get input from console
	for (int i = 0; i < playerNumber; i++){
		cout << "Player" << sign[i] << ", this is your turn, please input the coordinate: (i.e. 2 2)£¬ if you want to exit, input -1:" << endl;
		//get user input
		int inputch;
		time_t begin = clock();
		cin >> inputch;
		if (inputch != -1){
			while (inputch > boardSize || inputch < 1){
				cout << "Invalid x input. Please input again: " << endl;
				cin >> inputch;
			}
		}
		if (1 <= inputch && inputch <= boardSize)
		{
			inputx = inputch;
			cin >> inputy;
			//catch exception,or input position is not empty, input again
			while (cin.fail()  || inputy > boardSize || inputy < 1){
				cout << "Invalid y input. Please input again: " << endl;
				cin.clear();
				cin.sync();
				//continue;
				cin >> inputy;
			}		
			while (empty(inputx - 1, inputy - 1) == false){
				cin >> inputx >> inputy;
			}
			time_t end = clock();
			long time_span = end - begin;
			//set vect[][] of this input the sign[i]
			vect[inputx - 1][inputy - 1] = sign[i];
			signOfPlayer = sign[i];
			//redraw the board
			system("cls");
			drawBoard(boardSize);
			fileout2 << inputx - 1 << " " << inputy - 1 << " " << signOfPlayer<< " "<< time_span << "\n";
		}
		else if (inputch == -1){
			exit(1);
		}
		
		//define a method to decide if one of the player win the game.
		//if find winner, do not return, call function printOutResult(), and that function will go to the end and exit
		if (findWinner() == true){
			printOutResult();
			fileout2.close();
			exit(1);
		}
		else if (winningPossibility() == false){
			printOutResult();
			fileout2.close();
			exit(1);
		}
	}
}

void TicTacToe::timedelay(long long timeuse)
{
	//for debug
	long long time = clock();
	clock_t start_time = clock();
	clock_t end_time = timeuse + start_time;
	while (clock() <= end_time);
}

void TicTacToe::saveAndExit(){

}

bool TicTacToe::empty(int i, int j){
	if (vect[i][j] == ' '){
		return true;
	}
	else{
		cout << "Sorry, this spot is not empty, please input again." << endl;
		return false;
	}
}

bool TicTacToe::winningPossibility(){
	if (playerNumber > 26 || playerNumber < 2){
		return 0;
	}
	if (boardSize < 0){
		return 0;
	}
	if (boardSize == 1){
		return 0;
	}
	if (boardSize > 1 && boardSize * boardSize < playerNumber){
		return 0;
	}
	if (winChessNumber < 0){
		return 0;
	}
	if (winChessNumber == 1){
		return 0;
	}
	if (winChessNumber > 1 && winChessNumber > boardSize){
		return 0;
	}
	//here should be >=??
	if (winChessNumber > 1 && winChessNumber * playerNumber >= boardSize * boardSize){
		return 0;
	}
	//if get even result, return false; else return true
	if (getEvenResult() == false){
		return false;
	}

	return true;
}

bool TicTacToe::findWinner(){
	int count = 1;
		for (int i = 1; i < winChessNumber; i++){
			if (inputy-i >= 1){
				if (vect[inputx-1][inputy-1 -i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		for (int i = 1; i < winChessNumber; i++){
			if (inputy + i <= boardSize){
				if (vect[inputx-1][inputy-1+i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		if (count >= winChessNumber){ return true; }
		else{ count = 1; }
		for (int i = 1; i < winChessNumber; i++){
			if (inputx + i <= boardSize){
				if (vect[inputx-1+i][inputy-1] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		for (int i = 1; i < winChessNumber; i++){
			if (inputx - i >= 1){
				if (vect[inputx-1-i][inputy-1] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		if (count >= winChessNumber){ return true; }
		else{ count = 1; }
		for (int i = 1; i < winChessNumber; i++){
			if (inputx +i <= boardSize && inputy + i <= boardSize){
				if (vect[inputx-1 + i][inputy-1 + i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		for (int i = 1; i < winChessNumber; i++){
			if (inputx - i >=1 && inputy - i >= 1){
				if (vect[inputx-1 - i][inputy-1 - i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		if (count >= winChessNumber){ return true; }
		else{ count = 1; }
		for (int i = 1; i < winChessNumber; i++){
			if (inputx + i <= boardSize && inputy - i >= 1){
				if (vect[inputx-1 + i][inputy-1 -i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		for (int i = 1; i < winChessNumber; i++){
			if (inputx - i >= 1 && inputy + i < boardSize){
				if (vect[inputx-1 - i][inputy-1 + i] == signOfPlayer){
					count++;
				}
				else break;
			}
			else break;
		}
		if (count >= winChessNumber){ return true; }
	return false;
}

bool TicTacToe::getEvenResult(){
	int count = 0;
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			if (vect[i][j] != ' '){
				count++;
			}
		}
	}
	if (count == boardSize * boardSize){
		return false;
	}
	else{ return true; }
}

void TicTacToe::printOutResult(){
	if (findWinner() == true){
		cout << "Congratulation, Player " << signOfPlayer << "! You win!" << endl;
	}
	else if (winningPossibility() == false){
		cout << "Game Over! You are even." << endl;
	}
}