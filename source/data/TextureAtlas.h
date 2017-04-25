#include "../parser/Parser.h"
#include "../parser/ParserNodeSearch.h"
#include <string>
#include <map>
#include <array>

namespace liquid { namespace data {
#ifndef _TEXTUREATLAS_H
#define _TEXTUREATLAS_H

/** \class TextureAtlas
 *
 * \ingroup Data
 * \brief Uses the Parser class to define how to consume an image efficiently
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 25/04/2017
 *
 */

class TextureAtlas
{
public:
    /// Defines a Texture Coordinate in the form (x, y)
    typedef std::array<float, 2> TextureCoord;

    /// Defines a texture region in the form ((x,y), (x,y), (x,y), (x,y))
    typedef std::array<TextureCoord, 4> TextureRegion;

public:
    /** \brief TextureAtlas Constructor
      * \param parser Parser to construct atlas data
      */
    TextureAtlas(parser::Parser& parser);

    /// TextureAtlas Destructor
    ~TextureAtlas();
    
    /// Compiles using the given Parser class into an atlas
    void compile();

    /// Flushes current data
    void flush();

    /** \brief Assign a new Parser to construct data from
      * \param parser Parser to be used
      */
    void setParser(parser::Parser& parser);

    /** \brief Find the TextureRegion for the given name
      * \param name Name of the region to find
      * \return Found region, if none found will return {}
      */
    TextureRegion getTextureRegion(std::string name);

    /** \brief Find the TextureCoordinate for the given name at the given index
      * \param name Name of the region to find
      * \param index Index of the TextureCoord to find
      * \return Found coordinates, if none found will return {}
      */
    TextureCoord getTextureCoord(std::string name, int32_t index);

protected:
    std::map<std::string, TextureRegion> mTextureAtlas; ///< Compiled std::map of atlas pairs (name, region)

protected:
    parser::Parser mParser; ///< Specified Parser to gather the required data
};

#endif // _TEXTUREATLAS_H
}}
