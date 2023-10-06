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
			mStartScreen->ResetAnimation();
			mEvent->removeEvent(i);

			mAudio->PlaySFX("MUS/Chiptune0.wav", 0, 5);
		}
	}
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	processEvents();

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
}

void ScreenManager::Render() {
	mBackgroundStars->Render();

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

	mBackgroundStars = BackgroundStars::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = Start;

	mCursor = new GLTexture("Cursor.png");
	mCursor->Position(Vec2_Zero);

	mAudio->PlaySFX("MUS/GameStart.wav", 0, 4);
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;
	mEvent = nullptr;
	mAudio = nullptr;

	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mCursor;
	mCursor = nullptr;
}