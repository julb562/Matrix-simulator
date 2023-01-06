#include <string>
#include <iostream>
#include "screen.h"
#include "wormfamily.h"

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

bool Screen::processMatrix() {
	typedef void(*functionPointer)();

	std::string	debug="Debug thing";
	const float wormRatio=0.8f;
	WormFamily family(this, wormRatio);
	family.initializeWorms();

	while (!m_Matrix_StopSignal) {
		family.processWorms();
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
