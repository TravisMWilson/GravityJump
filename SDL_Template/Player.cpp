#include "Player.h"

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
	mEvent = EventManager::Instance();

	mLevel = 1;
	mScore = 0;

	loadData();
}

Player::~Player() {
	mEvent = nullptr;
}

int Player::score() {
	return mScore;
}

void Player::score(int amount) {
	mScore += amount;
}

int Player::level() {
	return mLevel;
}

void Player::level(int level) {
	mLevel += level;
	saveData();
}

void Player::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i].substr(0, 8) == "Blank") {
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
				mScore = stoi(line);
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
		outputFile << mScore << std::endl;

		outputFile.close();
	}
}

void Player::Update() {
	processEvents();
}

void Player::Render() {

}