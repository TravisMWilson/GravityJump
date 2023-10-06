#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mGameSpace = new GameSpace(false, 0.02f);
	mGameSpace->Parent(this);
	mGameSpace->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mGameSpace->Scroll(true);

	mDecorationSpace = new GameSpace(true, 0.01f);
	mDecorationSpace->Parent(this);
	mDecorationSpace->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mDecorationSpace->Scroll(true);

	mSideBar = new PlayScreenUI(mGameSpace->player());
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH - (541.0f / 2), Graphics::SCREEN_HEIGHT * 0.5f);

	mStars = BackgroundStars::Instance();
	mAudio = AudioManager::Instance();
	mTimer = new Timer();
}

PlayScreen::~PlayScreen() {
	mAudio = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	delete mGameSpace;
	mGameSpace = nullptr;

	delete mDecorationSpace;
	mDecorationSpace = nullptr;
}

void PlayScreen::Update() {
	mTimer->Update();

	if (mSideBar->inShop()) {
		mDecorationSpace->Scroll(false);
		mGameSpace->Scroll(false);
		mStars->Scroll(false);
	}
	else {
		mDecorationSpace->Scroll(true);
		mGameSpace->Scroll(true);
		mStars->Scroll(true);
	}

	mDecorationSpace->Update();
	mGameSpace->Update();
	mSideBar->Update();

	mSideBar->enemiesLeft(mGameSpace->enemyCount());

	if (mTimer->TotalTime() > 60.0f) {
		mMusicSelection++;
		mAudio->PlaySFX("MUS/Chiptune" + std::to_string(mMusicSelection) + ".wav", 0, 5);
		mTimer->Reset();

		if (mMusicSelection >= 9) {
			mMusicSelection = -1;
		}
	}
}

void PlayScreen::Render() {
	mDecorationSpace->Render();
	mGameSpace->Render();
	mSideBar->Render();
}
