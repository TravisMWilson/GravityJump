#ifndef __PLAYSCREENUI_H
#define __PLAYSCREENUI_H

#include <vector>
#include <string>

#include "EventManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "GameEntity.h"
#include "Scoreboard.h"
#include "GLTexture.h"
#include "ShopList.h"
#include "Player.h"
#include "Button.h"
#include "Timer.h"

using namespace SDLFramework;

class PlayScreenUI : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	EventManager* mEvent;
	InputManager* mInput;

	Player* mPlayer;

	GameEntity* mShopMenu;
	ShopList* mShopList;
	GLTexture* mBackground;
	GLTexture* mBackgroundColor;
	Button* mButton;
	Button* mButton1;
	bool mInShop;

	GameEntity* mDisplay;
	Scoreboard* mDisplayMoney;
	Scoreboard* mDisplayDamage;
	Scoreboard* mDisplayEnemieCount;
	GLTexture* mDisplayBackground;
	GLTexture* mShipHUD1;
	GLTexture* mShipHUD2;
	GLTexture* mShipHUD3;
	GLTexture* mShipCrosshair;
	GLTexture* mCursor;
	int mEnemiesLeft;
	int mEnemiesLeftLastFrame;

	GameEntity* mFlags;
	std::vector<GLTexture*> mFlagTextures;
	int mRemainingLevels;
	float mFlagXOffset;
	float mFlagYOffset;
	float mFlagTimer;
	float mFlagInterval;

private:
	void ClearFlags();
	void AddNextFlag();
	void AddFlag(float width, int value);

public:
	PlayScreenUI(Player* player);
	~PlayScreenUI();

	void SetLevel(int level);

	void processEvents();

	bool inShop();

	void enemiesLeft(int enemies);

	void Update() override;
	void Render() override;
};

#endif