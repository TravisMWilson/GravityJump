#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "AnimatedGLTexture.h"
#include "PhysEntity.h"
#include "GLTexture.h"
#include "Random.h"
#include "Spike.h"
#include "Timer.h"

using namespace SDLFramework;

class Platform : public PhysEntity {
private:
	Random* mRand;
	Timer* mTimer;

	GLTexture* mTexture;
	AnimatedGLTexture* mBreakupTexture;

	Spike* mSpike;

	bool mBreaking;
	float mSpeed;

	bool IgnoreCollisions() override;

public:
	Platform();
	~Platform();

	void placePlatform();
	void checkPlatformPosition();
	void breakPlatform();
	bool isBreaking();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};

#endif

