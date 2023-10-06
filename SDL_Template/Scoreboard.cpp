#include "Scoreboard.h"
#include "PhysicsHelper.h"

Scoreboard::Scoreboard(bool isToolTip, bool hasToolTip) : Scoreboard({230, 230, 230}, isToolTip, hasToolTip) {

}

Scoreboard::Scoreboard(SDL_Color color, bool isToolTip, bool hasToolTip) {
	mInput = InputManager::Instance();

	mHasToolTip = hasToolTip;
	mIsToolTip = isToolTip;
	mColor = color;

	Score(0);

	if (!mIsToolTip) {
		mToolTip = new Scoreboard(mColor, true);
		mToolTip->Score(mScoreValue, ScorePlacement::CENTER);

		mToolTipBackground = new GLTexture("galaga.png", 69, 115, 1, 1);
		mToolTipBackground->Parent(mToolTip);
		mToolTipBackground->Position(Vector2(10.0f, 0.0f));
	}
}

Scoreboard::~Scoreboard() {
	mInput = nullptr;
	ClearBoard();
}

void Scoreboard::Score(unsigned long long score, int placement) {
	mScoreValue = score;
	std::string str = std::to_string(score);
	if (!mIsToolTip) str = getCondensedNumber(score);
	Score(str, placement);
}

void Scoreboard::Score(std::string str, int placement) {
	ClearBoard();

	if (mScoreValue == 0 && str != "MAX") mScoreValue = stoull(str);
	mScoreFloatValue = 0.0f;
	size_t decimalPos = str.find('.');
	if (decimalPos != std::string::npos) mScoreFloatValue = stof(str);

	unsigned lastIndex = (unsigned)str.length() - 1;

	for (unsigned i = 0; i <= lastIndex; i++) {
		mScore.push_back(new GLTexture(str.substr(i, 1), "galagafont.ttf", 40, mColor));
		mScore[i]->Parent(this);

		if (placement == ScorePlacement::LEFT) {
			mScore[i]->Position(Vector2(20.0f * (lastIndex - (lastIndex - i)), 0.0f));
		}
		else if (placement == ScorePlacement::CENTER) {
			mScore[i]->Position(Vector2(-20.0f * (((lastIndex / 2.0f) - 0.5f) - i), 0.0f));
		}
		else if (placement == ScorePlacement::RIGHT) {
			mScore[i]->Position(Vector2(-20.0f * (lastIndex - i), 0.0f));
		}
	}

	mSize = Vector2(20.0f * (lastIndex + 1), 20.0f);
}

Vector2 Scoreboard::Size() {
	return mSize;
}

void Scoreboard::hideToolTip() {
	mHasToolTip = false;
}

void Scoreboard::Render() {
	for (auto digit : mScore) {
		digit->Render();
	}

	Vector2 mousePosition = mInput->MousePosition();

	if (CheckCollision(mousePosition, mScore[0]->Position() - Vector2(8.0f, mSize.y / 2), mSize) && !mIsToolTip && mHasToolTip) {
		if (mScoreFloatValue != 0.0f) {
			mToolTip->Score(removeTrailingZeros(mScoreFloatValue), ScorePlacement::CENTER);
		}
		else {
			mToolTip->Score(mScoreValue, ScorePlacement::CENTER);
		}

		mToolTip->Position(mousePosition + Vector2(-(mToolTip->Size().x / 2.0f) - 20.0f, 0.0f));
		mToolTipBackground->Scale(Vector2(mToolTip->Size().x, 25.0f));

		mToolTipBackground->Render();
		mToolTip->Render();
	}
}

void Scoreboard::ClearBoard() {
	for (auto s : mScore) {
		delete s;
	}

	mScore.clear();
}
