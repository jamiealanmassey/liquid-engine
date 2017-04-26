#include "../parser/Parser.h"
#include "../parser/ParserNodeSearch.h"
#include "../data/TextureAtlas.h"
#include "AnimationDefs.h"

namespace liquid { namespace animation {
#ifndef _ANIMATIONPARSER_H
#define _ANIMATIONPARSER_H

class AnimationParser
{
public:
    AnimationParser(parser::Parser& parser);
    AnimationParser(parser::Parser& parser, data::TextureAtlas& textureAtlas);
    ~AnimationParser();

    Animation getAnimation(std::string name);
    AnimationTable getAnimationTable();

protected:
    AnimationTable mAnimationTable;
};

#endif // _ANIMATIONPARSER_H
}}
