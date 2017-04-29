#include "Widget.h"

namespace liquid { namespace ui {
#ifndef _SLIDER_H
#define _SLIDER_H

class Slider : public Widget
{
public:
    enum eSliderType
    {
        SLIDERTYPE_HORIZONTAL = 1,
        SLIDERTYPE_VERTICAL = 0,
    };

public:
    Slider(float x, float y);
    ~Slider();

    void setSliderThumb(Widget* thumb);
    void setSliderType(eSliderType type);

    Widget* getSliderThumb();
    const eSliderType getSliderType() const;
    const float getSliderRatio() const;

    /// \brief Override Widget::handleMousePressed
    void handleMousePressed(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseReleased
    void handleMouseReleased(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseMoveds
    void handleMouseMoved(float x, float y) override;

protected:
    Widget* mSliderThumb;
    eSliderType mSliderType;
    float mSliderRatio;
};

#endif // _SLIDER_H
}}
