#ifdef SFML
#include "../../common/Camera.h"
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLCAMERA_H
#define _SFMLCAMERA_H

/**
 * \class SFMLCamera
 *
 * \ingroup Impl
 * \brief SFML-specific implementation of the ICamera class, uses sf::View to manipulate the scene
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 27/04/2017
 *
 */

class SFMLCamera : public common::Camera
{
public:
    /** \brief SFMLCamera Constructor
      * \param centreX Centre of the Camera on the X-Axis
      * \param centreY Centre of the Camera on the Y-Axis
      */
    SFMLCamera(float centreX, float centreY);

    /** \brief SFMLCamera Constructor
      * \param centreX Centre of the Camera on the X-Axis
      * \param centreY Centre of the Camera on the Y-Axis
      * \param width Width of the Camera's view in pixels
      * \param height Height of the Camera's view in pixels
      */
    SFMLCamera(float centreX, float centreY, float width, float height);

    /// SFMLCamera Destructor
    ~SFMLCamera();

    /// \brief Update override, updates tweeners and screenshake etc.
    virtual void update() override;

    /** \brief Override to set the centre of the Camera
      * \param postition Array of the centre in 2D space
      */
    virtual void setCentre(std::array<float, 2> position) override;

    /** \brief Override to set the dimensions of the Camera
      * \param dimensions Array of the dimensions in 2D space
      */
    virtual void setDimensions(std::array<float, 2> dimensions) override;

    /** \brief Override to set the rotation of the Camera
      * \param rotation Rotation of the Camera (0 - 360)
      */
    virtual void setRotation(float rotation) override;

    /** \brief Override to set the zoom factor of the Camera
      * \param zoomFactor Zoom factor of the Camera
      */
    virtual void setZoomFactor(float zoomFactor) override;

    /** \brief Override to ease the Camera position, resets tweeners
      * \param targetPosition Array representing the position in 2D space
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easePosition(std::array<float, 2> targetPosition, float duration) override;

    /** \brief Override to ease the Camera rotation, resets tweeners
      * \param targetRotation Rotation to ease to
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easeRotation(float targetRotation, float duration) override;

    /** \brief Override to ease the Camera zoom factor, resets tweeners
      * \param targetZoomFactor Zoom factor to ease to
      * \param duration Time to get to the target in milliseconds
      */
    virtual void easeZoomFactor(float targetZoomFactor, float duration) override;

    /** \brief Override for shaking the Camera with the given characteristics for determined time
      * \param duration Duration of the screenshake in milliseconds
      * \param radius Radius in which to shake the Camera
      * \param axis Axis to shake the Camera around (X, Y or XY)
      */
    virtual void shake(float duration, float radius, eShakeAxis axis) override;

    /// \return Gets the sf::View of this Camera
    sf::View getSFMLView() const;

protected:
    /// \brief Small helper function to update the active Screenshake
    void updateScreenShake();

protected:
    bool                 mShaking;          ///< Denotes if the Screen is currently shaking
    float                mShakeDuration;    ///< Duration of the current screenshake
    float                mShakeAccumulator; ///< Accumulated time of the screenshake
    float                mShakeRadius;      ///< Radius of the screenshake when calculated
    float                mShakeRadiusBegin; ///< First sampled radius of the screenshake
    float                mShakeAngle;       ///< Current angle of the screenshake
    eShakeAxis           mShakeAxis;        ///< Axis to perfom the screenshake on
    sf::View             mSFMLView;         ///< Stored version of the Camera as an sf::View
    std::array<float, 2> mShakeOffset;      ///< Calculated offset for the current frame
};

#endif // _SFMLCAMERA_H
}}

#endif // SFML
