#include "Widget.h"
#include "../events/EventDispatcher.h"
#include "../events/KeyboardEventData.h"
#include "../events/MouseEventData.h"
#include "../data/TextureAtlas.h"

namespace liquid { namespace ui {
#ifndef _WIDGETMANAGER_H
#define _WIDGETMANAGER_H

class WidgetManager
{
public:
    WidgetManager(const data::TextureAtlas& textureAtlas);
    ~WidgetManager();

    virtual void update();

    virtual void insertWidget(Widget* widget);
    virtual void removeWidget(Widget* widget);

    void updateEntered(const events::MouseEventData& eventData);
    void updateFocused(const events::MouseEventData& eventData);

    void buttonPressedCheck(Widget* widget, int32_t mouseButton);
    Widget* findNextParent(Widget* widget, float x, float y);
    Widget* findNextInside(Widget* widget, float x, float y);

    data::TextureAtlas& getTextureAtlas();

protected:
    bool handleKeyboardEvent(const events::KeyboardEventData& eventData);
    bool handleMouseEvent(const events::MouseEventData& eventData);

protected:
    std::vector<Widget*> mWidgets;
    Widget* mEnteredWidget;
    Widget* mFocusedWidget;
    int32_t mHandleMouse;
    int32_t mHandleKeyboard;
    data::TextureAtlas mTextureAtlas;
};

#endif // _WIDGETMANAGER_H
}}
