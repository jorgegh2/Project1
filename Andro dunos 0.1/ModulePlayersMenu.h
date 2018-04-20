#ifndef __MODULEPLAYERSMENU_H__
#define __MODULEPLAYERSMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct SDL_Rect;

class ModulePlayersMenu : public Module
{
public:
	ModulePlayersMenu();
	~ModulePlayersMenu();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr; // background
	SDL_Texture* graphics2 = nullptr; // logo
	SDL_Texture* graphics3 = nullptr; // player_p1_start
	SDL_Texture* graphics4 = nullptr; // player_p2_start
	SDL_Texture* graphics5 = nullptr; // visco games
	SDL_Texture* graphics6 = nullptr; // text
	SDL_Texture* graphics7 = nullptr; // timer
	Animation* current_animation = nullptr;   // animation for timer
	Animation* current_animation2 = nullptr;  // animation for player_1p_start
	Animation* current_animation3 = nullptr;  // animation for player_2p_start

	Animation timer;
	Animation p1;
	Animation p2;
	SDL_Rect bg;

	int coins = 0;

	int time_passed = 0;
	bool change_bg = false;
};

#endif // __MODULEPLAYERSMENU_H__