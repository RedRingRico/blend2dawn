#ifndef __B2D_BLENDERTYPES_HPP__
#define __B2D_BLENDERTYPES_HPP__

typedef struct __BLENDER_FILE_HEADER
{
	// Should be "BLENDER"
	char	ID[ 7 ];
	// 32- or 64-bit | _ or -
	char	BitSize;
	// Endianess v == Small | V == Big
	char	Endianess;
	// N.MO format
	char	Version[ 3 ];
}BLENDER_FILE_HEADER;

typedef struct __BLENDER_FILE_BLOCK_HEADER
{
	// ID of the file block
	char	Code[ 4 ];
	// Total size (in bytes) of the data after this header
	int		Size;
	// The memory address the structure was located at when written to storage
	// [Not applicable, also, needs to be variable between 4 and 8 bytes]
	void	*OldMemoryAddress;
	// SDNA Index
	int		SDNAIndex;
	// How many of these are there?
	int		Count;
}BLENDER_FILE_BLOCK_HEADER;

typedef struct __BLENDER_SDNA
{	
	char	ID[ 4 ];
	char	Name[ 4 ];
}BLENDER_SDNA;

#endif

