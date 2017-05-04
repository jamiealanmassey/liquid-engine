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
    
    static int32_t convertInt32(void* data);
    static float convertFloat(void* data);
    static double convertDouble(void* data);
    static bool convertBoolean(void* data);
    static std::string convertString(void* data);

protected:
    std::map<std::string, void*>             mDataTable;
    std::map<std::string, utilities::Stack*> mStackTable;
};

#endif // _BEHAVIOURCONTEXT_H
}}
