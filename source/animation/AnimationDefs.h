#include "AnimationFrame.h"

namespace liquid { namespace animation {
#ifndef _ANIMATIONDEFS_H
#define _ANIMATIONDEFS_H

typedef std::vector<AnimationFrame> Animation;
typedef std::map<std::string, Animation> AnimationTable;
typedef std::map<int32_t, std::string> AnimationIndexer;

#endif // _ANIMATIONDEFS_H
}}
