#include "Parser.h"
#include <PugiXML/pugixml.hpp>
#include <fstream>

namespace liquid { namespace data {
#ifndef _PARSERXML_H
#define _PARSERXML_H

class ParserXML : public Parser
{
public:
    ParserXML();
    ~ParserXML();

    virtual void parseFile(std::string file) override;
    virtual void parseString(std::string str) override;

    void dumpFile();

protected:
    void parseNextNode(ParserNode* parentNode, pugi::xml_node xmlNode);
};

#endif // _PARSERXML_H
}}
