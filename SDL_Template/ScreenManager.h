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

	InputManager* mInput;
	EventManager* mEvent;
	AudioManager* mAudio;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	GLTexture* mCursor;

public:
	static ScreenManager * Instance();
	static void Release();

	void processEvents();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif