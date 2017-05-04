#include <list>

namespace liquid { namespace utilities {
#ifndef _STACK_H
#define _STACK_H

class Stack
{
public:
    Stack();
    ~Stack();

    void push(void* element);
    void* peek();
    void* pop();

    const uint32_t size() const;
    const bool empty() const;

protected:
    std::list<void*> mStack;
};

#endif // _STACK_H
}}
