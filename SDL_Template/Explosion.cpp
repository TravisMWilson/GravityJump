#include "Explosion.h"

Explosion::Explosion() {
	mAudio = AudioManager::Instance();
	mRand = Random::Instance();

	mTargetTexture = new AnimatedGLTexture("Target.png", 0, 0, 736, 736, 4, 4.0f);
	mTargetTexture->Parent(this);
	mTargetTexture->SetWrapMode(Animation::WrapModes::Once);
	mTargetTexture->Position(Vec2_Zero);
	mTargetTexture->Active(false);

	mExplosionTexture = new AnimatedGLTexture("Explosion.png", 0, 0, 512, 736, 48, 2.0f);
	mExplosionTexture->Parent(this);
	mExplosionTexture->SetWrapMode(Animation::WrapModes::Once);
	mExplosionTexture->Position(Vec2_Zero);
	mExplosionTexture->Active(false);

	Active(false);
}

Explosion::~Explosion() {
	mAudio = nullptr;
	mRand = nullptr;

	delete mExplosionTexture;
	mExplosionTexture = nullptr;

	delete mTargetTexture;
	mTargetTexture = nullptr;
}

Vector2 Explosion::scaledDimensions() {
	return mTargetTexture->ScaledDimensions();
}

void Explosion::Update() {
	if (mRand->RandomRange(0, 100) == 0 && !mTargetTexture->Active() && !mExplosionTexture->Active()) {
		Position(mRand->RandomRange(0.0f, (float)Graphics::SCREEN_WIDTH), mRand->RandomRange(0.0f, (float)Graphics::SCREEN_HEIGHT));
		mTargetTexture->Scale(Vector2(0.0f, 0.0f));
		mTargetTexture->ResetAnimation();
		mTargetTexture->Active(true);
	}

	if (mTargetTexture->Active()) {
		if (mTargetTexture->Scale().x < 1.0f) {
			mTargetTexture->Scale(mTargetTexture->Scale() + Vector2(0.025f, 0.025f));
		}

		mTargetTexture->Update();

		if (!mTargetTexture->IsAnimating()) {
			mTargetTexture->Active(false);
			mExplosionTexture->ResetAnimation();
			mExplosionTexture->Active(true);
			mAudio->PlaySFX("SFX/Explosion.wav", 0, 2);
			Active(true);
		}
	}

	if (mExplosionTexture->Active()) {
		mExplosionTexture->Update();

		if (!mExplosionTexture->IsAnimating()) {
			mExplosionTexture->Active(false);
		}
	}
}

void Explosion::Render() {
	if (mTargetTexture->Active()) {
		mTargetTexture->Render();
	}

	if (mExplosionTexture->Active()) {
		mExplosionTexture->Render();
	}
}