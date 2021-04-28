#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "game_Base.h"
#include "Button.h"
#include "Enemy.h"
#include "Character.h"

bool Init();
bool LoadMedia();
void Close();

std::string getHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path,
    const int& score,
    const std::string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
    LTexture(&g_BackgroundTexture)[BACKGROUND_LAYER],
    SDL_Renderer* g_Renderer);

/*void RenderScrollingBackground1(std::vector <double>& offsetSpeed,
    LTexture(&g_BackgroundTexture)[BACKGROUND_LAYER1],
    SDL_Renderer* g_Renderer);

void RenderScrollingBackground2(std::vector <double>& offsetSpeed,
    LTexture(&g_BackgroundTexture)[BACKGROUND_LAYER2],
    SDL_Renderer* g_Renderer); */

void RenderScrollingGround(int& speed,
    const int acceleration,
    LTexture g_GroundTexture,
    SDL_Renderer* g_Renderer);

void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* g_Click);

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&g_BackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    LTexture g_InstructionTexture,
    LTexture g_BackButtonTexture,
    SDL_Renderer* g_Renderer,
    bool& Quit_game,
    Mix_Chunk* g_Click);

void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
    Mix_Chunk* g_Click);

void HandleContinueButton(Button ContinueButton,
    LTexture g_ContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* g_Renderer,
    SDL_Rect(&g_ContinueButton)[BUTTON_TOTAL],
    bool& game_State,
    bool& Quit,
    Mix_Chunk* g_Click);

void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* g_Renderer,
    SDL_Rect(&g_ContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button ContinueButton,
    LTexture g_ContinueButtonTexture,
    bool& game_state,
    bool& Quit,
    Mix_Chunk* g_Click);

void GenerateEnemy(Enemy& enemy1,
    Enemy& enemy2,
    Enemy& enemy3,
    SDL_Rect(&g_EnemyClips)[FLYING_FRAMES],
    SDL_Renderer* g_Renderer);

bool CheckColission(Character character,
    SDL_Rect* char_clip,
    Enemy enemy,
    SDL_Rect* enemy_clip = nullptr);

bool CheckEnemyColission(Character character,
    Enemy enemy1,
    Enemy enemy2,
    Enemy enemy3,
    SDL_Rect* char_clip,
    SDL_Rect* enemy_clip = nullptr);

void ControlCharFrame(int& frame);

void ControlEnemyFrame(int& frame);

void DrawPlayerScore(LTexture g_TextTexture,
    LTexture g_ScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* g_Renderer,
    TTF_Font* g_Font,
    const int& score);

void DrawPlayerHighScore(LTexture g_TextTexture,
    LTexture g_HighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* g_Renderer,
    TTF_Font* g_Font,
    const std::string& HighScore);

void DrawEndGameSelection(LTexture g_LoseTexture,
    SDL_Event* e,
    SDL_Renderer* g_Renderer,
    bool& Play_Again);

#endif // !GAME_UTILS_H_

