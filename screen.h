#ifndef SCREEN_H
#define SCREEN_H
#include <thread>
#include <chrono>
#include <wchar.h>
#include <locale.h>

#ifdef _WIN32
	#include <curses.h>
#else
	#include <ncurses.h>
#endif


struct Coord {
	unsigned int x;
	unsigned int y;

	bool operator==(const Coord &other) {
		if ( this->x == other.x && this->y == other.y)
			return 1;
		return 0;
	}

	bool operator!=(const Coord &other) {
		return !(*this==other);
	}
};

class Screen
{
	public:
		Screen();
		virtual ~Screen();
		Coord getMax();
		WINDOW 			*wnd;
		void    pushChar(int x, int y, chtype output);
		bool	runMatrix(WINDOW* wnd);
		void	stopMatrix(WINDOW* wnd);
		void	runMatrix() { runMatrix( stdscr); };

	protected:

	private:
		unsigned int	maxX, maxY;
		bool			processMatrix();
		wchar_t*		m_data;
		bool			m_Matrix_Processing=0;
		bool			m_Matrix_StopSignal=0;
		std::thread* 	m_Matrix_Process;
		unsigned int 	m_MatrixProcessWaitTime=100;
};


#endif // SCREEN_H
