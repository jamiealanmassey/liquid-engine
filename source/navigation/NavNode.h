#ifndef _NAVNODE_H
#define _NAVNODE_H

#define INVALID_NODE_INDEX -1

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

class NavNode
{
public:
	NavNode(int32_t index = INVALID_NODE_INDEX);
	~NavNode();

	/* Setter functions */
	void setTraversable(bool flag)			{ m_Traversable = flag; }
	void setIndex(int32_t index)			{ m_Index = index;		}
	void setPosition(const sf::Vector2f& v) { m_Position = v;		}

	/* Getter functions */
	bool		 checkTraversable() const { return m_Traversable; }
	int32_t		 getIndex()		    const { return m_Index;		  }
	sf::Vector2f getPosition()		const { return m_Position;	  }

protected:
	bool		 m_Traversable; ///< Flag to denote whether you can traverse this node
	int32_t		 m_Index;		///< Index of the node
	sf::Vector2f m_Position;	///< Position of the node in the world
};

class NavEdge
{
public:
	NavEdge();
	NavEdge(int32_t from, int32_t to, double cost = 1.0f);
	~NavEdge();

public:
	int32_t m_From;
	int32_t m_To;
	double  m_Cost;
};

typedef std::list<NavEdge>		 NavEdgeList;
typedef std::vector<NavNode>	 NavNodes;
typedef std::vector<NavEdgeList> NavEdges;

#endif // _NAVNODE_H
