#include <functional>

namespace liquid { namespace utilities {
#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

/**
 * \class PriorityQueue
 *
 * \ingroup Utilities
 * \brief Implements a Priority Queue for given value types
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 22/04/2017
 *
 */

template <class T>
class PriorityQueue
{
public:
    /// Defines a comparison Function to use
    typedef std::function<bool(T a, T b)> ComparisonFunc;

public:
    /** \brief PriorityQueue Constructor
      * \param size Fixed size of the PriorityQueue
      * \param comparisonFunc Method to compare values
      */
    PriorityQueue(int32_t size, ComparisonFunc comparisonFunc)
    {
        mSize = 0;
        mHeap = new T[size];
        mComparisonFunc = comparisonFunc;
    }

    /// PriorityQueue Destructor
    ~PriorityQueue()
    {
        delete[] mHeap;
    }

    /** \brief Pops the next value off of the heap
      * \param index Location of value to pop
      * \return The popped element
      */
    T pop(int32_t index)
    {
        if (mSize == 0)
            return 0;

        T root = mHeap[index];
        mHeap[index] = mHeap[mSize - 1];
        mSize--;

        int32_t curIndex = index;
        int32_t childIndex = 2 * curIndex + 1;

        while (childIndex < mSize)
        {
            if (mComparisonFunc(mHeap[childIndex], mHeap[curIndex]))
            {
                if (mComparisonFunc(mHeap[childIndex + 1], mHeap[childIndex]))
                    childIndex++;

                T temp = mHeap[childIndex];
                mHeap[childIndex] = mHeap[curIndex];
                mHeap[curIndex] = temp;
                curIndex = childIndex;
            }
            else break;

            childIndex = 2 * curIndex + 1;
        }

        return root;
    }

    /** \brief Inserts a new value into the PriorityQueue
      * \param value Value to add to the heap
      */
    void insert(T value)
    {
        mHeap[mSize] = value;
        mSize++;

        int32_t curIndex = (mSize - 1);
        int32_t parentIndex = (int32_t)std::floor((curIndex - 1.0f) / 2.0f);
        int32_t counter = 0;

        while (parentIndex >= 0)
        {
            counter++;

            if (mComparisonFunc(mHeap[curIndex], mHeap[parentIndex]))
            {
                T& temp = mHeap[parentIndex];
                mHeap[parentIndex] = mHeap[curIndex];
                mHeap[curIndex] = temp;
                curIndex = parentIndex;
            }
            else break;

            parentIndex = (int32_t)std::floor((curIndex - 1.0f) / 2.0f);
        }
    }

    /** \brief Update the priority of a value (simple pop and re-insert)
      * \param value Value to update the priortiy of
      */
    void updatePriority(T value)
    {
        for (uint32_t i = 0; i < mSize; i++)
        {
            if (mHeap[i] == value)
            {
                T element = pop(i);
                insert(element);
                break;
            }
        }
    }

    /** \brief Checks to see if the PriorityQueue contains a value on the heap
      * \param value Value to be checked
      * \return True if found, otherwise false
      */
    const bool contains(T value)
    {
        for (int32_t i = 0; i < mSize; i++)
        {
            if (mHeap[i] == value)
                return true;
        }

        return false;
    }

    /// \return Current size of the heap
    const uint32_t getSize() const
    {
        return mSize;
    }

    /// \return True if the heap is empty, otherwise false
    const bool isEmpty() const
    {
        return mSize == 0;
    }

protected:
    T*             mHeap;           ///< The heap of data values to use
    uint32_t       mSize;           ///< Fixed size of the heap, and thus the PriorityQueue
    ComparisonFunc mComparisonFunc; ///< Comparison Function to use
};

#endif // _PRIORITYQUEUE_H
}}
