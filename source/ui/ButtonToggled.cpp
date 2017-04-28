#include "ButtonToggled.h"
#include "WidgetManager.h"

namespace liquid {
namespace ui {

    ButtonToggled::ButtonToggled(float x, float y, std::array<std::string, 3> textureNames) :
        Button(x, y, textureNames)
    {
        mToggled = false;
    }

    ButtonToggled::~ButtonToggled()
    {}

    void ButtonToggled::setPressed(bool flag)
    {
        Widget::setPressed(flag);

        if (flag == false)
            return;

        data::TextureAtlas& atlas = mParentWidgetManager->getTextureAtlas();
        data::TextureAtlas::TextureRegion region;

        if (mToggled == true)
        {
            region = atlas.getTextureRegion(mTextureNames[0]);
            mToggled = false;
        }
        else
        {
            region = atlas.getTextureRegion(mTextureNames[1]);
            mToggled = true;
        }

        mVerticesPtr[0]->setTexCoord(region[0]);
        mVerticesPtr[1]->setTexCoord(region[1]);
        mVerticesPtr[2]->setTexCoord(region[2]);
        mVerticesPtr[3]->setTexCoord(region[3]);
    }

    const bool ButtonToggled::isToggled() const
    {
        return mToggled;
    }

}}
