#ifndef __BUTTON_H
#define __BUTTON_H

#include "InputManager.h"
#include "EventManager.h"
#include "GameEntity.h"
#include "GLTexture.h"

using namespace SDLFramework;

class Button : public GameEntity {
private:
	InputManager* mInput;
	EventManager* mEvents;
	GLTexture* mTexture;

	std::string mName;

	Vector2 mPos;
	Vector2 mSize;

public:
	Button(std::string name, std::string texture, int x, int y, int w, int h);
	Button(std::string name, GLTexture* texture);
	~Button();

	void pressed(Vector2 mousePosition);

	void Update() override;
	void Render() override;
};

#endif