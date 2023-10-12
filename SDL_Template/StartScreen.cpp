#include "StartScreen.h"

StartScreen::StartScreen() {
	mAnimatedLogo = new AnimatedGLTexture("GravityJumpLogo.png", 0, 0, 615, 282, 25, 2.0f, Animation::Layouts::Horizontal);
	mAnimatedLogo->Parent(this);
	mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);

	mLogoBackground = new GLTexture("GravityJumpLogoBackground.png");
	mLogoBackground->Parent(this);
	mLogoBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);

	mStart = new Button("Start", new GLTexture("START", "AovelSansRounded-rdDL.ttf", 48, { 30, 30, 30 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f + 35.0f);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mBottomBar->Parent(this);

	mNamco = new GLTexture("Travis Wilson", "Copenhagen-z3Z0.ttf", 60, { 66, 109, 107 });
	mNamco->Parent(mBottomBar);
	mNamco->Position(Vec2_Zero);

	mDates = new GLTexture("2023 PURPLE STUDIOS", "AovelSansRounded-rdDL.ttf", 48, { 30, 30, 30 });
	mDates->Parent(mBottomBar);
	mDates->Position(0.0f, 90.0f);
}

StartScreen::~StartScreen() {
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;
	delete mLogoBackground;
	mLogoBackground = nullptr;

	delete mStart;
	mStart = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mNamco = nullptr;
	delete mDates;
	mDates = nullptr;
}

void StartScreen::Update() {
	mAnimatedLogo->Update();
	mStart->Update();
}

void StartScreen::Render() {
	mLogoBackground->Render();
	mAnimatedLogo->Render();
	mStart->Render();
	mNamco->Render();
	mDates->Render();
}