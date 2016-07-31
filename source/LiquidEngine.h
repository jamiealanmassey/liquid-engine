#ifndef _LIQUIDENGINE_H
#define _LIQUIDENGINE_H

// COMMON INCLUDES
#include "common/ContactManager.h"
#include "common/Entity.h"
#include "common/EventManager.h"
#include "common/GameManager.h"
#include "common/GameScene.h"
#include "common/LuaInstance.h"
#include "common/ResourceManager.h"

// GRAPHICS INCLUDES
#include "graphics/Particle.h"
#include "graphics/ParticleEmitter.h"
#include "graphics/PostProcessor.h"
#include "graphics/Renderable.h"
#include "graphics/RenderableText.h"
#include "graphics/Renderer.h"

// LIGHTING INCLUDES
#include "graphics/lighting/Light.h"
#include "graphics/lighting/LightFXProcessor.h"
#include "graphics/lighting/PointLight.h"

// NAVIGATION INCLUDES
#include "navigation/AStar.h"
#include "navigation/NavGraph.h"
#include "navigation/NavNode.h"
#include "navigation/NavPath.h"

// UI INCLUDES
#include "ui/UIElement.h"
#include "ui/UIEventTable.h"
#include "ui/UIManager.h"
#include "ui/UISkinRenderable.h"
#include "ui/UITransitionEffect.h"
#include "ui/UITransitionTable.h"
#include "ui/dynamic/UISlider.h"
#include "ui/dynamic/UIStaticBox.h"
#include "ui/dynamic/UITooltip.h"
#include "ui/dynamic/UIWindow.h"
#include "ui/simple/UIButton.h"
#include "ui/simple/UIComboBox.h"
#include "ui/simple/UIListBox.h"
#include "ui/simple/UISelectionBox.h"
#include "ui/simple/UISelectionElement.h"
#include "ui/simple/UIStaticLabel.h"
#include "ui/simple/UIToggle.h"

// UTILITIES INCLUDES
#include "utilities/DeltaTime.h"
#include "utilities/FileName.h"
#include "utilities/IDGenerator.h"
#include "utilities/LerpValue.h"
#include "utilities/Logger.h"
#include "utilities/PriorityQueue.h"
#include "utilities/Random.h"
#include "utilities/Vectors.h"

#endif // _LIQUIDENGINE_H
