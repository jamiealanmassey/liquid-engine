#include "SFMLRenderableText.h"
#include "SFMLRenderer.h"

namespace liquid {
namespace impl {

    SFMLRenderableText::SFMLRenderableText(std::string str) :
        graphics::RenderableText()
    {
        setString(str);
        
    }

    SFMLRenderableText::~SFMLRenderableText()
    {
    }

    void SFMLRenderableText::draw(graphics::Renderer* renderer)
    {
        SFMLRenderer* sfml = static_cast<SFMLRenderer*>(renderer);
        sf::RenderWindow* window = sfml->getRenderWindow();
        window->draw(mText);
    }

    void SFMLRenderableText::setString(std::string str)
    {
        graphics::RenderableText::setString(str);
        sf::String sfString(mString);
        mText.setString(sfString);
    }

    void SFMLRenderableText::setColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        mText.setFillColor(sf::Color(r, g, b, a));
    }

    void SFMLRenderableText::setPosition(float x, float y)
    {
        mText.setPosition(x, y);
    }

    float SFMLRenderableText::getCharacterSize(char character)
    {
        return mFont.getGlyph(character, mText.getCharacterSize(), false).advance;
    }

    void SFMLRenderableText::setFont(sf::Font& font)
    {
        mFont = font;
        mText.setFont(mFont);
    }

}}
