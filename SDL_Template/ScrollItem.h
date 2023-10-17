#ifndef __SHOPITEM_H
#define __SHOPITEM_H

#include <string>

#include "AnimatedGLTexture.h"
#include "EventManager.h"
#include "InputManager.h"
#include "GameEntity.h"
#include "Scoreboard.h"
#include "GLTexture.h"
#include "Player.h"
#include "Button.h"
#include "Timer.h"

using namespace SDLFramework;

class ScrollItem : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	EventManager* mEvent;
	Player* mPlayer;

	std::string mItemName;

	GLTexture* mBackground;

	AnimatedGLTexture* mAnimIcon;
	GLTexture* mIcon;

	Button* mButton;
	Scoreboard* mCurrentLevel;
	Scoreboard* mCurrentCost;
	long mBaseCost;
	long mCost;
	long mLevel;

public:
	ScrollItem(std::string itemName, AnimatedGLTexture* icon, long baseCost);
	ScrollItem(std::string itemName, GLTexture* icon, long baseCost);
	~ScrollItem();

	void processEvents();

	void setupItem();

	void Update() override;
	void Render() override;
};

#endif