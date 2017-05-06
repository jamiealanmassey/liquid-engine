#include <string>
#include "IRenderable.h"

namespace liquid { namespace graphics {
#ifndef _RENDERABLETEXT_H
#define _RENDERABLETEXT_H

class RenderableText : public IRenderable
{
public:
    RenderableText();
    ~RenderableText();

    virtual void setString(std::string str);

    virtual void setPosition(float x, float y) = 0;

    virtual void setColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;

    virtual float getCharacterSize(char character) = 0;

    const std::string getString() const;

protected:
    std::string mString;
};

#endif // _RENDERABLETEXT_H
}}
