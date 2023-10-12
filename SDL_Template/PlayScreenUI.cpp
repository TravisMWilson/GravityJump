#include "PlayScreenUI.h"

PlayScreenUI::PlayScreenUI() {
	mPlayer = Player::Instance();

	mDisplay = new GameEntity();
	mDisplay->Position(Vector2(Vec2_Zero));

	mDisplayHiScore = new Scoreboard({ 255, 216, 0 });
	mDisplayHiScore->Parent(mDisplay);
	mDisplayHiScore->Position(Vector2(Graphics::SCREEN_WIDTH - 20.0f, 25.0f));

	mDisplayScore = new Scoreboard({ 255, 0, 0 });
	mDisplayScore->Parent(mDisplay);
	mDisplayScore->Position(Vector2(Graphics::SCREEN_WIDTH - 20.0f, 60.0f));
}

PlayScreenUI::~PlayScreenUI() {
	mPlayer = nullptr;

	delete mDisplay;
	mDisplay = nullptr;
	delete mDisplayHiScore;
	mDisplayHiScore = nullptr;
	delete mDisplayScore;
	mDisplayScore = nullptr;
}

void PlayScreenUI::Update() {
	mDisplayHiScore->Score(mPlayer->hiScore());
	mDisplayScore->Score(mPlayer->score());
}

void PlayScreenUI::Render() {
	mDisplayHiScore->Render();
	mDisplayScore->Render();
}