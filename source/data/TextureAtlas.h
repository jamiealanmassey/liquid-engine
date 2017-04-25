#include "../parser/Parser.h"
#include <string>
#include <map>
#include <array>

namespace liquid { namespace data {
#ifndef _TEXTUREATLAS_H
#define _TEXTUREATLAS_H

class TextureAtlas
{
public:
    typedef std::array<float, 2>        TextureCoord;
    typedef std::array<TextureCoord, 4> TextureRegion;

public:
    TextureAtlas(parser::Parser& parser);
    ~TextureAtlas();
    
    void compile();
    void flush();

    TextureRegion getTextureRegion(std::string name);
    TextureCoord getTextureCoord(std::string name, int32_t index);

protected:
    std::map<std::string, TextureRegion> mTextureAtlas; ///< Compiled std::map of atlas pairs (name, region)

protected:
    parser::Parser mParser; ///< Specified Parser to gather the required data
};

#endif // _TEXTUREATLAS_H
}}
