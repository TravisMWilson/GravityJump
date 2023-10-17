#ifndef __EVENTMANAGER_H
#define __EVENTMANAGER_H

#include <string>
#include <vector>

namespace SDLFramework {
	class EventManager {
	private:
		static EventManager* sInstance;

		std::vector<std::string> mEvents;

	public:
		static EventManager* Instance();
		static void Release();

		void sendEvent(std::string eventName);
		void removeEvent(int index);
		void clearEvents();
		std::vector<std::string> getEvents();

	private:
		EventManager();
		~EventManager();
	};
}
#endif