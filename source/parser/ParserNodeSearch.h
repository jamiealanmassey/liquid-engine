#include "ParserNode.h"

namespace liquid { namespace parser {
#ifndef _PARSERNODESEARCH_H
#define _PARSERNODESEARCH_H

/** \class ParserNodeSearch
 *
 * \ingroup Parser
 * \brief Traverses over the given ParserNode in different ways
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 25/04/2017
 *
 */

class ParserNodeSearch
{
public:
    /** \brief ParserNodeSearch Constructor
      * \param reference Reference to the root node from which to traverse
      */
    ParserNodeSearch(ParserNode* reference);

    /// ParserNodeSearch Destructor
    ~ParserNodeSearch();

    /** \brief Traverse to a new node in the tree
      * \param name Name of the node to traverse to
      * \return True if succesfully traversed to node, otherwise false
      *
      * Attempts to traverse to the ParserNode with the specified name, to do
      * this the function first traverses to the root ParserNode and then
      * recursively searches down the tree until either the node is found or
      * no node is found
      */
    bool traverseNode(std::string name);

    /** \brief Traverse to a child node of this node
      * \param name Name of the node to traverse to
      * \return True if succesfully traversed to node, otherwise false
      *
      * Attempts to traverse to one of the child nodes to this ParserNode,
      * however it will only traverse down to a child node of this node, not
      * a child node of this node's child nodes
      */
    bool traverseChild(std::string name);

    /** \brief Traverse to this ParserNode's Parent node
      * \return True if there was a parent and traversed, otherwise false
      */
    bool traverseParent();
    
    /// \brief Resets mCurrentNode to the first passed mReferenceNode
    void resetNodeSearch();

    /** \brief Search down from this node for a node with the given name
      * \param name Name of the desired node represented as std::string
      * \return Pointer to a ParserNode if found, otherwise nullptr
      */
    ParserNode* findParserNode(std::string name);

    /** \brief Search down from this node for all nodes with the given name
      * \param name Name of the desired nodes represented as std::string
      * \return Collection of ParserNode objects, empty if none found
      */
    std::list<ParserNode*> findParserNodes(std::string name);

    /** \brief Search for child nodes of this node with the given name
      * \param name Name of the desired nodes represented as std::string
      * \return Collection of ParserNode objects, empty if none found
      */
    std::list<ParserNode*> findParserNodesRelative(std::string name);

    /** \brief Search down from this node for all data with the given key
      * \param key Key of the key-pair value to search for in each object
      * \return Collection of std::string objects representing the found values, empty if none found
      */
    std::list<std::string> findAllData(std::string key);

    /// \return Gets the initial reference ParserNode given
    ParserNode* getReferenceNode() const;

    /// \return Gets the current ParserNode in the traversal
    ParserNode* getCurrentNode() const;

protected:
    /** \brief Recursively search through the tree to find the ParserNode with the given name
      * \param node Next node to search
      * \param name Name of the desired node
      * \return Pointer to found ParserNode, otherwise nullptr
      */
    ParserNode* getParserNode(ParserNode* node, std::string name);

    /** \brief Recursively search through the tree to find any ParserNode with the given name
      * \param node Next node to search
      * \param name Name of the desired nodes
      * \return Collection of ParserNode objects, empty if none found
      */
    std::list<ParserNode*> getParserNodes(ParserNode* node, std::string name);

    /** \brief Recursively search through the tree to find any data with the given key
      * \param node Next node to search
      * \param key Key of the key-pair for data in each node
      * \return Collection of std::string objects representing the found values, empty if none found
      */
    std::list<std::string> getAllData(ParserNode* node, std::string key);

protected:
    ParserNode* mReferenceNode; ///< First node given to the search
    ParserNode* mCurrentNode;   ///< Current ParserNode in the traversal
};

#endif // _PARSERNODESEARCH_H
}}
