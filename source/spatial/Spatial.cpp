#include "Spatial.h"

namespace liquid {
namespace spatial {

    Spatial::Spatial(int32_t spatialType)
    {
        mSpatialType = spatialType;
    }

    Spatial::~Spatial()
    {}

    const int32_t Spatial::getSpatialType() const
    {
        return mSpatialType;
    }

}}
