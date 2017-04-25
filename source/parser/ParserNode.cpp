#include "ParserNode.h"

namespace liquid {
namespace parser {

    ParserNode::ParserNode()
    {
        mParentNode = nullptr;
        mName = "";
    }

    ParserNode::ParserNode(ParserNode* parentNode)
    {
        mParentNode = parentNode;
        mName = "";
    }

    ParserNode::ParserNode(ParserNode* parentNode, std::string name)
    {
        mParentNode = parentNode;
        mName = name;
    }

    ParserNode::~ParserNode()
    {}

    bool ParserNode::insertData(std::string key, std::string value)
    {
        if (mData.find(key) == mData.end())
        {
            mData[key] = value;
            return true;
        }

        return false;
    }

    bool ParserNode::removeData(std::string key)
    {
        if (mData.find(key) != mData.end())
        {
            mData.erase(key);
            return true;
        }

        return false;
    }

    void ParserNode::setParentNode(ParserNode* node)
    {
        mParentNode = node;
    }

    void ParserNode::insertChildNode(ParserNode* node)
    {
        mChildNodes.push_back(node);
    }

    void ParserNode::removeChildNode(ParserNode* node)
    {
        std::list<ParserNode*>::iterator it =
        std::find(mChildNodes.begin(), mChildNodes.end(), node);

        if (it != mChildNodes.end())
        {
            (*it)->setParentNode(nullptr);
            mChildNodes.erase(it);
        }
    }

    void ParserNode::setName(std::string name)
    {
        mName = name;
    }

    const std::string ParserNode::getValueAsString(std::string key)
    {
        return getDataValue(key);
    }

    const int32_t ParserNode::getValueAsInteger32(std::string key)
    {
        std::string value = getDataValue(key);
        if (value == "")
            return 0;
        else
            return std::stoi(value);
    }

    const float ParserNode::getValueAsFloat(std::string key)
    {
        std::string value = getDataValue(key);
        if (value == "")
            return 0.0f;
        else
            return std::stof(value);
    }

    const double ParserNode::getValueAsDouble(std::string key)
    {
        std::string value = getDataValue(key);
        if (value == "")
            return 0.0;
        else
            return std::stod(value);
    }

    const bool ParserNode::getValueAsBoolean(std::string key)
    {
        std::string value = getDataValue(key);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        return (value == "1" || value == "true");
    }

    const uint32_t ParserNode::getDataCount() const
    {
        return mData.size();
    }

    const ParserNode::NodeData& ParserNode::getData() const
    {
        return mData;
    }

    ParserNode* ParserNode::getChildNode(std::string name)
    {
        std::list<ParserNode*>::iterator it =
        std::find_if(mChildNodes.begin(), mChildNodes.end(),
            [&nm = name](const ParserNode* node)
        {
            return (node->getName() == nm);
        });

        if (it != mChildNodes.end())
            return (*it);
        
        return nullptr;
    }

    const std::string ParserNode::getName() const
    {
        return mName;
    }

    std::list<ParserNode*> ParserNode::getChildren() const
    {
        return mChildNodes;
    }

    const std::string ParserNode::getDataValue(std::string key)
    {
        if (mData.find(key) != mData.end())
            return mData[key];

        return "";
    }

}}
