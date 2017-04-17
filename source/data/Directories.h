#include <string>
#include <map>

namespace liquid { namespace data {
#ifndef _DIRECTORIES_H
#define _DIRECTORIES_H

/**
 * \class Directories
 *
 * \ingroup Data
 * \brief Takes the given directories, searches them and can be abstracted to store resources
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 10/04/2017
 *
 */

class Directories
{
private:
    /// Directories Constructor
    Directories();

    /// Directories Destructor
    ~Directories();

public:
    /** \brief Using the sourced directories creates Resources
      *
      * Use this Manager to take the given and found directories to search for 
      * files and translate them into Resources for the ResourceManager by i.e.
      * using the file extension that is attached to the filename (perhaps use
      * the FileName class for this.
      */
    virtual void fillResourceManager();

    /** \brief Adds a directory to the mDirectories map
      * \param identifier std::string representation to name the path for retrieval
      * \param path The path to store relative to the folder where the program is executed
      */
    virtual void addDirectory(std::string identifier, std::string path);
    
    /** \brief Retrieve a Directory using the identifier (name)
      * \param identifier ID of the directory to retrieve
      * \return The directory path
      */
    virtual std::string getDirectory(std::string identifier);
    
    /** \brief Remove a directory using the identifier (name)
      * \param identifier ID of the directory to remove
      */
    virtual void removeDirectory(std::string identifier);
    
    /** \brief Sets for searching sub-directories additionally to the given one
      * \param recursive Flag to set
      */
    void setSearchRecursively(bool recursive);

    /// \brief The one and only instance of this class (Singleton)
    static Directories& instance();

protected:
    std::map<std::string, std::string> mDirectories;       ///< Map of key-pairs of (string, string) to set names to directories
    bool                               mSearchRecursively; ///< Denotes that if when fillResourceManager() is called to search sub-directories
};

#endif // _DIRECTORIES_H
}}
