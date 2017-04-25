#include <experimental/filesystem>
#include "../parser/ParserConfig.h"

namespace liquid { namespace data {
#ifndef _SETTINGS_H
#define _SETTINGS_H

/**
 * \class Settings
 *
 * \ingroup Data
 * \brief Defines a structure for general-purpose game-settings
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 05/04/2017
 *
 */

class Settings : public parser::ParserConfig
{
public:
    /// Settings Constructor
    Settings();
    
    /// Settings Destructor
    ~Settings();

    /** \brief Parses a file and assign Settings to values
      * \param file File to be parsed
      * \return True if parsed correctly, False otherwise
      *
      * Loads appropriate data using inherited ConfigurationParser into the mData
      * variable, then uses those loaded values to assign the hard values to each
      * stored variable in this class. The class may be extended to hardcode more
      * settings, otherwise you can retrieve them directly by using the functions
      * provided by ConfigurationParser to access them.
      */
    virtual void parseFile(std::string file) override;

    /** \brief Parses a file and assign Settings to values
      * \param file File to be parsed
      * \return True if parsed correctly, False otherwise
      *
      * Loads appropriate data using inherited ConfigurationParser into the mData
      * variable, then uses those loaded values to assign the hard values to each
      * stored variable in this class. The class may be extended to hardcode more
      * settings, otherwise you can retrieve them directly by using the functions
      * provided by ConfigurationParser to access them.
      *
      * Note: The std::string needs to be formatted correctly with whitespace
      * between bindings names + values and each line ended with \n
      */
    virtual void parseString(std::string str) override;

    /// \return Frame Limit capped to represented Integer
    int32_t getFrameLimit() const;

    /// \return The width of the screen in pixels (integer)
    int32_t getScreenWidth() const;

    /// \return The height of the screen in pixels (integer)
    int32_t getScreenHeight() const;

    /// \return Flag representing if the screen should be windowed or not
    bool getFullscreen() const;

    /// \return Flag to denote if particles should be enabled and simulated
    bool getParticlesEnabled() const;

    /// \return Flag to denote if Vertical Sync should be enabled
    bool getEnableVSync() const;

    /// \return Scale of the GUI where 1.0 is the initial size
    float getGUIScale() const;

    /// \return Master volume, 0 - 100.0f
    float getVolumeMaster() const;

    /// \return Music volume, 0 - 100.0f
    float getVolumeMusic() const;

    /// \return Ambiance volume, 0 - 100.0f
    float getVolumeAmbiance() const;

    /// \return Dialogue volume, 0 - 100.0f
    float getVolumeDialogue() const;

private:
    void assignSettings();

protected:
    int32_t mFrameLimit;       ///< Framerate limit
    int32_t mScreenWidth;      ///< Width of screen in pixels
    int32_t mScreenHeight;     ///< Height of screen in pixels
    bool    mFullscreen;       ///< Flag denoting if fullscreen or not
    bool    mParticlesEnabled; ///< Flag denoting if particles should be enabled
    bool    mEnableVSync;      ///< Flag denoting if vertical sync be enabled
    float   mGUIScale;         ///< Scale of the GUI relative to 1.0f
    float   mVolumeMaster;     ///< Master volume where 0 - 100.0f
    float   mVolumeMusic;      ///< Music volume where 0 - 100.0f
    float   mVolumeAmbiance;   ///< Ambiance volume where 0 - 100.0f
    float   mVolumeDialogue;   ///< Dialogue volume where 0 - 100.0f

public:
    std::string mDefaultSettings; ///< Default settings for if file doesn't exist
};

#endif // _SETTINGS_H
}}
