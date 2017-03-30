//working algorithm without dynamic memory
#include <string>
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <conio.h>
#include <stdlib.h>
using namespace std;
const int length = 10, width = 10;
int Array[length][width], d, i, j, WayRow[length * width], WayColumn[length * width], len = 0;
const int WALL = -2, PASS = -1;

int EnterCoordinates(char* variable) {
	puts(variable);
	cout << " is ";
	int input;
	cin >> input;
	return input - 1;
}

bool findWay(int row_start, int column_start, int row_finish, int column_finish) {
	int row_displacement[4] = { 1, 0, -1, 0 };
	int column_displacement[4] = { 0, 1, 0, -1 };
	int d = 0, row, column, k;
	bool stop;

	if ((Array[row_start][column_start] == WALL) || (Array[row_finish][column_finish] == WALL))
		return false;

	Array[row_start][column_start] = 0;
	do {
		stop = true; //по умолчанию считаем, что повторять еще раз алгоритм не нужно
		for (row = 0; row < length; row++) { //проходим по каждой строчке
			for (column = 0; column < width; column++) { //в ней - по каждой колонке
				if (Array[row][column] == d) { //
					for (k = 0; k < 4; k++) {
						int icolumn = column + column_displacement[k], irow = row + row_displacement[k];
						if ((icolumn >= 0) && (icolumn < width) && (irow >= 0) && (irow < length) && (Array[irow][icolumn] == PASS)) {
							stop = false;
							Array[irow][icolumn] = d + 1;
						}
					}
				}
			}
		}
		d++;
	} while ((stop) || (Array[row_finish][column_finish] == PASS));
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			cout << Array[i][j] << "\t";
		}
		cout << endl;
	}

	_getch();
	system("cls");

	if (Array[row_finish][column_finish] == PASS)
		return false;

	len = Array[row_finish][column_finish];
	d = len;
	WayRow[d] = row_finish;
	WayColumn[d] = column_finish;
	while (d > 0) {
		d--;
		for (k = 0; k < 4; ++k) {
			int icolumn = WayColumn[d + 1] + column_displacement[k], irow = WayRow[d + 1] + row_displacement[k];
			if ((icolumn >= 0) && (icolumn < width) && (irow >= 0) && (irow < length) && (Array[irow][icolumn] == d)) {
				WayRow[d] = irow;
				WayColumn[d] = icolumn;
				break;
			}
		}
	}
	WayRow[0] = row_start;
	WayColumn[0] = column_start;

	for (int i = 0; i <= len; i++) {
		cout << "WayRow = " << WayRow[i] << " WayColumn = " << WayColumn[i] << endl;
	}
	return true;
}

int main()
{
	int d = 0;
	int rowstart, columnstart, rowfinish, columnfinish;
	cout << "Enter the coordinates of the start:\n";
	rowstart = EnterCoordinates("row");
	columnstart = EnterCoordinates("column");
	system("cls");
	cout << "Enter the coordinates of the finish:\n";
	rowfinish = EnterCoordinates("row");
	columnfinish = EnterCoordinates("column");

	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			Array[i][j] = PASS;
		}
	}

	char choice = '1';
	while (choice == '1') {
		system("cls");
		cout << "Enter the coordinate of wall, please:\n";
		int row = EnterCoordinates("row");
		int column = EnterCoordinates("column");
		Array[row][column] = WALL;
		system("cls");
		cout << "Do you want to add a new wall?\n1. Yes.\n2. No.\n";
		choice = _getch();
	}
	system("cls");
	if (findWay(rowstart, columnstart, rowfinish, columnfinish) == true) {
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				if (Array[i][j] == 0) {
					cout << "S ";
				}
				else if (Array[i][j] == WALL) {
					cout << "  ";
				}
				else {
					if ((i == rowfinish) && (j == columnfinish)) {
						cout << "F ";
					}
					else {
						bool amount = false;
						for (int p = 0; p < len; p++) {
							if ((i == WayRow[p]) && (j == WayColumn[p])) {
								cout << "H ";
								amount = true;
							}
						}
						if (amount == false) {
							cout << ". ";
						}
					}
				}
			}cout << endl;
		}
	}
	else {
		system("cls");
		cout << "YOU SHALL NOT PASS!" << endl;
	}
	return 0;
}
