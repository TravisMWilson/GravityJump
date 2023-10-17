#include "Button.h"
#include "PhysicsHelper.h"

Button::Button(std::string name, std::string texture, int x, int y, int w, int h) {
	mInput = InputManager::Instance();
	mEvents = EventManager::Instance();

	mName = name;

	mSize = Vector2((float)w, (float)h);

	mTexture = new GLTexture(texture, x, y, w, h, true);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
}

Button::Button(std::string name, GLTexture* texture) {
	mInput = InputManager::Instance();
	mEvents = EventManager::Instance();

	mName = name;

	mSize = texture->ScaledDimensions();

	mTexture = texture;
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
}

Button::~Button() {
	mInput = nullptr;
	mEvents = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

Vector2 Button::size() {
	return mSize;
}

void Button::pressed() {
	mPos = Position() - Vector2(mSize.x / 2, mSize.y /2);

	if (CheckCollision(mInput->MousePosition(), mPos, mSize)) {
		mEvents->sendEvent(mName);
	}
}

void Button::Update() {
	if (Active()) {
		if (mInput->MouseButtonPressed(InputManager::MouseButton::Left)) {
			pressed();
		}
	}
}

void Button::Render() {
	mTexture->Render();
}