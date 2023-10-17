#ifndef __PLAYSCREENUI_H
#define __PLAYSCREENUI_H

#include <vector>
#include <string>

#include "EventManager.h"
#include "GameEntity.h"
#include "Scoreboard.h"
#include "GLTexture.h"
#include "Player.h"
#include "Timer.h"

using namespace SDLFramework;

class PlayScreenUI : public GameEntity {
private:
	EventManager* mEvent;
	Player* mPlayer;
	Timer* mTimer;

	GameEntity* mDisplay;
	Scoreboard* mDisplayHiScore;
	Scoreboard* mDisplayScore;

	GameEntity* mGameOverDisplay;
	Scoreboard* mGameOverHiScore;
	Scoreboard* mGameOverScore;
	GLTexture* mGameOverMessage;
	bool mGameOver;

public:
	PlayScreenUI();
	~PlayScreenUI();

	void processEvents();

	void Update() override;
	void Render() override;
};

#endif