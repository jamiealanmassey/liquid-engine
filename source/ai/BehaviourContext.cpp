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
            mDataTable.erase(name);
    }

    void BehaviourContext::setData(std::string name, void* data)
    {
        if (dataExists(name) == true)
        {
            removeData(name);
            mDataTable[name] = data;
        }
        else
            insertData(name, data);
    }

    void* BehaviourContext::getData(std::string name)
    {
        if (dataExists(name) == true)
            return mDataTable[name];

        return nullptr;
    }

    void BehaviourContext::luaSetDataInt32(std::string name, int32_t data)
    {
        setData(name, (void*)data);
    }

    void BehaviourContext::luaSetDataFloat(std::string name, float data)
    {
        setData(name, (void*)&data);
    }

    void BehaviourContext::luaSetDataDouble(std::string name, double data)
    {
        setData(name, (void*)&data);
    }

    void BehaviourContext::luaSetDataBoolean(std::string name, bool data)
    {
        setData(name, (void*)&data);
    }

    void BehaviourContext::luaSetDataString(std::string name, std::string data)
    {
        setData(name, static_cast<void*>(&data));
    }

    void BehaviourContext::luaPushStackInt32(std::string name, int32_t data)
    {
        if (stackExists(name) == false)
            createStack(name);

        pushStack(name, (void*)data);
    }

    void BehaviourContext::luaPushStackFloat(std::string name, float data)
    {
        if (stackExists(name) == false)
            createStack(name);

        pushStack(name, (void*)&data);
    }

    void BehaviourContext::luaPushStackDouble(std::string name, double data)
    {
        if (stackExists(name) == false)
            createStack(name);

        pushStack(name, (void*)&data);
    }

    void BehaviourContext::luaPushStackBoolean(std::string name, bool data)
    {
        if (stackExists(name) == false)
            createStack(name);

        pushStack(name, (void*)data);
    }

    void BehaviourContext::luaPushStackString(std::string name, std::string data)
    {
        if (stackExists(name) == false)
            createStack(name);

        pushStack(name, static_cast<void*>(&data));
    }

    int32_t BehaviourContext::luaPeekStackInt32(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(int32_t))
                return (int32_t)data;
        }
        
        return 0;
    }

    int32_t BehaviourContext::luaPopStackInt32(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(int32_t))
            {
                popStack(name);
                return (int32_t)data;
            }
        }

        return 0;
    }

    float BehaviourContext::luaPeekStackFloat(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(float))
                return *(float*)data;
        }

        return 0.f;
    }

    float BehaviourContext::luaPopStackFloat(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(float))
            {
                popStack(name);
                return *(float*)data;
            }
        }

        return 0;
    }

    double BehaviourContext::luaPeekStackDouble(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(double))
                return *(double*)data;
        }

        return 0.0;
    }

    double BehaviourContext::luaPopStackDouble(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(double))
            {
                popStack(name);
                return *(double*)data;
            }
        }

        return 0.0;
    }

    bool BehaviourContext::luaPeekStackBoolean(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(bool))
                return (bool)data;
        }

        return false;
    }

    bool BehaviourContext::luaPopStackBoolean(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr && sizeof(data) == sizeof(bool))
            {
                popStack(name);
                return (bool)data;
            }
        }

        return false;
    }

    std::string BehaviourContext::luaPeekStackString(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr)
                return *static_cast<std::string*>(data);
        }

        return "";
    }

    std::string BehaviourContext::luaPopStackString(std::string name)
    {
        if (stackExists(name) == true)
        {
            void* data = peekStack(name);

            if (data != nullptr)
            {
                popStack(name);
                return *static_cast<std::string*>(data);
            }
        }

        return "";
    }

    int32_t BehaviourContext::convertInt32(std::string name)
    {
        void* data = getData(name);

        if (data != nullptr && sizeof(data) == sizeof(int32_t))
        {
            int num = (int32_t)data;
            return num;
        }

        return 0;
    }

    double BehaviourContext::convertDouble(std::string name)
    {
        void* data = getData(name);

        if (data != nullptr && sizeof(data) == sizeof(double))
            return *(double*)data;

        return 0.0;
    }

    float BehaviourContext::convertFloat(std::string name)
    {
        void* data = getData(name);

        if (data != nullptr && sizeof(data) == sizeof(float))
            return *(float*)data;

        return 0.f;
    }

    bool BehaviourContext::convertBoolean(std::string name)
    {
        void* data = getData(name);

        if (data != nullptr && sizeof(data) == sizeof(bool))
            return *(bool*)data;

        return false;
    }

    std::string BehaviourContext::convertString(std::string name)
    {
        void* data = getData(name);

        if (data != nullptr)
            return *(static_cast<std::string*>(data));

        return "";
    }

}}
