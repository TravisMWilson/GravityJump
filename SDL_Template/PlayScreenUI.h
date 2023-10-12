#ifndef __PLAYSCREENUI_H
#define __PLAYSCREENUI_H

#include <vector>
#include <string>

#include "GameEntity.h"
#include "Scoreboard.h"
#include "GLTexture.h"
#include "Player.h"

using namespace SDLFramework;

class PlayScreenUI : public GameEntity {
private:
	Player* mPlayer;

	GameEntity* mDisplay;
	Scoreboard* mDisplayHiScore;
	Scoreboard* mDisplayScore;

public:
	PlayScreenUI();
	~PlayScreenUI();

	void Update() override;
	void Render() override;
};

#endif