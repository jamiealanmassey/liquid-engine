#include "Widget.h"
#include "Button.h"

namespace liquid { namespace ui {
#ifndef _TOGGLE_H
#define _TOGGLE_H

/**
 * \class Toggle
 *
 * \ingroup UI
 * \brief Similar to the Button class except toggles, extends the Button class
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 28/04/2017
 *
 */

class Toggle : public Button
{
public:
    /** \brief Toggles Constructor
      * \param x Position of the Widget on the X-Axis
      * \param y Position of the Widget on the Y-Axis
      * \param textureNames Texture names to extrapolate from the stored data::TextureAtlas
      */
    Toggle(float x, float y, std::array<std::string, 3> textureNames);

    /// Toggle Destructor
    ~Toggle();

    /** \brief Uses the given flag to update mToggled and mVerticesPtr
      * \param flag Boolean value to assign
      */
    void toggle(bool flag);

    /// \return True if the Widget is toggled on, otherwise false
    const bool isToggled() const;

    /// \brief Override Widget::handleMousePressed
    void handleMousePressed(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseReleased
    void handleMouseReleased(int32_t button, float x, float y) override;

protected:
    bool mToggled; ///< Flag for wether the Widget is toggled on or off
};

#endif // _TOGGLE_H
}}
