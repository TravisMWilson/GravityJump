#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include "AudioManager.h"
#include "PlayScreenUI.h"
#include "GameEntity.h"
#include "Timer.h"

class PlayScreen : public GameEntity {
private:
	AudioManager* mAudio;
	Timer* mTimer;

	PlayScreenUI* mSideBar;

	int mMusicSelection;

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;
};

#endif