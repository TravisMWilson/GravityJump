#include "GameManager.h"

namespace SDLFramework {

	GameManager * GameManager::sInstance = nullptr;

	GameManager * GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		while (!mQuit) {
			mTimer->Update();

			while (SDL_PollEvent(&mEvent)) {
				switch (mEvent.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				case SDL_MOUSEWHEEL:
					if (mEvent.wheel.direction == SDL_MOUSEWHEEL_NORMAL) {
						mInputManager->MouseWheelScroll(mEvent.wheel.y);
					}

					break;
				}
			}

			mTargetTime = mTimer->TotalTime();

			if (mTargetTime >= 0.99f / FRAME_RATE) {
				Update();
				LateUpdate();
				Render();
				mTimer->Reset();
			}
		}
	}

	void GameManager::Update() {
		mInputManager->Update();
		mScreenManager->Update();
	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();
		mInputManager->MouseWheelScroll(0);
		mPhysicsManager->Update();
	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mScreenManager->Render();
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false), mEvent(SDL_Event()) {
		Graphics::SetMode(Graphics::RenderMode::GL);
		mGraphics = Graphics::Instance();
		mTimer = new Timer();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();

		mPhysicsManager = PhysicsManager::Instance();
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Player, PhysicsManager::CollisionFlags::Platform | PhysicsManager::CollisionFlags::Explosion);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Platform, PhysicsManager::CollisionFlags::Player);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Explosion, PhysicsManager::CollisionFlags::Player);

		mScreenManager = ScreenManager::Instance();
	}

	GameManager::~GameManager() {
		ScreenManager::Release();
		mScreenManager = nullptr;

		delete mTimer;
		mTimer = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		Graphics::Release();
		mGraphics = nullptr;

		// Quit SDL subsystems
		SDL_Quit();
	}
}