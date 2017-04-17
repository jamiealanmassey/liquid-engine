#include "Settings.h"

namespace liquid {
namespace data {

    Settings::Settings()
    {
        mDefaultSettings =
            "-- GAME SETTINGS\n"
            "frame_limit 60\n"
            "screen_width 1920\n"
            "screen_height 1080\n"
            "fullscreen false\n"
            "particles_enabled true\n"
            "enable_vsync false\n"
            "gui_scale 1.0\n"
            "\n"
            "-- VOLUME SETTINGS\n"
            "master 100.0\n"
            "music 100.0\n"
            "ambiance 100.0\n"
            "dialogue 100.0\n";
    }

    Settings::~Settings()
    {}

    bool Settings::parseFile(std::string file)
    {
        if (std::experimental::filesystem::exists(file) == false)
        {
            std::ofstream fileStream(file);
            fileStream << mDefaultSettings;
            fileStream.close();
        }

        if (ConfigurationParser::parseFile(file) == false)
            return false;

        assignSettings();
        return true;
    }

    bool Settings::parseString(std::string str)
    {
        if (ConfigurationParser::parseString(str) == false)
            return false;

        assignSettings();
        return true;
    }

    int32_t Settings::getFrameLimit() const
    {
        return mFrameLimit;
    }

    int32_t Settings::getScreenWidth() const
    {
        return mScreenWidth;
    }

    int32_t Settings::getScreenHeight() const
    {
        return mScreenHeight;
    }

    bool Settings::getFullscreen() const
    {
        return mFullscreen;
    }

    bool Settings::getParticlesEnabled() const
    {
        return mParticlesEnabled;
    }

    bool Settings::getEnableVSync() const
    {
        return mEnableVSync;
    }

    float Settings::getGUIScale() const
    {
        return mGUIScale;
    }

    float Settings::getVolumeMaster() const
    {
        return mVolumeMaster;
    }

    float Settings::getVolumeMusic() const
    {
        return mVolumeMusic;
    }

    float Settings::getVolumeAmbiance() const
    {
        return mVolumeAmbiance;
    }

    float Settings::getVolumeDialogue() const
    {
        return mVolumeDialogue;
    }

    void Settings::assignSettings()
    {
        mFrameLimit = getValueAsInteger32("frame_limit");
        mScreenWidth = getValueAsInteger32("screen_width");
        mScreenHeight = getValueAsInteger32("screen_height");
        mFullscreen = getValueAsBoolean("fullscreen");
        mParticlesEnabled = getValueAsBoolean("particles_enabled");
        mEnableVSync = getValueAsBoolean("enable_vsync");
        mGUIScale = getValueAsFloat("gui_scale");
        mVolumeMaster = getValueAsFloat("master");
        mVolumeMusic = getValueAsFloat("music");
        mVolumeAmbiance = getValueAsFloat("ambiance");
        mVolumeDialogue = getValueAsFloat("dialogue");
    }

}}
