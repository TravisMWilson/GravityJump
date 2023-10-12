#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include <vector>

#include "AnimatedGLTexture.h"
#include "EventManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PlayScreenUI.h"
#include "GameEntity.h"
#include "Platform.h"
#include "Random.h"
#include "Player.h"
#include "Timer.h"

class PlayScreen : public GameEntity {
private:
	EventManager* mEvent;
	InputManager* mInput;
	Random* mRand;
	Timer* mTimer;
	Player* mPlayer;

	PlayScreenUI* mSideBar;

	std::vector<Platform*> mPlatforms;

	AnimatedGLTexture* mTarget;
	AnimatedGLTexture* mExplosion;

public:
	PlayScreen();
	~PlayScreen();

	void newPlatform();
	void removePlatforms();

	void Update() override;
	void Render() override;
};

#endif