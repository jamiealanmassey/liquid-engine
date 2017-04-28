#include "Widget.h"

namespace liquid { namespace ui {
#ifndef _BUTTON_H
#define _BUTTON_H

class Button : public Widget
{
public:
    Button(float x, float y, std::array<std::string, 3> textureNames);
    ~Button();

    virtual void initialise() override;
    virtual void update() override;

    virtual void setPressed(bool flag) override;
    virtual void setEntered(bool flag) override;

    virtual void setPosition(float x, float y) override;
    virtual void addPosition(float x, float y) override;

    void handleMousePressed(int32_t button, float x, float y) override;
    void handleMouseReleased(int32_t button, float x, float y) override;
    void handleMouseMoved(float x, float y) override;
    void handleKeyboardPressed(int32_t key) override;
    void handleKeyboardReleased(int32_t key) override;

protected:
    std::array<std::string, 3> mTextureNames;
};

#endif // _BUTTON_H
}}
