#include "Platform.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Platform::IgnoreCollisions() {
	return !Active();
}

Platform::Platform() {
	mRand = Random::Instance();
	mTimer = new Timer();

	mTexture = new GLTexture("GravityJump.png", 1, 214, 192, 40);
	mTexture->Scale(Vector2(mRand->RandomRange(0.8f, 1.2f), mRand->RandomRange(0.8f, 1.2f)));
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mBreakupTexture = new AnimatedGLTexture("GravityJump.png", 194, 124, 233, 131, 4, 0.5f, Animation::Layouts::Horizontal);
	mBreakupTexture->Parent(this);
	mBreakupTexture->SetWrapMode(Animation::WrapModes::Once);
	mBreakupTexture->Position(Vec2_Zero);

	mTag = "Platform";
	mBreaking = false;
	mSpeed = mRand->RandomRange(50.0f, 150.0f);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Platform);

	placePlatform();
}

Platform::~Platform() {
	mRand = nullptr;
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Platform::placePlatform() {
	float randomAngle = mRand->RandomRange(0, 3) * 90.0f;

	if (randomAngle == 0) {
		Position(Vector2(mRand->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH), (float)Graphics::SCREEN_HEIGHT));
		mTag = "Up";
	}
	else if (randomAngle == 90) {
		Position(Vector2(0.0f, mRand->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT)));
		mTag = "Right";
	}
	else if (randomAngle == 180) {
		Position(Vector2(mRand->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH), 0.0f));
		mTag = "Down";
	}
	else if (randomAngle == 270) {
		Position(Vector2((float)Graphics::SCREEN_WIDTH, mRand->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT)));
		mTag = "Left";
	}

	Rotation(randomAngle);
}

void Platform::checkPlatformPosition() {
	if (Position().y > Graphics::SCREEN_HEIGHT + (mTexture->ScaledDimensions().y * 0.5f)) {
		Active(false);
	}
	else if (Position().y < -mTexture->ScaledDimensions().y * 0.5f) {
		Active(false);
	}

	if (Position().x > Graphics::SCREEN_WIDTH + (mTexture->ScaledDimensions().x * 0.5f)) {
		Active(false);
	}
	else if (Position().x < -mTexture->ScaledDimensions().x * 0.5f) {
		Active(false);
	}
}

void Platform::breakPlatform() {
	mBreakupTexture->ResetAnimation();
	mBreaking = true;
}

bool Platform::isBreaking() {
	return mBreaking;
}

void Platform::Hit(PhysEntity* other) {
	
}

void Platform::Update() {
	mTimer->Update();

	checkPlatformPosition();

	if (mBreaking) {
		mBreakupTexture->Update();

		if (!mBreakupTexture->IsAnimating()) {
			Active(false);
		}
	}
	else {
		Translate(Vec2_Up * mSpeed * mTimer->DeltaTime());
	}

	mTimer->Reset();
}

void Platform::Render() {
	if (mBreaking) {
		mBreakupTexture->Render();
	}
	else {
		mTexture->Render();
	}
}