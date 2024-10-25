#include<iostream>
#include<time.h>
#include<windows.h>
#include <cstdlib>
using namespace std;
const int max_rows = 20;
const int max_cols = 20;
void menu()
{
	cout << " 1.HUMAN VS HUMAN" << endl;
	cout << " 2.HUMAN VS COMPUTER" << endl;
}
void init(char b[][max_cols], int& dim, int& nop, int& turn, string names[], char psym[], int& wc, int& c)
{


	menu();
	do {
		cout << "enter choice " << endl;
		cin >> c;
		if (c != 1 && c != 2)
		{
			cout << "enter a valid choice " << endl;
		}
	} while (c != 1 && c != 2);
	cout << "enter the dimensions of the board you want " << endl;
	cin >> dim;
	if (c == 1)
	{
		cout << " Enter the win counts \n";
		cin >> wc;
		cout << "enter the number of player " << endl;
		cin >> nop;
		for (int i = 0; i < nop; i++)
		{
			cout << "enter player " << i + 1 << " name" << endl;
			cin >> names[i];
			cout << " choose " << names[i] << "'s symbol " << endl;
			cin >> psym[i];
		}

	}
	if (c == 2)
	{
		cout << " Enter the win counts \n";
		cin >> wc;
		nop = 2;
		cout << "enter player's name" << endl;
		cin >> names[1];
		cout << " choose " << names[1] << "'s symbol " << endl;
		cin >> psym[1];
		names[0] = "computer";
		psym[0] = '!';
		cout << names[0] << "'s symbol is " << psym[0] << endl;


	}
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			b[r][c] = '-';
		}
	}
	turn = rand() % nop;
}
void displayboard(char b[][max_cols], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout << b[r][c];
		}
		cout << endl;

	}
}
void trnmsg(string names, char psym)
{
	cout << names << "'s (" << psym << ")" << " turn" << endl;
}

bool horizon(char b[][max_cols], int dim, int row, int col, int wc, char s)
{
	if (col + wc > dim)
		return 0;
	for (int c = 0; c < wc; c++)
	{
		if (b[row][col + c] != s)
		{
			return 0;
		}
	}
	return 1;
}
bool vert(char b[][max_cols], int dim, int row, int col, int wc, char s)
{
	if (row + wc > dim)
		return 0;
	for (int c = 0; c < wc; c++)
	{
		if (b[row + c][col] != s)
		{
			return 0;
		}
	}
	return 1;

}
bool diagLFT(char b[][max_cols], int dim, int row, int col, int wc, char s)
{
	if (row + wc > dim || col - wc < 0)
		return 0;
	for (int c = 0; c < wc; c++)
	{
		if (b[row + c][col - c] != s)
		{
			return 0;
		}
	}
	return 1;
}
bool diagRGHT(char b[][max_cols], int dim, int row, int col, int wc, char s)
{
	if (row + wc > dim || col + wc > dim)
		return 0;
	for (int c = 0; c < wc; c++)
	{
		if (b[row + c][col + c] != s)
		{
			return 0;
		}
	}
	return 1;
}

bool isvalid(char b[][max_cols], int pr, int pc, int dim)
{
	if (pr<0 || pr>dim || pc<0 || pc>dim)
		return 0;
	else
		return b[pr][pc] == '-';
}
bool iswin(char b[][max_cols], int dim, char sym, int wc)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (horizon(b, dim, r, c, wc, sym) || vert(b, dim, r, c, wc, sym) || diagLFT(b, dim, r, c, wc, sym) || diagRGHT(b, dim, r, c, wc, sym))
				return 1;
		}
	}
	return 0;
}
void copys(char b[][max_cols], char copy[max_rows][max_cols], int rows, int cols)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			copy[r][c] = b[r][c];
		}
	}
}
bool placecomputer(char b[][max_cols], int dim, int rows, int cols, int wc, int& pr, int& pc)
{
	char copy[max_rows][max_cols];
	copys(b, copy, rows, cols);
	for (int r = 0; r <= dim; r++)
	{
		for (int c = 0; c <= dim; c++)
		{
			if (isvalid(b, r, c, dim))
			{
				copy[r][c] = '!';
				if (iswin(b, dim, '!', wc))
				{
					pr = r;
					pc = c;
					return 1;
				}
				else
					copy[r][c] = '-';
			}
		}
	}
	return false;
}
bool block(char b[][max_cols], char s, int dim, int rows, int cols, int wc, int& pr, int& pc)
{
	char copy[max_rows][max_cols];
	copys(b, copy, rows, cols);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (isvalid(b, r, c, dim))
			{
				copy[r][c] = s;
				if (iswin(b, dim, s, wc))
				{
					pr = r;
					pc = c;
					return true;
				}
				else
					copy[r][c] = '-';
			}
		}
	}
	return false;
}
void computerturn(char b[][max_cols], char s, int dim, int rows, int cols, int wc, int& pr, int& pc)
{
	for (int i = 2; i < wc; i++)
	{
		if (placecomputer(b, dim, rows, cols, i, pr, pc))
		{
			return;
		}
		else if (i >= 3 && block(b, s, dim, rows, cols, (i), pr, pc))
		{
			return;
		}


	}
	do
	{
		pr = rand() % dim;
		pc = rand() % dim;
	} while (!isvalid(b, pr, pc, dim));

}


void selectposition(char b[][max_cols], int rows, int cols, int& pr, int& pc, int wc, int choice, char sy[], int turns, int dim)
{
	if (choice == 2)
	{
		char s = sy[1];
		if (turns == 0)
		{
			computerturn(b, s, dim, rows, cols, wc, pr, pc);
		}
		else
		{
			cout << "enter your row and column" << endl;
			cin >> pr >> pc;
			pr--;
			pc--;
		}
	}
	else
	{
		cout << "enter your row and column" << endl;
		cin >> pr >> pc;
		pr--;
		pc--;
	}

}

void updateboard(char b[][max_cols], char psym, int pr, int pc)
{
	b[pr][pc] = psym;
}

void updateb(char b[][max_cols], int pr, int pc, char psym)
{
	b[pr][pc] = psym;
}
void chngtrn(int& turn, int nop)
{
	turn = (turn + 1) % nop;
}
bool boardfull(char b[][max_cols], int dim)
{
	int count = 0;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (b[r][c] != '-')
				count++;
		}
	}
	if (count == dim * dim) {
		return true;
	}
	return false;
}
bool stop(char b[][max_cols], int dim, int winnercnt, int nop)
{
	bool oneplyrleft = 0;
	if (winnercnt == nop - 1)
		oneplyrleft = true;
	if (boardfull(b, dim) || oneplyrleft)
	{
		return  false;
	}
	else
		return true;
}



bool winnerturn(int wpos[], int winnercnt, int turn)
{
	for (int i = 0; i < winnercnt; i++)
	{
		if (wpos[i] == turn)
		{
			return 1;
		}
	}
	return 0;
}

void winners(char b[][max_cols], int dim, int win[], int ind, string names[])
{
	cout << "\t\t\t\t***********GAME OVER*********** " << endl;
	if (boardfull(b, dim))
	{
		cout << "\t\t\t\t\t   GAME DRAW ";
	}
	for (int i = 0; i < ind; i++)
	{
		int c = win[i];
		cout << i + 1 << ". " << names[c] << endl;
	}
}
int main()
{
	char b[max_rows][max_cols], psym[max_rows];
	int nop = 0, turns = 0, pr = 0, pc = 0, dim = 0, wc = 5, wpos[max_cols] = {}, winnercnt = 0, choice = 0;
	string names[100] = {};
	init(b, dim, nop, turns, names, psym, wc, choice);
	system("cls");
	displayboard(b, dim);

	do {
		do {
			trnmsg(names[turns], psym[turns]);
			selectposition(b, dim, dim, pr, pc, wc, choice, psym, turns, dim);
			if (!isvalid(b, pr, pc, dim))
			{
				cout << "INVALID POSTION SELECTED" << endl;
			}

		} while (!isvalid(b, pr, pc, dim));

		updateb(b, pr, pc, psym[turns]);
		system("cls");
		displayboard(b, dim);
		if (iswin(b, dim, psym[turns], wc))
		{
			wpos[winnercnt] = turns;
			winnercnt++;
		}
		do {
			chngtrn(turns, nop);
		} while (winnerturn(wpos, winnercnt, turns));
	} while (stop(b, dim, winnercnt, nop));
	winners(b, dim, wpos, winnercnt, names);
	return 0;
}