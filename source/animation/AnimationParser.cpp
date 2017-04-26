#include "AnimationParser.h"

namespace liquid {
namespace animation {

    AnimationParser::AnimationParser(parser::Parser& parser)
    {
        parser::ParserNodeSearch search(parser.getRootParserNode());
        search.findParserNodes("");
    }

    AnimationParser::AnimationParser(parser::Parser& parser, data::TextureAtlas& textureAtlas)
    {
        parser::ParserNodeSearch search(parser.getRootParserNode());
        if (search.traverseChild("animation") == false)
            return;

        parser::ParserNode* animNode = search.findParserNode("name");
        std::list<parser::ParserNode*> nodes = search.findParserNodes("frame");
        std::string animName = animNode->getValueAsString("name");
        Animation animation;

        for (auto node : nodes)
        {
            std::string frameName = node->getValueAsString("frame");
            AnimationFrame frame(textureAtlas, frameName, 35.0f);
            animation.push_back(frame);
        }

        mAnimationTable[animName] = animation;
    }

    AnimationParser::~AnimationParser()
    {}

    Animation AnimationParser::getAnimation(std::string name)
    {
        if (mAnimationTable.find(name) != mAnimationTable.end())
            return mAnimationTable[name];

        return Animation();
    }

    AnimationTable AnimationParser::getAnimationTable()
    {
        return mAnimationTable;
    }

}}
