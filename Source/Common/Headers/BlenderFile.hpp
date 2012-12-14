#ifndef __B2D_BLENDERFILE_HPP__
#define __B2D_BLENDERFILE_HPP__

#include <BlenderTypes.hpp>
#include <vector>

class BlenderFile
{
public:
	int Read( const char *p_pBlendFile );

private:
	std::vector< char > m_SDNANames;
	std::vector< char > m_SDNATypes;
	std::vector< short > m_SDNATypesSizes;
	std::vector< short > m_SDNAStructureTypes;
	std::vector< short > m_SDNAFieldTypes;
};

#endif

