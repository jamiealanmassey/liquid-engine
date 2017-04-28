#include "Toggle.h"
#include "WidgetManager.h"

namespace liquid {
namespace ui {

    Toggle::Toggle(float x, float y, std::array<std::string, 3> textureNames) :
        Button(x, y, textureNames)
    {
        mToggled = false;
    }

    Toggle::~Toggle()
    {}

    const bool Toggle::isToggled() const
    {
        return mToggled;
    }

    void Toggle::toggle(bool flag)
    {
        mToggled = flag;
        data::TextureAtlas& atlas = mParentWidgetManager->getTextureAtlas();
        data::TextureAtlas::TextureRegion region;

        if (mToggled == true)
            region = atlas.getTextureRegion(mTextureNames[1]);
        else
            region = atlas.getTextureRegion(mTextureNames[0]);

        mVerticesPtr[0]->setTexCoord(region[0]);
        mVerticesPtr[1]->setTexCoord(region[1]);
        mVerticesPtr[2]->setTexCoord(region[2]);
        mVerticesPtr[3]->setTexCoord(region[3]);
    }

    void Toggle::handleMousePressed(int32_t button, float x, float y)
    {
        toggle(!mToggled);
    }

    void Toggle::handleMouseReleased(int32_t button, float x, float y)
    {
    }

}}
