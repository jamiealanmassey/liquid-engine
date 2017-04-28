#include "Widget.h"
#include "Button.h"

namespace liquid { namespace ui {
#ifndef _BUTTONTOGGLED_H
#define _BUTTONTOGGLED_H

class ButtonToggled : public Button
{
public:
    ButtonToggled(float x, float y, std::array<std::string, 3> textureNames);
    ~ButtonToggled();

    virtual void setPressed(bool flag) override;

    const bool isToggled() const;

protected:
    bool mToggled;
};

#endif // _BUTTONTOGGLED_H
}}
