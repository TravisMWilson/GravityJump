#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H

#include "AudioManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "StartScreen.h"
#include "PlayScreen.h"
#include "GLTexture.h"

class ScreenManager {
private:
	static ScreenManager* sInstance;

	enum Screens { Start, Play };
	Screens mCurrentScreen;

	Timer* mTimer;
	InputManager* mInput;
	EventManager* mEvent;
	AudioManager* mAudio;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	GLTexture* mCursor;
	GLTexture* mBackground;

	int mMusicSelection;

public:
	static ScreenManager * Instance();
	static void Release();

	void moveBackground();
	void processEvents();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif