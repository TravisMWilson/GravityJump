#include "TutorialScreen.h"

TutorialScreen::TutorialScreen() {
	mBackground = new GLTexture("GravityJumpLogoBackground.png", 170, 170, 1, 1);
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mBackground->Scale(Vector2(900.0f, 900.0f));

	mStart = new Button("Start", new GLTexture("START", "AovelSansRounded-rdDL.ttf", 48, { 230, 230, 230 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.9f);
}

TutorialScreen::~TutorialScreen() {
	delete mStart;
	mStart = nullptr;
}

void TutorialScreen::Update() {
	mBackground->Update();
	mStart->Update();
}

void TutorialScreen::Render() {
	mBackground->Render();
	mStart->Render();
}