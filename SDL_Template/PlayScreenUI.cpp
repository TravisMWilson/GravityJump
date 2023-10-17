#include "PlayScreenUI.h"

PlayScreenUI::PlayScreenUI() {
	mEvent = EventManager::Instance();
	mPlayer = Player::Instance();
	mTimer = new Timer();

	mGameOver = false;

	mDisplay = new GameEntity();
	mDisplay->Position(Vector2(Graphics::SCREEN_WIDTH - 20.0f, 25.0f));

	mDisplayHiScore = new Scoreboard({ 255, 216, 0 });
	mDisplayHiScore->Parent(mDisplay);
	mDisplayHiScore->Position(Vec2_Zero);

	mDisplayScore = new Scoreboard({ 255, 0, 0 });
	mDisplayScore->Parent(mDisplay);
	mDisplayScore->Position(Vector2(0.0f, 35.0f));

	mGameOverDisplay = new GameEntity();
	mGameOverDisplay->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mGameOverMessage = new GLTexture("GameOver.png");
	mGameOverMessage->Parent(mGameOverDisplay);
	mGameOverMessage->Position(Vector2(0.0f, -150.0f));

	mGameOverHiScore = new Scoreboard({ 255, 216, 0 });
	mGameOverHiScore->Parent(mGameOverDisplay);
	mGameOverHiScore->Position(Vector2(0.0f, 50.0f));

	mGameOverScore = new Scoreboard({ 255, 0, 0 });
	mGameOverScore->Parent(mGameOverDisplay);
	mGameOverScore->Position(Vector2(0.0f, 100.0f));
}

PlayScreenUI::~PlayScreenUI() {
	mEvent = nullptr;
	mPlayer = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mDisplay;
	mDisplay = nullptr;
	delete mDisplayHiScore;
	mDisplayHiScore = nullptr;
	delete mDisplayScore;
	mDisplayScore = nullptr;

	delete mGameOverDisplay;
	mGameOverDisplay = nullptr;
	delete mGameOverMessage;
	mGameOverMessage = nullptr;
	delete mGameOverHiScore;
	mGameOverHiScore = nullptr;
	delete mGameOverScore;
	mGameOverScore = nullptr;
}

void PlayScreenUI::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "DisplayGameOver") {

			if (!mGameOver) {
				mTimer->CompleteReset();
			}

			mGameOver = true;
			mGameOverHiScore->Score("Hiscore: " + std::to_string(mPlayer->hiScore()), Scoreboard::CENTER);
			mGameOverScore->Score("Score: " + std::to_string(mPlayer->score()), Scoreboard::CENTER);

			if (mTimer->TotalTime() >= 4.0f) {
				mGameOver = false;
				mEvent->sendEvent("BackToStart");
				mEvent->removeEvent(i);
			}
		}
	}
}

void PlayScreenUI::Update() {
	mTimer->Update();

	if (!mGameOver) {
		mDisplayHiScore->Score(mPlayer->hiScore());
		mDisplayScore->Score(mPlayer->score());
	}

	processEvents();
}

void PlayScreenUI::Render() {
	if (mGameOver) {
		mGameOverMessage->Render();
		mGameOverHiScore->Render();
		mGameOverScore->Render();
	}
	else {
		mDisplayHiScore->Render();
		mDisplayScore->Render();
	}
}