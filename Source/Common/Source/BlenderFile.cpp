#include <BlenderFile.hpp>
#include <cstdio>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <sstream>

int BlenderFile::Read( const char *p_pBlendFile )
{
	FILE *pFile = nullptr;
	pFile = fopen( p_pBlendFile, "rb" );

	if( pFile == nullptr )
	{	
		printw( "Could not open file: %s\n", p_pBlendFile );
		refresh( );
		return 1;
	}

	// Is there any more than the file's header in the file?
	fseek( pFile, 0, SEEK_END );
	long FileSize = ftell( pFile );
	rewind( pFile );

	if( FileSize <= sizeof( BLENDER_FILE_HEADER ) )
	{
		printw( "File is not substantially large enough to contain valid "
			"Blender information\n" );
		refresh( );
		return 1;
	}

	BLENDER_FILE_HEADER Header;
	fread( &Header, sizeof( BLENDER_FILE_HEADER ), 1, pFile );

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

	printw( "File size: %ld\n", FileSize );
	size_t Cur = ftell( pFile );
	size_t Itr = 0;
	while( Cur < FileSize )
	{
		BLENDER_FILE_BLOCK_HEADER BlockHeader;

		fread( &BlockHeader, sizeof( BLENDER_FILE_BLOCK_HEADER ), 1, pFile );

		char *pCode = new char[ 5 ];
		strncpy( pCode, BlockHeader.Code, 4 );
		pCode[ 4 ] = '\0';		

		if( strncmp( "DNA1", pCode, 4 ) == 0 )
		{
			mvprintw( 11, 0, "Found at %ld | %d\n", Itr, BlockHeader.Size );
		}
		Cur = ftell( pFile ) + BlockHeader.Size;

		mvprintw( 10, 0, "%ld: %s | %ld : %ld\n", Cur, pCode, Itr, BlockHeader.Size );

		refresh( );
		fseek( pFile, BlockHeader.Size, SEEK_CUR );


		delete [ ] pCode;
		++Itr;
	}

	fclose( pFile );

	return 0;
}
