#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

#include <iostream>
#include <fstream>
#include <limits>

Player* Player::sInstance = nullptr;

Player* Player::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Player();
	}

	return sInstance;
}

void Player::Release() {
	delete sInstance;
	sInstance = nullptr;
}

bool Player::IgnoreCollisions() {
	return !Active();
}

Player::Player() {
	mEvent = EventManager::Instance();
	mInput = InputManager::Instance();
	mTimer = new Timer();

	mTexture = new GLTexture("GravityJump.png", 1, 1064, 54, 90);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mGravity = DOWN;

	mCanSwitchGravity = true;
	mJumpingTimer = 0;
	mGravityTimer = 0;
	mLevel = 1;
	mScore = 0;

	loadData();

	AddCollider(new BoxCollider(Vector2(40.0f, 80.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Player);
}

Player::~Player() {
	mEvent = nullptr;
	mInput = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Player::move() {
	if (Rotation() == mRotationalGoal) {
		if (mInput->KeyDown(SDL_SCANCODE_W)) {
			if (mGravity == Player::DOWN) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::LEFT) {
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::RIGHT) {
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_S)) {
			if (mGravity == Player::UP) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::LEFT) {
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::RIGHT) {
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_A)) {
			if (mGravity == Player::RIGHT) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::DOWN) {
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::UP) {
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_D)) {
			if (mGravity == Player::LEFT) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::DOWN) {
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::UP) {
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		Translate(-Vec2_Up * 500.0f * mTimer->DeltaTime());
	}
}

void Player::changeGravity() {
	if (mGravityTimer > 0.0f) {
		mGravityTimer += mTimer->DeltaTime();
	}

	if (Rotation() != mRotationalGoal) {
		Rotate(500.0f * mTimer->DeltaTime());

		if (Rotation() <= mRotationalGoal + 20.0f && mTexture->Rotation() >= mRotationalGoal - 20.0f) {
			Rotation(mRotationalGoal);
		}
	}

	if (mGravityTimer <= 0.0f && mCanSwitchGravity) {
		if (mInput->KeyDown(SDL_SCANCODE_UP)) {
			mGravity = UP;
			mRotationalGoal = 180.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
			mGravity = DOWN;
			mRotationalGoal = 0.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
			mGravity = LEFT;
			mRotationalGoal = 90.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
			mGravity = RIGHT;
			mRotationalGoal = 270.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}
	}
}

int Player::gravity() {
	return mGravity;
}

void Player::gravity(int direction) {
	mGravity = direction;
}

int Player::score() {
	return mScore;
}

void Player::score(int amount) {
	mScore += amount;
}

int Player::level() {
	return mLevel;
}

void Player::level(int level) {
	mLevel += level;
	saveData();
}

void Player::Hit(PhysEntity* other) {
	if (other->tag() == "Up") {
		if (mGravity == Player::UP && Position().y - (mTexture->ScaledDimensions().y / 2) >= (other->Position().y - 40.0f)) {
			Position(Position() - Vector2(0.0f, (Position().y - (mTexture->ScaledDimensions().y / 2)) - (other->Position().y + 10.0f)));
			mCanSwitchGravity = true;
		}
	}
	else if (other->tag() == "Down") {
		if (mGravity == Player::DOWN && Position().y + (mTexture->ScaledDimensions().y / 2) <= (other->Position().y + 40.0f)) {
			Position(Position() - Vector2(0.0f, (Position().y + (mTexture->ScaledDimensions().y / 2)) - (other->Position().y - 10.0f)));
			mCanSwitchGravity = true;
		}
	}
	else if (other->tag() == "Left") {
		if (mGravity == Player::LEFT && Position().x - (mTexture->ScaledDimensions().y / 2) >= (other->Position().x - 40.0f)) {
			Position(Position() - Vector2((Position().x - (mTexture->ScaledDimensions().y / 2)) - (other->Position().x + 10.0f), 0.0f));
			mCanSwitchGravity = true;
		}
	}
	else if (other->tag() == "Right") {
		if (mGravity == Player::RIGHT && Position().x + (mTexture->ScaledDimensions().y / 2) <= (other->Position().x + 40.0f)) {
			Position(Position() - Vector2((Position().x + (mTexture->ScaledDimensions().y / 2)) - (other->Position().x - 10.0f), 0.0f));
			mCanSwitchGravity = true;
		}
	}
}

void Player::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "ActivatePlayer") {
			Active(true);
			mEvent->removeEvent(i);
		}
	}
}

void Player::loadData() {
	std::ifstream inputFile("data.txt");

	if (inputFile.is_open()) {
		std::string line;

		int lineIndex = 0;

		while (std::getline(inputFile, line)) {
			if (lineIndex == 0) {
				mLevel = stoi(line);
			}
			else if (lineIndex == 1) {
				mScore = stoi(line);
			}

			lineIndex++;
		}

		inputFile.close();
	}
}

void Player::saveData() {
	std::ofstream outputFile("data.txt", std::ios::trunc);

	if (outputFile.is_open()) {
		outputFile << mLevel << std::endl;
		outputFile << mScore << std::endl;

		outputFile.close();
	}
}

void Player::Update() {
	mTimer->Update();

	if (Active()) {
		move();
		changeGravity();
	}

	processEvents();

	mTimer->Reset();
}

void Player::Render() {
	mTexture->Render();
}