# Matrix

This important program runs Matrix-effect simulation in console. It's intended to be cross platform eventually.

Version 0.02 - Windows port

	- Compiles and runs on both Windows & Linux

	- Linux Version uses ncurses
		- Resets on console resize
		- Tested with libncurses-dev 6.3 in Ubuntu

	- WIN32 version tested with PDCurses x86 v 3.9 by William McBrine
	  and specifically PDCurses for Windows console
		- WIN32-version doesn't handle console resizes correctly
		
Credits:

	- PDCurses by William McBrine  https://pdcurses.org/
	- PDCurses Windows console port was originally provided by Chris Szurgot szurgot@itribe.net
