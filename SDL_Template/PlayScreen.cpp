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

	mTarget = new AnimatedGLTexture("Target.png", 0, 0, 736, 736, 4, 4.0f, Animation::Layouts::Horizontal);
	mTarget->Parent(this);
	mTarget->SetWrapMode(Animation::WrapModes::Once);
	mTarget->Active(false);

	mExplosion = new AnimatedGLTexture("Explosion.png", 0, 0, 512, 736, 48, 2.0f, Animation::Layouts::Horizontal);
	mExplosion->Parent(this);
	mExplosion->SetWrapMode(Animation::WrapModes::Once);
	mExplosion->Active(false);
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

	delete mTarget;
	mTarget = nullptr;

	delete mExplosion;
	mExplosion = nullptr;

	for (auto* platform : mPlatforms) {
		delete platform;
		platform = nullptr;
	}

	mPlatforms.clear();
}

void PlayScreen::newPlatform() {
	if ((mPlatforms.size() < 15 && mRand->RandomRange(0, 100) == 0) || mPlatforms.size() < 5) {
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

void PlayScreen::Update() {
	mTimer->Update();
	mSideBar->Update();

	newPlatform();

	for (auto* platform : mPlatforms) {
		platform->Update();
	}

	removePlatforms();

	mPlayer->Update();
	mPlayer->score(1);

	if (mRand->RandomRange(0, 100) == 0 && !mTarget->Active() && !mExplosion->Active()) {
		mTarget->Position(mRand->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH), mRand->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT));
		mExplosion->Position(mTarget->Position());
		mTarget->Scale(Vector2(0.0f, 0.0f));
		mTarget->ResetAnimation();
		mTarget->Active(true);
	}

	if (mTarget->Active()) {
		if (mTarget->Scale().x < 1.0f) {
			mTarget->Scale(mTarget->Scale() + Vector2(0.025f, 0.025f));
		}

		mTarget->Update();

		if (!mTarget->IsAnimating()) {
			mTarget->Active(false);
			mExplosion->ResetAnimation();
			mExplosion->Active(true);

			if (CheckCollision(mPlayer->Position(), mExplosion->Position(), (int)(mExplosion->ScaledDimensions().y * 0.5f))) {
				mPlayer->Active(false);
			}

			for (auto* platform : mPlatforms) {
				if (CheckCollision(platform->Position(), mExplosion->Position(), (int)(mExplosion->ScaledDimensions().y * 0.55f))) {
					platform->breakPlatform();
				}
			}
		}
	}

	if (mExplosion->Active()) {
		mExplosion->Update();

		if (!mExplosion->IsAnimating()) {
			mExplosion->Active(false);
		}
	}

	if (!mPlayer->Active()) {
		if (mPlayer->score() > mPlayer->hiScore()) {
			mPlayer->hiScore(mPlayer->score());
		}

		mEvent->sendEvent("GameOver");
	}
}

void PlayScreen::Render() {
	for (auto* platform : mPlatforms) {
		platform->Render();
	}

	mSideBar->Render();
	mPlayer->Render();

	if (mTarget->Active()) {
		mTarget->Render();
	}

	if (mExplosion->Active()) {
		mExplosion->Render();
	}
}
