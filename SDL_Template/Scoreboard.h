#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include <vector>

#include "GameEntity.h"
#include "GLTexture.h"

using namespace SDLFramework;

class Scoreboard : public GameEntity {
public:
	enum ScorePlacement { LEFT, CENTER, RIGHT };

private:
	std::vector<GLTexture*> mScore;
	int mScoreValue;
	SDL_Color mColor;
	Vector2 mSize;

public:
	Scoreboard();
	Scoreboard(SDL_Color color);
	~Scoreboard();

	void Score(int score, int placement = ScorePlacement::RIGHT);
	void Score(std::string str, int placement = ScorePlacement::RIGHT);

	Vector2 Size();

	void Render() override;

private:
	void ClearBoard();
};
#endif