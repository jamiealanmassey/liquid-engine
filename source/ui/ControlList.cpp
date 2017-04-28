#include "ControlList.h"

namespace liquid {
namespace ui {

    ControlList::ControlList(float x, float y, std::array<std::string, 2> textureNames) :
        Widget(x, y)
    {
        mTextureNames = textureNames;
        mControlType = eControlType::CONTROLTYPE_SINGLE;
    }

    ControlList::~ControlList()
    {}

    void ControlList::insertElement(Toggle* element)
    {
        mElements.push_back(element);
    }

    void ControlList::removeElement(Toggle* element)
    {
        std::remove(mElements.begin(), mElements.end(), element);
    }

    void ControlList::setTextureNames(std::array<std::string, 2> textureNames)
    {
        mTextureNames = textureNames;
    }

    void ControlList::setControlType(eControlType controlType)
    {
        mControlType = controlType;
    }

    void ControlList::handleMousePressed(int32_t button, float x, float y)
    {
        for (uint32_t i = 0; i < mElements.size(); i++)
        {
            if (mControlType == eControlType::CONTROLTYPE_SINGLE && mElements[i]->isToggled())
            {
                mElements[i]->setPressed(false);
                mElements[i]->toggle(false);
            }

            if (mElements[i]->isPointInside(x, y))
                mElements[i]->toggle(!mElements[i]->isToggled());
        }
    }

    void ControlList::handleMouseReleased(int32_t button, float x, float y) {}
    void ControlList::handleMouseMoved(float x, float y) {}
    void ControlList::handleKeyboardPressed(int32_t key) {}
    void ControlList::handleKeyboardReleased(int32_t key) {}

}}
