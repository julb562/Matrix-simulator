#ifndef WORMFAMILY_H
#define WORMFAMILY_H
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "screen.h"

#define CHAR_RANGE rand() % 60 + 390

class Worm {
	public:
		std::vector<chtype>	charArray;
		Worm(Screen* newScreen);
		void test();
		void initialize(Coord maxCoordinates);
		void process(Screen* screen);

	private:
		int 	xPos, yPos, maxYPos, lastYPos, length, speed;
		Coord	knownMaxCoord;
		bool	initialized=0;
		int		timesInitialized=0;
		Screen*	screen;
};

class WormFamily {
	public:
		WormFamily(Screen* screen, float wormRatio);
		virtual ~WormFamily();
		void processWorms();
		void initializeWorms();

	protected:

	private:
		Screen*				screen;
		float				wormRatio;
		std::vector<Worm>	m_wormArray;
		Coord				m_lastScreenSize;
		int					m_worms=0;
};

#endif // WORMFAMILY_H
