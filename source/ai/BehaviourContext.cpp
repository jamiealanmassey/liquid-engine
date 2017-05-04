#include "BehaviourContext.h"

namespace liquid {
namespace ai {

    BehaviourContext::BehaviourContext()
    {
    }

    BehaviourContext::~BehaviourContext()
    {
    }

    bool BehaviourContext::dataExists(std::string name)
    {
        return (mDataTable.find(name) != mDataTable.end());
    }

    bool BehaviourContext::stackExists(std::string name)
    {
        return (mStackTable.find(name) != mStackTable.end());
    }

    void BehaviourContext::createStack(std::string name)
    {
        if (stackExists(name) == true)
            return;

        mStackTable[name] = new utilities::Stack;
    }

    void BehaviourContext::deleteStack(std::string name)
    {
        if (stackExists(name) == true)
        {
            utilities::Stack* stack = mStackTable[name];
            mStackTable.erase(name);
            delete stack;
        }
    }

    void BehaviourContext::pushStack(std::string name, void* data)
    {
        if (stackExists(name) == true)
            mStackTable[name]->push(data);
    }

    void* BehaviourContext::popStack(std::string name)
    {
        if (stackExists(name) == true)
            return mStackTable[name]->pop();

        return nullptr;
    }

    void* BehaviourContext::peekStack(std::string name)
    {
        if (stackExists(name) == true)
            return mStackTable[name]->peek();

        return nullptr;
    }

    void BehaviourContext::insertData(std::string name, void* data)
    {
        if (dataExists(name) == false)
            mDataTable[name] = data;
    }

    void BehaviourContext::removeData(std::string name)
    {
        if (dataExists(name) == true)
        {
            void* data = mDataTable[name];
            mDataTable.erase(name);
            delete data;
        }
    }

    void BehaviourContext::setData(std::string name, void* data)
    {
        if (dataExists(name) == true)
        {
            removeData(name);
            mDataTable[name] = data;
        }
    }

    void* BehaviourContext::getData(std::string name)
    {
        if (dataExists(name) == true)
            return mDataTable[name];

        return nullptr;
    }

    int32_t BehaviourContext::convertInt32(void* data)
    {
        if (data != nullptr && sizeof(data) == sizeof(int32_t))
            return (int32_t)data;

        return 0;
    }

    double BehaviourContext::convertDouble(void* data)
    {
        if (data != nullptr && sizeof(data) == sizeof(double))
            return *(double*)data;

        return 0.0;
    }

    float BehaviourContext::convertFloat(void* data)
    {
        if (data != nullptr && sizeof(data) == sizeof(float))
            return *(float*)data;

        return 0.f;
    }

    bool BehaviourContext::convertBoolean(void* data)
    {
        if (data != nullptr && sizeof(data) == sizeof(bool))
            return (bool)data;

        return false;
    }

    std::string BehaviourContext::convertString(void* data)
    {
        if (data != nullptr)
            return *(static_cast<std::string*>(data));

        return "";
    }

}}
