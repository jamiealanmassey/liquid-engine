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

    const std::string getString() const;

protected:
    std::string mString;
};

#endif // _RENDERABLETEXT_H
}}
