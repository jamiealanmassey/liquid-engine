#include "../common/Entity.h"

namespace liquid { namespace ui {
#ifndef _WIDGET_H
#define _WIDGET_H

class WidgetManager;
class Widget : public common::Entity
{
public:
    Widget(float x, float y);
    ~Widget();

    virtual void initialise() override;
    virtual void update() override;

    virtual void setPosition(float x, float y) override;
    virtual void addPosition(float x, float y) override;

    virtual bool acceptsFocus();
    virtual bool acceptsFocusKeyboard();

    virtual void setPressed(bool flag);
    virtual void setEntered(bool flag);

    virtual void setSize(float w, float h);
    virtual void setMinSize(float w, float h);
    virtual void setMaxSize(float w, float h);

    virtual void show();
    virtual void hide();
    virtual void enable();
    virtual void disable();

    virtual void setCanFocus(bool flag);
    virtual void setCanFocusKeyboard(bool flag);
    virtual void setCanEnter(bool flag);

    virtual void setFocused(bool flag);

    void setParentWidgetManager(WidgetManager* widgetManager);

    WidgetManager* getParentWidgetManager() const;

    const bool canAcceptFocus() const;
    const bool canAcceptFocusKeyboard() const;
    const bool canEnter() const;
    const bool canLoseFocus() const;
    const bool hasFocus() const;

    const bool isEnabled() const;
    const bool isActive() const;
    const bool isPressed() const;
    const bool isEntered() const;

    //void setTooltip(Tooltip* tooltip, float offsetX = 0.f, float offsetY = 0.f);
    //void setTooltipFollow(bool flag);

public:
    virtual void handleMousePressed(int32_t button, float x, float y) = 0;
    virtual void handleMouseReleased(int32_t button, float x, float y) = 0;
    virtual void handleMouseMoved(float x, float y) = 0;
    virtual void handleKeyboardPressed(int32_t key) = 0;
    virtual void handleKeyboardReleased(int32_t key) = 0;

protected:
    bool mFocused;
    bool mAcceptsFocus;
    bool mAcceptsFocusKeyboard;
    bool mAcceptsEntered;
    bool mEnabled;
    bool mActive;
    bool mPresssed;
    bool mEntered;
    bool mCanLoseFocus;
    std::array<float, 2> mSize;
    std::array<float, 2> mSizeMin;
    std::array<float, 2> mSizeMax;
    WidgetManager* mParentWidgetManager;
};

#endif // _WIDGET_H
}}
