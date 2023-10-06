#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H

#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "Button.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	AnimatedGLTexture * mAnimatedLogo;

	Button * mStart;

	GameEntity * mBottomBar;
	Texture * mNamco;
	Texture * mDates;

public:
	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;
};
#endif