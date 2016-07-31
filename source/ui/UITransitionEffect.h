#ifndef _UITRANSITIONEFFECT_H
#define _UITRANSITIONEFFECT_H

#include <SFML/Graphics.hpp>
#include <functional>

class UIElement;
class UITransitionEffect
{
public:
	typedef std::function<void()> FinishFunc;

public:
	UITransitionEffect(UIElement* element, float duration, FinishFunc finished = nullptr);
	~UITransitionEffect();

	virtual void initialise() {}
	virtual void update()	  {}

	virtual void trigger();
	virtual void resetLifetime();

	bool  isActive()	const { return m_Active;   }
	float getLifetime() const { return m_Lifetime; }

protected:
	FinishFunc m_FinishedCallback;
	UIElement* m_Element;
	float	   m_Lifetime;
	float	   m_Duration;
	bool       m_Active;
};

class UITransitionTranslate : public UITransitionEffect
{
public:
	UITransitionTranslate(UIElement* element, float duration, sf::Vector2f point, FinishFunc finished = nullptr);
	~UITransitionTranslate();

	void initialise();
	void update();

	void trigger() override;

	void setIsAbsolute(bool flag) { m_IsAbsolute = flag; }

protected:
	sf::Vector2f m_PositionTarget;
	sf::Vector2f m_Point;
	bool		 m_IsAbsolute;
};

#endif // _UITRANSITIONEFFECT_H
