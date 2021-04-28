#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "game_Base.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* g_Font, SDL_Color textColor, SDL_Renderer* g_Renderer);

	bool LoadFromFile(std::string path, SDL_Renderer *g_Renderer);

	void Render(int x, int y, SDL_Renderer* g_Renderer, SDL_Rect* clip = nullptr);

	int GetWidth();

	int GetHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !LTEXTURE_H_

