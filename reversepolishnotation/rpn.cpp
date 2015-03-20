#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;
int i = 0;

int operandnum = 0, operatornum = 0;
class symbol {
public:
	vector<float> vec;

};

class operand : public symbol {
public:
	char get_operand(int i){
		return vec[i];
	}
};

class operators : public symbol{
	double operate(double a, double b);
};

//these classes are used to calculate and return the result
class add : public operators {
public:
	double operate(double a, double b){
		return (a) + (b);
	}
};

class substract : public operators {
public:

	double operate(double a, double b){
		return (b) - (a);
	}
};

class multiple : public operators {
public:

	double operate(double a, double b){
		return (a) * (b);
	}
};

class devide : public operators {
public:

	double operate(double a, double b){
		return (b) / (a);
	}
};

class module : public operators {
public:
	double operate(double a, double b){
		return fmod(b,a);
	}
	/*double operate(char a, char b){
		return (b) % (a);
	}
	double operate(double a, char b){
		return fmod(b, a);
	}
	double operate(char a, double b){
		return fmod(b, a);
	}*/
};

class pow1 : public operators {
public:

	double operate(double a, double b){
		return pow((b), (a));
	}
};

void get_answer(symbol s1){
	//symbol s1;
	float x;
	int i = 0;
	stack<float> opStack, eval;
	double topNum = 0, nextNum = 0, answer = 0;
	//while (!s1.vec.empty()) {
	while (i < s1.vec.size()) {
		x = s1.vec[i];
		//ss1.vec.pop_back();
		i++;
		if ((char)x != '+' && (char)x != '-' && (char)x != '*' && (char)x != '/' && (char)x != '%' && (char)x != '^')
			eval.push(x - 48);
		else{ // t is an operator token
			topNum = eval.top(); // Get operand from stack
			eval.pop(); // Remove operand from stack
			nextNum = eval.top(); // Get operand from stack
			eval.pop(); // Remove operand from stack
			switch ((char)x) {
			case '+': {add op_add; answer = op_add.operate(topNum, nextNum); break; }
			case '-': {substract op_sub; answer = op_sub.operate(topNum, nextNum); break; }
			case '*': {multiple op_mul; answer = op_mul.operate(topNum, nextNum); break; }
			case '/':
			{
				if (nextNum != 0){
					devide op_devide; answer = op_devide.operate(topNum, nextNum);
				}
				else
				{
					cout << "0 cannot devide!" << endl;
					exit(0);
				}
				break;
			}
			case '%':
			{
				if (nextNum != 0){
					module op_module; answer = op_module.operate(topNum, nextNum);
				}
				else
				{
					cout << "0 cannot module!" << endl;
					exit(0);
				}
				break;
			}
			case '^': {pow1 op_pow; answer = op_pow.operate(topNum, nextNum); break; }
			default:break;
			}
			eval.push(answer);
		}
	}
	//cout << endl;
	cout << eval.top() << endl;

}

void main(){
	symbol s1;
	//read file one char at a time
	ifstream infile;
	infile.open("infile.dat");
	if (infile.fail())
	{
		cout << "please check the file, opening file failed!" << endl;
	}
	//there is a function for clear i and vector

	char x;
	while (infile.get(x)){
		//if x is not operators or operands, cout error message and call clear function and break this loop go to next line
		//how to go to next line? if x is not \n or \r, continue read x, then break, so next time, x will read the new line
A:		if (!isdigit(x)){//if x is not digit
			if (x != '+' && x != '-' && x != '*' && x != '/' && x != '%' && x != 'p' && x != '.' && x != ' ' && x != '\n' && x != '\r'){//if x is not digit or any of the operators, and there is a trick, if there is a alpha, it must start with p, because there is only a pow is alpha, other
				cout << "SYNTAX ERROR" << endl;
				while (x != '\n' && x != '\r'){
					infile.get(x);
				}
				//infile.get(x);
				continue;
			}
		}
		//if program goes to here, that means until now it is either a operand or a operator or space, 
		//if space, i++, get next x, continue until not a space, then use set function in symbol class, set the value to the vector
		double whole_number;
		if (x != ' ' && x != '\n' && x != '\r'){
			if (isdigit(x) || x == '.')
			{
				//a new input that starts with a number:
				//we have to keep reading until we get the whole number
				//double whole_number;
				bool float_point_detected = false;
				if (x == '.')
				{
					whole_number = 0;
					float_point_detected = true;
				}
				else
				{
					whole_number = x - 48; //ascii to int
				}
				infile.get(x);
				if (float_point_detected == true && !isdigit(x)){
					cout << "SYNTAX ERROR" << endl;
					while (x != '\n' && x != '\r'){
						infile.get(x);
					}
					goto A;
				}
				int number_of_digit = 1;
				while (isdigit(x) || (x == '.' && !float_point_detected))
				{
					if (x == '.')
					{
						float_point_detected = true;
						infile.get(x);
						/*while (x == ' '){
							infile.get(x);
						}*/
						/*if (!isdigit(x)){
							cout << "SYNTAX ERROR" << endl;
							while (x != '\n' && x != '\r'){
								infile.get(x);
							}
							goto A;
						}*/
						if (!isdigit(x)){
							operandnum++;
							s1.vec.push_back(whole_number + 48);
							goto A;
						}
						
						continue;
					}

					if (!float_point_detected)
					{
						whole_number *= 10;
						whole_number += x - 48;
					}
					else if (isdigit(x))
					{
						number_of_digit *= 10;
						double tmp = x - 48;
						tmp /= number_of_digit;
						whole_number += tmp;
					}
					infile.get(x);
				}
				//cout << whole_number + 48 << endl;
				operandnum++;
				s1.vec.push_back(whole_number + 48);
			}
			if (x == '+' || x == '-' || x == '*' || x == '/' || x == '%'){
				operatornum++;
				if (operandnum > operatornum)
				s1.vec.push_back(x);
				else{
					//cout << "SYNTAX ERROR" << endl;
					while (x != '\n' && x != '\r'){
						infile.get(x);
					}
					goto A;
				}
				//i++;
			}
			else if (x == 'p'){
				infile.get(x);
				if (x == 'o'){
					infile.get(x);
					if (x == 'w'){
						operatornum++;
						if (operandnum > operatornum)
						s1.vec.push_back('^');
						else{
							cout << "SYNTAX ERROR" << endl;
							while (x != '\n' && x != '\r'){
								infile.get(x);
							}
							goto A;
						}
						//i++;
					}
					else{
						cout << "SYNTAX ERROR" << endl;
						while (x != '\n' && x != '\r'){
							infile.get(x);
						}
						goto A;
					}
				}
				else{
					cout << "SYNTAX ERROR" << endl;
					while (x != '\n' && x != '\r'){
						infile.get(x);
					}
					goto A;
				}
			}
		}
		//until x is \n or \r
		//1. call the calculator function to get the result and print to screen with a \n
		//2. call the clear function to reset i and vector
		if (x == 10 || x == '\r'){
			//for (int i = 0; i < s1.vec.size(); i++){
			//	cout << s1.vec[i]<< " ";
			//}
			//cout << endl;
			if (!s1.vec.empty()){
				if (operandnum == operatornum +1)
					get_answer(s1);
				else{
					cout << "SYNTAX ERROR" << endl;
				}
			}
			s1.vec.clear();
			operandnum = 0;
			operatornum = 0;
		}
	}
}

