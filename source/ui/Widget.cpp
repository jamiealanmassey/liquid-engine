#include "Widget.h"
#include "WidgetManager.h"
#include "../common/LuaManager.h"

namespace liquid {
namespace ui {

    Widget::Widget(float x, float y) :
        common::Entity(),
        mLuaFuncMousePressed(common::LuaManager::instance().getLuaState()),
        mLuaFuncMouseReleased(common::LuaManager::instance().getLuaState()),
        mLuaFuncMouseMoved(common::LuaManager::instance().getLuaState()),
        mLuaFuncKeyboardPressed(common::LuaManager::instance().getLuaState()),
        mLuaFuncKeyboardReleased(common::LuaManager::instance().getLuaState())
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

    void Widget::setLuaScript(std::string luaScript)
    {
        mLuaScript = luaScript;
        lua_State* lua = common::LuaManager::instance().getLuaState();
        common::LuaManager::instance().executeScript(mLuaScript);

        mLuaFuncCreate = luabridge::getGlobal(lua, "create");
        mLuaFuncUpdate = luabridge::getGlobal(lua, "update");
        mLuaFuncKill = luabridge::getGlobal(lua, "kill");
        mLuaFuncMousePressed = luabridge::getGlobal(lua, "mousePressed");
        mLuaFuncMouseReleased = luabridge::getGlobal(lua, "mouseReleased");
        mLuaFuncMouseMoved = luabridge::getGlobal(lua, "mouseMoved");
        mLuaFuncKeyboardPressed = luabridge::getGlobal(lua, "keyboardPressed");
        mLuaFuncKeyboardReleased = luabridge::getGlobal(lua, "keyboardReleased");
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

    void Widget::setTexture(std::string textureName)
    {
        data::TextureAtlas& atlas = mParentWidgetManager->getTextureAtlas();
        data::TextureAtlas::TextureRegion region;
        region = atlas.getTextureRegion(textureName);

        float width = region[1][0] - region[0][0];
        float height = region[2][1] - region[1][1];

        mVerticesPtr[0]->setTexCoord(region[0]);
        mVerticesPtr[1]->setTexCoord(region[1]);
        mVerticesPtr[2]->setTexCoord(region[2]);
        mVerticesPtr[3]->setTexCoord(region[3]);
        setSize(width, height);
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

    void Widget::handleMousePressed(int32_t button, float x, float y)
    {
        if (mLuaFuncMousePressed.isNil() == false)
            mLuaFuncMousePressed(button, x, y);
    }

    void Widget::handleMouseReleased(int32_t button, float x, float y)
    {
        if (mLuaFuncMouseReleased.isNil() == false)
            mLuaFuncMouseReleased(button, x, y);
    }

    void Widget::handleMouseMoved(float x, float y)
    {
        if (mLuaFuncMouseMoved.isNil() == false)
            mLuaFuncMouseMoved(x, y);
    }

    void Widget::handleKeyboardPressed(int32_t key)
    {
        if (mLuaFuncKeyboardPressed.isNil() == false)
            mLuaFuncKeyboardPressed(key);
    }

    void Widget::handleKeyboardReleased(int32_t key)
    {
        if (mLuaFuncKeyboardReleased.isNil() == false)
            mLuaFuncKeyboardReleased(key);
    }

}}
