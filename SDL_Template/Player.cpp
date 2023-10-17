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

	mStaticTextures.push_back(new SDL_Rect({ 474, 0, 79, 102 }));
	mStaticTextures.push_back(new SDL_Rect({ 553, 0, 79, 102 }));
	mStaticTextures.push_back(new SDL_Rect({ 632, 0, 79, 102 }));

	mTexture = new GLTexture("GravityJump.png", 632, 0, 79, 102);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mRunAnimation = new AnimatedGLTexture("GravityJump.png", 0, 0, 79, 102, 6, 0.5f);
	mRunAnimation->Parent(this);
	mRunAnimation->Position(Vec2_Zero);
	mRunAnimation->Active(false);

	mGravity = DOWN;

	mCanSwitchGravity = true;
	mJumped = false;
	mCanJump = true;
	mGravityTimer = 0;
	mHiScore = 1;
	mScore = 0;

	loadData();

	AddCollider(new BoxCollider(Vector2(40.0f, 90.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Player);
}

Player::~Player() {
	mEvent = nullptr;
	mInput = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mRunAnimation;
	mRunAnimation = nullptr;

	for (auto* texture : mStaticTextures) {
		delete texture;
		texture = nullptr;
	}

	mStaticTextures.clear();

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Player::resetPlayer() {
	Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	Rotation(0.0f);
	Active(false);

	mJumped = false;
	mCanJump = true;

	mGravity = DOWN;
	mGravityTimer = 0;
	mRotationalGoal = 0.0f;
	mCanSwitchGravity = true;

	mScore = 0;

	mRunAnimation->Active(false);
	mTexture->SetSourceRect(mStaticTextures[STATIC]);
}

void Player::move() {
	if (Rotation() == mRotationalGoal) {
		if (mInput->KeyDown(SDL_SCANCODE_W)) {
			if (mGravity == Player::DOWN && !mJumped) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
				mTexture->SetSourceRect(mStaticTextures[JUMPING]);
				mRunAnimation->Active(false);
				mCanJump = false;
			}
			else if (mGravity == Player::LEFT) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(-1.0f, 1.0f));
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::RIGHT) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(1.0f, 1.0f));
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_S)) {
			if (mGravity == Player::UP && !mJumped) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
				mTexture->SetSourceRect(mStaticTextures[JUMPING]);
				mRunAnimation->Active(false);
				mCanJump = false;
			}
			else if (mGravity == Player::LEFT) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(1.0f, 1.0f));
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::RIGHT) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(-1.0f, 1.0f));
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_A)) {
			if (mGravity == Player::RIGHT && !mJumped) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
				mTexture->SetSourceRect(mStaticTextures[JUMPING]);
				mRunAnimation->Active(false);
				mCanJump = false;
			}
			else if (mGravity == Player::DOWN) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(-1.0f, 1.0f));
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::UP) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(1.0f, 1.0f));
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if (mInput->KeyDown(SDL_SCANCODE_D)) {
			if (mGravity == Player::LEFT && !mJumped) {
				Translate(Vec2_Up * 1000.0f * mTimer->DeltaTime());
				mTexture->SetSourceRect(mStaticTextures[JUMPING]);
				mRunAnimation->Active(false);
				mCanJump = false;
			}
			else if (mGravity == Player::DOWN) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(1.0f, 1.0f));
				mTexture->Scale(Vector2(1.0f, 1.0f));
				Translate(-Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
			else if (mGravity == Player::UP) {
				if (mCanJump) {
					mRunAnimation->Active(true);
				}

				mRunAnimation->Scale(Vector2(-1.0f, 1.0f));
				mTexture->Scale(Vector2(-1.0f, 1.0f));
				Translate(Vec2_Right * 500.0f * mTimer->DeltaTime());
			}
		}

		if ((mInput->KeyReleased(SDL_SCANCODE_W) && mGravity == Player::DOWN)
			|| (mInput->KeyReleased(SDL_SCANCODE_S) && mGravity == Player::UP)
			|| (mInput->KeyReleased(SDL_SCANCODE_A) && mGravity == Player::RIGHT)
			|| (mInput->KeyReleased(SDL_SCANCODE_D) && mGravity == Player::LEFT)) {
			if (!mCanJump) {
				mJumped = true;
				mTexture->SetSourceRect(mStaticTextures[FALLING]);
			}
		}

		if ((mInput->KeyReleased(SDL_SCANCODE_W) && (mGravity == Player::LEFT || mGravity == Player::RIGHT))
			|| (mInput->KeyReleased(SDL_SCANCODE_S) && (mGravity == Player::LEFT || mGravity == Player::RIGHT))
			|| (mInput->KeyReleased(SDL_SCANCODE_A) && (mGravity == Player::UP || mGravity == Player::DOWN))
			|| (mInput->KeyReleased(SDL_SCANCODE_D) && (mGravity == Player::UP || mGravity == Player::DOWN))) {
			if (mRunAnimation->Active()) {
				mRunAnimation->Active(false);
				mTexture->SetSourceRect(mStaticTextures[STATIC]);
			}
		}

		Translate(-Vec2_Up * 500.0f * mTimer->DeltaTime());
	}

	if (Position().y < 0.0f - std::abs(mTexture->ScaledDimensions().y / 2)
		|| Position().y > Graphics::SCREEN_HEIGHT + std::abs(mTexture->ScaledDimensions().y / 2)
		|| Position().x < 0.0f - std::abs(mTexture->ScaledDimensions().x / 2)
		|| Position().x > Graphics::SCREEN_WIDTH + std::abs(mTexture->ScaledDimensions().x / 2)) {
		Active(false);
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
			mTexture->SetSourceRect(mStaticTextures[FALLING]);
			mRunAnimation->Active(false);
			mGravity = UP;
			mRotationalGoal = 180.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
			mTexture->SetSourceRect(mStaticTextures[FALLING]);
			mRunAnimation->Active(false);
			mGravity = DOWN;
			mRotationalGoal = 0.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
			mTexture->SetSourceRect(mStaticTextures[FALLING]);
			mRunAnimation->Active(false);
			mGravity = LEFT;
			mRotationalGoal = 90.0f;
			mGravityTimer = 0.75f;
			mCanSwitchGravity = false;
		}

		if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
			mTexture->SetSourceRect(mStaticTextures[FALLING]);
			mRunAnimation->Active(false);
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

int Player::hiScore() {
	return mHiScore;
}

void Player::hiScore(int level) {
	mHiScore = level;
	saveData();
}

void Player::Hit(PhysEntity* other) {
	if (other->tag() == "Up") {
		if (mGravity == Player::UP && Position().y - (mTexture->ScaledDimensions().y / 2) >= (other->Position().y - 40.0f)) {
			Position(Position() - Vector2(0.0f, (Position().y - (mTexture->ScaledDimensions().y / 2)) - (other->Position().y + 10.0f)));
			mTexture->SetSourceRect(mStaticTextures[STATIC]);
			mCanSwitchGravity = true;
			mJumped = false;
			mCanJump = true;
		}
	}
	else if (other->tag() == "Down") {
		if (mGravity == Player::DOWN && Position().y + (mTexture->ScaledDimensions().y / 2) <= (other->Position().y + 40.0f)) {
			Position(Position() - Vector2(0.0f, (Position().y + (mTexture->ScaledDimensions().y / 2)) - (other->Position().y - 10.0f)));
			mTexture->SetSourceRect(mStaticTextures[STATIC]);
			mCanSwitchGravity = true;
			mJumped = false;
			mCanJump = true;
		}
	}
	else if (other->tag() == "Left") {
		if (mGravity == Player::LEFT && Position().x - (mTexture->ScaledDimensions().y / 2) >= (other->Position().x - 40.0f)) {
			Position(Position() - Vector2((Position().x - (mTexture->ScaledDimensions().y / 2)) - (other->Position().x + 10.0f), 0.0f));
			mTexture->SetSourceRect(mStaticTextures[STATIC]);
			mCanSwitchGravity = true;
			mJumped = false;
			mCanJump = true;
		}
	}
	else if (other->tag() == "Right") {
		if (mGravity == Player::RIGHT && Position().x + (mTexture->ScaledDimensions().y / 2) <= (other->Position().x + 40.0f)) {
			Position(Position() - Vector2((Position().x + (mTexture->ScaledDimensions().y / 2)) - (other->Position().x - 10.0f), 0.0f));
			mTexture->SetSourceRect(mStaticTextures[STATIC]);
			mCanSwitchGravity = true;
			mJumped = false;
			mCanJump = true;
		}
	}
	else if (other->tag() == "Spike") {
		mEvent->sendEvent("GameOver");
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
				mHiScore = stoi(line);
			}

			lineIndex++;
		}

		inputFile.close();
	}
}

void Player::saveData() {
	std::ofstream outputFile("data.txt", std::ios::trunc);

	if (outputFile.is_open()) {
		outputFile << mHiScore << std::endl;

		outputFile.close();
	}
}

void Player::Update() {
	mTimer->Update();

	if (Active()) {
		mRunAnimation->Update();

		move();
		changeGravity();
	}

	processEvents();

	mTimer->Reset();
}

void Player::Render() {
	if (Active()) {
		if (mRunAnimation->Active()) {
			mRunAnimation->Render();
		}
		else {
			mTexture->Render();
		}
	}

	PhysEntity::Render();
}