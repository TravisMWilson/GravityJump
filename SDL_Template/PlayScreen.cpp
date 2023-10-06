#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mSideBar = new PlayScreenUI();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH - (541.0f / 2), Graphics::SCREEN_HEIGHT * 0.5f);

	mAudio = AudioManager::Instance();
	mTimer = new Timer();
}

PlayScreen::~PlayScreen() {
	mAudio = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mSideBar;
	mSideBar = nullptr;
}

void PlayScreen::Update() {
	mTimer->Update();
	mSideBar->Update();

	if (mTimer->TotalTime() > 60.0f) {
		mMusicSelection++;
		mAudio->PlaySFX("MUS/BackgroundMusic" + std::to_string(mMusicSelection) + ".wav", 0, 5);
		mTimer->Reset();

		if (mMusicSelection >= 1) {
			mMusicSelection = -1;
		}
	}
}

void PlayScreen::Render() {
	mSideBar->Render();
}
