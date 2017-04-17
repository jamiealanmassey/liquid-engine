#include <stdint.h>
#include <math.h>
#include <array>
#include <ctime>
#include <cstdlib>

namespace liquid { namespace utilities {
#ifndef _RANDOM_H
#define _RANDOM_H

/**
 * \class Random
 *
 * \ingroup Utilities
 * \brief Gives access to functions for creating random numbers
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 10/04/2017
 *
 */

class Random
{
private:
    /// Random Constructor
    Random();

    /// Random Destructor
    ~Random();

public:
    /** \brief Takes two values and produces a number between them
      * \param min int32_t value of minimum number should be
      * \param max int32_t value of maximum number should be
      * \return Randomly generated int32_t number
      */
    int32_t randomRange(int32_t min, int32_t max);

    /** \brief Takes two values and produces a number between them
      * \param min float value of minimum number should be
      * \param max float value of maximum number should be
      * \return Randomly generated float number
      */
    float randomRange(float min, float max);

    /** \brief Takes two values and produces a number between them
      * \param min double value of minimum number should be
      * \param max double value of maximum number should be
      * \return Randomly generated double number
      */
    double randomRange(double min, double max);

    /** \brief Takes two vector values and produces a random vector between them
      * \param min vector value of minimum number should be
      * \param max vector value of maximum number should be
      * \return Randomly generated vector
      */
    std::array<float, 2> randomRange(std::array<float, 2> min, std::array<float, 2> max);

    /** \brief Generates a random unit vector between (0-1) on both axes
      * \return Randomly generated vector
      */
    std::array<float, 2> randomUnitVector();

    /** \brief Gets the instance of this class (singleton)
      * \return Pointer to the on instance of this class in memory
      */
    static Random& instance();
};


#endif // _RANDOM_H
}}
