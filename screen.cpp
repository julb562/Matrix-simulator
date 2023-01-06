#include <stdlib.h>
#include "screen.h"
#include <math.h>
#include <string>
#include <iostream>

#define matrixWormsAmmount 100
#define CHAR_RANGE rand() % 60 + 390
//#define CHAR_RANGE 'D'

Screen::Screen() {
	setlocale(LC_ALL, "");
	wnd = initscr(); // curses call to initialize window
	cbreak(); // curses call to set no waiting for Enter key
	noecho(); // curses call to set no echoing
	getmaxyx(wnd,maxY,maxX); // curses call to find size of window
	refresh(); // curses call to implement all changes since last refresh
	if (has_colors()) {
		start_color();
		init_pair( 1,7,0);
		init_pair( 2,2,0);
    }
};

Screen::~Screen() {
	endwin();
}


void Screen::pushChar(int x, int y, chtype output) {
	mvaddch(y,x,output);
}


Coord	Screen::getMax() {
	getmaxyx(wnd,maxY,maxX);
	return {maxX, maxY};
}

//bool Screen::processMatrix(WINDOW* wnd) {
bool Screen::processMatrix() {
	typedef void(*functionPointer)();
	struct Worm {
		int 	length, xPos;
		float 	yPos, speed;
		bool	initialized=0;
		int		timesInited=0;
		void initialize(int maxX, int maxY) {
			length=		rand() % maxY + 8;
			xPos=		rand() % maxX;
			yPos=		0;
			speed= 	((rand() % 90 +10) / static_cast<float>(100));
			initialized=1;
			timesInited++;
		}
	};
	Worm	worm[matrixWormsAmmount];
	int 	wormTimer=0;
	Coord	lastCoord=getMax();
	Coord	newCoord;
	cchar_t outputCChar;
	wchar_t outputWChar=L'ä';

	std::string	debug="Debug thing";
	int 	wormsToDisplay=round(maxX/0.8f);
	if (wormsToDisplay>matrixWormsAmmount)
		wormsToDisplay=matrixWormsAmmount;
	while (!m_Matrix_StopSignal) {

		newCoord=getMax();

		if (lastCoord != newCoord) {
			for (int i=0; i<matrixWormsAmmount; i++)
				worm[i].initialized=0;
			wormsToDisplay=round(maxX/0.8f);
			if (wormsToDisplay>matrixWormsAmmount)
				wormsToDisplay=matrixWormsAmmount;
			lastCoord=newCoord;
			clear();
		}

		for (int i=0; i<wormsToDisplay; i++) {
			if (!worm[i].initialized)
				worm[i].initialize(maxX,maxY);
			attroff(A_BOLD);
			outputWChar=CHAR_RANGE;
			setcchar(&outputCChar, &outputWChar, 0, 2, NULL);
			mvadd_wch( round(worm[i].yPos), worm[i].xPos, &outputCChar);
			worm[i].yPos+=worm[i].speed;
			if (worm[i].yPos>maxY+worm[i].length+1) {
				worm[i].initialized=0;
			}
			attron(A_BOLD);
			outputWChar=CHAR_RANGE;
			setcchar(&outputCChar, &outputWChar, 0, 2, NULL);
			mvadd_wch( round(worm[i].yPos), worm[i].xPos, &outputCChar);
			mvaddch( round(worm[i].yPos)-worm[i].length, worm[i].xPos, ' ');
		}

		wormTimer++;
		//m_Matrix_StopSignal=1;
		debug="maxY: "+std::to_string(maxY);
		mvaddstr(7,2,debug.c_str());
		debug="Initialized: "+std::to_string(worm[1].timesInited);
		mvaddstr(8,2,debug.c_str());
		move(0,0);
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(m_MatrixProcessWaitTime));
	}
}

bool Screen::runMatrix(WINDOW* wnd) {
	if (m_Matrix_Processing)
		return 0;
	if (has_colors())
		attron(COLOR_PAIR(2));
	clear();
	m_Matrix_StopSignal=0;
	m_Matrix_Processing=1;
	m_Matrix_Process=new std::thread(&Screen::processMatrix, this);
	return 1;

}

void Screen::stopMatrix(WINDOW* wnd) {
	m_Matrix_StopSignal=1;
	if (has_colors())
		attron(COLOR_PAIR(1));
	attroff(A_BOLD);
	m_Matrix_Process->join();
}
