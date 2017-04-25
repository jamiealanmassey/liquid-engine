#include <map>
#include <string>
#include <algorithm>
#include <list>

namespace liquid { namespace parser {
#ifndef _PARSENODE_H
#define _PARSENODE_H

/** \class ParserNode
 *
 * \ingroup Data
 * \brief Defines a structure of data in a node based system for the Parser class; stores mapped values
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 24/04/2017
 *
 */

class ParserNode
{
public:
    /// Defines how the data is stored in the ParserNode
    typedef std::map<std::string, std::string> NodeData;

public:
    /// ParserNode Constructor
    ParserNode();

    /** \brief ParserNode Constructor
      * \param parentNode Pointer to the parent ParserNode of this Node
      */
    ParserNode(ParserNode* parentNode);

    /** \brief ParserNode Constructor
      * \param parentNode Pointer to the parent ParserNode of this Node
      * \param name Name of this ParserNode in the Parser
      */
    ParserNode(ParserNode* parentNode, std::string name);

    /// ParserNode Destructor
    ~ParserNode();

    /** \brief Inserts specified data with the specified key
      * \param key Key of the data as a std::string
      * \param value Value of the data as a std::string
      * \return True if successfully inserted, otherwise false: already data with that key
      */
    virtual bool insertData(std::string key, std::string value);

    /** \brief Removes specified data with the specified key
      * \param key Key of the data as a std::string
      * \return True if successfully removed, otherwise false: no data with that key
      */
    virtual bool removeData(std::string key);

    /** \brief Sets the parent of this ParserNode
      * \param node Pointer to the parent ParserNode
      */
    virtual void setParentNode(ParserNode* node);

    /** \brief Inserts a child to this ParserNode
      * \param node Pointer to the child ParserNode
      */
    virtual void insertChildNode(ParserNode* node);

    /** \brief Removes a child to this ParserNode
      * \param node Pointer to the child ParserNode
      */
    virtual void removeChildNode(ParserNode* node);

    /** \brief Sets the name of the ParserNode
      * \param name Name to be set as a std::string
      */
    void setName(std::string name);

    /** \brief Gets the value with the given name as an std::string
      * \param name Name of the value (key) you wish to access
      * \return Returns the value, default: ""
      */
    const std::string getValueAsString(std::string key);

    /** \brief Gets the value with the given key as a int32_t
      * \param key Name of the value (key) you wish to access
      * \return Returns the value, default: 0
      */
    const int32_t getValueAsInteger32(std::string key);

    /** \brief Gets the value with the given key as a float
      * \param key Name of the value (key) you wish to access
      * \return Returns the value, default: 0.0f
      */
    const float getValueAsFloat(std::string key);

    /** \brief Gets the value with the given key as a double
      * \param key Name of the value (key) you wish to access
      * \return Returns the value, default: 0.0
      */
    const double getValueAsDouble(std::string key);

    /** \brief Gets the value with the given key as a boolean
      * \param key Name of the value (key) you wish to access
      * \return Returns the value, default: false
      */
    const bool getValueAsBoolean(std::string key);

    /** \brief Gets the total count of data stored in this ParserNode
      * \return The count of data stored as a int32_t
      */
    const uint32_t getDataCount() const;

    /** \brief Gets the NodeData == std::map(std::string, std::string) stored in this Node
      * \return Collection of Node data represented as a std::map
      */
    const NodeData& getData() const;

    /// \return Gets the Name of this ParserNode
    const std::string getName() const;

    /// \return Gets the std::list that stores all the child ParserNode objects
    std::list<ParserNode*> getChildren() const;

protected:
    /** \brief Uses the input key to retrieve the std::string value as a std::string
      * \param key Key to use to find the value
      * \return Gives the found value, default: ""
      */
    const std::string getDataValue(std::string key);

protected:
    ParserNode*            mParentNode; ///< Parent to this ParserNode
    NodeData               mData;       ///< The data stored in this ParserNode
    std::string            mName;       ///< Name of this node
    std::list<ParserNode*> mChildNodes; ///< Child of this ParserNode
};

#endif // _PARSENODE_H
}}
