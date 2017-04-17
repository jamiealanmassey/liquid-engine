#include "Directories.h"
#include "../common/ResourceManager.h"

namespace liquid {
namespace data {

    Directories::Directories()
    {
        mSearchRecursively = true;
    }

    Directories::~Directories()
    {}

    void Directories::fillResourceManager()
    {}

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
