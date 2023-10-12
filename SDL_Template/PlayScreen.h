#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include <vector>

#include "AudioManager.h"
#include "PlayScreenUI.h"
#include "GameEntity.h"
#include "Platform.h"
#include "Random.h"
#include "Player.h"
#include "Timer.h"

class PlayScreen : public GameEntity {
private:
	AudioManager* mAudio;
	InputManager* mInput;
	Random* mRand;
	Timer* mTimer;
	Player* mPlayer;

	PlayScreenUI* mSideBar;

	std::vector<Platform*> mPlatforms;

	int mMusicSelection;

public:
	PlayScreen();
	~PlayScreen();

	void newPlatform();
	void removePlatforms();

	void Update() override;
	void Render() override;
};

#endif