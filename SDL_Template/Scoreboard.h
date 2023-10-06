#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include <vector>

#include "InputManager.h"
#include "GameEntity.h"
#include "GLTexture.h"

using namespace SDLFramework;

class Scoreboard : public GameEntity {
public:
	enum ScorePlacement { LEFT, CENTER, RIGHT };

private:
	InputManager* mInput;

	std::vector<GLTexture*> mScore;
	unsigned long long mScoreValue;
	float mScoreFloatValue;

	Scoreboard* mToolTip;
	GLTexture* mToolTipBackground;
	GLTexture* mToolTipDecoration;
	bool mHasToolTip;
	bool mIsToolTip;

	SDL_Color mColor;
	Vector2 mSize;

public:
	Scoreboard(bool isToolTip = false, bool hasToolTip = true);
	Scoreboard(SDL_Color color, bool isToolTip = false, bool hasToolTip = true);
	~Scoreboard();

	void Score(unsigned long long score, int placement = ScorePlacement::RIGHT);
	void Score(std::string str, int placement = ScorePlacement::RIGHT);

	Vector2 Size();

	void hideToolTip();

	void Render() override;

private:
	void ClearBoard();
};
#endif