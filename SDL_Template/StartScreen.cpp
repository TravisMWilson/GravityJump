#include "StartScreen.h"

StartScreen::StartScreen() {
	mInput = InputManager::Instance();
	mTimer = new Timer();

	mLogo = new GLTexture("GalagaLogo.png", 0, 0, 504, 346);
	mAnimatedLogo = new AnimatedGLTexture("GalagaLogo.png", 0, 0, 504, 346, 3, 0.5f, Animation::Layouts::Vertical);
	
	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

	mStart = new Button("Start", new GLTexture("START", "galagafont.ttf", 80, { 230, 230, 230 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f + 35.0f);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mNamco = new GLTexture("travis wilson", "namco__.ttf", 36, { 200, 0, 0 });
	mDates = new GLTexture("2023 PURPLE STUDIOS", "galagafont.ttf", 80, { 230, 230, 230 });

	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);

	mNamco->Position(Vec2_Zero);
	mDates->Position(0.0f, 90.0f);

	ResetAnimation();

	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen() {
	delete mLogo;
	mLogo = nullptr;
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

	delete mTimer;
	mTimer = nullptr;
	mInput = nullptr;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}

void StartScreen::Update() {
	mTimer->Update();

	if (!mAnimationDone) {
		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			mTimer->Reset();
		}

		Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
		mAnimationTimer = mTimer->TotalTime();
		
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else {
		mAnimatedLogo->Update();

		if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {

		}
	}

	mStart->Update();
}

void StartScreen::Render() {
	if (!mAnimationDone) {
		mLogo->Render();
	}
	else {
		mAnimatedLogo->Render();
	}

	mStart->Render();

	mNamco->Render();
	mDates->Render();
}