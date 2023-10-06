#include "PlayScreenUI.h"
#include "MathHelper.h"
#include "PhysicsHelper.h"

void PlayScreenUI::ClearFlags() {
	for (unsigned i = 0; i < mFlagTextures.size(); ++i) {
		delete mFlagTextures[i];
		mFlagTextures[i] = nullptr;
	}

	mFlagTextures.clear();
}

void PlayScreenUI::AddNextFlag() {
	if (mRemainingLevels >= 640) {
		AddFlag(17, 640);
	}
	else if (mRemainingLevels >= 320) {
		AddFlag(17, 320);
	}
	else if (mRemainingLevels >= 160) {
		AddFlag(17, 160);
	}
	else if (mRemainingLevels >= 80) {
		AddFlag(17, 80);
	}
	else if (mRemainingLevels >= 40) {
		AddFlag(17, 40);
	}
	else if (mRemainingLevels >= 20) {
		AddFlag(17, 20);
	}
	else if (mRemainingLevels >= 10) {
		AddFlag(15, 10);
	}
	else if (mRemainingLevels >= 5) {
		AddFlag(9, 5);
	}
	else {
		AddFlag(9, 1);
	}
}

void PlayScreenUI::AddFlag(float width, int value) {
	int index = (int)mFlagTextures.size();
	float scale = 3.44f;

	if (index > 0) {
		mFlagXOffset += (width * scale) / 2;
	}

	if (mFlagXOffset > 351) {
		mFlagYOffset += 20 * scale;
		mFlagXOffset = 0;
	}

	mRemainingLevels -= value;
	int x = 208;

	switch (value) {
	case 640:
		x = 68;
		break;
	case 320:
		x = 85;
		break;
	case 160:
		x = 102;
		break;
	case 80:
		x = 119;
		break;
	case 40:
		x = 136;
		break;
	case 20:
		x = 153;
		break;
	case 10:
		x = 171;
		break;
	case 5:
		x = 191;
		break;
	}

	mFlagTextures.push_back(new GLTexture("galaga.png", x, 68, (int)width, 18));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Scale(Vector2(scale, scale));
	mFlagTextures[index]->Position(mFlagXOffset + 40, mFlagYOffset);
	mFlagXOffset += (width * scale) / 2;

	mAudio->PlaySFX("SFX/FlagSound.wav", 0, -1);
}

PlayScreenUI::PlayScreenUI(Player* player) {
	mTimer = new Timer();
	mAudio = AudioManager::Instance();
	mEvent = EventManager::Instance();
	mInput = InputManager::Instance();

	mShopMenu = new GameEntity();
	mShopMenu->Parent(this);
	mShopMenu->Position(Vec2_Zero);

	mBackground = new GLTexture("ShopBar.png");
	mBackground->Parent(mShopMenu);
	mBackground->Position(Vector2(1.0f, 0.0f));

	mBackgroundColor = new GLTexture("galaga.png", 73, 115, 1, 1);
	mBackgroundColor->Parent(mShopMenu);
	mBackgroundColor->Position(Vector2(1.0f, 0.0f));

	mButton = new Button("ShowShop", new GLTexture("ShopBarButton.png"));
	mButton->Parent(mShopMenu);
	mButton->Position(Vector2(-280.0f, 0.0f));
	mButton->Active(false);

	mButton1 = new Button("HideShop", new GLTexture("ShopBarButton1.png"));
	mButton1->Parent(mShopMenu);
	mButton1->Position(Vector2(-280.0f, 0.0f));

	if (ShopList::SHOP_ITEM_COUNT * (ShopList::SHOP_ITEM_HEIGHT + ShopList::ITEM_PADDING) < Graphics::SCREEN_HEIGHT) {
		mShopList = new ShopList(Vector2(mBackground->ScaledDimensions().x, Graphics::SCREEN_HEIGHT + 200.0f), ShopList::SHOP_ITEM_COUNT);
		mShopList->Parent(mShopMenu);
		mShopList->Position(Vector2(0.0f, 100.0f));
	}
	else {
		mShopList = new ShopList(Vector2(mBackground->ScaledDimensions().x, ShopList::SHOP_ITEM_COUNT * (ShopList::SHOP_ITEM_HEIGHT + ShopList::ITEM_PADDING)), ShopList::SHOP_ITEM_COUNT);
		mShopList->Parent(mShopMenu);
		mShopList->Position(Vector2(0.0f, ((ShopList::SHOP_ITEM_COUNT * (ShopList::SHOP_ITEM_HEIGHT + ShopList::ITEM_PADDING)) - Graphics::SCREEN_HEIGHT) / 2));
	}
	
	mDisplay = new GameEntity();
	mDisplay->Position(Vector2(Vec2_Zero));

	mDisplayBackground = new GLTexture("TopBarCounter.png");
	mDisplayBackground->Parent(mDisplay);
	mDisplayBackground->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 48.5f));

	mDisplayMoney = new Scoreboard({ 255, 216, 0 });
	mDisplayMoney->Parent(mDisplay);
	mDisplayMoney->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f + 100.0f, 26.0f));

	mDisplayDamage = new Scoreboard({ 255, 0, 0 });
	mDisplayDamage->Parent(mDisplay);
	mDisplayDamage->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 70.0f));

	mDisplayEnemieCount = new Scoreboard({ 255, 216, 0 }, false, false);
	mDisplayEnemieCount->Parent(mDisplay);
	mDisplayEnemieCount->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f - 99.0f, 26.0f));

	mShipHUD1 = new GLTexture("ShipHUD.png", 1, 387, 263, 263);
	mShipHUD1->Parent(mDisplay);
	mShipHUD1->Position(Vector2(131.0f, Graphics::SCREEN_HEIGHT - 131.0f));

	mShipHUD2 = new GLTexture("ShipHUD.png", 383, 387, 263, 263);
	mShipHUD2->Parent(mDisplay);
	mShipHUD2->Position(Vector2(Graphics::SCREEN_WIDTH - 131.0f, Graphics::SCREEN_HEIGHT - 131.0f));

	mShipHUD3 = new GLTexture("ShipHUD.png", 383, 1, 263, 267);
	mShipHUD3->Parent(mDisplay);
	mShipHUD3->Position(Vector2(Graphics::SCREEN_WIDTH - 131.0f, 131.0f));

	mShipCrosshair = new GLTexture("ShipCrosshair.png");
	mShipCrosshair->Position(Vec2_Zero);

	mFlags = new GameEntity();
	mFlags->Position(Vector2(50.0f, 50.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.25f;

	mPlayer = player;
	SetLevel(player->level());
}

PlayScreenUI::~PlayScreenUI() {
	delete mTimer;
	mTimer = nullptr;
	mAudio = nullptr;
	mEvent = nullptr;
	mInput = nullptr;

	delete mBackground;
	mBackground = nullptr;
	delete mBackgroundColor;
	mBackgroundColor = nullptr;

	delete mButton;
	mButton = nullptr;
	delete mButton1;
	mButton1 = nullptr;

	delete mShopMenu;
	mShopMenu = nullptr;
	delete mShopList;
	mShopList = nullptr;

	delete mDisplay;
	mDisplay = nullptr;
	delete mDisplayMoney;
	mDisplayMoney = nullptr;
	delete mDisplayDamage;
	mDisplayDamage = nullptr;
	delete mDisplayEnemieCount;
	mDisplayEnemieCount = nullptr;
	delete mDisplayBackground;
	mDisplayBackground = nullptr;
	delete mShipHUD1;
	mShipHUD1 = nullptr;
	delete mShipHUD2;
	mShipHUD2 = nullptr;
	delete mShipHUD3;
	mShipHUD3 = nullptr;
	delete mShipCrosshair;
	mShipCrosshair = nullptr;

	delete mFlags;
	mFlags = nullptr;

	ClearFlags();
}

void PlayScreenUI::SetLevel(int level) {
	ClearFlags();

	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
}

void PlayScreenUI::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "ShowShop") {
			float speedMultiplier = 0.5f + ((mShopMenu->Position().x - Graphics::SCREEN_WIDTH + 270.5f) / 10);

			Vector2 moveVector = Vector2(-1.0f, 0.0f) * speedMultiplier;
			mShopMenu->Translate(moveVector, World);

			if (mShopMenu->Position().x <= Graphics::SCREEN_WIDTH - 270.5f) {
				mShopMenu->Position(0.0f, 0.0f);
				mEvent->removeEvent(i);
			}
		}
		if (events[i] == "HideShop") {
			float speedMultiplier = 0.5f + ((mShopMenu->Position().x - Graphics::SCREEN_WIDTH + 270.5f) / 10);

			Vector2 moveVector = Vector2(1.0f, 0.0f) * speedMultiplier;
			mShopMenu->Translate(moveVector, World);

			if (mShopMenu->Position().x >= Graphics::SCREEN_WIDTH + 270.5f) {
				mShopMenu->Position(541.0f, 0.0f);
				mEvent->removeEvent(i);
			}
		}
		else if (events[i] == "NextLevel") {
			mEvent->sendEvent("AddMoney" + (mPlayer->level() * 100));

			mPlayer->level(1);
			SetLevel(mPlayer->level());

			mEvent->removeEvent(i);
		}
	}
}

bool PlayScreenUI::inShop() {
	return mInShop;
}

void PlayScreenUI::enemiesLeft(int enemies) {
	mEnemiesLeftLastFrame = enemies;
}

void PlayScreenUI::Update() {
	mTimer->Update();
	mButton->Update();
	mButton1->Update();
	mShopList->Update();

	processEvents();

	if (mRemainingLevels > 0) {
		mFlagTimer = mTimer->TotalTime();

		if (mFlagTimer >= mFlagInterval) {
			AddNextFlag();
			mFlagTimer = 0.0f;
			mTimer->Reset();
		}
	}

	if (mEnemiesLeftLastFrame != mEnemiesLeft) {
		mEnemiesLeft = mEnemiesLeftLastFrame;

		int maxEnemies = (int)std::floor((float)mPlayer->level() * 0.34f) + 10;

		std::string enemyMessage = std::to_string(mEnemiesLeft) + "/" + std::to_string(maxEnemies);
		mDisplayEnemieCount->Score(enemyMessage, Scoreboard::ScorePlacement::LEFT);
	}

	mDisplayMoney->Score(mPlayer->money());
	mDisplayDamage->Score(mPlayer->damage());

	Vector2 mousePosition = mInput->MousePosition();

	mShipCrosshair->Position(mousePosition);

	if (mousePosition.x > mBackground->Position().x - (mBackground->ScaledDimensions().x / 2)) {
		mInShop = true;
	}
	else {
		mInShop = false;
	}
}

void PlayScreenUI::Render() {
	mShipCrosshair->Render();
	mShipHUD1->Render();
	mShipHUD2->Render();
	mShipHUD3->Render();
	mShopList->Render();
	mBackground->Render();
	mDisplayBackground->Render();
	mDisplayMoney->Render();
	mDisplayDamage->Render();
	mDisplayEnemieCount->Render();

	if (mShopMenu->Position().x > Graphics::SCREEN_WIDTH) {
		mButton->Active(true);
		mButton1->Active(false);
		mButton1->Render();
	}
	else {
		mButton1->Active(true);
		mButton->Active(false);
		mButton->Render();
	}

	for (auto flag : mFlagTextures) {
		flag->Render();
	}
}