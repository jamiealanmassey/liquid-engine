#include "Widget.h"
#include "../events/EventDispatcher.h"
#include "../events/KeyboardEventData.h"
#include "../events/MouseEventData.h"
#include "../events/TextEventData.h"
#include "../data/TextureAtlas.h"

namespace liquid { namespace ui {
#ifndef _WIDGETMANAGER_H
#define _WIDGETMANAGER_H

/**
 * \class WidgetManager
 *
 * \ingroup UI
 * \brief Collects and manages Widget objects
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 28/04/2017
 *
 */

class WidgetManager
{
public:
    /** \brief WidgetManager Constructor
      * \param textureAtlas Texture atlas for interface elements
      */
    WidgetManager(const data::TextureAtlas& textureAtlas);

    /// WidgetManager Destructor
    ~WidgetManager();

    /// \brief Update called every frame
    virtual void update();

    /** \brief Inserts a new Widget object into the Manager
      * \param widget Widget to insert
      */
    virtual void insertWidget(Widget* widget);

    /** \brief Removes a Widget object from the Manager
      * \param widget Widget to remove
      */
    virtual void removeWidget(Widget* widget);

    /** \brief Searches through the collection of Widget objects to find if they've been entered
      * \param eventData Sampled event data from the events::EventDisptcher
      */
    void updateEntered(const events::MouseEventData& eventData);

    /** \brief Searches through the collection of Widget objects to find if they've been focused
      * \param eventData Sampled event data from the events::EventDisptcher
      */
    void updateFocused(const events::MouseEventData& eventData);

    /** \brief Checks if the given Widget is pressed, if true then turn it off
      * \param widget Pointer to the Widget to test
      */
    void buttonPressedCheck(Widget* widget);

    /** \brief Recursive function to find the top-most parent Widget
      * \param widget Next Widget object to test
      * \param x X-position of mouse
      * \param y Y-position of mouse
      * \return Found Widget object, given Widget if none found
      */
    Widget* findNextParent(Widget* widget, float x, float y);

    /** \brief Recursive function to find the lowest Widget the mouse is inside of
      * \param widget Next Widget object to test
      * \param x X-position of mouse
      * \param y Y-position of mouse
      * \return Found Widget object, given Widget if none found
      */
    Widget* findNextInside(Widget* widget, float x, float y);

    /// \return Gets the collection of Widget objects managed by this manager
    std::vector<Widget*> getWidgets();

    /// \return The texture atlas defining the textures for the interface
    data::TextureAtlas& getTextureAtlas();

    /// \return Last Widget object that was entered
    Widget* getEnteredWidget();

    /// \return Last widget object that was focused
    Widget* getFocusedWidget();

protected:
    /** \brief Callback passed to EventDispatcher<KeyboardEventData>
      * \param eventData Collected event data from events::EventManager
      * \return True if successful
      *
      * Called everytime an event is triggered via events::EventDispatcher,
      * the function then calls updateEntered(eventData) and updateFocused(eventData)
      * and calls the respective event on the currently entered (mEnteredWidget) object
      */
    bool handleKeyboardEvent(const events::KeyboardEventData& eventData);

    /** \brief Callback passed to EventDispatcher<MouseEventData>
      * \param eventData Collected event data from events::EventManager
      * \return True if successful
      */
    bool handleMouseEvent(const events::MouseEventData& eventData);

    /** \brief Callback passed to EventDispatcher<TextEventData>
      * \param eventData Collected event data from events::EventManager
      * \return True if successful
      */
    bool handleTextEvent(const events::TextEventData& eventData);

protected:
    std::vector<Widget*> mWidgets;        ///< Collection of Widget objects for this manager
    Widget*              mEnteredWidget;  ///< Last Widget object that was entered
    Widget*              mFocusedWidget;  ///< Last Widget object that was focused
    int32_t              mHandleMouse;    ///< ID of the Mouse Event
    int32_t              mHandleKeyboard; ///< ID of the keyboard event
    int32_t              mHandleText;     ///< ID of the text event
    data::TextureAtlas   mTextureAtlas;   ///< Texture atlas for the interface textures
};

#endif // _WIDGETMANAGER_H
}}
