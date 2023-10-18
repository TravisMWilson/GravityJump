#include "Bird.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Bird::IgnoreCollisions() {
	return !Active();
}

Bird::Bird() {
	mEvent = EventManager::Instance();
	mRand = Random::Instance();
	mTimer = new Timer();

	mSpeed = 400.0f;

	mTexture = new AnimatedGLTexture("Bird.png", 0, 0, 240, 269, 22, 1.0f);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(0.2f, 0.2f));

	mBirdTimer = new Scoreboard({ 30, 30, 30 });
	mBirdTimer->Position(Graphics::SCREEN_WIDTH * 0.5f, 50.0f);
	
	Active(true);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Bird);
}

Bird::~Bird() {
	mRand = nullptr;
	mEvent = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mBirdTimer;
	mBirdTimer = nullptr;

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Bird::move() {
	Translate(Vec2_Right * mSpeed * mTimer->DeltaTime());

	if (Active()) {
		if (Position().x >= Graphics::SCREEN_WIDTH - mTexture->ScaledDimensions().x) {
			mTexture->Scale(Vector2(0.2f, 0.2f));
			Rotation(mRand->RandomRange(-30.0f, 30.0f));
			mSpeed = -mSpeed;
			Active(false);
		}
		else if (Position().x <= -mTexture->ScaledDimensions().x) {
			mTexture->Scale(Vector2(-0.2f, 0.2f));
			Rotation(mRand->RandomRange(-30.0f, 30.0f));
			mSpeed = -mSpeed;
			Active(false);
		}
	}
	else {
		if (Position().x < Graphics::SCREEN_WIDTH - mTexture->ScaledDimensions().x
			&& Position().x > -mTexture->ScaledDimensions().x) {
			Active(true);
		}
	}

	if (Position().y + 200 >= Graphics::SCREEN_HEIGHT + mTexture->ScaledDimensions().y) {
		if (mTexture->Scale().x > 0) {
			Rotate(2);
		}
		else {
			Rotate(-2);
		}
	}
	else if (Position().y - 200 <= -mTexture->ScaledDimensions().y) {
		if (mTexture->Scale().x > 0) {
			Rotate(-2);
		}
		else {
			Rotate(2);
		}
	}
}

void Bird::resetBirdTimer() {
	mTimer->Reset();
}

void Bird::Hit(PhysEntity* other) {
	mTimer->Reset();
}

void Bird::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "ResetBirdTimer") {
			resetBirdTimer();
			mEvent->removeEvent(i);
		}
	}
}

void Bird::Update() {
	mTimer->Update();

	move();
	mTexture->Update();

	if (mTimer->TotalTime() >= 20.0f) {
		mEvent->sendEvent("GameOver");
		mTimer->Reset();
	}

	mBirdTimer->Score(FormatTime(20.0f - mTimer->TotalTime()), Scoreboard::ScorePlacement::CENTER);

	processEvents();
}

void Bird::Render() {
	mBirdTimer->Render();
	mTexture->Render();

	PhysEntity::Render();
}