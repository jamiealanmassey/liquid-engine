#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

#include <functional>

class NavGraph;
class PriorityQueueMin
{
public:
	typedef std::function<bool(int32_t a, int32_t b)> CompareFunc;

public:
	PriorityQueueMin(int32_t size, CompareFunc compare_func);
	~PriorityQueueMin();

	int32_t pop(int32_t index);
	void	insert(int32_t data);
	void	updatePriority(int32_t data);
	bool	contains(int32_t data);

	uint32_t getSize() const { return m_Size; }
	bool	 isEmpty() const { return m_Size == 0; }

protected:
	int32_t*	m_Heap;		   ///< Heap of values
	uint32_t	m_Size;		   ///< Size of the heap
	CompareFunc m_CompareFunc; ///< Function callback to comparision method
};

#endif // _PRIORITYQUEUE_H
