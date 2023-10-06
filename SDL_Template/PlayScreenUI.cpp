#include "PlayScreenUI.h"

PlayScreenUI::PlayScreenUI() {
	mPlayer = Player::Instance();

	mDisplay = new GameEntity();
	mDisplay->Position(Vector2(Vec2_Zero));

	mDisplayLevel = new Scoreboard({ 255, 216, 0 });
	mDisplayLevel->Parent(mDisplay);
	mDisplayLevel->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f + 100.0f, 26.0f));

	mDisplayScore = new Scoreboard({ 255, 0, 0 });
	mDisplayScore->Parent(mDisplay);
	mDisplayScore->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 70.0f));
}

PlayScreenUI::~PlayScreenUI() {
	mPlayer = nullptr;

	delete mDisplay;
	mDisplay = nullptr;
	delete mDisplayLevel;
	mDisplayLevel = nullptr;
	delete mDisplayScore;
	mDisplayScore = nullptr;
}

void PlayScreenUI::Update() {
	mDisplayLevel->Score(mPlayer->level());
	mDisplayScore->Score(mPlayer->score());
}

void PlayScreenUI::Render() {
	mDisplayLevel->Render();
	mDisplayScore->Render();
}