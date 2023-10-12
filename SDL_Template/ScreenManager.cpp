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

void ScreenManager::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "Start") {
			mCurrentScreen = Play;
			mEvent->sendEvent("ActivatePlayer");
			mEvent->removeEvent(i);
		}
		else if (events[i] == "GameOver") {
			mCurrentScreen = Start;
			delete mPlayScreen;
			mPlayScreen = new PlayScreen();
			mEvent->removeEvent(i);
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
	processEvents();

	if (mTimer->TotalTime() > 85.0f) {
		mMusicSelection++;
		mAudio->PlaySFX("MUS/BackgroundMusic" + std::to_string(mMusicSelection) + ".wav", 0, 1);
		mTimer->Reset();

		if (mMusicSelection >= 9) {
			mMusicSelection = -1;
		}
	}

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();
		break;
	case Play:
		mPlayScreen->Update();
		break;
	}

	Vector2 mousePosition = mInput->MousePosition();
	mCursor->Position(mousePosition);



	mTimer->Reset();
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
	}

	mCursor->Render();
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mAudio = AudioManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = Start;

	mCursor = new GLTexture("GravityJump.png", 1, 144, 4, 4);
	mCursor->Position(Vec2_Zero);

	mBackground = new GLTexture("Background.png");
	mBackground->Position(Vector2(0.0f, Graphics::SCREEN_HEIGHT / 2));

	mMusicSelection = 0;

	mAudio->PlaySFX("MUS/BackgroundMusic1.wav", 0, 1);
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;
	mEvent = nullptr;
	mAudio = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mCursor;
	mCursor = nullptr;

	delete mBackground;
	mBackground = nullptr;
}