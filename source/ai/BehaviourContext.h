#include <map>
#include "../utilities/Stack.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURCONTEXT_H
#define _BEHAVIOURCONTEXT_H

class BehaviourContext
{
public:
    BehaviourContext();
    ~BehaviourContext();

    bool dataExists(std::string name);
    bool stackExists(std::string name);

    void createStack(std::string name);
    void deleteStack(std::string name);

    void pushStack(std::string name, void* data);
    void* popStack(std::string name);
    void* peekStack(std::string name);

    void insertData(std::string name, void* data);
    void removeData(std::string name);
    void setData(std::string name, void* data);
    void* getData(std::string name);

    void luaSetDataInt32(std::string name, int32_t data);
    void luaSetDataFloat(std::string name, float data);
    void luaSetDataDouble(std::string name, double data);
    void luaSetDataBoolean(std::string name, bool data);
    void luaSetDataString(std::string name, std::string data);

    void luaPushStackInt32(std::string name, int32_t data);
    void luaPushStackFloat(std::string name, float data);
    void luaPushStackDouble(std::string name, double data);
    void luaPushStackBoolean(std::string name, bool data);
    void luaPushStackString(std::string name, std::string data);

    int32_t luaPeekStackInt32(std::string name);
    int32_t luaPopStackInt32(std::string name);

    float luaPeekStackFloat(std::string name);
    float luaPopStackFloat(std::string name);

    double luaPeekStackDouble(std::string name);
    double luaPopStackDouble(std::string name);

    bool luaPeekStackBoolean(std::string name);
    bool luaPopStackBoolean(std::string name);

    std::string luaPeekStackString(std::string name);
    std::string luaPopStackString(std::string name);

    int32_t convertInt32(std::string name);
    float convertFloat(std::string name);
    double convertDouble(std::string name);
    bool convertBoolean(std::string name);
    std::string convertString(std::string name);

protected:
    std::map<std::string, void*>             mDataTable;
    std::map<std::string, utilities::Stack*> mStackTable;
};

#endif // _BEHAVIOURCONTEXT_H
}}
