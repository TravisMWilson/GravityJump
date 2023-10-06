#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>

#include "EventManager.h"
#include "GameEntity.h"

using namespace SDLFramework;

class Player : public GameEntity {
private:
	static Player* sInstance;

	EventManager* mEvent;

	int mScore;
	int mLevel;

public:
	static Player* Instance();
	static void Release();

	Player();
	~Player();

	int score();
	void score(int value);
	int level();
	void level(int value);

	void processEvents();

	void loadData();
	void saveData();

	void Update();
	void Render();
};

#endif