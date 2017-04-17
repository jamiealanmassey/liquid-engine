#include "Bindings.h"

namespace liquid {
namespace data {

    Bindings::Bindings() :
        ConfigurationParser()
    {
        mFuncCallbackConvert = std::bind(&Bindings::defaultConvertFunc, this, std::placeholders::_1);
        mDefaultBindings =
            "-- KEYBOARD BINDINGS\n"
            "keyboard_move_up W\n"
            "keyboard_move_left A\n"
            "keyboard_move_down S\n"
            "keyboard_move_right D\n"
            "keyboard_interact F\n"
            "keyboard_open_menu Escape\n"
            "\n"
            "-- GAMEPAD BINDINGS\n"
            "gamepad_interact X\n"
            "gamepad_open_menu Start\n";
    }

    Bindings::~Bindings()
    {}

    bool Bindings::parseFile(std::string file)
    {
        if (mFuncCallbackConvert == nullptr)
            return false;

        if (std::experimental::filesystem::exists(file) == false)
        {
            std::ofstream fileStream(file);
            fileStream << mDefaultBindings;
            fileStream.close();
        }

        if (ConfigurationParser::parseFile(file) == false)
            return false;

        mBindingsData.clear();
        for (auto it : mData)
            mBindingsData[it.first] = mFuncCallbackConvert(it.second);

        return true;
    }

    bool Bindings::parseString(std::string str)
    {
        if (mFuncCallbackConvert == nullptr)
            return false;

        if (ConfigurationParser::parseString(str) == false)
            return false;

        mBindingsData.clear();
        for (auto it : mData)
            mBindingsData[it.first] = mFuncCallbackConvert(it.second);

        return true;
    }

    uint32_t Bindings::getBindingValue(std::string name)
    {
        std::map<std::string, uint32_t>::iterator it = mBindingsData.find(name);
        if (it == mBindingsData.end())
            return 0;

        return it->second;
    }

}}
