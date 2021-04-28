#include "Character.h"

Character::Character()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *g_Jump)
{
	if (e.type == SDL_KEYDOWN )
	{
		switch (e.key.keysym.sym)
		{
		    case SDL_KEYDOWN:
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    // QuitMenu = true;
                }
            }
            case SDLK_UP:
            {
                if (OnGround())
                {
                    Mix_PlayChannel(MIX_CHANNEL, g_Jump, NOT_REPEATITIVE);
                    status = JUMP;
                }
            }
		}
	}
	if (e.type == SDL_KEYUP )
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            {
                if(posY <= MIN_HEIGHT)
                    status = FALL;
            }
        }
    }
}

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *g_Renderer, LTexture g_CharacterTexture)
{
	g_CharacterTexture.Render(posX, posY, g_Renderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}
