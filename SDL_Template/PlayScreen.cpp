#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mRand = Random::Instance();
	mTimer = new Timer();

	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mPlayer->Active(false);

	mSideBar = new PlayScreenUI();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH - (541.0f / 2), Graphics::SCREEN_HEIGHT * 0.5f);

	mMusicSelection = 0;

	//mAudio->PlaySFX("MUS/BackgroundMusic1.wav", 0, 1);
}

PlayScreen::~PlayScreen() {
	mAudio = nullptr;
	mRand = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mSideBar;
	mSideBar = nullptr;
}

void PlayScreen::newPlatform() {
	if ((mPlatforms.size() < 10 && mRand->RandomRange(0, 100) == 0) || mPlatforms.size() < 3) {
		mPlatforms.push_back(new Platform());
		mPlatforms.back()->Parent(this);
	}
}

void PlayScreen::removePlatforms() {
	for (int i = mPlatforms.size() - 1; i >= 0; i--) {
		if (!mPlatforms[i]->Active()) {
			delete mPlatforms[i];
			mPlatforms[i] = nullptr;
			mPlatforms.erase(mPlatforms.begin() + i);
		}
	}
}

void PlayScreen::Update() {
	mTimer->Update();
	mSideBar->Update();

	if (mTimer->TotalTime() > 60.0f) {
		mMusicSelection++;
		//mAudio->PlaySFX("MUS/BackgroundMusic" + std::to_string(mMusicSelection) + ".wav", 0, 1);
		mTimer->Reset();

		if (mMusicSelection >= 1) {
			mMusicSelection = 0;
		}
	}

	newPlatform();

	for (auto* platform : mPlatforms) {
		platform->Translate(Vec2_Up * 100.0f * mTimer->DeltaTime());
		platform->Update();
	}

	removePlatforms();

	mPlayer->Update();
}

void PlayScreen::Render() {
	for (auto* platform : mPlatforms) {
		platform->Render();
	}

	mSideBar->Render();
	mPlayer->Render();
}
