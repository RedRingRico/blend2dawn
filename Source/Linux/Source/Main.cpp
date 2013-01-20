#include <ncurses.h>
#include <BlenderFile.hpp>
#include <GitVersion.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	BlenderFile File;
	initscr( );
	printw( "blend2dawn\n[Ver. 0.0.0.%d | %s]\n", GIT_ROLLINGCOUNT,
		GIT_COMMITHASH );

	if( p_Argc > 1 )
	{
		printw( "Processing [%s]\n", p_ppArgv[ 1 ] );
		File.Read( p_ppArgv[ 1 ] );
	}
	refresh( );
	getch( );
	endwin( );
	return 0;
}
