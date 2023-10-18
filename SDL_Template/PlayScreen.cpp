#include "PlayScreen.h"
#include "PhysicsHelper.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mRand = Random::Instance();
	mTimer = new Timer();

	mPlayer = Player::Instance();
	mPlayer->resetPlayer();

	mSideBar = new PlayScreenUI();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH - (541.0f / 2), Graphics::SCREEN_HEIGHT * 0.5f);

	mExplosion = new Explosion();
	mExplosion->Parent(this);

	mBird = new Bird();
	mBird->Parent(this);
	mBird->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
}

PlayScreen::~PlayScreen() {
	mRand = nullptr;
	mEvent = nullptr;
	mInput = nullptr;
	mPlayer = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	delete mExplosion;
	mExplosion = nullptr;

	delete mBird;
	mBird = nullptr;

	for (auto* platform : mPlatforms) {
		delete platform;
		platform = nullptr;
	}

	mPlatforms.clear();
}

void PlayScreen::newPlatform() {
	if ((mPlatforms.size() < 10 && mRand->RandomRange(0, 50) == 0) || mPlatforms.size() < 4) {
		mPlatforms.push_back(new Platform());
		mPlatforms.back()->Parent(this);
	}
}

void PlayScreen::removePlatforms() {
	for (int i = (int)mPlatforms.size() - 1; i >= 0; i--) {
		if (!mPlatforms[i]->Active()) {
			delete mPlatforms[i];
			mPlatforms[i] = nullptr;
			mPlatforms.erase(mPlatforms.begin() + i);
		}
	}
}

void PlayScreen::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "GameOver") {
			Active(false);

			if (mPlayer->score() >= mPlayer->hiScore()) {
				mPlayer->hiScore(mPlayer->score());
			}

			mEvent->sendEvent("DisplayGameOver");
			mEvent->removeEvent(i);
		}
	}
}

void PlayScreen::Update() {
	mTimer->Update();
	mSideBar->Update();

	if (Active()) {

		newPlatform();

		for (auto* platform : mPlatforms) {
			platform->Update();
		}

		removePlatforms();

		mPlayer->Update();
		mPlayer->score(1);

		mBird->Update();

		mExplosion->Update();

		if (mExplosion->Active()) {
			if (CheckCollision(mPlayer->Position(), mExplosion->Position(), (int)(mExplosion->scaledDimensions().y * 0.5f))) {
				mPlayer->Active(false);
			}

			for (auto* platform : mPlatforms) {
				if (CheckCollision(platform->Position(), mExplosion->Position(), (int)(mExplosion->scaledDimensions().y * 0.55f))) {
					platform->breakPlatform();
				}
			}

			mExplosion->Active(false);
		}

		if (!mPlayer->Active()) {
			mEvent->sendEvent("GameOver");
		}
	}

	processEvents();
}

void PlayScreen::Render() {
	for (auto* platform : mPlatforms) {
		platform->Render();
	}

	mSideBar->Render();

	if (Active()) {
		mPlayer->Render();
		mBird->Render();
		mExplosion->Render();
	}
}
