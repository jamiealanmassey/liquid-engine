#include "ParserXML.h"

namespace liquid {
namespace parser {

    ParserXML::ParserXML()
    {}

    ParserXML::~ParserXML()
    {}

    void ParserXML::parseFile(std::string file)
    {
        pugi::xml_document doc;
        if (doc.load_file(file.c_str()) == 0)
            return;

        ParserNode* rootNode = new ParserNode;
        parseNextNode(rootNode, doc.root().first_child());
        mParserNodes.push_back(rootNode);
    }

    void ParserXML::parseString(std::string str)
    {
        pugi::xml_document doc;
        if (doc.load_string(str.c_str()) == 0)
            return;

        ParserNode* rootNode = new ParserNode;
        parseNextNode(rootNode, doc.root().first_child());
        mParserNodes.push_back(rootNode);
    }

    void ParserXML::parseNextNode(ParserNode* parserNode, pugi::xml_node xmlNode)
    {
        if (xmlNode.first_attribute())
        {
            std::string parserName = xmlNode.first_attribute().value();
            std::string parserValue = xmlNode.first_child().value();
            parserNode->setName(parserName);
            parserNode->insertData(parserName, parserValue);
        }

        if (xmlNode.first_child().first_child())
        {
            for (pugi::xml_node node : xmlNode.children())
            {
                ParserNode* nextNode = new ParserNode();
                nextNode->setParentNode(parserNode);
                parserNode->insertChildNode(nextNode);
                parseNextNode(nextNode, node);
            }
        }
    }

    void outputNextNode(std::ofstream& stream, ParserNode* node, int32_t depth)
    {
        for (uint32_t i = 0; i < depth; i++)
            stream << "\t";

        stream << "[" << node->getName() << "]";

        if (node->getData().empty() == false && node->getData().begin()->second != "")
            stream << " : " << node->getData().begin()->second << "\n";
        else
            stream << "\n";

        if (node->getChildren().size() > 0)
        {
            for (auto child : node->getChildren())
                outputNextNode(stream, child, depth + 1);
        }
    }

    void ParserXML::dumpFile()
    {
        std::ofstream stream;
        stream.open("xml_dump_tree.txt");
        ParserNode* node = mParserNodes[0];
        outputNextNode(stream, node, 0);
        stream.close();
    }

}}
