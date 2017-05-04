#include "Stack.h"

namespace liquid {
namespace utilities {

    Stack::Stack()
    {
    }

    Stack::~Stack()
    {
        while (mStack.empty() == false)
        {
            delete mStack.front();
            mStack.pop_front();
        }
    }

    void Stack::push(void* element)
    {
        mStack.push_front(element);
    }

    void* Stack::peek()
    {
        return mStack.front();
    }

    void* Stack::pop()
    {
        void* element = mStack.front();
        mStack.pop_front();
        return element;
    }

    const uint32_t Stack::size() const
    {
        return mStack.size();
    }

    const bool Stack::empty() const
    {
        return mStack.empty();
    }

}}
