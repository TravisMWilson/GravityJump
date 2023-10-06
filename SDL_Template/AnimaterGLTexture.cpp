#include "AnimatedGLTexture.h"

namespace SDLFramework {

	void AnimatedGLTexture::RunAnimation() {
		if (!mAnim.done) {
			mAnim.frameTimer = mTimer->TotalTime();

			if (mAnim.frameTimer >= mAnim.speed) {
				if (mAnim.wrapMode == Animation::WrapModes::Loop) {
					mAnim.frameTimer -= mAnim.speed;
				}
				else {
					mAnim.done = true;
					mAnim.frameTimer = mAnim.speed - mAnim.timePerFrame;
				}

				mTimer->Reset();
			}

			if (mAnim.layout == Animation::Layouts::Horizontal) {
				mSourceRect.x = mAnim.startX + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mWidth;
			}
			else {
				mSourceRect.y = mAnim.startY + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mHeight;
			}
		}
	}

	AnimatedGLTexture::AnimatedGLTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts layout, bool managed) : GLTexture(filename, x, y, w, h, managed) {
		mTimer = new Timer();

		mAnim.startX = x;
		mAnim.startY = y;

		mAnim.frameCount = frameCount;
		mAnim.speed = animationSpeed;
		mAnim.timePerFrame = mAnim.speed / mAnim.frameCount;
		mAnim.frameTimer = 0.0f;

		mAnim.wrapMode = Animation::WrapModes::Loop;
		mAnim.layout = layout;

		mAnim.done = false;
	}

	AnimatedGLTexture::~AnimatedGLTexture() {
		delete mTimer;
		mTimer = nullptr;
	}

	void AnimatedGLTexture::SetWrapMode(Animation::WrapModes wrapMode) {
		mAnim.wrapMode = wrapMode;
	}

	void AnimatedGLTexture::ResetAnimation() {
		mAnim.frameTimer = 0.0f;
		mAnim.done = false;
	}

	bool AnimatedGLTexture::IsAnimating() {
		return !mAnim.done;
	}

	void AnimatedGLTexture::Update() {
		mTimer->Update();
		RunAnimation();
	}
}