#ifndef __SCROLLBAR_H
#define __SCROLLBAR_H

#include <vector>

#include "InputManager.h"
#include "GameEntity.h"
#include "GLTexture.h"
#include "ScrollItem.h"

using namespace SDLFramework;

class ScrollBar : public GameEntity {
private:
	InputManager* mInput;

	Vector2 mSize;

	int mItemCount;

	GLTexture* mBackground;

	std::vector<ScrollItem*> mItems;

public:
	static const int ITEM_COUNT = 8;
	static const int ITEM_HEIGHT = 60;
	static const int ITEM_PADDING = 6;

	ScrollBar(Vector2 barSize, int numItems);
	~ScrollBar();

	Vector2 size();
	void size(Vector2 barSize);

	void Update() override;
	void Render() override;
};

#endif