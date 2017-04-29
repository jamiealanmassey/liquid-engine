#ifndef _LIQUIDENGINE_H
#define _LIQUIDENGINE_H

/**
  * \defgroup AI
  * \defgroup Animation
  * \defgroup Audio
  * \defgroup Common
  * \defgroup Data
  * \defgroup Events
  * \defgroup Graphics
  * \defgroup Impl
  * \defgroup Navigation
  * \defgroup Parser
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

#include "animation/AnimationDefs.h"
#include "animation/AnimationFrame.h"
#include "animation/AnimationParser.h"
#include "animation/Animator.h"

#include "common/Entity.h"
#include "common/GameManager.h"
#include "common/GameScene.h"
#include "common/LuaInstance.h"
#include "common/Particle.h"
#include "common/ParticleEmitter.h"
#include "common/ResourceManager.h"

#include "data/Bindings.h"
#include "data/Directories.h"
#include "data/ParticleData.h"
#include "data/Settings.h"
#include "data/TextureAtlas.h"

#include "events/EventDispatcher.h"
#include "events/EventManager.h"
#include "events/JoystickEventData.h"
#include "events/KeyboardEventData.h"
#include "events/MouseEventData.h"
#include "events/WindowEventData.h"

#include "graphics/ICamera.h"
#include "graphics/IRenderable.h"
#include "graphics/Light.h"
#include "graphics/LightingManager.h"
#include "graphics/Renderable.h"
#include "graphics/RenderableBatch.h"
#include "graphics/Renderer.h"

#include "impl/sfml/SFMLCamera.h"
#include "impl/sfml/SFMLEventManager.h"
#include "impl/sfml/SFMLLightingManager.h"
#include "impl/sfml/SFMLRenderable.h"
#include "impl/sfml/SFMLRenderableBatch.h"
#include "impl/sfml/SFMLRenderer.h"

#include "navigation/AStar.h"
#include "navigation/NavEdge.h"
#include "navigation/NavGraph.h"
#include "navigation/NavNode.h"
#include "navigation/NavPath.h"

#include "parser/Parser.h"
#include "parser/ParserConfig.h"
#include "parser/ParserNode.h"
#include "parser/ParserNodeSearch.h"
#include "parser/ParserXML.h"

#include "spatial/QuadNode.h"
#include "spatial/QuadTree.h"
#include "spatial/Spatial.h"

#include "tweener/EasingFuncs.h"
#include "tweener/EasingFunction.h"
#include "tweener/ITweener.h"
#include "tweener/Tweener.h"
#include "tweener/TweenerGroup.h"
#include "tweener/TweenerSequence.h"

#include "ui/Button.h"
#include "ui/ControlList.h"
#include "ui/Slider.h"
#include "ui/Toggle.h"
#include "ui/Widget.h"
#include "ui/WidgetManager.h"

#include "utilities/DeltaTime.h"
#include "utilities/Random.h"
#include "utilities/Vertex2.h"

#endif // _LIQUIDENGINE_H
