#include "StartScreen.h"

StartScreen::StartScreen() {
	mAnimatedLogo = new AnimatedGLTexture("GravityJump.png", 0, 0, 700, 900, 15, 1.2f, Animation::Layouts::Horizontal);
	mAnimatedLogo->Parent(this);
	mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);

	mStart = new Button("Start", new GLTexture("START", "galagafont.ttf", 80, { 230, 230, 230 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f + 35.0f);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mBottomBar->Parent(this);

	mNamco = new GLTexture("travis wilson", "galagafont.ttf", 36, { 200, 0, 0 });
	mNamco->Parent(mBottomBar);
	mNamco->Position(Vec2_Zero);

	mDates = new GLTexture("2023 PURPLE STUDIOS", "galagafont.ttf", 80, { 230, 230, 230 });
	mDates->Parent(mBottomBar);
	mDates->Position(0.0f, 90.0f);
}

StartScreen::~StartScreen() {
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;

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
	mAnimatedLogo->Render();
	mStart->Render();
	mNamco->Render();
	mDates->Render();
}