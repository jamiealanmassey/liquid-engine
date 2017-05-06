#include "WidgetManager.h"

namespace liquid {
namespace ui {

    WidgetManager::WidgetManager(const data::TextureAtlas& textureAtlas) :
        mTextureAtlas(textureAtlas)
    {
        mHandleKeyboard = events::EventDispatcher<events::KeyboardEventData>::addListener(
            std::bind(&WidgetManager::handleKeyboardEvent, this, std::placeholders::_1));

        mHandleMouse = events::EventDispatcher<events::MouseEventData>::addListener(
            std::bind(&WidgetManager::handleMouseEvent, this, std::placeholders::_1));

        mHandleText = events::EventDispatcher<events::TextEventData>::addListener(
            std::bind(&WidgetManager::handleTextEvent, this, std::placeholders::_1));
    }

    WidgetManager::~WidgetManager()
    {
        events::EventDispatcher<events::KeyboardEventData>::removeListener(mHandleKeyboard);
        events::EventDispatcher<events::MouseEventData>::removeListener(mHandleMouse);
        events::EventDispatcher < events::TextEventData>::removeListener(mHandleText);
    }

    void WidgetManager::update()
    {
        for (uint32_t i = 0; i < mWidgets.size(); i++)
            mWidgets[i]->update();
    }

    void WidgetManager::insertWidget(Widget* widget)
    {
        widget->setParentWidgetManager(this);
        widget->initialise();
        mWidgets.push_back(widget);
    }

    void WidgetManager::removeWidget(Widget* widget)
    {
        std::remove(mWidgets.begin(), mWidgets.end(), widget);
    }

    void WidgetManager::updateEntered(const events::MouseEventData& eventData)
    {
        float mouseX = eventData.mPositionX;
        float mouseY = eventData.mPositionY;

        // TODO: impl handle functions for entered + exited in Widget class
        if (mEnteredWidget && mEnteredWidget->isPointInside(mouseX, mouseY) == false)
        {
            if (mEnteredWidget->isPressed())
                mEnteredWidget->setPressed(false);

            mEnteredWidget->setEntered(false);
            mEnteredWidget = nullptr;
        }

        std::vector<Widget*> entered;
        std::vector<Widget*>::reverse_iterator it;

        for (it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
        {
            if ((*it)->isActive() && (*it)->isEnabled() &&
                (*it)->isPointInside(mouseX, mouseY) && (*it)->canEnter())
            {
                entered.push_back(*it);
            }
        }

        if (entered.empty() == false)
        {
            Widget* findEntered = nullptr;

            if (entered[0]->getParentEntity())
                findEntered = findNextParent(entered[0], mouseX, mouseY);

            if (findEntered == nullptr)
                findEntered = entered[0];

            mEnteredWidget = findEntered;
            mEnteredWidget->setEntered(true);
        }
    }

    void WidgetManager::updateFocused(const events::MouseEventData& eventData)
    {
        float mouseX = eventData.mPositionX;
        float mouseY = eventData.mPositionY;

        if (eventData.mPressed == true)
        {
            if (eventData.mMouseButton == 0 && mEnteredWidget)
            {
                Widget* selection = findNextInside(mEnteredWidget, mouseX, mouseY);

                if (selection == nullptr)
                    selection = mEnteredWidget;

                if (selection->canAcceptFocus() && selection->hasFocus() == false)
                {
                    mFocusedWidget = selection;
                    mFocusedWidget->setFocused(true);
                }
            }
            else if (eventData.mMouseButton == 0 && mFocusedWidget)
            {
                if (mFocusedWidget->isPointInside(mouseX, mouseY) == false)
                {
                    mFocusedWidget->setFocused(false);
                    mFocusedWidget = nullptr;
                }
            }
            else if (eventData.mMouseButton == 1)
            {
                if (mFocusedWidget != nullptr)
                {
                    mFocusedWidget->setFocused(false);
                    mFocusedWidget = nullptr;
                }
            }
        }
        else if (eventData.mPressed == false)
        {
            if (eventData.mMouseButton == 1)
            {
                buttonPressedCheck(mEnteredWidget);
                buttonPressedCheck(mFocusedWidget);
            }
        }
    }

    void WidgetManager::buttonPressedCheck(Widget* widget)
    {
        if (widget != nullptr && widget->isPressed())
            widget->setPressed(false);
    }

    Widget* WidgetManager::findNextParent(Widget* widget, float x, float y)
    {
        Widget* nextParent = nullptr;
        Widget* parent = static_cast<Widget*>(widget->getParentEntity());

        if (parent != nullptr && parent->isPointInside(x, y) && parent->canEnter())
            nextParent = findNextParent(parent, x, y);

        if (nextParent == nullptr)
            return widget;

        return nextParent;
    }

    Widget* WidgetManager::findNextInside(Widget* widget, float x, float y)
    {
        std::vector<common::Entity*>& children = widget->getChildren();
        Widget* selection = nullptr;

        for (uint32_t i = 0; i < children.size(); i++)
        {
            Widget* conv = static_cast<Widget*>(children[i]);
            if (children[i]->isPointInside(x, y) && conv->canEnter())
                selection = findNextInside(conv, x, y);
            else
                return conv;
        }

        if (selection == nullptr)
            return widget;

        return selection;
    }

    std::vector<Widget*> WidgetManager::getWidgets()
    {
        return mWidgets;
    }

    data::TextureAtlas& WidgetManager::getTextureAtlas()
    {
        return mTextureAtlas;
    }

    Widget* WidgetManager::getEnteredWidget()
    {
        return mEnteredWidget;
    }

    Widget* WidgetManager::getFocusedWidget()
    {
        return mFocusedWidget;
    }

    bool WidgetManager::handleKeyboardEvent(const events::KeyboardEventData& eventData)
    {
        for (uint32_t i = 0; i < mWidgets.size(); i++)
        {
            if (mWidgets[i]->isPressed())
                mWidgets[i]->handleKeyboardPressed(0); // TODO
        }

        return true;
    }

    bool WidgetManager::handleMouseEvent(const events::MouseEventData& eventData)
    {
        updateEntered(eventData);
        updateFocused(eventData);

        if (mEnteredWidget != nullptr)
        {
            int32_t button = eventData.mMouseButton;
            float mouseX = eventData.mPositionX;
            float mouseY = eventData.mPositionY;

            if (eventData.mMoved == true)
                mEnteredWidget->handleMouseMoved(mouseX, mouseY);
            else if (eventData.mPressed == true)
            {
                mEnteredWidget->setPressed(true);
                mEnteredWidget->handleMousePressed(button, mouseX, mouseY);
            }
            else if (eventData.mPressed == false)
            {
                mEnteredWidget->setPressed(false);
                mEnteredWidget->handleMouseReleased(button, mouseX, mouseY);
            }
        }
        
        return true;
    }

    bool WidgetManager::handleTextEvent(const events::TextEventData& eventData)
    {
        if (mFocusedWidget != nullptr)
            mFocusedWidget->handleTextEntered(eventData.mCharacter);

        return true;
    }

}}
