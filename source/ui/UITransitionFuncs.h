#ifndef _UITRANSITIONFUNCS_H
#define _UITRANSITIONFUNCS_H

#include "UITransitionData.h"

#include <algorithm>

class UIElement;
class UITransitionState;

// -------- PREDEFINED TRANSITION STATE FUNCS ----------
bool TransitionFuncMoveTo(UIElement*  element, UITransitionState* state, TransitionMoveTo* data);
bool TransitionFuncFadeOut(UIElement* element, UITransitionState* state, TransitionFade* data);
bool TransitionFuncFadeIn(UIElement*  element, UITransitionState* state, TransitionFade* data);
bool TransitionFuncAnimate(UIElement* element, UITransitionState* state, TransitionAnimate* data);
bool TransitionFuncColourTo(UIElement* element, UITransitionState* state, TransitionColour* data);

#endif // _UITRANSITIONFUNCS_H
