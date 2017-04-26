#include "ParserNodeSearch.h"

namespace liquid {
namespace parser {

    ParserNodeSearch::ParserNodeSearch(ParserNode* reference)
    {
        mReferenceNode = reference;
        mCurrentNode = mReferenceNode;
    }

    ParserNodeSearch::~ParserNodeSearch()
    {}

    bool ParserNodeSearch::traverseNode(std::string name)
    {
        ParserNode* findNode = mReferenceNode;
        while (findNode->getParentNode() != nullptr)
            findNode = findNode->getParentNode();

        if ((findNode = getParserNode(findNode, name)) != nullptr)
        {
            mCurrentNode = findNode;
            return true;
        }

        return false;
    }

    bool ParserNodeSearch::traverseChild(std::string name)
    {
        ParserNode* node = mCurrentNode->getChildNode(name);
        if (node != nullptr)
        {
            mCurrentNode = node;
            return true;
        }

        return false;
    }

    bool ParserNodeSearch::traverseParent()
    {
        if (mCurrentNode->getParentNode() != nullptr)
        {
            mCurrentNode = mCurrentNode->getParentNode();
            return true;
        }

        return false;
    }

    void ParserNodeSearch::resetNodeSearch()
    {
        mCurrentNode = mReferenceNode;
    }

    ParserNode* ParserNodeSearch::findParserNode(std::string name)
    {
        return getParserNode(mCurrentNode, name);
    }

    std::list<ParserNode*> ParserNodeSearch::findParserNodes(std::string name)
    {
        return getParserNodes(mCurrentNode, name);
    }
    std::list<std::string> ParserNodeSearch::findAllData(std::string key)
    {
        return getAllData(mCurrentNode, key);
    }

    ParserNode* ParserNodeSearch::getParserNode(ParserNode* node, std::string name)
    {
        if (node->getName() == name)
            return node;

        for (auto child : node->getChildren())
        {
            ParserNode* foundNode = getParserNode(child, name);
            if (foundNode != nullptr)
                return foundNode;
        }

        return nullptr;
    }

    std::list<ParserNode*> ParserNodeSearch::getParserNodes(ParserNode* node, std::string name)
    {
        std::list<ParserNode*> nodes;
        if (node->getName() == name)
            nodes.push_back(node);

        for (auto child : node->getChildren())
        {
            std::list<ParserNode*> cNodes = getParserNodes(child, name);
            nodes.insert(nodes.end(), cNodes.begin(), cNodes.end());
        }

        return nodes;
    }

    std::list<std::string> ParserNodeSearch::getAllData(ParserNode* node, std::string key)
    {
        std::list<std::string> data;
        std::string dataNode = node->getValueAsString(key);

        if (dataNode != "")
            data.push_back(dataNode);

        for (auto child : node->getChildren())
        {
            std::list<std::string> cData = getAllData(child, key);
            data.insert(data.end(), cData.begin(), cData.end());
        }

        return data;
    }

    ParserNode* ParserNodeSearch::getReferenceNode() const
    {
        return mReferenceNode;
    }

    ParserNode* ParserNodeSearch::getCurrentNode() const
    {
        return mCurrentNode;
    }

}}
