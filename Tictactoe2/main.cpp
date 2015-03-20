#include "Tic_tac_toe1.h"
#include <iostream>
#include <string>
using namespace std;
void main(){
	TicTacToe Test;
	//savedState is the name of the file that saved the state of the game
	if (Test.savedState()==0){//if this is a new game, the file should be 0 byte
		Test.newStarter();
	}
	else{//ask if the user wants to start a new game or resume last game.
		cout << "Do you want to resume last game?(yes/y for resume, no/n for restart)";
		cin >> Test.startOrResume;
		if (Test.userChoice(Test.startOrResume) == 0){//start new game
			Test.newStarter();
		}
		else if (Test.userChoice(Test.startOrResume) == 1){//resume last game
			Test.resumeGame();
		}
	}
}