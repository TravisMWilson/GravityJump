#include "TutorialScreen.h"

TutorialScreen::TutorialScreen() {
	mBackground = new GLTexture("GravityJumpLogoBackground.png", 170, 170, 1, 1);
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mBackground->Scale(Vector2(900.0f, 900.0f));

	mStart = new Button("Start", new GLTexture("START", "AovelSansRounded-rdDL.ttf", 48, { 230, 230, 230 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.9f);
	
	mPlayerAnimation = new AnimatedGLTexture("GravityJump.png", 0, 0, 79, 102, 6, 0.5f);
	mPlayerAnimation->Parent(this);
	mPlayerAnimation->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.1f);
	mPlayerAnimation->ScaleToPixelHeight(mPlayerAnimation->ScaledDimensions(), 80.0f);

	mMoveDescription = new GLTexture("Move the player using W, A, S, D", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mMoveDescription->Parent(this);
	mMoveDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerTexture = new GLTexture("GravityJump.png", 632, 0, 79, 102);
	mPlayerTexture->Parent(this);
	mPlayerTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.2f);
	mPlayerTexture->ScaleToPixelHeight(mPlayerTexture->ScaledDimensions(), 80.0f);

	mGravityDescription = new GLTexture("Change gravity using the arrow keys", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mGravityDescription->Parent(this);
	mGravityDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.2f);

	mScoreTexture = new Scoreboard({ 255, 0, 0 });
	mScoreTexture->Parent(this);
	mScoreTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.3f);
	mScoreTexture->Score(123, Scoreboard::CENTER);

	mScoreDescription = new GLTexture("You gain score by surviving as long as you can", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mScoreDescription->Parent(this);
	mScoreDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.3f);

	mPlatformTexture = new GLTexture("GravityJump.png", 1, 214, 192, 40);
	mPlatformTexture->Parent(this);
	mPlatformTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.4f);
	mPlatformTexture->ScaleToPixelWidth(mPlatformTexture->ScaledDimensions(), 80.0f);
	mPlatformTexture->Rotation(180.0f);

	mPlatformDescription = new GLTexture("Jump on the platforms to avoid falling", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mPlatformDescription->Parent(this);
	mPlatformDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.4f);

	mSpikesTexture = new GLTexture("GravityJump.png", 971, 1, 162, 81);
	mSpikesTexture->Parent(this);
	mSpikesTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.5f);
	mSpikesTexture->ScaleToPixelWidth(mSpikesTexture->ScaledDimensions(), 80.0f);

	mSpikesDescription = new GLTexture("Avoid the spikes", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mSpikesDescription->Parent(this);
	mSpikesDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f);

	mTargetTexture = new AnimatedGLTexture("Target.png", 0, 0, 736, 736, 4, 4.0f);
	mTargetTexture->Parent(this);
	mTargetTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.6f);
	mTargetTexture->ScaleToPixelHeight(mTargetTexture->ScaledDimensions(), 80.0f);

	mTargetDescription = new GLTexture("Once the timer ends everything in this space will explode", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mTargetDescription->Parent(this);
	mTargetDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.6f);

	mExplosionTexture = new AnimatedGLTexture("Explosion.png", 0, 0, 512, 736, 48, 2.0f);
	mExplosionTexture->Parent(this);
	mExplosionTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.7f);
	mExplosionTexture->ScaleToPixelHeight(mExplosionTexture->ScaledDimensions(), 80.0f);

	mExplosionDescription = new GLTexture("Fire goes boom", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mExplosionDescription->Parent(this);
	mExplosionDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.7f);

	mBirdTexture = new AnimatedGLTexture("Bird.png", 0, 0, 240, 269, 22, 1.0f);
	mBirdTexture->Parent(this);
	mBirdTexture->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.8f);
	mBirdTexture->ScaleToPixelHeight(mBirdTexture->ScaledDimensions(), 80.0f);

	mBirdDescription = new GLTexture("Catch the bird to reset the timer, if it runs out you loose", "AovelSansRounded-rdDL.ttf", 24, { 230, 230, 230 });
	mBirdDescription->Parent(this);
	mBirdDescription->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.8f);
}

TutorialScreen::~TutorialScreen() {
	delete mStart;
	mStart = nullptr;
}

void TutorialScreen::Update() {
	mBackground->Update();
	mStart->Update();
	mPlayerAnimation->Update();
	mTargetTexture->Update();
	mExplosionTexture->Update();
	mBirdTexture->Update();
}

void TutorialScreen::Render() {
	mBackground->Render();
	mPlayerAnimation->Render();
	mMoveDescription->Render();
	mPlayerTexture->Render();
	mGravityDescription->Render();
	mScoreTexture->Render();
	mScoreDescription->Render();
	mPlatformTexture->Render();
	mPlatformDescription->Render();
	mSpikesTexture->Render();
	mSpikesDescription->Render();
	mTargetTexture->Render();
	mTargetDescription->Render();
	mExplosionTexture->Render();
	mExplosionDescription->Render();
	mBirdTexture->Render();
	mBirdDescription->Render();
	mStart->Render();
}