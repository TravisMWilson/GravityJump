#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H

#include "AnimatedGLTexture.h"
#include "BackgroundStars.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "Button.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer * mTimer;
	InputManager * mInput;

	// Logo Entities
	GLTexture * mLogo;
	AnimatedGLTexture * mAnimatedLogo;

	// Play Mode Entities
	Button * mStart;

	// Bottom Bar Entities
	GameEntity * mBottomBar;
	Texture * mNamco;
	Texture * mDates;

	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	// stars
	BackgroundStars* mStars;

public:
	StartScreen();
	~StartScreen();

	void ResetAnimation();

	void Update() override;
	void Render() override;
};
#endif