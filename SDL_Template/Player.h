#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>

#include "AudioManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "GameEntity.h"
#include "AIShip.h"
#include "Bullet.h"

using namespace SDLFramework;

struct Upgrades {
	long shipLevel;
	long damageLevel;
	long healthLevel;
	long reloadLevel;
};

class Player : public GameEntity {
public:
	enum UpgradeType {
		SHIP,
		DAMAGE,
		HEALTH,
		RELOAD
	};

private:
	static const int MAX_SHIPS = 8;
	static const int MAX_BULLETS = 2;

	static Player* sInstance;

	InputManager* mInput;
	EventManager* mEvent;
	AudioManager* mAudio;

	std::vector<AIShip*> mShips;
	std::vector<Upgrades*> mUpgrades;

	Bullet* mBullets[MAX_BULLETS];
	bool mCanFire;

	unsigned long long mMoney;
	long mDamage;
	int mLevel;

public:
	static Player* Instance();
	static void Release();

	Player();
	~Player();

	void handleFiring();
	void canFire(bool toggle);
	Bullet* bullet(int index);

	void updateUpgrades(int index, int stat, int level);

	unsigned long long money();
	void money(unsigned long long value);
	void reduceMoney(unsigned long long value);
	long damage();
	void damage(long value);
	int level();
	void level(int value);

	std::vector<AIShip*> ships();
	std::vector<Upgrades*> upgrades();

	void processEvents();

	void loadData();
	void saveData();

	void Update();
	void Render();
};

#endif