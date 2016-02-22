#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include <PugiXML/pugixml.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

enum eFileType
{
	FILETYPE_TEXTURE	= 0,
	FILETYPE_BATCHDEF	= 1,
	FILETYPE_MUSIC		= 2,
	FILETYPE_SOUND		= 3,
	FILETYPE_FONT		= 4,
	FILETYPE_VERTSHADER = 5,
	FILETYPE_FRAGSHADER = 6,
};

struct LookupData
{
	LookupData() :
		texture(nullptr),
		batchdef(""),
		font(nullptr),
		shader(nullptr)
	{}

	sf::Texture* texture;
	std::string  batchdef;
	sf::Font*	 font;
	sf::Shader*  shader;
};

class ResourceManager
{
public:
	typedef std::vector<std::string>							DirectoryList;
	typedef std::map<std::string, std::vector<std::string>>		DataSources;
	typedef std::map<std::string, std::map<eFileType, int32_t>> LookupTable;

public:
	ResourceManager();
	~ResourceManager();

	/* Core Functions */
	void initialise();

	/* Compilation of data for storing resources */
	void compileDirectoryList();
	void compileDataSources();
	void compileLookupTable();

	/* Helper Function(s) */
	bool findTypeExists(std::string table_name, eFileType file_type);

	/* Lookup Functions */
	LookupData   lookupName(std::string name);
	sf::Texture* lookupTexture(std::string name);
	std::string	 lookupBatchData(std::string name);
	sf::Font*	 lookupFont(std::string name);
	sf::Shader*	 lookupShader(std::string name);

	/* Instance Func */
	static ResourceManager& instance();

protected:
	DirectoryList m_DirectoryList; ///< List of sourced directories
	DataSources   m_DataSources; ///< Map of data sources stored during sourcing
	LookupTable	  m_LookupTable; ///< Lookup table for resources

private:
	std::map<std::pair<std::string, int32_t>, sf::Texture*> m_TextureTable; ///< Stored textures
	std::map<std::pair<std::string, int32_t>, std::string>	m_BatchTable;	///< Stored batches
	std::map<std::pair<std::string, int32_t>, sf::Font*>	m_FontTable;	///< Stored fonts
	std::map<std::pair<std::string, int32_t>, sf::Shader*>	m_ShaderTable;	///< Stored shaders
};

#endif // _RESOURCEMANAGER_H
