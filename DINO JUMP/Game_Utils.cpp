#include "game_Utils.h"

int UpdateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}

std::string getHighScoreFromFile(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(std::string path,
	const int& score,
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::out);

	ConvertToInt >> oldHighScore;

	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&g_BackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* g_Renderer)
{
	std::vector <double> layer_speed;

	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(LAYER_6_SPEED);
	layer_speed.push_back(LAYER_7_SPEED);
	layer_speed.push_back(LAYER_8_SPEED);
	layer_speed.push_back(LAYER_9_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -g_BackgroundTexture[i].GetWidth())
		{
			offsetSpeed[i] = 0;
		}
		g_BackgroundTexture[i].Render(offsetSpeed[i], 0, g_Renderer);
		g_BackgroundTexture[i].Render(offsetSpeed[i] + g_BackgroundTexture[i].GetWidth(), 0, g_Renderer);
	}
}

void RenderScrollingGround(int& speed,
	const int acceleration,
	LTexture g_GroundTexture,
	SDL_Renderer* g_Renderer)
{
	speed -= GROUND_SPEED + acceleration;
	if (speed < -g_GroundTexture.GetWidth())
	{
		speed = 0;
	}
	g_GroundTexture.Render(speed, 0, g_Renderer);
	g_GroundTexture.Render(speed + g_GroundTexture.GetWidth(), 0, g_Renderer);
}

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* g_Click)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}
	else if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, g_Click, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&g_BackButton)[BUTTON_TOTAL],
	Button& HelpButton,
	Button& BackButton,
	LTexture g_InstructionTexture,
	LTexture g_BackButtonTexture,
	SDL_Renderer *g_Renderer,
	bool &Quit_Game,
	Mix_Chunk *g_Click)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_Game = true;
						Close();
					}
					else if (e->type == SDL_KEYDOWN)
                    {
                        if (e->key.keysym.sym == SDLK_ESCAPE)
                        {
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
                            ReadDone = true;
                        }
                    }
					else if (BackButton.IsInside(e, COMMON_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					g_InstructionTexture.Render(0, 0, g_Renderer);

					SDL_Rect* currentClip_Back = &g_BackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, g_Renderer, g_BackButtonTexture);

					SDL_RenderPresent(g_Renderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* g_Click)
{
    if (e->type == SDL_KEYDOWN)
        if (e->key.keysym.sym == SDLK_ESCAPE)
        {
            Quit = true;
        }
    if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleContinueButton(Button ContinueButton,
	LTexture g_ContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* g_Renderer,
	SDL_Rect(&g_ContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	bool& Quit,
	Mix_Chunk* g_Click)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
	    do
        {
            if (e->type == SDL_QUIT)
            {
                Quit  = true;
                Close();
            }
            if (ContinueButton.IsInside(e, SMALL_BUTTON))
            {
                switch (e->type)
                {
                case SDL_MOUSEMOTION:
                    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
                    Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
                    Mix_ResumeMusic();
                    Game_State = true;
                    Back_To_Game = true;
                    break;
                }
            }
            else
            {
                ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
            }
        } while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);


        SDL_Rect* currentClip_Continue = &g_ContinueButton[ContinueButton.currentSprite];
        ContinueButton.Render(currentClip_Continue, g_Renderer, g_ContinueButtonTexture);

        SDL_RenderPresent(g_Renderer);
	}
}

void HandlePauseButton(SDL_Event* e,
	SDL_Renderer* g_Renderer,
	SDL_Rect (&g_ContinueButton)[BUTTON_TOTAL],
	Button& PauseButton,
	Button ContinueButton,
	LTexture g_ContinueButtonTexture,
	bool &Game_State,
	bool &Quit,
	Mix_Chunk *g_Click)
{
	bool Pause_Game = false;
    //while (!Pause_Game)
    {
        if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
        {
            PauseButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
            Mix_PauseMusic();
            Game_State = false;
            Pause_Game = true;
            HandleContinueButton(ContinueButton, g_ContinueButtonTexture, e, g_Renderer, g_ContinueButton, Game_State, Quit, g_Click);
        }
        else if (PauseButton.IsInside(e, SMALL_BUTTON))
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                PauseButton.currentSprite = BUTTON_MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                PauseButton.currentSprite = BUTTON_MOUSE_OVER;
                Mix_PlayChannel(MIX_CHANNEL, g_Click, NOT_REPEATITIVE);
                Mix_PauseMusic();
                break;
            case SDL_MOUSEBUTTONUP:
                Game_State = false;
                Pause_Game = true;
                HandleContinueButton(ContinueButton, g_ContinueButtonTexture, e, g_Renderer, g_ContinueButton, Game_State, Quit, g_Click);
                break;
            }
        }
        else
        {
            PauseButton.currentSprite = BUTTON_MOUSE_OUT;
        }
    }
}

void GenerateEnemy(Enemy& enemy1,
	Enemy& enemy2,
	Enemy& enemy3,
	SDL_Rect(&g_EnemyClips)[FLYING_FRAMES],
	SDL_Renderer * g_Renderer)
{
	enemy1.LoadFromFile("imgs/enemy/cactus.png", g_Renderer);
	enemy2.LoadFromFile("imgs/enemy/cactus.png", g_Renderer);
	enemy3.LoadFromFile("imgs/enemy/bat.png", g_Renderer);
	{
		g_EnemyClips[0].x = 43 * 3;
		g_EnemyClips[0].y = 0;
		g_EnemyClips[0].w = 43;
		g_EnemyClips[0].h = 30;

		g_EnemyClips[1].x = 43 * 4;
		g_EnemyClips[1].y = 0;
		g_EnemyClips[1].w = 43;
		g_EnemyClips[1].h = 30;

		g_EnemyClips[2].x = 43 * 2;
		g_EnemyClips[2].y = 0;
		g_EnemyClips[2].w = 43;
		g_EnemyClips[2].h = 30;

		g_EnemyClips[3].x = 43;
		g_EnemyClips[3].y = 0;
		g_EnemyClips[3].w = 43;
		g_EnemyClips[3].h = 30;

		g_EnemyClips[4].x = 0;
		g_EnemyClips[4].y = 0;
		g_EnemyClips[4].w = 43;
		g_EnemyClips[4].h = 30;
	}
}

bool CheckColission(Character character,
	SDL_Rect* char_clip,
	Enemy enemy,
	SDL_Rect* enemy_clip)
{
	bool collide = false;

	int left_a = character.GetPosX();
	int right_a = character.GetPosX() + char_clip->w;
	int top_a = character.GetPosY();
	int bottom_a = character.GetPosY() + char_clip->h;

	if (enemy.GetType() == ON_GROUND_ENEMY)
	{
		const int TRASH_PIXEL_1 = 25;
		const int TRASH_PIXEL_2 = 30;

		int left_b = enemy.GetPosX();
		int right_b = enemy.GetPosX() + enemy.GetWidth();
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy.GetHeight();

		if (right_a - TRASH_PIXEL_1 >= left_b && left_a + TRASH_PIXEL_1 <= right_b)
		{
			if (bottom_a - TRASH_PIXEL_2 >= top_b)
			{
				collide = true;
			}
		}
	}
	else
	{
		const int TRASH_PIXEL_1 = 22;
		const int TRASH_PIXEL_2 = 18;

		int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
		int right_b = enemy.GetPosX() + enemy_clip->w - TRASH_PIXEL_1;
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy_clip->h - TRASH_PIXEL_2;

		if (right_a >= left_b && left_a <= right_b)
		{
			if (top_a <= bottom_b && top_a >= top_b)
			{
				collide = true;
			}

			if (bottom_a >= bottom_b && bottom_a <= top_b)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool CheckEnemyColission(Character character,
	Enemy enemy1,
	Enemy enemy2,
	Enemy enemy3,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip
	)
{
	if (CheckColission(character, char_clip, enemy1))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy2))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy3, enemy_clip))
	{
		return true;
	}
	return false;
}

void ControlCharFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void ControlEnemyFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
	{
		frame = 0;
	}
}

void DrawPlayerScore(LTexture g_TextTexture,
	LTexture g_ScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *g_Renderer,
	TTF_Font *g_Font,
	const int& score)
{
	g_TextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, g_Renderer);
	if (g_ScoreTexture.LoadFromRenderedText(std::to_string(score), g_Font, textColor, g_Renderer))
    {
		g_ScoreTexture.Render(SCORE_POSX, SCORE_POSY, g_Renderer);
	}
}

void DrawPlayerHighScore(LTexture g_TextTexture,
	LTexture g_HighScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* g_Renderer,
	TTF_Font* g_Font,
	const std::string& HighScore)
{
	g_TextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, g_Renderer);
	if (g_HighScoreTexture.LoadFromRenderedText(HighScore, g_Font, textColor, g_Renderer))
	{
		g_HighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, g_Renderer);
	}
}

void DrawEndGameSelection(LTexture g_LoseTexture,
	SDL_Event *e,
	SDL_Renderer *g_Renderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_game = false;
		while (!End_game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_game = true;
						break;
					case SDLK_ESCAPE:
						End_game = true;
						Play_Again = false;
						break;
					}
				}
			}

			g_LoseTexture.Render(0, 0, g_Renderer);

			SDL_RenderPresent(g_Renderer);
		}
	}
}



