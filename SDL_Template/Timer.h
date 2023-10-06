#ifndef __TIMER_H
#define __TIMER_H

#include <SDL.h>
#include <chrono>

class Timer {
private:
	std::chrono::steady_clock::time_point mStartTime;
	std::chrono::steady_clock::time_point mElapsedTime;
	std::chrono::steady_clock::time_point mCurrentTime;
	std::chrono::microseconds mDeltaTime;
	std::chrono::microseconds mTotalTime;
	float mTimeScale;

public:
	Timer();
	~Timer();

	void Reset();
	float DeltaTime() const;
	float TotalTime() const;

	void TimeScale(float ts);
	float TimeScale() const;

	void Update();
};

#endif