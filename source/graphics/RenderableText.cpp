#include "RenderableText.h"

namespace liquid {
namespace graphics {

    RenderableText::RenderableText() :
        IRenderable()
    {
    }

    RenderableText::~RenderableText()
    {
    }

    void RenderableText::setString(std::string str)
    {
        mString = str;
    }

    const std::string RenderableText::getString() const
    {
        return mString;
    }

}}
