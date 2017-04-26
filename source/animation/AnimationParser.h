#include "../parser/Parser.h"
#include "../parser/ParserNodeSearch.h"
#include "../data/TextureAtlas.h"
#include "AnimationDefs.h"

namespace liquid { namespace animation {
#ifndef _ANIMATIONPARSER_H
#define _ANIMATIONPARSER_H

/** 
 * \class AnimationParser
 *
 * \ingroup Animation
 * \brief Takes a parser::Parser object and produces an AnimationTable from the given data
 */

class AnimationParser
{
public:
    /** \brief AnimationParser Constructor
      * \param parser Reference to the parser::Parser to collect data
      */
    AnimationParser(parser::Parser& parser);

    /** \brief AnimationParser Constructor
      * \param parser Reference to the parser::Parser to collect data
      * \param textureAtlas Reference to data::TextureAtlas to use to collect region data
      */
    AnimationParser(parser::Parser& parser, data::TextureAtlas& textureAtlas);

    /// AnimationParser Destructor
    ~AnimationParser();

    /** \brief Retrieve an Animation with the given name
      * \param name Name of Animation represented as a std::string
      * \return Returns the Animation, Animation() if none found
      */
    Animation getAnimation(std::string name);

    /// \return Gets the produced AnimationTable from the given data
    AnimationTable getAnimationTable();

protected:
    AnimationTable mAnimationTable; ///< Stored AnimationTable from given data
};

#endif // _ANIMATIONPARSER_H
}}
