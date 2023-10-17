 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::playMusic() {
	if (mTimer->TotalTime() > 85.0f) {
		mMusicSelection++;
		mAudio->PlaySFX("MUS/BackgroundMusic" + std::to_string(mMusicSelection) + ".wav", 0, 1);
		mTimer->Reset();

		if (mMusicSelection >= 9) {
			mMusicSelection = -1;
		}
	}
}

void ScreenManager::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "Start") {
			mPlayScreen = new PlayScreen();
			mCurrentScreen = Play;
			mEvent->sendEvent("ActivatePlayer");
			mEvent->sendEvent("ResetBirdTimer");
			mEvent->removeEvent(i);
		}
		else if (events[i] == "Tutorial") {
			mCurrentScreen = Tutorial;
			mEvent->removeEvent(i);
		}
		else if (events[i] == "BackToStart") {
			mCurrentScreen = Start;
			mEvent->clearEvents();
			delete mPlayScreen;
		}
	}
}

void ScreenManager::moveBackground() {
	mBackground->Translate(Vector2(-1.0f, 0.0f));

	if (mBackground->Position().x + (mBackground->ScaledDimensions().x / 2) <= Graphics::SCREEN_WIDTH) {
		mBackground->Position(Vector2(((mBackground->ScaledDimensions().x / 2)) - 900, Graphics::SCREEN_HEIGHT / 2));
	}
}

void ScreenManager::Update() {
	mTimer->Update();

	moveBackground();
	playMusic();
	processEvents();

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();
		break;
	case Play:
		mPlayScreen->Update();
		break;
	case Tutorial:
		mTutorialScreen->Update();
		break;
	}

	Vector2 mousePosition = mInput->MousePosition();
	mCursor->Position(mousePosition);
}

void ScreenManager::Render() {
	mBackground->Render();

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	case Tutorial:
		mTutorialScreen->Render();
		break;
	}

	mCursor->Render();
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mAudio = AudioManager::Instance();
	mTimer = new Timer();

	mStartScreen = new StartScreen();
	mPlayScreen = nullptr;
	mTutorialScreen = new TutorialScreen();

	mCurrentScreen = Start;

	mCursor = new GLTexture("GravityJump.png", 1, 144, 4, 4);
	mCursor->Position(Vec2_Zero);

	mBackground = new GLTexture("Background.png");
	mBackground->Position(Vector2(0.0f, Graphics::SCREEN_HEIGHT / 2));

	mMusicSelection = 0;

	mAudio->PlaySFX("MUS/BackgroundMusic0.wav", 0, 1);
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;
	mEvent = nullptr;
	mAudio = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	if (mPlayScreen != nullptr) {
		delete mPlayScreen;
		mPlayScreen = nullptr;
	}

	delete mCursor;
	mCursor = nullptr;

	delete mBackground;
	mBackground = nullptr;
}