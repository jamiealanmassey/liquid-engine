#include "Random.h"

namespace liquid {
namespace utilities {

    Random::Random()
    {
        std::srand(std::time(nullptr));
    }

    Random::~Random()
    {}

    int32_t Random::randomRange(int32_t min, int32_t max)
    {
        return std::rand() % (max - min) + min;
    }

    float Random::randomRange(float min, float max)
    {
        return ((max - min) * ((float)std::rand() / RAND_MAX)) + min;
    }

    double Random::randomRange(double min, double max)
    {
        return ((max - min) * ((double)std::rand() / RAND_MAX)) + min;
    }

    std::array<float, 2> Random::randomRange(std::array<float, 2> min, std::array<float, 2> max)
    {
        float rx = randomRange(min[0], max[0]);
        float ry = randomRange(min[1], max[1]);

        return { rx,ry };
    }

    std::array<float, 2> Random::randomUnitVector()
    {
        float rx = randomRange(-1.0f, 1.0f);
        float ry = randomRange(-1.0f, 1.0f);
        float len = std::sqrt((rx * rx) + (ry * ry));

        if (len != 0.0f)
        {
            rx /= len;
            ry /= len;
        }

        return { rx,ry };
    }

    Random& Random::instance()
    {
        static Random singleton;
        return singleton;
    }

}}
