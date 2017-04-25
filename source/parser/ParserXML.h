#include "Parser.h"
#include <PugiXML/pugixml.hpp>
#include <fstream>

namespace liquid { namespace parser {
#ifndef _PARSERXML_H
#define _PARSERXML_H

/** \class ParserXML
 *
 * \ingroup Data
 * \brief De-constructs a pugi::xml_document into a Parser class as ParserNode objects
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 25/04/2017
 *
 */

class ParserXML : public Parser
{
public:
    /// ParserXML Constructor
    ParserXML();

    /// ParserXML Destructor
    ~ParserXML();

    /** \brief Overrides the Parser::parseFile function 
      * \param file Path to the file to be parsed
      */
    virtual void parseFile(std::string file) override;

    /** \brief Overrides the Parser::parseString function
      * \param str String to be parsed
      */
    virtual void parseString(std::string str) override;

    /// \brief Dumps the Parser Tree to a plain text file
    void dumpXMLTreeToFile();

    /// \brief Dumps the Parser Tree to a collection of strings
    std::list<std::string> dumpXMLTreeToList();

protected:
    /** \brief Dumps each node recursively layer by layer
      * \param stream Filestream to write node to
      * \param node ParserNode to use for data output
      * \param depth Current depth of the recursion
      */
    void dumpNextNode(std::list<std::string>& data, ParserNode* node, int32_t depth);

    /** \brief Constructs a ParserNode tree for the Parser with pugiXML
      * \param parserNode The next parserNode to give values to
      * \param xmlNode The next pugi::xml_node in the DOM-tree
      * 
      * Recursively goes through each XML node in the given pugi::xml_document
      * and create a new ParserNode for it, simultaneously linking up previous
      * ParserNode objects and inserting the data of the xml node into the given
      * ParserNode
      */
    void parseNextNode(ParserNode* parserNode, pugi::xml_node xmlNode);

    /** \brief Parse through an XML Tree using the given document
      * \param document XML Document loaded via PugiXML
      */
    void parseXMLTree(const pugi::xml_document& document);
};

#endif // _PARSERXML_H
}}
