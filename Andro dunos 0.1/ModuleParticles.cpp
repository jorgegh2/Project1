#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Basic_shoot 0_up
	basic_shoot_0_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_0_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_0_up.anim.loop = false;
	basic_shoot_0_up.anim.speed = 0.3f;
	basic_shoot_0_up.speed.x = 5;
	basic_shoot_0_up.life = 3000;

	// Basic_shoot 0_down
	basic_shoot_0_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_0_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_0_down.anim.loop = false;
	basic_shoot_0_down.anim.speed = 0.3f;
	basic_shoot_0_down.speed.x = 5;
	basic_shoot_0_down.life = 3000;

	// Laser 0
	laser_0.anim.PushBack({ 57, 16, 16, 3 });
	laser_0.anim.loop = false;
	laser_0.anim.speed = 0.3f;
	laser_0.speed.x = 4;
	laser_0.life = 3000;


	// Basic_shoot 1
	basic_shoot_1.anim.PushBack({ 28, 39, 15, 4 });
	basic_shoot_1.anim.PushBack({ 26, 39, 13, 4 });
	basic_shoot_1.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1.anim.loop = false;
	basic_shoot_1.anim.speed = 0.3f;
	basic_shoot_1.speed.x = 5;
	basic_shoot_1.life = 3000;

	// Basic_shoot 1_up
	basic_shoot_1_up.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_1_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_1_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1_up.anim.loop = false;
	basic_shoot_1_up.anim.speed = 0.3f;
	basic_shoot_1_up.speed.x = 5;
	basic_shoot_1_up.life = 3000;

	// Basic_shoot 1_down
	basic_shoot_1_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_1_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_1_down.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_1_down.anim.loop = false;
	basic_shoot_1_down.anim.speed = 0.3f;
	basic_shoot_1_down.speed.x = 5;
	basic_shoot_1_down.life = 3000;

	// Laser 1 up
	laser_1.anim.PushBack({ 57, 35, 16, 18 });
	laser_1.anim.loop = false;
	laser_1.anim.speed = 0.3f;
	laser_1.speed.x = 4;
	laser_1.speed.y = -3;
	laser_1.life = 3000;

	// Laser 1 down
	laser_1_5.anim.PushBack({ 57, 60, 16, 18 });
	laser_1_5.anim.loop = false;
	laser_1_5.anim.speed = 0.3f;
	laser_1_5.speed.x = 4;
	laser_1_5.speed.y = 3;
	laser_1_5.life = 3000;


	// Basic_shoot 2
	basic_shoot_2.anim.PushBack({ 22, 51, 15, 6 });
	basic_shoot_2.anim.PushBack({ 20, 51, 17, 6 });
	basic_shoot_2.anim.PushBack({ 18, 51, 19, 6 });
	basic_shoot_2.anim.PushBack({ 16, 51, 21, 6 });
	basic_shoot_2.anim.loop = false;
	basic_shoot_2.anim.speed = 0.3f;
	basic_shoot_2.speed.x = 5;
	basic_shoot_2.life = 3000;

	// Basic_shoot 2_up
	basic_shoot_2_up.anim.PushBack({ 24, 33, 11, 10 });
	basic_shoot_2_up.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_2_up.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_2_up.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_2_up.anim.loop = false;
	basic_shoot_2_up.anim.speed = 0.3f;
	basic_shoot_2_up.speed.x = 5;
	basic_shoot_2_up.life = 3000;

	// Basic_shoot 2_down
	basic_shoot_2_down.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_2_down.anim.PushBack({ 24, 37, 11, 6 });
	basic_shoot_2_down.anim.PushBack({ 24, 35, 11, 8 });
	basic_shoot_2_down.anim.PushBack({ 24, 33, 11, 10 });
	basic_shoot_2_down.anim.loop = false;
	basic_shoot_2_down.anim.speed = 0.3f;
	basic_shoot_2_down.speed.x = 5;
	basic_shoot_2_down.life = 3000;

	// Laser 2 up
	laser_2.anim.PushBack({ 57, 60, 16, 18 });
	laser_2.anim.loop = false;
	laser_2.anim.speed = 0.3f;
	laser_2.speed.x = -2;
	laser_2.speed.y = -3;
	laser_2.life = 3000;

	// Laser 2 down
	laser_2_5.anim.PushBack({ 57, 35, 16, 18 });
	laser_2_5.anim.loop = false;
	laser_2_5.anim.speed = 0.3f;
	laser_2_5.speed.x = -2;
	laser_2_5.speed.y = 3;
	laser_2_5.life = 3000;

	//Disparo_trasero_0
	back_shoot_0.anim.PushBack({ 3, 8, 15, 5 });
	back_shoot_0.anim.loop = false;
	back_shoot_0.anim.speed = 0.3f;
	back_shoot_0.speed.x = 4;
	back_shoot_0.life = 3000;

	//Disparo_trasero_1
	back_shoot_1.anim.PushBack({ 3, 23, 15, 5 });
	back_shoot_1.anim.loop = false;
	back_shoot_1.anim.speed = 0.3f;
	back_shoot_1.speed.x = -3;
	back_shoot_1.life = 3000;


	/*normal & power-up 1*/
	// Helix_01_1
	helix_01_1.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_1.anim.loop = false;
	helix_01_1.anim.speed = 0.3f;
	helix_01_1.speed.x = 4;
	helix_01_1.speed.y = 1;
	helix_01_1.life = 3000;

	// Helix_01_2
	helix_01_2.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_2.anim.loop = false;
	helix_01_2.anim.speed = 0.3f;
	helix_01_2.speed.x = 4;
	helix_01_2.speed.y = -1;
	helix_01_2.life = 3000;

	// Helix 01_3
	helix_01_3.anim.PushBack({ 41, 23, 13, 6 });
	helix_01_3.anim.loop = false;
	helix_01_3.anim.speed = 0.3f;
	helix_01_3.speed.x = 4;
	helix_01_3.speed.y = 0;
	helix_01_3.life = 3000;
	/*power-up 2*/
	// Helix 02_1
	helix_02_1.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_1.anim.loop = false;
	helix_02_1.anim.speed = 0.3f;
	helix_02_1.speed.x = 4;
	helix_02_1.speed.y = 1;
	helix_02_1.life = 3000;

	// Helix 02_2
	helix_02_2.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_2.anim.loop = false;
	helix_02_2.anim.speed = 0.3f;
	helix_02_2.speed.x = 4;
	helix_02_2.speed.y = -1;
	helix_02_2.life = 3000;

	// Helix 02_2
	helix_02_3.anim.PushBack({ 41, 38, 13, 8 });
	helix_02_3.anim.loop = false;
	helix_02_3.anim.speed = 0.3f;
	helix_02_3.speed.x = 4;
	helix_02_3.speed.y = 0;
	helix_02_3.life = 3000;


	// Explosion ship
	explosion.anim.PushBack({ 33, 19, 35, 35 });
	explosion.anim.PushBack({ 82, 18, 35, 35 });
	explosion.anim.PushBack({ 134, 19, 35, 35 });
	explosion.anim.PushBack({ 187, 19, 35, 35 });
	explosion.anim.PushBack({ 33, 55, 35, 35 });
	explosion.anim.PushBack({ 82, 56, 35, 35 });
	explosion.anim.PushBack({ 134, 55, 35, 35 });
	explosion.anim.PushBack({ 187, 54, 35, 35 });
	explosion.anim.PushBack({ 7, 95, 35, 35 });
	explosion.anim.PushBack({ 50, 95, 35, 35 });
	explosion.anim.PushBack({ 87, 95, 35, 35 });
	explosion.anim.PushBack({ 118, 95, 35, 35 });
	explosion.anim.PushBack({ 148, 95, 35, 35 });
	explosion.anim.PushBack({ 177, 95, 35, 35 });
	explosion.anim.PushBack({ 204, 95, 35, 35 });
	explosion.anim.PushBack({ 228, 95, 28, 35 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.7f;
	explosion.Type = explosion.EXPLOSION;

	//Explosion 2nd player ship
	explosion2.anim.PushBack({ 45, 143, 35, 35 });
	explosion2.anim.PushBack({ 82, 142, 35, 31 });
	explosion2.anim.PushBack({ 122, 140, 35, 33 });
	explosion2.anim.PushBack({ 162, 139, 35, 34 });
	explosion2.anim.PushBack({ 48, 174, 35, 35 });
	explosion2.anim.PushBack({ 89, 172, 35, 35 });
	explosion2.anim.PushBack({ 132, 173, 35, 35 });
	explosion2.anim.PushBack({ 187, 54, 35, 35 });
	explosion2.anim.PushBack({ 7, 95, 35, 35 });
	explosion2.anim.PushBack({ 50, 95, 35, 35 });
	explosion2.anim.PushBack({ 87, 95, 35, 35 });
	explosion2.anim.PushBack({ 118, 95, 35, 35 });
	explosion2.anim.PushBack({ 148, 95, 35, 35 });
	explosion2.anim.PushBack({ 177, 95, 35, 35 });
	explosion2.anim.PushBack({ 204, 95, 35, 35 });
	explosion2.anim.PushBack({ 228, 95, 28, 35 });
	explosion2.anim.loop = false;
	explosion2.anim.speed = 0.7f;
	explosion2.Type = explosion.EXPLOSION;

	//1st Explosion enemy
	enemy_explosion1.anim.PushBack({ 4, 12, 39, 30 });
	enemy_explosion1.anim.PushBack({ 26, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 63, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 103, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 142, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 183, 11, 39, 38 });
	enemy_explosion1.anim.PushBack({ 11, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 58, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 108, 52, 39, 38 });
	enemy_explosion1.anim.PushBack({ 153, 52, 39, 38 });
	enemy_explosion1.anim.loop = false;
	enemy_explosion1.anim.speed = 0.6f;
	enemy_explosion1.Type = explosion.EXPLOSION_ENEMY;

	//2nd Explosion enemy
	enemy_explosion2.anim.PushBack({ 6, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 38, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 72, 100, 39, 38 });
	enemy_explosion2.anim.PushBack({ 117, 99, 39, 38 });
	enemy_explosion2.anim.PushBack({ 160, 98, 39, 38 });
	enemy_explosion2.anim.PushBack({ 203, 99, 39, 38 });
	enemy_explosion2.anim.PushBack({ 10, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 47, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 84, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 122, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 160, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 197, 138, 39, 38 });
	enemy_explosion2.anim.PushBack({ 8, 178, 39, 38 });
	enemy_explosion2.anim.PushBack({ 42, 178, 39, 38 });
	enemy_explosion2.anim.PushBack({ 73, 178, 39, 38 });
	enemy_explosion2.anim.loop = false;
	enemy_explosion2.anim.speed = 0.7f;
	enemy_explosion2.Type = explosion.EXPLOSION_ENEMY;

	//3rd explosion enemy
	enemy_explosion2.anim.PushBack({ 112, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 139, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 168, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 205, 217, 24, 24 });
	enemy_explosion2.anim.PushBack({ 14, 105, 24, 24 });
	enemy_explosion3.anim.loop = false;
	enemy_explosion3.anim.speed = 0.5f;
	enemy_explosion3.Type = explosion.EXPLOSION_ENEMY;

	//Enemy15 shot
	enemy15shot.anim.PushBack({ 84, 10, 53, 29 });
	enemy15shot.anim.PushBack({ 139, 10, 54, 29 });
	enemy15shot.anim.PushBack({ 30, 44, 56, 29 });
	enemy15shot.anim.PushBack({ 91, 44, 58, 29 });
	enemy15shot.anim.loop = false;
	enemy15shot.speed.x = -2;
	enemy15shot.speed.y = 0;
	enemy15shot.life = 2500;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Images/Ship/laser_types.png");
	graphics2 = App->textures->Load("Images/Ship/ship-explosion.png");
	graphics3 = App->textures->Load("Images/Enemies/explosions_all_in_one.png");
	enemy15shotgraphics = App->textures->Load("Images/Enemies/15.png");



	return true;
}


// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);
	App->textures->Unload(enemy15shotgraphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			switch (p->Type) {
			case p->EXPLOSION:
				App->render->Blit(graphics2, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			case p->EXPLOSION_ENEMY:
				App->render->Blit(graphics3, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;
			case p->SHOOT:

				App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			case p->SHOOT_ENEMY:

				App->render->Blit(enemy15shotgraphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
				break;

			}

			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->Type = particle.Type;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//code
			//App->particles->AddParticle(App->particles->explosion, active[i]->position.x, active[i]->position.y);

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

