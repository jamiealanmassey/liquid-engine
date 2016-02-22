#include "ResourceManager.h"
#include "../utilities/FileName.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::initialise()
{
	// 1) Create directory list by sourcing sub-directories
	// 2) Produce data sources by looking through each directory and matching
	//	  names together for storing
	// 3) Finally create the lookup table by assigning resources with an ID
	compileDirectoryList();
	compileDataSources();
	compileLookupTable();
}

void ResourceManager::compileDirectoryList()
{
	// Add root directory to the list
	m_DirectoryList.push_back("assets/");

	// While we are not at the end of the directory list we are going to find
	// the sub-directories of each folder and store them in the vector
	for (uint32_t i = 0; i < m_DirectoryList.size(); i++)
	{
		// Create file data and a handle to search for folders
		WIN32_FIND_DATA file_data;
		HANDLE	search = FindFirstFileA((m_DirectoryList[i] + "*").c_str(), &file_data);

		// Keep searching for files and adding them to the directory list
		// until there are no more
		do
		{
			if ((file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && file_data.cFileName[0] != '.')
				m_DirectoryList.push_back(m_DirectoryList[i] + file_data.cFileName + "/");
		} 
		while (FindNextFileA(search, &file_data));

		// Make sure to close folder search
		FindClose(search);
	}
}

void ResourceManager::compileDataSources()
{
	// Create a vector to store a list of sourced files
	std::vector<std::string> files;

	// Search through each directory sampling file data
	for (auto folder : m_DirectoryList)
	{
		// Create data and search handle to find files
		WIN32_FIND_DATA file_data;
		HANDLE search = FindFirstFileA((folder + "*").c_str(), &file_data);

		// Go through each file in the folder and take the path + filename storing the
		// information in our temporary files vector
		do
		{
			if (!(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				files.push_back(folder + file_data.cFileName);
		} 
		while (FindNextFileA(search, &file_data));

		// Close the file search handle
		FindClose(search);
	}

	// Iterate through sourced data splitting file name and extension and placing given file
	// data into m_DataSources
	for (auto data : files)
		m_DataSources[FileName(data).getFilename()].push_back(data);
}

void ResourceManager::compileLookupTable()
{
	// Create iterator to go through our data sources
	DataSources::iterator it = m_DataSources.begin();

	// Iterate through each data source compiling data into a lookup table which can
	// be used later to find resources
	for (; it != m_DataSources.end(); ++it)
	{
		// Go through each resource adding it to our lookup table
		for (auto resource : it->second)
		{
			// Create FileName
			FileName file(resource);

			// Sample both name and extension again
			std::string name = file.getFilename();
			std::string ext  = file.getExtension();

			// First find out which resource type that we are dealing with
			if (ext == "png" || ext == "jpeg" || ext == "jpg" || ext == "bmp")
			{
				// Create texture table iterator
				std::map<std::pair<std::string, int32_t>, sf::Texture*>::iterator it = m_TextureTable.begin();
				bool    found_texture = false;
				int32_t found_texture_index = 0;

				// Iterate through each texture table element
				for (; it != m_TextureTable.end(); ++it)
				{
					if ((*it).first.first == name)
					{
						found_texture = true;
						found_texture_index = (*it).first.second;
					}
				}

				// If there was no texture found then we want to create the new texture
				// and add it to the texture table
				if (!found_texture)
				{
					// Create texture from file
					sf::Texture* texture = new sf::Texture;
					texture->loadFromFile(resource);

					// Produce key pair to store name and id
					std::pair<std::string, int32_t> res_id = std::pair<std::string, int32_t>
						(name, m_TextureTable.size() + 1);

					// Store texture with key pair and set found texture index
					m_TextureTable[res_id] = texture;
					found_texture_index = res_id.second;
				}

				// Set lookup table name and file type
				m_LookupTable[name][FILETYPE_TEXTURE] = found_texture_index;
			}
			else if (ext == "batch")
			{

			}
			else if (ext == "ttf")
			{
				// Create font table iterator
				std::map<std::pair<std::string, int32_t>, sf::Font*>::iterator it = m_FontTable.begin();
				bool    found_font = false;
				int32_t found_font_index = 0;

				// Iterate through each font table element
				for (; it != m_FontTable.end(); ++it)
				{
					if ((*it).first.first == name)
					{
						found_font = true;
						found_font_index = (*it).first.second;
					}
				}

				// If there was no font found then we want to create the new texture
				// and add it to the texture table
				if (!found_font)
				{
					// Create texture from file
					sf::Font* font = new sf::Font;
					font->loadFromFile(resource);

					// Produce key pair to store name and id
					std::pair<std::string, int32_t> res_id = std::pair<std::string, int32_t>
						(name, m_FontTable.size() + 1);

					// Store texture with key pair and set found texture index
					m_FontTable[res_id] = font;
					found_font_index = res_id.second;
				}

				// Set lookup table name and file type
				m_LookupTable[name][FILETYPE_FONT] = found_font_index;
			}
		}
	}
}

bool ResourceManager::findTypeExists(std::string table_name, eFileType file_type)
{
	// Attempt to find if file type exists
	if (m_LookupTable[table_name].find(file_type) != m_LookupTable[table_name].end())
		return true;
	else
		return false;
}

LookupData ResourceManager::lookupName(std::string name)
{
	LookupData data;
	data.texture = lookupTexture(name);
	data.font = lookupFont(name);
	// TODO: rest of lookups

	return data;
}

sf::Texture* ResourceManager::lookupTexture(std::string name)
{
	if (m_LookupTable.find(name) == m_LookupTable.end())
		return nullptr;

	if (!findTypeExists(name, FILETYPE_TEXTURE))
		return nullptr;

	std::pair<std::string, int32_t> key =
		std::pair<std::string, int32_t>(name, m_LookupTable[name][FILETYPE_TEXTURE]);
	
	return m_TextureTable[key];
}

std::string ResourceManager::lookupBatchData(std::string name)
{
	return std::string();
}

sf::Font * ResourceManager::lookupFont(std::string name)
{
	if (m_LookupTable.find(name) == m_LookupTable.end())
		return nullptr;

	if (!findTypeExists(name, FILETYPE_FONT))
		return nullptr;

	std::pair<std::string, int32_t> key =
		std::pair<std::string, int32_t>(name, m_LookupTable[name][FILETYPE_FONT]);

	return m_FontTable[key];
}

sf::Shader * ResourceManager::lookupShader(std::string name)
{
	return nullptr;
}

ResourceManager& ResourceManager::instance()
{
	static ResourceManager singleton;
	return singleton;
}
