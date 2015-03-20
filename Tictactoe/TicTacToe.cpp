#include <iostream>
#include <vector>
#include <stdexcept>
#include "TicTacToe.h"
using namespace std;

TicTacToe::TicTacToe(){
	count = 0;
	for (int i = 0; i <= 3; i++){
		v1.push_back(' ');
		v2.push_back(' ');
		v3.push_back(' ');
	}
	vect.push_back(v1);
	vect.push_back(v2);
	vect.push_back(v3);
}

void TicTacToe::drawBoard(){
	cout << "  1   2   3 " << endl;
	cout << "1 " << vect[0][0] << " | " << vect[0][1] << " | " << vect[0][2] << " " << endl;
	cout << " ---+---+---" << endl;
	cout << "2 " << vect[1][0] << " | " << vect[1][1] << " | " << vect[1][2] << " " << endl;
	cout << " ---+---+---" << endl;
	cout << "3 " << vect[2][0] << " | " << vect[2][1] << " | " << vect[2][2] << " " << endl;
}

void TicTacToe::getInput(){
	for (int i = 0; i < 5; i++){
			if (flag == true){
			A:
				cout << "Player1, this is your turn, please input the position, format like this(x y): " << endl;
				cin >> inputX1 >> inputY1;
				if (cin.fail() || inputX1 >=4 || inputX1 <1 || inputY1 >=4 || inputY1 <1){
					cout << "Invalid input." << endl;
					cin.clear();
					cin.sync();
					continue;
				}
				else{
					while (empty(inputX1 - 1, inputY1 - 1) == false){
						goto A;
					}

					vect[inputX1 - 1][inputY1 - 1] = 'X';
					count++;
					system("cls");
					drawBoard();
					flag = false;
					if (findWinner()){ return; }
				}
				if (i == 4){ return; }
			}
		B:
			cout << "Player2, this is your turn, please input the position, format like this (x y): " << endl;
			cin >> inputX2 >> inputY2;
			if (cin.fail() || inputX2 >= 4 || inputX2 <1 || inputY2 >= 4 || inputY2 <1){
				cout << "Invalid input." << endl;
				cin.clear();
				cin.sync();
				continue;
			}
			else{
				while (empty(inputX2 - 1, inputY2 - 1) == false){
					goto B;
				}

				vect[inputX2 - 1][inputY2 - 1] = 'O';
				count++;
				system("cls");
				drawBoard();
				flag = true;
				if (findWinner()){ return; }
			}
	}
	return;
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

bool TicTacToe::findWinner(){
	if ((vect[0][0] == vect[1][1] && vect[1][1] == vect[2][2]) && (vect[1][1] == 'X' || vect[1][1] == 'O')){
		return true;
	}
	else if ((vect[0][2] == vect[1][1] && vect[1][1] == vect[2][0]) && (vect[1][1] == 'X' || vect[1][1] == 'O')){
		return true;
	}
	else{
		for (int i = 0; i <= 2; i++){
			if ((vect[i][0] == vect[i][1] && vect[i][1] == vect[i][2]) && (vect[i][1] == 'X' || vect[i][1] == 'O')){
				return true;
			}
			else if ((vect[0][i] == vect[1][i] && vect[1][i] == vect[2][i]) && (vect[1][i] == 'X' || vect[1][i] == 'O')){
				return true;
			}
		}
	}
	return false;
}

void TicTacToe::winner(){
	if (flag == false && findWinner() == true){
		cout << "Congratulation, Player1! You win!" << endl;
	}
	else if (flag == true && findWinner() == true){
		cout << "Congratulation, Player2! You win!" << endl;
	}
	else if(count == 9 && findWinner() == false){
		cout << "Game Over! You are even." << endl;
	}
}