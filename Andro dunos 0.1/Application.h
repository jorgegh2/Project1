#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleGameIntroduction;
class ModuleStageClear;
class Level01;
class Module;
class ModuleAudio;
class ModuleParticles;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModulePlayer* player = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	Level01* level01 = nullptr;
	ModuleGameIntroduction* game_intro = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleStageClear* stage_clear = nullptr;
	ModuleParticles* particles = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__