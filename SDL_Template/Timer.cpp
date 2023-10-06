#include "Timer.h"

Timer::Timer() {
	mStartTime = std::chrono::high_resolution_clock::now();
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer() {

}

void Timer::Reset() {
	Update();
	mStartTime = std::chrono::high_resolution_clock::now();
}

float Timer::DeltaTime() const {
	return mDeltaTime.count() * 0.000001f;
}

float Timer::TotalTime() const {
	return mTotalTime.count() * 0.000001f;
}

void Timer::TimeScale(float ts) {
	mTimeScale = ts;
}

float Timer::TimeScale() const {
	return mTimeScale;
}

void Timer::Update() {
	mCurrentTime = std::chrono::high_resolution_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(mElapsedTime - mCurrentTime);
	mElapsedTime = mCurrentTime;
	mTotalTime = std::chrono::duration_cast<std::chrono::microseconds>(mCurrentTime - mStartTime);
}