#include <iostream>
#include <vector>
using namespace std;

class TicTacToe{
private:
	bool flag = true;
	int inputX1, inputY1, inputX2, inputY2;
	int count;
	vector<vector<char>> vect;
	vector<char> v1;
	vector<char> v2;
	vector<char> v3;
public:
	TicTacToe();
	void drawBoard();
	void getInput();
	bool findWinner();
	bool empty(int i, int j);
	bool exception(int i, int j);
	void winner();
};