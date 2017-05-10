#include "Directories.h"
#include "../common/ResourceManager.h"
#include "../data/TextureAtlas.h"
#include "../parser/ParserXML.h"
#include <Windows.h>
#include <iostream>
#include <filesystem>

namespace liquid {
namespace data {

    Directories::Directories()
    {
        mSearchRecursively = true;
    }

    Directories::~Directories()
    {}

    void Directories::fillResourceManager()
    {
        for (auto directory : mDirectories)
        {
            std::string search = std::experimental::filesystem::current_path().string();
            search.append("\\");
            search.append(directory.second);

            for (auto& p : std::experimental::filesystem::
                recursive_directory_iterator(search))
            {
                std::string name = p.path().stem().string();
                std::string extension = p.path().extension().string();
                
                if (extension == ".atlas")
                {
                    parser::ParserXML atlasParser;
                    atlasParser.parseFile(name + extension);
                    data::TextureAtlas* textureAtlas = new data::TextureAtlas(atlasParser);
                    common::ResourceManager<data::TextureAtlas>::addResource(name, textureAtlas);
                }
            }  
        }
    }

    void Directories::addDirectory(std::string identifier, std::string path)
    {
        mDirectories[identifier] = path;
    }

    std::string Directories::getDirectory(std::string identifier)
    {
        if (mDirectories.find(identifier) == mDirectories.end())
            return "";

        return mDirectories[identifier];
    }

    void Directories::removeDirectory(std::string identifier)
    {
        std::map<std::string, std::string>::iterator it =
            mDirectories.find(identifier);

        if (it != mDirectories.end())
            mDirectories.erase(it);
    }

    void Directories::setSearchRecursively(bool recursive)
    {
        mSearchRecursively = recursive;
    }

    Directories& Directories::instance()
    {
        static Directories singleton;
        return singleton;
    }

}}
