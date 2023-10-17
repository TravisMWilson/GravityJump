#include "EventManager.h"

namespace SDLFramework {

	EventManager* EventManager::sInstance = nullptr;

	EventManager* EventManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new EventManager();
		}
		return sInstance;
	}

	void EventManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void EventManager::sendEvent(std::string eventName) {
		mEvents.push_back(eventName);
	}

	void EventManager::removeEvent(int index) {
		mEvents.erase(mEvents.begin() + index);
	}

	void EventManager::clearEvents() {
		mEvents.clear();
	}

	std::vector<std::string> EventManager::getEvents() {
		return mEvents;
	}

	EventManager::EventManager() {

	}

	EventManager::~EventManager() {

	}
}