#include "game_Base.h"
#include "game_Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy.h"

SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* g_Font = nullptr;
Mix_Music* g_Music = nullptr;
Mix_Music* g_MenuMusic = nullptr;
Mix_Chunk* g_Click = nullptr;
Mix_Chunk* g_Jump = nullptr;
Mix_Chunk* g_Lose = nullptr;


const std::string SCENCE1[BACKGROUND_LAYER] = {
    "imgs/background/Scence_01.png",
	"imgs/background/Scence_02.png",
	"imgs/background/Scence_03.png",
	"imgs/background/Scence_04.png",
	"imgs/background/Scence_05.png",
	"imgs/background/Scence_06.png",
	"imgs/background/Scence_07.png",
	"imgs/background/Scence_08.png",
	"imgs/background/Scence_09.png",
};

const std::string SCENCE2[BACKGROUND_LAYER] = {
    "imgs/background/Scence2_01.png",
	"imgs/background/Scence2_02.png",
	"imgs/background/Scence2_03.png",
	"imgs/background/Scence2_04.png",
	"imgs/background/Scence2_05.png",
	"imgs/background/Scence2_06.png",
	"imgs/background/Scence2_07.png",
	"imgs/background/Scence2_08.png",
	"imgs/background/Scence2_09.png",
};

const std::string SCENCE3[BACKGROUND_LAYER] = {
    "imgs/background/Scence3_01.png",
	"imgs/background/Scence3_02.png",
	"imgs/background/Scence3_03.png",
	"imgs/background/Scence3_04.png",
	"imgs/background/Scence3_05.png",
	"imgs/background/Scence3_06.png",
	"imgs/background/Scence3_07.png",
	"imgs/background/Scence3_08.png",
	"imgs/background/Scence3_09.png",
};

SDL_Rect g_PlayButton[BUTTON_TOTAL];
SDL_Rect g_HelpButton[BUTTON_TOTAL];
SDL_Rect g_ExitButton[BUTTON_TOTAL];
SDL_Rect g_BackButton[BUTTON_TOTAL];
SDL_Rect g_PauseButton[BUTTON_TOTAL];
SDL_Rect g_ContinueButton[BUTTON_TOTAL];
SDL_Rect g_PlayAgainButton[BUTTON_TOTAL];
SDL_Rect g_CharacterClips[RUNNING_FRAMES];
SDL_Rect g_EnemyClips[FLYING_FRAMES];

LTexture g_MenuTexture;
LTexture g_InstructionTexture;
LTexture g_BackgroundTexture1[BACKGROUND_LAYER];
LTexture g_BackgroundTexture2[BACKGROUND_LAYER];
LTexture g_BackgroundTexture3[BACKGROUND_LAYER];
LTexture g_CharacterTexture;
LTexture g_GroundTexture;
LTexture g_PlayButtonTexture;
LTexture g_HelpButtonTexture;
LTexture g_ExitButtonTexture;
LTexture g_BackButtonTexture;
LTexture g_PauseButtonTexture;
LTexture g_ContinueButtonTexture;
LTexture g_LoseTexture;
LTexture g_Text1Texture;
LTexture g_ScoreTexture;
LTexture g_Text2Texture;
LTexture g_HighScoreTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

Character character;

bool pressDown = false;

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool Quit_Menu = false;
			bool Play_Again = false;

			Mix_PlayMusic(g_MenuMusic, IS_REPEATITIVE);
			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					bool Quit_game = false;
					HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, g_Click);

					HandleHelpButton(&e_mouse, g_BackButton,
									 HelpButton, BackButton,
									 g_InstructionTexture, g_BackButtonTexture,
									 g_Renderer, Quit_game, g_Click);

					HandleExitButton(&e_mouse, ExitButton, Quit_Menu, g_Click);

					if (Quit_game == true)
					{
						return 0;
					}
				}

				g_MenuTexture.Render(0, 0, g_Renderer);

				SDL_Rect* currentClip_Play = &g_PlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, g_Renderer, g_PlayButtonTexture);

				SDL_Rect* currentClip_Help = &g_HelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, g_Renderer, g_HelpButtonTexture);

				SDL_Rect* currentClip_Exit = &g_ExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, g_Renderer, g_ExitButtonTexture);

				SDL_RenderPresent(g_Renderer);
			}

			while (Play_Again)
			{
			    bool speedUp = false;
			    bool speedDown = false;
				srand(time(NULL));
				int time = 0;
				int score = 0;
				int acceleration = 0;
				int frame_Character = 0;
				int frame_Enemy = 0;
				std::string highscore = getHighScoreFromFile("high_score.txt");

				SDL_Event e;
				Enemy enemy1(ON_GROUND_ENEMY);
				Enemy enemy2(ON_GROUND_ENEMY);
				Enemy enemy3(IN_AIR_ENEMY);

				Mix_PlayMusic(g_Music, IS_REPEATITIVE);
				GenerateEnemy(enemy1, enemy2, enemy3, g_EnemyClips, g_Renderer);

                std::vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

				bool Quit = false;
				bool game_State = true;
				while (!Quit)
				{
					if (game_State)
					{
						UpdateGameTimeAndScore(time, acceleration, score);

						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								Quit = true;
								Play_Again = false;
							}
                            if(e.type == SDL_KEYDOWN)
                            {
                                switch (e.key.keysym.sym)
                                    {
                                         case SDLK_RIGHT:
                                         {
                                             speedUp = true;
                                         }
                                         case SDLK_LEFT:
                                         {
                                             speedDown = true;
                                         }
                                    }
                            }

                        HandlePauseButton(&e, g_Renderer, g_ContinueButton, PauseButton,
                                            ContinueButton, g_ContinueButtonTexture,
                                            game_State, Quit, g_Click);

                        character.HandleEvent(e, g_Jump);
                        }

						SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(g_Renderer);

						if((score/200)%3 == 0)
                        {
                            RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture1, g_Renderer);
						}
						else if ((score/200)%3 == 2)
						{
                            RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, g_Renderer);
						}
						else if ((score/200)%3 == 1)
                        {
                            RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, g_Renderer);
						}

						character.Move();
						SDL_Rect* currentClip_Character = nullptr;
						if (character.OnGround() && !pressDown)
						{
							currentClip_Character = &g_CharacterClips[frame_Character / SLOW_FRAME_CHAR];
							character.Render(currentClip_Character, g_Renderer, g_CharacterTexture);
						}
						else if (character.OnGround()&& pressDown)
						{
							currentClip_Character = &g_CharacterClips[frame_Character / SLOW_FRAME_CHAR];
							character.Render(currentClip_Character, g_Renderer, g_CharacterTexture);
						}
						else
						{
							currentClip_Character = &g_CharacterClips[0];
							character.Render(currentClip_Character, g_Renderer, g_CharacterTexture);
						}

						SDL_Rect* currentClip_Enemy = &g_EnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];

						if(speedUp) {
                            enemy1.Move(acceleration+7);
                            enemy1.Render(g_Renderer);

                            enemy2.Move(acceleration+7);
                            enemy2.Render(g_Renderer);

                            enemy3.Move(acceleration+7);
                            enemy3.Render(g_Renderer, currentClip_Enemy);

                            speedUp = false;
						}

						if(speedDown) {
                            enemy1.Move(acceleration-3);
                            enemy1.Render(g_Renderer);

                            enemy2.Move(acceleration-3);
                            enemy2.Render(g_Renderer);

                            enemy3.Move(acceleration-3);
                            enemy3.Render(g_Renderer, currentClip_Enemy);

                            speedDown = false;
						}

						else if(!speedUp || !speedDown) {
                            enemy1.Move(acceleration);
                            enemy1.Render(g_Renderer);

                            enemy2.Move(acceleration);
                            enemy2.Render(g_Renderer);

                            enemy3.Move(acceleration);
                            enemy3.Render(g_Renderer, currentClip_Enemy);
						}

						SDL_Rect* currentClip_Pause = &g_PauseButton[PauseButton.currentSprite];
						PauseButton.Render(currentClip_Pause, g_Renderer, g_PauseButtonTexture);


						DrawPlayerScore(g_Text1Texture, g_ScoreTexture, textColor, g_Renderer, g_Font, score);
						DrawPlayerHighScore(g_Text2Texture, g_HighScoreTexture, textColor, g_Renderer, g_Font, highscore);

						if (CheckEnemyColission(character,
							enemy1, enemy2, enemy3,
							currentClip_Character, currentClip_Enemy))
						{
							Mix_PauseMusic();
							Mix_PlayChannel(MIX_CHANNEL, g_Lose, NOT_REPEATITIVE);
							UpdateHighScore("high_score.txt", score, highscore);
							Quit = true;
						}

						SDL_RenderPresent(g_Renderer);

						ControlCharFrame(frame_Character);
						ControlEnemyFrame(frame_Enemy);
					}
				}

				DrawEndGameSelection(g_LoseTexture, &e, g_Renderer, Play_Again);
				if (!Play_Again)
				{
					enemy1.~Enemy();
					enemy2.~Enemy();
					enemy3.~Enemy();
				}
			}
		}
	}
	Close();

	return 0;
}

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		g_Window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_Window == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (g_Renderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
  				SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	g_Music = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (g_Music == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}

	g_MenuMusic = Mix_LoadMUS("sound/menu_audio.wav");
	if (g_MenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}

	g_Click = Mix_LoadWAV("sound/mouse_click.wav");
	if (g_Click == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	g_Jump = Mix_LoadWAV("sound/jump_sound.wav");
	if (g_Jump == nullptr)
	{
		LogError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}

	g_Lose = Mix_LoadWAV("sound/lose_sound.wav");
	if (g_Lose == nullptr)
	{
		LogError("Failed to load lose sound", MIX_ERROR);
		success = false;
	}

	else
	{
		g_Font = TTF_OpenFont("font/pixel_font.ttf", 28);
		if (g_Font == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			success = false;
		}
		else
		{
			if (!g_Text1Texture.LoadFromRenderedText("Your score: ", g_Font, textColor, g_Renderer))
			{
				std::cout << "Failed to render text1 texture" << std::endl;
				success = false;
			}

			if (!g_Text2Texture.LoadFromRenderedText("High score: ", g_Font, textColor, g_Renderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}

			if (!g_MenuTexture.LoadFromFile("imgs/background/menu.png", g_Renderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!g_InstructionTexture.LoadFromFile("imgs/background/instruction.png", g_Renderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!g_PlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", g_Renderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_PlayButton[i].x = 150 * i;
					g_PlayButton[i].y = 0;
					g_PlayButton[i].w = 150;
					g_PlayButton[i].h = 98;
				}
			}

			if (!g_HelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", g_Renderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_HelpButton[i].x = 150 * i;
					g_HelpButton[i].y = 0;
					g_HelpButton[i].w = 150;
					g_HelpButton[i].h = 98;
				}
			}

			if (!g_BackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", g_Renderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_BackButton[i].x = 100 * i;
					g_BackButton[i].y = 0;
					g_BackButton[i].w = 100;
					g_BackButton[i].h = 78;
				}
			}

			if (!g_ExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", g_Renderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_ExitButton[i].x = 150 * i;
					g_ExitButton[i].y = 0;
					g_ExitButton[i].w = 150;
					g_ExitButton[i].h = 98;
				}
			}

			if (!g_PauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_button.png", g_Renderer))
			{
				std::cout << "Failed to load pause_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_PauseButton[i].x = 22 * i;
					g_PauseButton[i].y = 0;
					g_PauseButton[i].w = 22;
					g_PauseButton[i].h = 34;
				}
			}

			if (!g_ContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_button.png", g_Renderer))
			{
				std::cout << "Failed to load continue_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					g_ContinueButton[i].x = 22 * i;
					g_ContinueButton[i].y = 0;
					g_ContinueButton[i].w = 22;
					g_ContinueButton[i].h = 34;
				}
			}

            for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture1[i].LoadFromFile(SCENCE1[i].c_str(), g_Renderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}

			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture2[i].LoadFromFile(SCENCE2[i].c_str(), g_Renderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}

			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture3[i].LoadFromFile(SCENCE3[i].c_str(), g_Renderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}

            g_CharacterTexture.LoadFromFile("imgs/character/char.png", g_Renderer);
				g_CharacterClips[0].x = 57 * 0;
				g_CharacterClips[0].y = 0;
				g_CharacterClips[0].w = 57;
				g_CharacterClips[0].h = 57;

				g_CharacterClips[1].x = 57 * 1;
				g_CharacterClips[1].y = 0;
				g_CharacterClips[1].w = 57;
				g_CharacterClips[1].h = 57;

				g_CharacterClips[2].x = 57 * 2;
				g_CharacterClips[2].y = 0;
				g_CharacterClips[2].w = 57;
				g_CharacterClips[2].h = 57;

				g_CharacterClips[3].x = 57 * 3;
				g_CharacterClips[3].y = 0;
				g_CharacterClips[3].w = 57;
				g_CharacterClips[3].h = 57;

				g_CharacterClips[4].x = 57 * 4;
				g_CharacterClips[4].y = 0;
				g_CharacterClips[4].w = 57;
				g_CharacterClips[4].h = 57;

				g_CharacterClips[5].x = 57 * 5;
				g_CharacterClips[5].y = 0;
				g_CharacterClips[5].w = 57;
				g_CharacterClips[5].h = 57;


			if (!g_LoseTexture.LoadFromFile("imgs/background/lose.png", g_Renderer))
			{
				std::cout << "Failed to load lose image." << std::endl;
				success = false;
			}
		}
	}
	return success;
}

void Close()
{
	g_MenuTexture.Free();
	g_InstructionTexture.Free();
	g_CharacterTexture.Free();
	g_GroundTexture.Free();
	g_PlayButtonTexture.Free();
	g_HelpButtonTexture.Free();
	g_ExitButtonTexture.Free();
	g_BackButtonTexture.Free();
	g_PauseButtonTexture.Free();
	g_ContinueButtonTexture.Free();
	g_LoseTexture.Free();
	g_Text1Texture.Free();
	g_ScoreTexture.Free();
	g_Text2Texture.Free();
	g_HighScoreTexture.Free();

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture1[i].Free();
	}

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture2[i].Free();
	}

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture3[i].Free();
	}

	Mix_FreeMusic(g_Music);
	Mix_FreeMusic(g_MenuMusic);
	Mix_FreeChunk(g_Click);
	Mix_FreeChunk(g_Lose);
	Mix_FreeChunk(g_Jump);
	g_Music = nullptr;
	g_MenuMusic = nullptr;
	g_Click = nullptr;
	g_Lose = nullptr;
	g_Jump = nullptr;

	SDL_DestroyRenderer(g_Renderer);
	g_Renderer = nullptr;

	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

