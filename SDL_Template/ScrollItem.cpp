#include "ScrollItem.h"

ScrollItem::ScrollItem(std::string itemName, AnimatedGLTexture* icon, long baseCost)
	: mItemName(itemName), mBaseCost(baseCost), mCost(baseCost) {

	mAnimIcon = icon;
	mAnimIcon->Parent(this);
	mAnimIcon->Position(Vector2(-100.0f, 0.0f));

	setupItem();
}

ScrollItem::ScrollItem(std::string itemName, GLTexture* icon, long baseCost)
	: mItemName(itemName), mBaseCost(baseCost), mCost(baseCost) {
	
	mIcon = icon;
	mIcon->Parent(this);
	mIcon->Position(Vector2(-100.0f, 0.0f));

	setupItem();
}

ScrollItem::~ScrollItem() {
	delete mTimer;
	mTimer = nullptr;
	mInput = nullptr;
	mEvent = nullptr;
	mPlayer = nullptr;

	delete mBackground;
	mBackground = nullptr;
	delete mIcon;
	mIcon = nullptr;
	delete mAnimIcon;
	mAnimIcon = nullptr;

	delete mButton;
	mButton = nullptr;
}

void ScrollItem::setupItem() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mPlayer = Player::Instance();
	mTimer = new Timer();

	mBackground = new GLTexture("ScrollItemBackground.png");
	mBackground->Parent(this);
	mBackground->Position(Vec2_Zero);

	mButton = new Button("Button" + mItemName, new GLTexture("BUY", "GameFont.ttf", 30, { 0, 255, 33 }));
	mButton->Parent(this);
	mButton->Position(Vector2(-55.0f, 0.0f));
	
	mLevel = 1;
	mCost = mBaseCost * mLevel;

	mCurrentCost = new Scoreboard({ 55, 0, 0 });
	mCurrentCost->Parent(this);
	mCurrentCost->Position(Vector2(-10.0f, 0.0f));
	mCurrentCost->Score(mCost, Scoreboard::ScorePlacement::LEFT);

	mCurrentLevel = new Scoreboard({ 55, 16, 0 });
	mCurrentLevel->Parent(this);
	mCurrentLevel->Position(Vector2(110.0f, 0.0f));
	mCurrentLevel->Score(mLevel);
}

void ScrollItem::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "Button" + mItemName) {
			//if (mPlayer->money() >= mCost) {
				//mPlayer->reduceMoney(mCost);

				mLevel++;
				mCost = mBaseCost * mLevel;

				mCurrentCost->Score(mCost, Scoreboard::ScorePlacement::LEFT);
				mCurrentLevel->Score(mLevel);

				//mPlayer->saveData();
			//}

			mEvent->removeEvent(i);
		}
	}
}

void ScrollItem::Update() {
	mTimer->Update();

	if (mIcon != nullptr) {
		mIcon->Rotate(mTimer->DeltaTime() * 10.0f);
	}

	if (mAnimIcon != nullptr) {
		mAnimIcon->Rotate(mTimer->DeltaTime() * 10.0f);
		mAnimIcon->Update();
	}

	mButton->Update();

	processEvents();

	mTimer->Reset();
}

void ScrollItem::Render() {
	mBackground->Render();

	if (mIcon != nullptr) mIcon->Render();
	if (mAnimIcon != nullptr) mAnimIcon->Render();

	mCurrentCost->Render();
	mCurrentLevel->Render();
	mButton->Render();
}
