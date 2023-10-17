#ifndef __BIRD_H
#define __BIRD_H

#include "AnimatedGLTexture.h"
#include "EventManager.h"
#include "PhysEntity.h"
#include "Scoreboard.h"
#include "Random.h"
#include "Timer.h"

using namespace SDLFramework;

class Bird : public PhysEntity {
private:
	EventManager* mEvent;
	Random* mRand;
	Timer* mTimer;

	AnimatedGLTexture* mTexture;

	Scoreboard* mBirdTimer;

	float mSpeed;

	bool IgnoreCollisions() override;

public:
	Bird();
	~Bird();

	void move();
	void resetBirdTimer();

	void Hit(PhysEntity* other) override;

	void processEvents();

	void Update() override;
	void Render() override;
};

#endif

