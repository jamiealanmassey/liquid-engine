#include "TextField.h"
#include "../common/GameManager.h"
#include <SFML/Graphics.hpp>

namespace liquid {
namespace ui {

    TextField::TextField(float x, float y) :
        Widget(x, y)
    {
    }

    TextField::~TextField()
    {
    }

    void TextField::setPosition(float x, float y)
    {
        Widget::setPosition(x, y);
    }

    void TextField::addPosition(float x, float y)
    {
        Widget::addPosition(x, y);
    }

    void TextField::setRenderableText(graphics::RenderableText* renderableText)
    {
        mRenderableText = renderableText;
    }

    void TextField::handleMousePressed(int32_t button, float x, float y)
    {
        Widget::handleMousePressed(button, x, y);
    }

    void TextField::handleMouseReleased(int32_t button, float x, float y)
    {
        Widget::handleMouseReleased(button, x, y);
    }

    void TextField::handleMouseMoved(float x, float y)
    {
        Widget::handleMouseMoved(x, y);
    }

    void TextField::handleKeyboardPressed(int32_t key)
    {
        Widget::handleKeyboardPressed(key);
    }

    void TextField::handleKeyboardReleased(int32_t key)
    {
        Widget::handleKeyboardReleased(key);
    }

    void TextField::handleTextEntered(uint32_t character)
    {
        Widget::handleTextEntered(character);
        liquid::data::Bindings* bindings = common::GameManager::instance().getBindingsClass();
        
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring result = converter.from_bytes(character);
        std::string text = mRenderableText->getString();
        
        size_t convertedNum = 0;
        char convert[1024];
        memset(convert, 1024, '\0');
        wcstombs_s(&convertedNum, convert, result.c_str(), 2);

        if (convert[0] == '\b')
            text.pop_back();
        else if (convert[0] == '\r')
            text.append("\n");
        else
            text.append(convert);

        mRenderableText->setString(text);
    }

}}
