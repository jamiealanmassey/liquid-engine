#include "Slider.h"

namespace liquid {
namespace ui {

    Slider::Slider(float x, float y) :
        Widget(x, y)
    {
        mSliderThumb = nullptr;
        mSliderRatio = 0.5f;
        mSliderType = SLIDERTYPE_VERTICAL;
    }

    Slider::~Slider()
    {}

    void Slider::setSliderThumb(Widget* thumb)
    {
        mSliderThumb = thumb;
    }

    void Slider::setSliderType(eSliderType type)
    {
        mSliderType = type;
    }

    Widget* Slider::getSliderThumb()
    {
        return mSliderThumb;
    }

    const Slider::eSliderType Slider::getSliderType() const
    {
        return mSliderType;
    }

    const float Slider::getSliderRatio() const
    {
        return mSliderRatio;
    }

    void Slider::handleMousePressed(int32_t button, float x, float y)
    {
        if (mSliderThumb && mSliderThumb->isPointInside(x, y))
            mSliderThumb->setPressed(true);
    }

    void Slider::handleMouseReleased(int32_t button, float x, float y)
    {
        if (mSliderThumb && mSliderThumb->isPressed())
            mSliderThumb->setPressed(false);
    }

    void Slider::handleMouseMoved(float x, float y) 
    {
        if (mSliderThumb && mSliderThumb->isPressed())
        {
            float positionX = std::max(x, mPositionX);
            float positionY = std::max(y, mPositionY);
        
            positionX = std::min(positionX, mPositionX + mWidth);
            positionY = std::min(positionY, mPositionY + mHeight);

            if (mSliderType == SLIDERTYPE_HORIZONTAL)
            {
                mSliderThumb->setPosition(positionX, mPositionY);
                mSliderRatio = (mSliderThumb->getPositionX() - mPositionX) / mWidth;
            }
            else
            {
                mSliderThumb->setPosition(mPositionX, positionY);
                mSliderRatio = (mSliderThumb->getPositionY() - mPositionY) / mHeight;
            }
        }
    }

}}
