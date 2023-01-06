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
	for (int i=0; i<m_worms; i++)
		m_wormArray[i].process(screen);
}

void WormFamily::initializeWorms() {
	m_lastScreenSize=screen->getMax();
	m_worms=round(m_lastScreenSize.x/wormRatio);
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
	cchar_t tempCChar;
	knownMaxCoord = maxCoordinates;
	wchar_t tempWChar;
	for (int i=0; i<length; i++) {
		tempWChar=CHAR_RANGE;
		setcchar(&tempCChar,&tempWChar,0,2,NULL );
		charArray.push_back(tempCChar);
	}
}

void Worm::process(Screen* screen) {
	if (!initialized)
		initialize(screen->getMax());

	yPos+=speed;
	int yDrawPos=round(yPos/100);
	if ( yDrawPos > maxYPos)
		initialize(knownMaxCoord);

	// Draw main part of this worm
	int charPos=0;
	for ( int i=yDrawPos-length; i<yDrawPos; i++ ) {
		if (i<0 || i>knownMaxCoord.y)
			continue;
		if (rand() % 10 >8)
			attron(A_BOLD);
		else
			attroff(A_BOLD);
		charPos=i % length;
		mvadd_wch( i, xPos, &charArray[charPos]);
	}
	cchar_t tempCChar;
	wchar_t tempWChar=CHAR_RANGE;

	// Draw the head of this worm
	if (yDrawPos>0 && yDrawPos<=knownMaxCoord.y) {
		setcchar(&tempCChar,&tempWChar,0,1,NULL );
		mvadd_wch( yPos/100, xPos, &tempCChar);
	}

	// Clear the end of this worm
	if (yDrawPos-length>=0 && yDrawPos-length<=knownMaxCoord.y) {
		tempWChar=' ';
		setcchar(&tempCChar,&tempWChar,0,1,NULL );
		mvadd_wch( yDrawPos-length, xPos, &tempCChar);
	}
}


