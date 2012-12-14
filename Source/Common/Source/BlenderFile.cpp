#include <BlenderFile.hpp>
#include <cstdio>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <sstream>

int BlenderFile::Read( const char *p_pBlendFile )
{
	FILE *pFile = fopen( p_pBlendFile, "rb" );

	BLENDER_FILE_HEADER Header;
	fread( &Header, sizeof( BLENDER_FILE_HEADER ), 1, pFile );

	fclose( pFile );

	char *pHeaderID = new char[ 8 ];
	strncpy( pHeaderID, Header.ID, 7 );
	pHeaderID[ 7 ] = '\0';
	std::string Endianess;
	std::string BitSize;

	if( Header.BitSize == '_' )
	{
		BitSize = "32-bit";
	}
	else if( Header.BitSize == '-' )
	{
		BitSize = "64-bit";
	}
	else
	{
		BitSize = "UNKNOWN";
	}

	if( Header.Endianess == 'v' )
	{
		Endianess = "Little Endian";
	}
	else if( Header.Endianess == 'V' )
	{
		Endianess = "Big Endian";
	}
	else
	{
		Endianess = "UNKNOWN";
	}


	printw( "%s | %s | %s | %c.%c%c\n", pHeaderID, BitSize.c_str( ),
		Endianess.c_str( ), Header.Version[ 0 ], Header.Version[ 1 ],
		Header.Version[ 2 ] );

	delete [ ] pHeaderID;

	return 0;
}
