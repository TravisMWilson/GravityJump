#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "PhysEntity.h"
#include "GLTexture.h"
#include "Random.h"

using namespace SDLFramework;

class Platform : public PhysEntity {
private:
	Random* mRand;

	GLTexture* mTexture;

	bool IgnoreCollisions() override;

public:
	Platform();
	~Platform();

	void placePlatform();
	void checkPlatformPosition();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};

#endif

