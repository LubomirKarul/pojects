#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <conio.h>
#include <windows.h>
using namespace std;
int x, y, ovX, ovY, score, dlchvost;
int chvostX[30], chvostY[30];
char pom, c, obt = 'q', r, pom2;
const int sirka = 30, vyska = 30;
bool gameover;
enum eSmer { STOP = 0, HORE, DOLE, VPRAVO, VLAVO };
eSmer smer;

void setup() {
	srand(time(NULL));
	smer = STOP;
	x = sirka / 2;
	y = vyska / 2;
	ovX = rand() % (sirka - 1) + 1;
	ovY = rand() % (vyska - 1) + 1;
	gameover = false;
	dlchvost = 0;
	score = 0;
}


void vypis() {
	system("cls");
	for (int a = 0; a < sirka + 1; a++)
		cout << "_";
	cout << endl;
	for (int a = 0; a < vyska; a++) {
		for (int b = 0; b < sirka; b++) {
			if (b == 0)
				cout << "|";
			else if (x == b && y == a)
				cout << "O";
			else if (ovX == b && ovY == a)
				cout << "@";
			else {
				bool vypis = false;
				for (int k = 0; k < dlchvost; k++) {
					if (chvostX[k] == b && chvostY[k] == a) {
						cout << "o";
						vypis = true;
					}
				}
				if (!vypis)
					cout << " ";

			}
			if (b == sirka - 1)
				cout << "|" << endl;
		}

	}
	for (int a = 0; a < sirka + 1; a++)
		cout << "_";
	cout << endl << "Score:" << score << endl;
}

void imput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':smer = VLAVO; break;
		case 'd':smer = VPRAVO; break;
		case 'w':smer = HORE; break;
		case 's':smer = DOLE; break;
		case 'x':gameover = true; break;
		}
	}
}

void logic() {
	int prevX = chvostX[0];
	int prevY = chvostY[0];
	int prev2X, prev2Y;
	chvostX[0] = x;
	chvostY[0] = y;
	for (int i = 1; i < dlchvost; i++)
	{
		prev2X = chvostX[i];
		prev2Y = chvostY[i];
		chvostX[i] = prevX;
		chvostY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (smer) {
	case VLAVO: x--; break;
	case VPRAVO: x++; break;
	case HORE: y--; break;
	case DOLE: y++; break;
	}
	if (x > sirka - 1 || x < 1 || y > vyska - 1 || y < 0)
		gameover = true;

	if (x == ovX && y == ovY) {
		dlchvost++;
		score += 10;
		ovX = rand() % (sirka - 1) + 1;
		ovY = rand() % (vyska - 1) + 1;
	}

	for (int i = 0; i < dlchvost; i++)
		if (chvostX[i] == x && chvostY[i] == y)
			gameover = true;
}

void hra() {
	setup();
	while (!gameover) {
		vypis();
		imput();
		logic();
		switch (obt) {
		case 'l': {
			Sleep(120);
			break;
		}
		case 's': {
			Sleep(95);
			break;
		}
		case 't': {
			Sleep(70);
			break;
		}
		case 'u': {
			Sleep(40);
			break;
		}
		default: {
			Sleep(90);
			break;
		}
		}
	}
	cout << "Prehral si" << endl;
	cout << "Pre dalsiu hru stlac 'a'" << endl <<
		"Ak sa chces vratit do menu stlac 'm'" << endl <<
		"Ak chces skoncit hru stlac cokolvek ine" << endl;
	cin >> pom;
}
void menu() {
	do {
		printf("Nastavenia(n)\n");
		printf("About(a)\n");
		printf("Start(s)\n");
		printf("Extra(e)\n");

		c = getchar();
		if (c == 'n') {
			system("cls");
			while (1) {
				printf("Zvol si obtiaznost\nLahka(l)\nStredna(s)\nTazka(t)\nUltra Tazka(u)");
				obt = getchar();
				if (obt == 'l' || obt == 's' || obt == 't' || obt == 'u') break;
				else system("cls");
			}
		}
		if (c == 'a') {
			printf("About\n");
			printf("Snake v2.1\nAutor: Lubomir Karul");
			pom2 = getchar(); pom2 = getchar();
		}
		if (c == 's') {
			if (!(obt == 'l' || obt == 's' || obt == 't' || obt == 'u')) {
				printf("Zvol si obtiznost");
				pom2 = getchar(); pom2 = getchar();
			}
			else break;
		}
		if (c == 'e') {
			printf("Extra\nComing soon\n");
			pom2 = getchar(); pom2 = getchar();
		}
		system("cls");
	} while (1);
}
int main(int argc, char** argv) {
	menu();
	hra();
	while (pom == 'm' || pom == 'M' || pom == 'a' || pom == 'A') {
		if (pom == 'm' || pom == 'M') {
			menu();
			hra();
		}
		hra();
	}
	cout << "Pre ukoncenie stac akekolvek tlacidlo na klavesnici" << endl;
	return 0;
}