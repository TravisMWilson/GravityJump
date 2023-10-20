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
	GLTexture* mDisplayHiScoreBackground;
	Scoreboard* mDisplayScore;
	GLTexture* mDisplayScoreBackground;

	GameEntity* mGameOverDisplay;
	Scoreboard* mGameOverHiScore;
	GLTexture* mGameOverHiScoreBackground;
	Scoreboard* mGameOverScore;
	GLTexture* mGameOverScoreBackground;
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