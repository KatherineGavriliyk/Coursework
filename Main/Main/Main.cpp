//не пашущий хз почему алгоритм (не делаетс€ проход по всем соседним €чейкам) 

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;
const int length = 15, width = 10;
int Array[length][width], d, i, j, WayX[length * width], WayY[length * width], len = 0;
const int WALL = -2, PASS = -1;

int EnterCoordinates(char variable) {
	cout << variable << " is ";
	int input;
	cin >> input;
	return input - 1;} //потому что нумераци€ элементов массива с 0, а не 1

bool findWay(int x_start, int y_start, int x_finish, int y_finish) {
	int x_displacement[4] = {1, 0, -1, 0}, 
	int y_displacement[4] = {0, 1, 0, -1};
	int d, x, y, k;
	bool what = true, stop;

/*	if ((Array[y_start][x_start] == WALL) || (Array[y_finish][x_finish] == WALL))
		what = false;*/

	d = 0;
	Array[y_start][x_start] = 0;
	do {
		stop = true;
		for (y = 0; y < length; ++y) {
			for (x = 0; x < width; ++x) {
				if (Array[y][x] == d) {
					for (k = 0; k < 4; ++k) {
						int iy = y + y_displacement[k], ix = x + x_displacement[k];
						if ((iy >= 0) && (iy < length) && (ix >= 0) && (ix < width) && (Array[iy][ix] == PASS)) {
							stop = false;
							Array[iy][ix] = d + 1;
						}
				}
			}
		}
		d++;
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				cout << Array[i][j] << "\t";
			}
			cout << endl;
		}
		_getch();
	}

	while ((!stop) && (Array[y_finish][x_finish] == PASS));
	system("cls");

	cout << Array[y_finish][x_finish];
	_getch();
	if (Array[y_finish][x_finish] == PASS)
		what = false;

	len = Array[y_finish][x_finish];
	x = x_finish;
	y = y_finish;
	d = len;
	while (d > 0) {
		WayX[d] = x;
		WayY[d] = y;
		d--;
		for (k = 0; k < 4; ++k) {
			int iy = y + y_displacement[k], ix = x + x_displacement[k];
			if ((iy >= 0) && (iy < length) && (ix >= 0) && (ix < width) && (Array[iy][ix] == d)) {
				x = x + x_displacement[k];
				y = y + y_displacement[k];
				break;
			}
		}
	}
	WayX[0] = x_start;
	WayY[0] = y_start;
	return what;
}

int _tmain()
{
	int d = 0;
	int xstart, ystart, xfinish, yfinish;
	cout << "Enter the coordinates of the start:\n";
	xstart = EnterCoordinates('x');
	ystart = EnterCoordinates('y');
	system("cls");
	cout << "Enter the coordinates of the finish:\n";
	xfinish = EnterCoordinates('x');
	yfinish = EnterCoordinates('y');

	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			Array[i][j] = PASS;
		}
	}

	/*char choice = '1';
	while (choice == '1') {
	system("cls");
	cout << "Enter the coordinate of wall, please:\n";
	int x = EnterCoordinates('x');
	int y = EnterCoordinates('y');
	Array[x][y] = WALL;
	system("cls");
	cout << "Do you want to add a new wall?\n1. Yes.\n2. No.\n";
	choice = _getch();}*/

	if (findWay(xstart, ystart, xfinish, yfinish) == true) {
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				if (Array[i][j] == 0)
					cout << "START\t";
				else {
					if ((i == xfinish) && (j == yfinish))
						cout << "FINISH\t";
					else {
						for (int p = 0; p < len; p++) {
							if ((i == WayX[p]) && (j == WayY[p])) {
								cout << "H\t";
							}
							else
								cout << " \t";
						};
					}
					cout << endl;
				}
			}
		}
	}
	else {
		system("cls");
		cout << "YOU SHALL NOT PASS!" << endl;
	}
	return 0;
}