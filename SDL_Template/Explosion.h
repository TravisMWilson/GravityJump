#ifndef __EXPLOSION_H
#define __EXPLOSION_H

#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "GameEntity.h"
#include "Random.h"
#include "Timer.h"

using namespace SDLFramework;

class Explosion : public GameEntity {
private:
	AudioManager* mAudio;
	Random* mRand;
	Timer* mTimer;

	AnimatedGLTexture* mExplosionTexture;
	AnimatedGLTexture* mTargetTexture;

public:
	Explosion();
	~Explosion();

	Vector2 scaledDimensions();

	void Update() override;
	void Render() override;
};

#endif

