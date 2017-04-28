#include "Widget.h"

namespace liquid {
namespace ui {

    Widget::Widget(float x, float y) :
        common::Entity()
    {
        setPosition(x, y);

        mFocused = false;
        mAcceptsFocus = true;
        mAcceptsFocusKeyboard = true;
        mAcceptsEntered = true;
        mEnabled = true;
        mActive = true;
        mPresssed = false;
        mEntered = false;
        mCanLoseFocus = true;
        mParentWidgetManager = nullptr;
    }

    Widget::~Widget()
    {}

    void Widget::initialise()
    {}

    void Widget::update()
    {}

    void Widget::setPosition(float x, float y)
    {
        Entity::setPosition(x, y);
    }

    void Widget::addPosition(float x, float y)
    {
        Entity::setPosition(x, y);
    }

    bool Widget::acceptsFocus()
    {
        return mAcceptsFocus;
    }

    bool Widget::acceptsFocusKeyboard()
    {
        return mAcceptsFocusKeyboard;
    }

    void Widget::setPressed(bool flag)
    {
        mPresssed = flag;
    }

    void Widget::setEntered(bool flag)
    {
        mEntered = flag;
    }

    void Widget::setSize(float w, float h)
    {
        if (mSizeMax[0] != 0.f && mSizeMax[1] != 0.f)
        {
            mSize[0] = std::max(std::min(w, mSizeMax[0]), mSizeMin[0]);
            mSize[1] = std::max(std::min(w, mSizeMax[1]), mSizeMin[1]);
        }
        else
        {
            mSize[0] = w;
            mSize[1] = h;
        }

        Entity::setSize(mSize[0], mSize[1]);
    }

    void Widget::setMinSize(float w, float h)
    {
        mSizeMin[0] = w;
        mSizeMin[1] = h;
        setSize(mSize[0], mSize[1]);
    }

    void Widget::setMaxSize(float w, float h)
    {
        mSizeMax[0] = w;
        mSizeMax[1] = h;
        setSize(mSize[0], mSize[1]);
    }

    void Widget::show()
    {
        mActive = true;
    }

    void Widget::hide()
    {
        mActive = false;
    }

    void Widget::enable()
    {
        mEnabled = true;
    }

    void Widget::disable()
    {
        mEnabled = false;
    }

    void Widget::setCanFocus(bool flag)
    {
        mAcceptsFocus = flag;
    }

    void Widget::setCanFocusKeyboard(bool flag)
    {
        mAcceptsFocusKeyboard = flag;
    }

    void Widget::setCanEnter(bool flag)
    {
        mAcceptsEntered = flag;
    }

    void Widget::setFocused(bool flag)
    {
        mFocused = flag;
    }

    void Widget::setParentWidgetManager(WidgetManager* widgetManager)
    {
        mParentWidgetManager = widgetManager;
    }

    WidgetManager* Widget::getParentWidgetManager() const
    {
        return mParentWidgetManager;
    }

    const bool Widget::canAcceptFocus() const
    {
        return mAcceptsFocus;
    }

    const bool Widget::canAcceptFocusKeyboard() const
    {
        return mAcceptsFocusKeyboard;
    }

    const bool Widget::canEnter() const
    {
        return mAcceptsEntered;
    }

    const bool Widget::canLoseFocus() const
    {
        return mCanLoseFocus;
    }

    const bool Widget::hasFocus() const
    {
        return mFocused;
    }

    const bool Widget::isEnabled() const
    {
        return mEnabled;
    }

    const bool Widget::isActive() const
    {
        return mActive;
    }

    const bool Widget::isPressed() const
    {
        return mPresssed;
    }

    const bool Widget::isEntered() const
    {
        return mEntered;
    }

}}
