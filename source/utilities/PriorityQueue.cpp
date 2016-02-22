#include "PriorityQueue.h"
#include "../Navigation/NavGraph.h"

PriorityQueueMin::PriorityQueueMin(int32_t size, CompareFunc compare_func) :
	m_Size(0),
	m_Heap(new int32_t[size]),
	m_CompareFunc(compare_func)
{
}

PriorityQueueMin::~PriorityQueueMin()
{
	delete[] m_Heap;
}

int32_t PriorityQueueMin::pop(int32_t index)
{
	if (isEmpty())
		return 0;

	int32_t root = m_Heap[index];
	m_Heap[index] = m_Heap[m_Size - 1];
	m_Size--;

	int32_t cur_index = index;
	int32_t child_index = 2 * cur_index + 1;

	while (child_index < m_Size)
	{
		if (m_CompareFunc(m_Heap[child_index], m_Heap[cur_index]))
		{
			//Swap with smaller child
			if (m_CompareFunc(m_Heap[child_index + 1], m_Heap[child_index]))
				child_index = (child_index + 1);

			int32_t temp = m_Heap[child_index];
			m_Heap[child_index] = m_Heap[cur_index];
			m_Heap[cur_index] = temp;
			cur_index = child_index;
		}
		else
			break;

		child_index = 2 * cur_index + 1;
	}

	return root;
}

void PriorityQueueMin::insert(int32_t data)
{
	m_Heap[m_Size] = data;
	m_Size++;

	int32_t cur_index = (m_Size - 1);
	int32_t parent_index = (int32_t)floor((cur_index - 1.0f) / 2.0f);
	int32_t counter = 0;

	while (parent_index >= 0)
	{
		counter++;

		if (m_CompareFunc(m_Heap[cur_index], m_Heap[parent_index]))
		{
			int32_t& temp = m_Heap[parent_index];
			m_Heap[parent_index] = m_Heap[cur_index];
			m_Heap[cur_index] = temp;
			cur_index = parent_index;
		}
		else
			break;

		parent_index = (int32_t)floor((cur_index - 1.0f) / 2.0f);
	}
}

void PriorityQueueMin::updatePriority(int32_t data)
{
	for (uint32_t i = 0; i < m_Size; i++)
	{
		if (m_Heap[i] == data)
		{
			int32_t element = pop(i);
			insert(element);
			break;
		}
	}
}

bool PriorityQueueMin::contains(int32_t data)
{
	for (int32_t i = 0; i < m_Size; i++)
	{
		if (m_Heap[i] == data)
			return true;
	}

	return false;
}
