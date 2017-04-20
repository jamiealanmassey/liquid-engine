#include <stdint.h>

namespace liquid { namespace navigation {
#ifndef _NAVEDGE_H
#define _NAVEDGE_H

#define INVALID_NAV_NODE -1

class NavEdge
{
public:
    NavEdge();
    NavEdge(int32_t from, int32_t to, double cost = 1.0f);
    ~NavEdge();

    void setEdgeFrom(int32_t from);
    void setEdgeTo(int32_t to);
    void setCost(double cost);

    const int32_t getEdgeFrom() const;
    const int32_t getEdgeTo() const;
    const double getCost() const;

protected:
    int32_t mEdgeFrom;
    int32_t mEdgeTo;
    double  mCost;
};

#endif // _NAVEDGE_H
}}
