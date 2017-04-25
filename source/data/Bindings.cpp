#include "Bindings.h"

namespace liquid {
namespace data {

    Bindings::Bindings() :
        ParserConfig()
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

    void Bindings::parseFile(std::string file)
    {
        if (mFuncCallbackConvert == nullptr)
            return;

        if (std::experimental::filesystem::exists(file) == false)
        {
            std::ofstream fileStream(file);
            fileStream << mDefaultBindings;
            fileStream.close();
        }

        ParserConfig::parseFile(file);
        mBindingsData.clear();

        for (auto it : mRootParserNode->getData())
            mBindingsData[it.first] = mFuncCallbackConvert(it.second);
    }

    void Bindings::parseString(std::string str)
    {
        if (mFuncCallbackConvert == nullptr)
            return;

        ParserConfig::parseString(str);
        mBindingsData.clear();

        for (auto it : mRootParserNode->getData())
            mBindingsData[it.first] = mFuncCallbackConvert(it.second);
    }

    uint32_t Bindings::getBindingValue(std::string name)
    {
        std::map<std::string, uint32_t>::iterator it = mBindingsData.find(name);
        if (it == mBindingsData.end())
            return 0;

        return it->second;
    }

}}
