#ifdef SFML
#include "../../graphics/RenderableText.h"
#include "../../graphics/Renderer.h"
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLRENDERABLETEXT_H
#define _SFMLRENDERABLETEXT_H

class SFMLRenderableText : public graphics::RenderableText
{
public:
    SFMLRenderableText(std::string str);
    ~SFMLRenderableText();

    virtual void draw(graphics::Renderer* renderer) override;

    virtual void setString(std::string str) override;

    virtual void setPosition(float x, float y) override;

    void setFont(sf::Font& font);

protected:
    sf::Text mText;
    sf::Font mFont;
};

#endif // _SFMLRENDERABLETEXT_H
}}

#endif // SFML
