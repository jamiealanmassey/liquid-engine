#include "Widget.h"

namespace liquid { namespace ui {
#ifndef _BUTTON_H
#define _BUTTON_H

/**
 * \class Button
 *
 * \ingroup UI
 * \brief Simple Button class that extends the Widget class
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 28/04/2017
 *
 */

class Button : public Widget
{
public:
    /** \brief Button Constructor
      * \param x Position of the Widget on the X-Axis
      * \param y Position of the Widget on the Y-Axis
      * \param textureNames Texture names to extrapolate from the stored data::TextureAtlas
      */
    Button(float x, float y, std::array<std::string, 3> textureNames);

    /// Button Destructor
    ~Button();

    /// \brief Override initialise 
    virtual void initialise() override;

    /** \brief Calls Widget::setPosition and centres attached text
      * \param x Position of the Widget on the X-Axis
      * \param y Position of the Widget on the Y-Axis
      */
    virtual void setPosition(float x, float y) override;

    /** \brief Calls Widget::addPosition and centres attached text
      * \param x Position of the Widget to add on the X-Axis
      * \param y Position of the Widget to add on the Y-Axis
      */
    virtual void addPosition(float x, float y) override;

    /** \brief Updates the texture using the stored mTextureNames variable
      * \param index Index of the mTextureNames to use
      *
      * Updates the texture stored from mTextureNames using the data::TextureAtlas
      * that is stored in the parent WidgetManager
      */
    void updateTexture(uint32_t index);

    /// \brief Override Widget::handleMousePressed
    void handleMousePressed(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseReleased
    void handleMouseReleased(int32_t button, float x, float y) override;

    /// \brief Override Widget::handleMouseMoveds
    void handleMouseMoved(float x, float y) override;

    /// \brief Override Widget::handleKeyboardPressed
    void handleKeyboardPressed(int32_t key) override;

    /// \brief Override Widget::handleKeyboardReleased
    void handleKeyboardReleased(int32_t key) override;

protected:
    std::array<std::string, 3> mTextureNames; ///< Array of textures to use for event response
};

#endif // _BUTTON_H
}}
