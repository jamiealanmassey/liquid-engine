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
    void dumpFile();

protected:
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
};

#endif // _PARSERXML_H
}}
