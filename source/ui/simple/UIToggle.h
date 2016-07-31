#ifndef _UITOGGLE_H
#define _UITOGGLE_H

#include "UIButton.h"

class UIToggle : public UIButton
{
public:
	UIToggle(UIElement* parent, std::string id, sf::Vector2f size, std::string elementName);
	~UIToggle();

	virtual void implInitialise() override;
	virtual void implUpdate()	  override;

	virtual void setPressed(bool flag) override;
	virtual void setEntered(bool flag) override;

	bool isToggled() const { return m_IsToggled; }

protected:
	bool m_IsToggled;
};

#endif // _UITOGGLE_H
