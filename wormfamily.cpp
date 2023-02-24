#include "wormfamily.h"

WormFamily::WormFamily(Screen* newScreen, float newWormRatio)
	:	screen(newScreen), wormRatio(newWormRatio)
{
}

WormFamily::~WormFamily()
{
	//dtor
}

void WormFamily::processWorms() {
	if (m_lastScreenSize!=screen->getMax())
		initializeWorms();
	for (int i=0; i<m_worms; i++)
		m_wormArray[i].process(screen);
}

void WormFamily::initializeWorms() {
	clear();
	m_lastScreenSize=screen->getMax();
	m_worms=(int)round(m_lastScreenSize.x/wormRatio);
	m_wormArray.clear();
	for (int i=0; i<m_worms; i++)
		m_wormArray.push_back(Worm(screen));
}

Worm::Worm(Screen* newScreen) : screen(newScreen) {}

void Worm::initialize(Coord maxCoordinates) {
	length=		rand() % maxCoordinates.y + 8;
	xPos=		rand() % maxCoordinates.x;
	yPos=		0;
	lastYPos=	0;
	maxYPos=		maxCoordinates.y+length+1;
	speed= 	((rand() % 90 +10));
	initialized=1;
	timesInitialized++;
	charArray.clear();
	knownMaxCoord = maxCoordinates;
	chtype tempWChar;
	for (int i=0; i<length; i++) {
		tempWChar=CHAR_RANGE;
		charArray.push_back(tempWChar);
	}
}

void Worm::process(Screen* screen) {
	if (!initialized)
		initialize(screen->getMax());

	yPos+=speed;
	int yDrawPos=(int)round(yPos/100);
	if ( yDrawPos > maxYPos) {
		initialize(knownMaxCoord);
		yDrawPos=(int)round(yPos/100);
	}

	// Draw main part of this worm

	if (has_colors())
		attron(COLOR_PAIR(2));

	int charPos=0;
	for ( int i=yDrawPos-length; i<yDrawPos; i++ ) {
		if (i<0 || i>=(int)knownMaxCoord.y)
			continue;
		if (rand() % 10 >8)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
		charPos=i % length;
		screen->pushChar(xPos, i, charArray[charPos]);
	}

	// Draw the head of this worm

	if (has_colors())
		attron(COLOR_PAIR(1));

	if (yDrawPos>0 && yDrawPos<(int)knownMaxCoord.y) {
		screen->pushChar(xPos, yDrawPos, (chtype)CHAR_RANGE);
	}

	// Clear the end of this worm
	if (yDrawPos-length>=0 && yDrawPos-length<=(int)knownMaxCoord.y) {
		screen->pushChar(xPos, yDrawPos-length, ' ');
	}
}


