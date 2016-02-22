#ifndef _NAVPATH_H
#define _NAVPATH_H

#include <SFML/Graphics.hpp>
#include <list>

#include "NavGraph.h"
#include "NavNode.h"

class NavPath
{
public:
	NavPath(NavGraph* graph);
	~NavPath() {}

	/* Core path functions */
	void render(sf::RenderTarget& target);

	/* Pusher functions for nodes */
	inline void pushFront(int32_t idx) { m_Nodes.push_front(idx); }
	inline void pushBack(int32_t idx)  { m_Nodes.push_back(idx);  }

	/* NavPath control functions */
	const NavNode& popFront();
	const NavNode& popBack();
	const NavNode& loopFront();
	const NavNode& loopBack();

	/* Pathing */
	std::vector<NavNode> getPath();
	std::vector<NavNode> getPathReverse();

	/* Getter functions for nodes */
	inline       bool     isEmpty()   const { return m_Nodes.empty();					}
	inline const NavNode& peekFront() const { return m_Graph->getNode(m_Nodes.front()); }
	inline const NavNode& peekBack()  const { return m_Graph->getNode(m_Nodes.back());	}

protected:
	NavGraph*		   m_Graph; ///< Pointer to given graph
	std::list<int32_t> m_Nodes; ///< List of nodes in the path
};

#endif // _NAVPATH_H
