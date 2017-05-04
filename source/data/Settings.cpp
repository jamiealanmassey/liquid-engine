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
            "fullscreen true\n"
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

    void Settings::parseFile(std::string file)
    {
        if (std::experimental::filesystem::exists(file) == false)
        {
            std::ofstream fileStream(file);
            fileStream << mDefaultSettings;
            fileStream.close();
        }

        ParserConfig::parseFile(file);
        assignSettings();
    }

    void Settings::parseString(std::string str)
    {
        ParserConfig::parseString(str);
        assignSettings();
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
        mFrameLimit = mRootParserNode->getValueAsInteger32("frame_limit");
        mScreenWidth = mRootParserNode->getValueAsInteger32("screen_width");
        mScreenHeight = mRootParserNode->getValueAsInteger32("screen_height");
        mFullscreen = mRootParserNode->getValueAsBoolean("fullscreen");
        mParticlesEnabled = mRootParserNode->getValueAsBoolean("particles_enabled");
        mEnableVSync = mRootParserNode->getValueAsBoolean("enable_vsync");
        mGUIScale = mRootParserNode->getValueAsFloat("gui_scale");
        mVolumeMaster = mRootParserNode->getValueAsFloat("master");
        mVolumeMusic = mRootParserNode->getValueAsFloat("music");
        mVolumeAmbiance = mRootParserNode->getValueAsFloat("ambiance");
        mVolumeDialogue = mRootParserNode->getValueAsFloat("dialogue");
    }

}}
