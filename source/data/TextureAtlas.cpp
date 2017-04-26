#include "TextureAtlas.h"

namespace liquid {
namespace data {

    TextureAtlas::TextureAtlas(parser::Parser& parser)
    {
        mParser = parser;
        compile();
    }

    TextureAtlas::~TextureAtlas()
    {}

    void TextureAtlas::compile()
    {
        parser::ParserNodeSearch nodes(mParser.getRootParserNode());
        std::list<parser::ParserNode*> regionNodes = nodes.findParserNodes("region");

        for (auto node : regionNodes)
        {
            std::string name = node->getChildNode("name")->getValueAsString("name");
            float coord1 = node->getChildNode("coord1")->getValueAsFloat("coord1");
            float coord2 = node->getChildNode("coord2")->getValueAsFloat("coord2");
            float coord3 = node->getChildNode("coord3")->getValueAsFloat("coord3");
            float coord4 = node->getChildNode("coord4")->getValueAsFloat("coord4");

            TextureCoord texCoord1 = { coord1, coord2 };
            TextureCoord texCoord2 = { coord1 + coord3, coord2 };
            TextureCoord texCoord3 = { coord1 + coord3, coord2 + coord4 };
            TextureCoord texCoord4 = { coord1, coord2 + coord4 };

            mTextureAtlas[name] = { texCoord1, texCoord2, texCoord3, texCoord4 };
        }
    }

    void TextureAtlas::flush()
    {
        mTextureAtlas.clear();
    }

    void TextureAtlas::setParser(parser::Parser& parser)
    {
        mParser = parser;
    }

    TextureAtlas::TextureRegion TextureAtlas::getTextureRegion(std::string name)
    {
        if (mTextureAtlas.find(name) != mTextureAtlas.end())
            return mTextureAtlas[name];

        return {};
    }

    TextureAtlas::TextureCoord TextureAtlas::getTextureCoord(std::string name, int32_t index)
    {
        if (mTextureAtlas.find(name) != mTextureAtlas.end())
            return mTextureAtlas[name][index];

        return {};
    }

}}
