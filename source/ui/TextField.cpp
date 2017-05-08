#include "TextField.h"
#include "../common/GameManager.h"
#include "../utilities/Vertex2.h"
#include "../utilities/DeltaTime.h"
#include <SFML/Graphics.hpp>

namespace liquid {
namespace ui {

    TextField::TextField(float x, float y) :
        Widget(x, y)
    {
        mRenderableText = nullptr;
        mCaret = nullptr;
        mTextureName = "";
        mAccumulator = 0.0f;
        mCaretToggle = false;
    }

    TextField::~TextField()
    {
    }

    void TextField::initialise()
    {
        if (mTextureName != "")
            setTexture(mTextureName);
    }

    void TextField::update()
    {
        if (hasFocus() == true)
            mAccumulator += utilities::DeltaTime::DELTA;

        if (mAccumulator > 500.0f)
        {
            mCaretToggle ? turnCaretOff() : turnCaretOn();
            mAccumulator = 0.0f;
        }
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
        mRenderableText->setPosition(mPositionX + 10.0f, mPositionY + 5.0f);
    }

    void TextField::setCaret(Widget* caret)
    {
        mCaret = caret;
        mCaret->setPosition(mPositionX + 14.0f, mPositionY + 10.0f);
        turnCaretOff();
    }

    void TextField::setTextureName(std::string textureName)
    {
        mTextureName = textureName;
    }

    void TextField::setFocused(bool flag)
    {
        Widget::setFocused(flag);

        flag ? turnCaretOn() : turnCaretOff();
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

        size_t convertedNum = 0;
        char convert[1024];
        memset(convert, 1024, '\0');
        wcstombs_s(&convertedNum, convert, result.c_str(), 2);

        if (convert[0] == '\b' && mWholeText.empty() == false)
            mWholeText.pop_back();
        else if (convert[0] != '\b' && convert[0] != '\r')
            mWholeText.append(convert);

        resizeRenderableText();
    }

    void TextField::resizeRenderableText()
    {
        uint32_t count = mWholeText.size();
        uint32_t i = count;
        float sizeX = 0.0f;

        for (; i > 0; i--)
        {
            sizeX += mRenderableText->getCharacterSize(mWholeText[i]);

            if (sizeX >= mSize[0] - 30.0f)
                break;
        }

        std::string parsed = mWholeText.substr(i, count - i);
        mRenderableText->setString(parsed);
        mCaret->setPosition(mPositionX + sizeX + (20.0f * (float)(i == 0)), mPositionY + 12.0f);
    }

    void TextField::turnCaretOn()
    {
        mCaretToggle = true;
        setCaretTransparency(255.0f);
    }

    void TextField::turnCaretOff()
    {
        mCaretToggle = false;
        setCaretTransparency(0.0f);
    }

    void TextField::setCaretTransparency(float alpha)
    {
        std::array<utilities::Vertex2*, 4> verts = mCaret->getVerticesPtr();
        std::array<float, 4> colour = verts[0]->getColour();

        verts[0]->setColour(colour[0], colour[1], colour[2], alpha);
        verts[1]->setColour(colour[0], colour[1], colour[2], alpha);
        verts[2]->setColour(colour[0], colour[1], colour[2], alpha);
        verts[3]->setColour(colour[0], colour[1], colour[2], alpha);
    }

}}
