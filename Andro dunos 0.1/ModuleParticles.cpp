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
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Images/laser_types.png");
	graphics2 = App->textures->Load("Images/ship-explosion.png");

	// Basic_shoot 0
	basic_shoot_0.anim.PushBack({ 24, 39, 11, 4 });
	basic_shoot_0.anim.loop = false;
	basic_shoot_0.anim.speed = 0.3f;
	basic_shoot_0.speed.x = 5;
	basic_shoot_0.life = 3000;

	// Laser 0
	laser_0.anim.PushBack({ 57, 16, 16, 3 });
	laser_0.anim.loop = false;
	laser_0.anim.speed = 0.3f;
	laser_0.speed.x = 5;
	laser_0.life = 3000;


	// Basic_shoot 1
	basic_shoot_1.anim.PushBack({ 22, 51, 15, 6 });
	basic_shoot_1.anim.loop = false;
	basic_shoot_1.anim.speed = 0.3f;
	basic_shoot_1.speed.x = 5;
	basic_shoot_1.life = 3000;

	// Laser 1
	laser_1.anim.PushBack({ 57, 35, 16, 18 });
	laser_1.anim.loop = false;
	laser_1.anim.speed = 0.3f;
	laser_1.speed.x = 5;
	laser_1.life = 3000;

	// Explosion
	explosion.anim.PushBack({ 198, 115, 15, 9 });
	explosion.anim.PushBack({ 167, 113, 19, 11 });
	explosion.anim.PushBack({ 131, 109, 24, 15 });
	explosion.anim.PushBack({ 91, 104, 28, 20 });
	explosion.anim.PushBack({ 49, 94, 30, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	return true;
}


// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int col_x, int col_y)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
			{
				if( col_x == -1 && col_y == -1)
					p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				else
					p->collider = App->collision->AddCollider({0,0, col_x, col_y}, collider_type, this);
			}
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

