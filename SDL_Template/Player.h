#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>

#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "EventManager.h"
#include "PhysEntity.h"
#include "GLTexture.h"
#include "Timer.h"

using namespace SDLFramework;

class Player : public PhysEntity {
public:
	enum GravityDirection { UP, DOWN, LEFT, RIGHT };
	enum TextureState { JUMPING, STATIC, FALLING };

private:
	static Player* sInstance;

	EventManager* mEvent;
	InputManager* mInput;
	Timer* mTimer;

	std::vector<SDL_Rect*> mStaticTextures;

	GLTexture* mTexture;
	AnimatedGLTexture* mRunAnimation;

	bool mJumped;
	bool mCanJump;

	int mGravity;
	float mGravityTimer;
	float mRotationalGoal;
	bool mCanSwitchGravity;

	int mScore;
	int mHiScore;

	bool IgnoreCollisions() override;

public:
	static Player* Instance();
	static void Release();

	Player();
	~Player();

	void resetPlayer();

	void moveDirection(float direction);
	void jump();
	void move();

	void fall(int gravity, float rotation);
	void changeGravity();
	int gravity();
	void gravity(int direction);

	int score();
	void score(int value);
	int hiScore();
	void hiScore(int value);

	void stand();
	void Hit(PhysEntity* other) override;

	void processEvents();

	void loadData();
	void saveData();

	void Update();
	void Render();
};

#endif