#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"

namespace SDLFramework {
	class Texture : public GameEntity {
	protected:
		SDL_Texture * mTex;
		Graphics * mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mSourceRect;
		SDL_Rect mDestinationRect;

	public:
		Texture(std::string filename, bool managed = true);
		Texture(std::string filename, int x, int y, int w, int h, bool managed = true);
		Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);
		virtual ~Texture();

		Vector2 ScaledDimensions();

		void SetSourceRect(SDL_Rect * sourceRect);
		SDL_Rect GetSourceRect();

		void SetWidth(int width);

		virtual void Render() override;

	protected:
		void UpdateDstRect();
	};
}
#endif