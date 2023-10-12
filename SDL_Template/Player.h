#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>

#include "InputManager.h"
#include "EventManager.h"
#include "PhysEntity.h"
#include "GLTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Player : public PhysEntity {
public:
	enum GravityDirection { UP, DOWN, LEFT, RIGHT };

private:
	static Player* sInstance;

	EventManager* mEvent;
	InputManager* mInput;
	Timer* mTimer;

	GLTexture* mTexture;

	bool mJumping;
	float mJumpingTimer;
	int mGravity;
	float mGravityTimer;
	float mRotationalGoal;
	bool mCanSwitchGravity;
	int mScore;
	int mLevel;

	bool IgnoreCollisions() override;

public:
	static Player* Instance();
	static void Release();

	Player();
	~Player();

	void move();

	void changeGravity();
	int gravity();
	void gravity(int direction);

	int score();
	void score(int value);
	int level();
	void level(int value);

	void Hit(PhysEntity* other) override;

	void processEvents();

	void loadData();
	void saveData();

	void Update();
	void Render();
};

#endif