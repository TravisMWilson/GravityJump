#ifndef __TUTORIALSCREEN_H
#define __TUTORIALSCREEN_H

#include "AnimatedGLTexture.h"
#include "Scoreboard.h"
#include "GameEntity.h"
#include "Button.h"

using namespace SDLFramework;

class TutorialScreen : public GameEntity {
private:
	GLTexture* mBackground;

	GLTexture* mPlayerAnimation;
	GLTexture* mMoveDescription;

	GLTexture* mPlayerTexture;
	GLTexture* mGravityDescription;

	Scoreboard* mScoreTexture;
	GLTexture* mScoreDescription;

	GLTexture* mPlatformTexture;
	GLTexture* mPlatformDescription;

	GLTexture* mSpikesTexture;
	GLTexture* mSpikesDescription;

	AnimatedGLTexture* mTargetTexture;
	GLTexture* mTargetDescription;

	AnimatedGLTexture* mExplosionTexture;
	GLTexture* mExplosionDescription;

	AnimatedGLTexture* mBirdTexture;
	GLTexture* mBirdDescription;

	Button* mStart;

public:
	TutorialScreen();
	~TutorialScreen();

	void Update() override;
	void Render() override;
};
#endif