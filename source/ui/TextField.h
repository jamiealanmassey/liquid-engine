#include "Widget.h"
#include "../graphics/RenderableText.h"
#include <locale>
#include <stdlib.h>

namespace liquid { namespace ui {
#ifndef _TEXTFIELD_H
#define _TEXTFIELD_H

class TextField : public Widget
{
public: 
    TextField(float x, float y);
    ~TextField();

    virtual void initialise() override;

    virtual void update() override;

    virtual void setPosition(float x, float y) override;
    virtual void addPosition(float x, float y) override;

    void setRenderableText(graphics::RenderableText* renderableText);

    void setCaret(Widget* caret);

    void setTextureName(std::string textureName);

    virtual void setFocused(bool flag) override;

    /// \brief Virtual for when the mouse has been pressed
    virtual void handleMousePressed(int32_t button, float x, float y) override;

    /// \brief Virtual for when the mouse has been released
    virtual void handleMouseReleased(int32_t button, float x, float y) override;

    /// \brief Virtual for when the mouse has been moved
    virtual void handleMouseMoved(float x, float y) override;

    /// \brief Virtual for when the keyboard has been pressed
    virtual void handleKeyboardPressed(int32_t key) override;

    /// \brief Virtual for when the keyboard has been pressed
    virtual void handleKeyboardReleased(int32_t key) override;

    /// \brief Virtual for when text has been entered
    virtual void handleTextEntered(uint32_t character) override;

protected:
    void resizeRenderableText();
    void turnCaretOn();
    void turnCaretOff();
    void setCaretTransparency(float alpha);

protected:
    graphics::RenderableText* mRenderableText;
    Widget*                   mCaret;
    std::string               mTextureName;
    std::string               mWholeText;
    float                     mAccumulator;
    bool                      mCaretToggle;
};

#endif // _TEXTFIELD_H
}}
