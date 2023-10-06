#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

#include <iostream>
#include <fstream>
#include <limits>

Player* Player::sInstance = nullptr;

Player* Player::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Player();
	}

	return sInstance;
}

void Player::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Player::Player() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mAudio = AudioManager::Instance();

	mCanFire = true;
	mLevel = 1;
	mDamage = 1;
	mMoney = 0;

	for (int i = 0; i < MAX_SHIPS; i++) {
		Upgrades* upgrades = new Upgrades();
		upgrades->shipLevel = 1;
		if (i == 0) upgrades->shipLevel = 2;
		upgrades->damageLevel = 1;
		upgrades->healthLevel = 1;
		upgrades->reloadLevel = 1;
		mUpgrades.push_back(upgrades);
	}

	loadData();

	mBullets[0] = new Bullet(new GLTexture("PlayerBullets.png", 0, 0, 121, 212), false);
	mBullets[1] = new Bullet(new GLTexture("PlayerBullets.png", 121, 0, 121, 212), true);

	for (int i = 0; i < MAX_SHIPS; i++) {
		if (mUpgrades[i]->shipLevel > 1) {
			for (int j = 0; j < mUpgrades[i]->shipLevel - 1; j++) {
				AIShip* ship = new AIShip(false, i);
				ship->damage(mUpgrades[i]->damageLevel * (i + 1));
				ship->health((mUpgrades[i]->healthLevel * 10) * (i + 1));
				ship->reload(mUpgrades[i]->reloadLevel);
				mShips.push_back(ship);
			}
		}
	}

	mDamage = mShips[0]->damage();
}

Player::~Player() {
	mInput = nullptr;
	mEvent = nullptr;
	mAudio = nullptr;

	delete mBullets[0];
	mBullets[0] = nullptr;
	delete mBullets[1];
	mBullets[1] = nullptr;
}

void Player::handleFiring() {
	if (mInput->MouseButtonPressed(InputManager::MouseButton::Left) && mCanFire) {
		Vector2 mousePosition = mInput->MousePosition();
		mDamage = mShips[0]->damage();

		if (!mBullets[0]->Active()) {
			mBullets[0]->damage(mDamage);
			mBullets[0]->Fire(Vector2(-100.0f, Graphics::SCREEN_HEIGHT * 0.75f), mousePosition);
			mAudio->PlaySFX("SFX/Fire.wav", 0, 3);
		}
		else if (!mBullets[1]->Active()) {
			mBullets[1]->damage(mDamage);
			mBullets[1]->Fire(Vector2(Graphics::SCREEN_WIDTH + 100.0f, Graphics::SCREEN_HEIGHT * 0.75f), mousePosition);
			mAudio->PlaySFX("SFX/Fire.wav", 0, 3);
		}
	}
	else if (!mCanFire) {
		mBullets[0]->Reload();
		mBullets[1]->Reload();
	}
}

void Player::canFire(bool toggle) {
	mCanFire = toggle;
}

Bullet* Player::bullet(int index) {
	return mBullets[index];
}

void Player::updateUpgrades(int index, int stat, int level) {
	if (stat == SHIP) {
		mUpgrades[index]->shipLevel = level;
	}
	else if (stat == DAMAGE) {
		mUpgrades[index]->damageLevel = level;
	}
	else if (stat == HEALTH) {
		mUpgrades[index]->healthLevel = level;
	}
	else if (stat == RELOAD) {
		mUpgrades[index]->reloadLevel = level;
	}
}

unsigned long long Player::money() {
	return mMoney;
}

void Player::money(unsigned long long amount) {
	mMoney += amount;
}

void Player::reduceMoney(unsigned long long amount) {
	mMoney -= amount;
}

long Player::damage() {
	return mDamage;
}

void Player::damage(long amount) {
	mDamage += amount;
}

int Player::level() {
	return mLevel;
}

void Player::level(int level) {
	mLevel += level;
	saveData();
}

std::vector<AIShip*> Player::ships() {
	return mShips;
}

std::vector<Upgrades*> Player::upgrades() {
	return mUpgrades;
}

void Player::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i].substr(0, 8) == "AddMoney") {
			money((unsigned long long)stoi(events[i].substr(8)));
			mEvent->removeEvent(i);
		}
		else if (events[i].substr(0, 12) == "UpdateDamage") {
			std::string shipName = events[i].substr(12);
			int shipIndex = stoi(events[i].substr(16));

			for (int i = 0; i < mShips.size(); i++) {
				if (mShips[i]->name() == shipName) {
					mShips[i]->damage(mShips[i]->damage() + (shipIndex + 1));
				}
			}

			mEvent->removeEvent(i);
		}
		else if (events[i].substr(0, 12) == "UpdateHealth") {
			std::string shipName = events[i].substr(12);
			int shipIndex = stoi(events[i].substr(16));

			for (int i = 0; i < mShips.size(); i++) {
				if (mShips[i]->name() == shipName) {
					mShips[i]->health(mShips[i]->health() + ((shipIndex + 1) * 10));
				}
			}

			mEvent->removeEvent(i);
		}
		else if (events[i].substr(0, 12) == "UpdateReload") {
			std::string shipName = events[i].substr(12);
			int shipIndex = stoi(events[i].substr(16));

			for (int i = 0; i < mShips.size(); i++) {
				if (mShips[i]->name() == shipName) {
					mShips[i]->reload(mShips[i]->reload() + 1);
				}
			}

			mEvent->removeEvent(i);
		}
		else if (events[i].substr(0, 10) == "UpdateShip") {
			int shipIndex = stoi(events[i].substr(14));

			AIShip* ship = new AIShip(false, shipIndex);

			bool foundShip = false;
			
			for (int i = 0; i < mShips.size(); i++) {
				if (stoi(mShips[i]->name().substr(4)) == shipIndex) {
					ship->damage(mShips[i]->damage());
					ship->health(mShips[i]->health());
					ship->reload(mShips[i]->reload());

					foundShip = true;

					break;
				}
			}

			if (!foundShip) {
				ship->damage(shipIndex + 1);
				ship->health(shipIndex + 1);
				ship->reload(shipIndex + 1);
			}

			ship->Parent(this->Parent());
			ship->Active(false);

			mShips.push_back(ship);

			mEvent->removeEvent(i);
		}
	}
}

void Player::loadData() {
	std::ifstream inputFile("data.txt");

	if (inputFile.is_open()) {
		std::string line;

		int lineIndex = 0;

		while (std::getline(inputFile, line)) {
			if (lineIndex == 0) {
				mLevel = stoi(line);
			}
			else if (lineIndex == 1) {
				mMoney = stoi(line);
			}
			else {
				int shipIndex = (lineIndex - 2) / 4;
				int statIndex = (lineIndex - 2) % 4;

				if (statIndex == 0) {
					mUpgrades[shipIndex]->shipLevel = stoi(line);
				}
				else if (statIndex == 1) {
					mUpgrades[shipIndex]->damageLevel = stoi(line);
				}
				else if (statIndex == 2) {
					mUpgrades[shipIndex]->healthLevel = stoi(line);
				}
				else if (statIndex == 3) {
					mUpgrades[shipIndex]->reloadLevel = stoi(line);
				}
			}

			lineIndex++;
		}

		inputFile.close();
	}
}

void Player::saveData() {
	std::ofstream outputFile("data.txt", std::ios::trunc);

	if (outputFile.is_open()) {
		outputFile << mLevel << std::endl;
		outputFile << mMoney << std::endl;

		for (int i = 0; i < MAX_SHIPS; i++) {
			outputFile << mUpgrades[i]->shipLevel << std::endl;
			outputFile << mUpgrades[i]->damageLevel << std::endl;
			outputFile << mUpgrades[i]->healthLevel << std::endl;
			outputFile << mUpgrades[i]->reloadLevel << std::endl;
		}

		outputFile.close();
	}
}

void Player::Update() {
	handleFiring();

	mBullets[0]->Update();
	mBullets[1]->Update();

	processEvents();
}

void Player::Render() {
	mBullets[0]->Render();
	mBullets[1]->Render();
}