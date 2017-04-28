#include "../common/Entity.h"

namespace liquid { namespace ui {
#ifndef _WIDGET_H
#define _WIDGET_H

/**
 * \class Widget
 *
 * \ingroup UI
 * \brief Defines how a Widget is represented and exposes some core functionality for any class that inherits it
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 28/04/2017
 *
 */

class WidgetManager;
class Widget : public common::Entity
{
public:
    /** \brief Widget Constructor
      * \param x Position in space on the X-Axis
      * \param y Position in space on the Y-Axis
      */
    Widget(float x, float y);

    /// Widget Destructor
    ~Widget();

    /// \brief Called when added to an WidgetManager
    virtual void initialise() override;

    /// \brief Called every frame
    virtual void update() override;

    /** \brief Updates the position of the Widget
      * \param x Position in space on the X-Axis
      * \param y Position in space on the Y-Axis
      *
      * When called the function will call down to Entity::setPosition
      */
    virtual void setPosition(float x, float y) override;

    /** \brief Updates the position of the Widget by adding the values
      * \param x Position in space on the X-Axis
      * \param y Position in space on the Y-Axis
      *
      * When called the function will call down to Entity::addPosition
      */
    virtual void addPosition(float x, float y) override;

    /// \return True if the Widget can accept focus, otherwise false
    virtual bool acceptsFocus();
    
    /// \return True if the Widget can accept focus from the keyboard, otherwise false
    virtual bool acceptsFocusKeyboard();

    /** \brief Assign boolean for if the Widget has been pressed
      * \param flag Denotes if Widget has been pressed
      */
    virtual void setPressed(bool flag);

    /** \brief Assign boolean for if the Widget has been entered
      * \param flag Denotes if Widget has been entered
      */
    virtual void setEntered(bool flag);

    /** \brief Override Entity::setSize to assign the new size
      * \param w Width of the Widget
      * \param h Height of the Widget
      *
      * Sets mSize of the Widget using the Entity::setSize function while using
      * the mSizeMin and mSizeMax variables to constrain it between those values
      */
    virtual void setSize(float w, float h);

    /** \brief Assign the minimum size of the Widget
      * \param w Minimum width of the Widget
      * \param h Minimum height of the Widget
      */
    virtual void setMinSize(float w, float h);

    /** \brief Assign the maximum size of the Widget
      * \param w Maximum width of the Widget
      * \param h Maximum height of the Widget
      */
    virtual void setMaxSize(float w, float h);

    /// \brief Shows the Widget
    virtual void show();

    /// \brief Hides the Widget
    virtual void hide();

    /// \brief Enable to Widget for use
    virtual void enable();

    /// \brief Disable the Widget from use
    virtual void disable();

    /** \brief Assigns boolean value to wether the Wiget can take focus
      * \param flag Boolean flag to assign
      */
    virtual void setCanFocus(bool flag);

    /** \brief Assigns boolean value to wether the Wiget can take focus from keyboard
      * \param flag Boolean flag to assign
      */
    virtual void setCanFocusKeyboard(bool flag);

    /** \brief Assigns boolean value to wether the Wiget can be entered
      * \param flag Boolean flag to assign
      */
    virtual void setCanEnter(bool flag);

    /** \brief Sets wether the Widget is focused or not
      * \param flag Boolean flag to assign
      */
    virtual void setFocused(bool flag);

    /** \brief Set the pointer for the parent WidgetManager
      * \param widgetManager Pointer to the parent WidgetManager of this Widget
      */
    void setParentWidgetManager(WidgetManager* widgetManager);

    /// \return Gets a pointer to the parent WidgetManager
    WidgetManager* getParentWidgetManager() const;

    /// \return True if the Widget can accept focus
    const bool canAcceptFocus() const;

    /// \return True if the Widget can accept focus from the keyboard
    const bool canAcceptFocusKeyboard() const;

    /// \return True if the Widget can be entered
    const bool canEnter() const;

    /// \return True if the Widget can lose focus
    const bool canLoseFocus() const;

    /// \return True if the Widget is currently being focused
    const bool hasFocus() const;

    /// \return True if the Widget is enabled
    const bool isEnabled() const;

    /// \return True if the Widget is currently active
    const bool isActive() const;

    /// \return True if the Widget is currently being pressed
    const bool isPressed() const;

    /// \return True if the Widget is currently being entered by the mouse
    const bool isEntered() const;

public:
    /// \brief Pure virtual for when the mouse has been pressed
    virtual void handleMousePressed(int32_t button, float x, float y) = 0;

    /// \brief Pure virtual for when the mouse has been released
    virtual void handleMouseReleased(int32_t button, float x, float y) = 0;

    /// \brief Pure virtual for when the mouse has been moved
    virtual void handleMouseMoved(float x, float y) = 0;

    /// \brief Pure virtual for when the keyboard has been pressed
    virtual void handleKeyboardPressed(int32_t key) = 0;

    /// \brief Pure virtual for when the keyboard has been pressed
    virtual void handleKeyboardReleased(int32_t key) = 0;

protected:
    bool                 mFocused;              ///< Denotes if the Widget is being focused
    bool                 mAcceptsFocus;         ///< Denotes if the Widget can accept focus
    bool                 mAcceptsFocusKeyboard; ///< Denotes if the Widget can accept focus from the keyboard
    bool                 mAcceptsEntered;       ///< Denotes if the Widget can be entered
    bool                 mEnabled;              ///< Denotes if the Widget is enabled currently
    bool                 mActive;               ///< Denotes if the Widget is currently active
    bool                 mPresssed;             ///< Flag for if the Widget is currently being pressed
    bool                 mEntered;              ///< Flag for if the Widget is currently entered by the mouse
    bool                 mCanLoseFocus;         ///< Denotes if the Widget can lose its focus
    std::array<float, 2> mSize;                 ///< Size of the Widget
    std::array<float, 2> mSizeMin;              ///< Minimum size of the Widget in pixels
    std::array<float, 2> mSizeMax;              ///< Maximum size of the Widget in pixels
    WidgetManager*       mParentWidgetManager;  ///< Pointer to the parent WidgetManager
};

#endif // _WIDGET_H
}}
