#include "Physics.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Player.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "Window.h"

Physics::Physics()
{
	name.Create("physics");
}

Physics::~Physics() {}

bool Physics::Awake(pugi::xml_node&)
{
	gravityy = { 0.0f, 0.0f };
	return true;
}

bool Physics::Start()
{
	timer = 0;

	return true;
}

bool Physics::PreUpdate()
{
	return true;
}


bool Physics::Update(float dt)
{
	//if (timer < 500)
	//{
	//	timer++;
	//	return true;
	//}

	Step(dt);

	//draw

	return true;
}


bool Physics::PostUpdate()
{

	return true;
}

bool Physics::CleanUp()
{

	return true;
}

void Physics::Step(float dt)
{
	
	app->player->ovni->totalForce = { 0.0f, 0.0f };
	app->player->ovni->acceleration = { 0.0f, 0.0f };

	for (int i = 0; i < app->scene->planetList.Count(); i++)
	{
		if ((pow(((app->player->ovni->position.x + (app->player->playerRect.w / 2)) - app->scene->planetList[i]->position.x), 2) + pow(((app->player->ovni->position.y + (app->player->playerRect.h / 2)) - app->scene->planetList[i]->position.y), 2)) < (app->scene->planetList[i]->fluidRad * app->scene->planetList[i]->fluidRad))
		{
			if (app->scene->planetList[i]->id == 6)
			{
				//app->player->ovni->forces.Add(app->player->ovni->ForceHydroDrag(app->player->ovni->velocity));
				app->player->ovni->forces.Add(app->player->ovni->ForceHydroBuoy(app->scene->planetList[i]->density, app->scene->planetList[i]->gravity, app->player->playerRect, app->player->ovni->position, app->scene->planetList[i]->position));
			}
			else
			{
				app->player->ovni->forces.Add(app->player->ovni->ForceAeroDrag(app->scene->planetList[i]->density, app->player->ovni->velocity, 5.0f, app->scene->planetList[i]->dragCoefficient));
			}
		}
		if ((pow(((app->player->ovni->position.x + (app->player->playerRect.w / 2)) - app->scene->planetList[i]->position.x), 2) + pow(((app->player->ovni->position.y + (app->player->playerRect.h / 2)) - app->scene->planetList[i]->position.y), 2)) < (app->scene->planetList[i]->orbitRad * app->scene->planetList[i]->orbitRad))
		{
			app->player->ovni->forces.Add(app->player->ovni->ForceGravity(app->player->ovni->mass, app->scene->planetList[i]->mass, app->player->ovni->position, app->scene->planetList[i]->position));
		}
	}
	for (int i = 0; i < app->player->ovni->forces.Count(); i++)
	{
		app->player->ovni->totalForce.x += app->player->ovni->forces[i].x;
		app->player->ovni->totalForce.y += app->player->ovni->forces[i].y;
	}
	app->player->ovni->forces.Clear();

	app->player->ovni->NewtonLaw(app->player->ovni->totalForce, app->player->ovni->mass);

	Integrate(dt);

}

void Physics::Integrate(float dt)
{
	app->player->ovni->position.x += app->player->ovni->velocity.x * dt + 0.5f * app->player->ovni->acceleration.x * dt * dt;
	app->player->ovni->velocity.x += app->player->ovni->acceleration.x * dt;

	app->player->ovni->position.y += app->player->ovni->velocity.y * dt + 0.5f * app->player->ovni->acceleration.y * dt * dt;
	app->player->ovni->velocity.y += app->player->ovni->acceleration.y * dt;
}

fPoint Spaceship::ForceGravity(float shipMass, float planetMass, fPoint shipPos, fPoint planetPos)
{
	float G = 40;

	float gravityF;
	fPoint gravityForce;

	fPoint newVec = { planetPos - shipPos };
	float dividendo = sqrt(newVec.x * newVec.x + newVec.y * newVec.y);

	if (dividendo < 5)
	{
		dividendo = 5;
	}

	newVec = { newVec.x / dividendo, newVec.y / dividendo };

	gravityF = G * ((shipMass * planetMass) / dividendo);

	gravityForce.x = newVec.x * gravityF;
	gravityForce.y = newVec.y * gravityF;

	return gravityForce;
}

fPoint Spaceship::ForceAeroDrag(float density, fPoint shipVel, float frontalArea, float dragCoefficient)
{
	fPoint aeroDragForce;

	aeroDragForce.x = 0.5 * density * shipVel.x * shipVel.x * frontalArea * dragCoefficient;
	aeroDragForce.y = 0.5 * density * shipVel.y * shipVel.y * frontalArea * dragCoefficient;

	if (shipVel.x >= 0)
	{
		aeroDragForce.x = -aeroDragForce.x;
	}
	if (shipVel.y >= 0)
	{
		aeroDragForce.y = -aeroDragForce.y;
	}
	return aeroDragForce;
}

fPoint Spaceship::ForceHydroDrag(fPoint shipVel)
{
	fPoint vel = shipVel;
	float b = 10;

	float dividendo = sqrt(pow(vel.x, 2) + pow(vel.y, 2));

	vel = { vel.x / dividendo, vel.y / dividendo };

	fPoint hydroDragForce = { 0,0 };
	hydroDragForce.x = shipVel.x * b;
	hydroDragForce.y = shipVel.y * b;

	hydroDragForce.x = -vel.x * hydroDragForce.x;
	hydroDragForce.y = -vel.y * hydroDragForce.y;

	return hydroDragForce;
}

fPoint Spaceship::ForceHydroBuoy(float density, fPoint gravity, SDL_Rect playerRect, fPoint shipPos, fPoint planetPos)
{
	fPoint buoyancyForce;

	buoyancyForce.x = -(density * gravity.x * playerRect.w * playerRect.h);
	buoyancyForce.y = -(density * gravity.y * playerRect.w * playerRect.h);

	if (shipPos.x >= planetPos.x)
	{
		buoyancyForce.x = density * gravity.x * playerRect.w * playerRect.h;
	}
	else
	{
		buoyancyForce.x = -(density * gravity.x * playerRect.w * playerRect.h);
	}

	if (shipPos.y >= planetPos.y)
	{
		buoyancyForce.y = density * gravity.y * playerRect.w * playerRect.h;
	}
	else
	{
		buoyancyForce.y = -(density * gravity.y * playerRect.w * playerRect.h);
	}
	buoyancyForce.x = buoyancyForce.x / 2;
	buoyancyForce.y = buoyancyForce.y / 2;
	
	return buoyancyForce;
}

// Constructors
Planet::Planet(fPoint position, float mass, int id, CircleCollider* collider, fPoint gravity, int fluidRad, int planetRad, int orbitRad, float density, float dragCoefficient)
{
	this->position = position;
	this->mass = mass;
	this->id = id;
	this->collider = collider;
	this->gravity = gravity;
	this->fluidRad = fluidRad;
	this->planetRad = planetRad;
	this->orbitRad = orbitRad;
	this->density = density;
	this->dragCoefficient = dragCoefficient;
}

Spaceship::Spaceship(fPoint position, float mass, CircleCollider* collider, fPoint velocity, fPoint acceleration, float frontalArea, int fuel, float rotation)
{
	this->position = position;
	this->mass = mass;
	this->collider = collider;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->frontalArea = frontalArea;
	this->fuel = fuel;
	this->rotation = rotation;
}

void Spaceship::ApplyForce(fPoint force)
{
	forces.Add(force);
}

void Spaceship::NewtonLaw(fPoint totalForce, float mass)
{
	acceleration.x = totalForce.x / mass;
	acceleration.y = totalForce.y / mass;
}
