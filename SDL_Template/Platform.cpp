#include "Platform.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Platform::IgnoreCollisions() {
	return !Active();
}

Platform::Platform() {
	mRand = Random::Instance();

	mTexture = new GLTexture("GravityJump.png", 1, 1159, 192, 40);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mTag = "Platform";

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Platform);

	placePlatform();
}

Platform::~Platform() {
	mRand = nullptr;

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

void Platform::Hit(PhysEntity* other) {
	
}

void Platform::Update() {
	checkPlatformPosition();
}

void Platform::Render() {
	mTexture->Render();
}