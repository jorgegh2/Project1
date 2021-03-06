#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "Level01.h"
#include "Level03.h"
#include "ModuleGameIntroduction.h"
#include "ModuleInsertCoin.h"
#include "ModulePlayersMenu.h"
#include "ModuleViscoGames.h"
#include "ModuleParticles.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "Module_Player_2.h"
#include "ModuleFonts.h"
#include "UI.h"
#include "ModulePowerUp.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = game_intro = new ModuleGameIntroduction();
	modules[6] = visco_games = new ModuleViscoGames();
	modules[7] = insert_coin = new ModuleInsertCoin();
	modules[8] = level03 = new Level03();
	modules[9] = level01 = new Level01();
	modules[10] = enemy = new ModuleEnemies();
	modules[11] = power_up = new ModulePowerUp();
	modules[12] = stage_clear = new ModuleStageClear();
	modules[13] = game_over = new ModuleGameOver();
	modules[14] = players_menu = new ModulePlayersMenu();
	modules[15] = particles = new ModuleParticles();
	modules[16] = player = new ModulePlayer();
	modules[17] = player2 = new ModulePlayer2();
	modules[18] = fade = new ModuleFadeToBlack();
	modules[19] = collision = new ModuleCollision();
	modules[20] = fonts = new ModuleFonts();
	modules[21] = UI = new ModuleUI();
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	
	App->player->Disable();
	App->player2->Disable();
	App->level01->Disable();
	App->level03->Disable();
	App->stage_clear->Disable();
	App->game_over->Disable();
	App->insert_coin->Disable();
	App->visco_games->Disable();
	App->players_menu->Disable();
	App->insert_coin->Disable();
	App->UI->Disable();
	App->power_up->Disable();

	collision->Enable();
	enemy->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

 	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
 		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}