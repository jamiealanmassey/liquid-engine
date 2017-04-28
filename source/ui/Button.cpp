#include "Button.h"
#include "WidgetManager.h"

namespace liquid {
namespace ui {

    Button::Button(float x, float y, std::array<std::string, 3> textureNames) :
        Widget(x, y)
    {
        mTextureNames = textureNames;
    }

    Button::~Button()
    {}

    void Button::initialise()
    {
        // TODO: also do this when vertices are set
        if (mVerticesSet)
        {
            data::TextureAtlas& atlas = mParentWidgetManager->getTextureAtlas();
            data::TextureAtlas::TextureRegion region;
            region = atlas.getTextureRegion(mTextureNames[0]);

            float width = region[1][0] - region[0][0];
            float height = region[2][1] - region[1][1];

            mVerticesPtr[0]->setTexCoord(region[0]);
            mVerticesPtr[1]->setTexCoord(region[1]);
            mVerticesPtr[2]->setTexCoord(region[2]);
            mVerticesPtr[3]->setTexCoord(region[3]);
            setSize(width, height);
        }
    }

    void Button::update()
    {

    }

    void Button::setPressed(bool flag)
    {
        Widget::setPressed(flag);
        data::TextureAtlas& atlas = mParentWidgetManager->getTextureAtlas();
        data::TextureAtlas::TextureRegion region;

        if (mPresssed == true)
            region = atlas.getTextureRegion(mTextureNames[1]);
        else
            region = atlas.getTextureRegion(mTextureNames[0]);

        mVerticesPtr[0]->setTexCoord(region[0]);
        mVerticesPtr[1]->setTexCoord(region[1]);
        mVerticesPtr[2]->setTexCoord(region[2]);
        mVerticesPtr[3]->setTexCoord(region[3]);
    }

    void Button::setEntered(bool flag)
    {
        Widget::setEntered(flag);
    }

    void Button::setPosition(float x, float y)
    {
        Widget::setPosition(x, y);
        // TODO: Centre the text
    }

    void Button::addPosition(float x, float y)
    {
        Widget::addPosition(x, y);
        // TODO: Centre the text
    }

    void Button::handleMousePressed(int32_t button, float x, float y) {}
    void Button::handleMouseReleased(int32_t button, float x, float y) {}
    void Button::handleMouseMoved(float x, float y) {}
    void Button::handleKeyboardPressed(int32_t key) {}
    void Button::handleKeyboardReleased(int32_t key) {}

}}
