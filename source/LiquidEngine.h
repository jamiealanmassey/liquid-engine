#ifndef _LIQUIDENGINE_H
#define _LIQUIDENGINE_H

/**
  * \defgroup AI
  * \defgroup Common
  * \defgroup Data
  * \defgroup Events
  * \defgroup Graphics
  * \defgroup Impl
  * \defgroup Navigation
  * \defgroup Spatial
  * \defgroup Tweener
  * \defgroup UI
  * \defgroup Utilities
  *
  * \brief Include directory for all includes of the project
  *
  * \author Jamie Massey
  * \version 2.0
  * \date 04/04/2017
  *
  */

#include "common/Entity.h"
#include "common/GameManager.h"
#include "common/GameScene.h"
#include "common/LuaInstance.h"
#include "common/ResourceManager.h"

#include "data/Bindings.h"
#include "data/ConfigurationParser.h"
#include "data/Directories.h"
#include "data/Settings.h"

#include "events/EventDispatcher.h"
#include "events/EventManager.h"
#include "events/JoystickEventData.h"
#include "events/KeyboardEventData.h"
#include "events/MouseEventData.h"
#include "events/WindowEventData.h"

#include "graphics/IRenderable.h"
#include "graphics/Renderable.h"
#include "graphics/RenderableBatch.h"
#include "graphics/Renderer.h"

#include "impl/sfml/SFMLEventManager.h"
#include "impl/sfml/SFMLRenderable.h"
#include "impl/sfml/SFMLRenderableBatch.h"
#include "impl/sfml/SFMLRenderer.h"

#include "tweener/EasingFuncs.h"
#include "tweener/EasingFunction.h"
#include "tweener/ITweener.h"
#include "tweener/Tweener.h"
#include "tweener/TweenerGroup.h"
#include "tweener/TweenerSequence.h"

#include "utilities/DeltaTime.h"
#include "utilities/Random.h"
#include "utilities/Vertex2.h"

#endif // _LIQUIDENGINE_H
