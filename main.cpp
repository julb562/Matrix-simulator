#include <iostream>
#include "screen.h"
#include <vector>

void fillScreen(int x, int y, Screen &screen) {
	for (int xPos=0; xPos<=x; xPos++) {
		for (int yPos=0; yPos<=y; yPos++) {
			screen.pushChar(xPos, yPos, '.');
		}
	}
}


int main()
{
	Screen mainScreen;
	char input = ' ';
	chtype		out='H';
	chtype		in='_';

	mainScreen.runMatrix();

	while (input != 'q') {

		input = getch();
		mainScreen.pushChar(8,3, input);
		in = mvinch(3, 8);
		mainScreen.pushChar(8,4, in);

	}
	mainScreen.stopMatrix(stdscr);
    return 0;
}
