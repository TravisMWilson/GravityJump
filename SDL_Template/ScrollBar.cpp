#include "ScrollBar.h"
#include "PhysicsHelper.h"
#include "AnimatedGLTexture.h"

ScrollBar::ScrollBar(Vector2 barSize, int numItems) {
	mInput = InputManager::Instance();

	mSize = barSize;
	mItemCount = numItems;

	mBackground = new GLTexture("ScrollBarBackground.png");
	mBackground->Parent(this);
	mBackground->Scale(Vector2(barSize.x, barSize.y));
	mBackground->Position(Vec2_Zero);

	for (int i = 0; i < mItemCount; i++) {
		mItems.push_back(new ScrollItem("Item" + std::to_string(i), new GLTexture("ScrollItemIcons.png", 20 * i, 0, 20, 20), (5 * i) + 1));
		mItems[i]->Parent(this);
		mItems[i]->Position(Vector2(0.0f, (-(barSize.y / 2) + (ITEM_HEIGHT * 0.5f)) + (ITEM_HEIGHT * i)));
	}
}

ScrollBar::~ScrollBar() {
	mInput = nullptr;

	for (int i = 0; i < mItemCount; i++) {
		delete mItems[i];
		mItems[i] = nullptr;
	}

	mItems.clear();

	delete mBackground;
	mBackground = nullptr;
}

Vector2 ScrollBar::size() {
	return mSize;
}

void ScrollBar::size(Vector2 barSize) {
	mSize = barSize;
	mBackground->Scale(barSize);
}

void ScrollBar::Update() {
	for (int i = 0; i < mItemCount; i++) {
		mItems[i]->Update();
	}

	Vector2 mousePosition = mInput->MousePosition();
	int scrollValue = mInput->MouseWheelScroll();

	if (scrollValue < 0) {
		if (CheckCollision(mousePosition, mBackground->Position() - Vector2(mBackground->ScaledDimensions().x / 2, mBackground->ScaledDimensions().y / 2), mBackground->ScaledDimensions())) {
			scrollValue = 0;

			Translate(Vector2(0.0f, -20.0f));

			if (Position().y + (mBackground->ScaledDimensions().y / 2) < Graphics::SCREEN_HEIGHT) {
				Translate(Vector2(0.0f, Graphics::SCREEN_HEIGHT - (Position().y + (mBackground->ScaledDimensions().y / 2))));
			}
		}
	}
	else if (scrollValue > 0) {
		if (CheckCollision(mousePosition, mBackground->Position() - Vector2(mBackground->ScaledDimensions().x / 2, mBackground->ScaledDimensions().y / 2), mBackground->ScaledDimensions())) {
			scrollValue = 0;

			Translate(Vector2(0.0f, 20.0f));

			if (Position().y - (mBackground->ScaledDimensions().y / 2) > 0) {
				Translate(Vector2(0.0f, -(Position().y - (mBackground->ScaledDimensions().y / 2))));
			}
		}
	}
}

void ScrollBar::Render() {
	mBackground->Render();

	for (int i = 0; i < mItemCount; i++) {
		mItems[i]->Render();
	}
}
