#include "NavEdge.h"

namespace liquid {
namespace navigation {

    NavEdge::NavEdge()
    {
        mEdgeFrom = INVALID_NAV_NODE;
        mEdgeTo = INVALID_NAV_NODE;
        mCost = 1.0f;
    }

    NavEdge::NavEdge(int32_t from, int32_t to, double cost)
    {
        mEdgeFrom = from;
        mEdgeTo = to;
        mCost = cost;
    }

    NavEdge::~NavEdge()
    {}

    void NavEdge::setEdgeFrom(int32_t from)
    {
        mEdgeFrom = from;
    }

    void NavEdge::setEdgeTo(int32_t to)
    {
        mEdgeTo = to;
    }

    void NavEdge::setCost(double cost)
    {
        mCost = cost;
    }

    const int32_t NavEdge::getEdgeFrom() const
    {
        return mEdgeFrom;
    }

    const int32_t NavEdge::getEdgeTo() const
    {
        return mEdgeTo;
    }

    const double NavEdge::getCost() const
    {
        return mCost;
    }

}}
