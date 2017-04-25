#include "ParserXML.h"

namespace liquid {
namespace parser {

    ParserXML::ParserXML()
    {}

    ParserXML::~ParserXML()
    {}

    void ParserXML::parseFile(std::string file)
    {
        pugi::xml_document document;
        document.load_file(file.c_str());
        parseXMLTree(document);
    }

    void ParserXML::parseString(std::string str)
    {
        pugi::xml_document document;
        document.load_string(str.c_str());
        parseXMLTree(document);
    }

    void ParserXML::dumpXMLTreeToFile()
    {
        std::list<std::string> data;
        std::ofstream stream;
        stream.open("xml_dump_tree.txt");
        dumpNextNode(data, mRootParserNode, 0);

        for (auto dataLine : data)
            stream << dataLine;

        stream.close();
    }

    std::list<std::string> ParserXML::dumpXMLTreeToList()
    {
        std::list<std::string> data;
        dumpNextNode(data, mRootParserNode, 0);
        return data;
    }

    void ParserXML::dumpNextNode(std::list<std::string>& data, ParserNode* node, int32_t depth)
    {
        std::string line = "";
        for (uint32_t i = 0; i < depth; i++)
            line += "\t";

        line += "[" + node->getName() + "]";

        if (node->getData().empty() == false && node->getData().begin()->second != "")
            line += " : " + node->getData().begin()->second + "\n";
        else
            line += "\n";

        data.push_back(line);

        if (node->getChildren().size() > 0)
        {
            for (auto child : node->getChildren())
                dumpNextNode(data, child, depth + 1);
        }

        /*for (uint32_t i = 0; i < depth; i++)
            stream << "\t";

        stream << "[" << node->getName() << "]";

        if (node->getData().empty() == false && node->getData().begin()->second != "")
            stream << " : " << node->getData().begin()->second << "\n";
        else
            stream << "\n";

        if (node->getChildren().size() > 0)
        {
            for (auto child : node->getChildren())
                dumpNextNode(stream, child, depth + 1);
        }*/
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

    void ParserXML::parseXMLTree(const pugi::xml_document& document)
    {
        ParserNode* rootNode = new ParserNode;
        parseNextNode(rootNode, document.root().first_child());
        mRootParserNode = rootNode;
    }

}}
