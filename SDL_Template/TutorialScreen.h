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

	Button* mStart;

public:
	TutorialScreen();
	~TutorialScreen();

	void Update() override;
	void Render() override;
};
#endif