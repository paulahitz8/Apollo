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
	app->player->ovni->velocity = { 10.0f, 10.0f };
	for (int i = 0; i < app->scene->planetList.Count(); i++)
	{
		if ((pow(((app->player->ovni->position.x + (app->player->playerRect.w / 2)) - app->scene->planetList[i]->position.x), 2) + pow(((app->player->ovni->position.y + (app->player->playerRect.h / 2)) - app->scene->planetList[i]->position.y), 2)) < (app->scene->planetList[i]->fluidRad * app->scene->planetList[i]->fluidRad))
		{
			if (app->scene->planetList[i]->id == 6)
			{
				app->player->ovni->forces.Add(app->player->ovni->ForceHydroDrag(app->player->ovni->velocity));
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
	app->player->ovni->totalForce = { 0.0f, 0.0f };
	Integrate(app->player->ovni, dt);
	app->player->ovni->acceleration = { 0.0f, 0.0f };
}

void Physics::Integrate(Spaceship* body, float dt)
{
	body->position.x += body->velocity.x * dt + 0.5f * body->acceleration.x * dt * dt;
	body->velocity.x += body->acceleration.x * dt;

	body->position.y += body->velocity.y * dt + 0.5f * body->acceleration.y * dt * dt;
	body->velocity.y += body->acceleration.y * dt;
}

fPoint Spaceship::ForceGravity(float shipMass, float planetMass, fPoint shipPos, fPoint planetPos)
{
	float G = 30;

	fPoint gravityForce;

	float rx = sqrt(pow((shipPos.x - planetPos.x), 2));
	float ry = sqrt(pow((shipPos.y - planetPos.y), 2));

	if (shipPos.x >= planetPos.x)
	{
		gravityForce.x = -G * ((shipMass * planetMass) / (rx * rx));
	}
	else
	{
		gravityForce.x = G * ((shipMass * planetMass) / (rx * rx));
	}

	if (shipPos.y >= planetPos.y)
	{
		gravityForce.y = -G * ((shipMass * planetMass) / (ry * ry));
	}
	else
	{
		gravityForce.y = G * ((shipMass * planetMass) / (ry * ry));
	}

	return gravityForce;
}

fPoint Spaceship::ForceAeroDrag(float density, fPoint shipVel, float frontalArea, float dragCoefficient)
{
	fPoint aeroDragForce;

	aeroDragForce.x = 0.5 * density * shipVel.x * shipVel.x * frontalArea * dragCoefficient;
	aeroDragForce.y = 0.5 * density * shipVel.y * shipVel.y * frontalArea * dragCoefficient;

	return aeroDragForce;
}

fPoint Spaceship::ForceHydroDrag(fPoint shipVel)
{
	float b = 1.0f;
	fPoint hydroDragForce;

	hydroDragForce.x = -b * shipVel.x;
	hydroDragForce.y = -b * shipVel.y;

	return hydroDragForce;
}

fPoint Spaceship::ForceHydroBuoy(float density, fPoint gravity, SDL_Rect playerRect, fPoint shipPos, fPoint planetPos)
{
	fPoint buoyancyForce;

	buoyancyForce.x = -(density * gravity.x * playerRect.w * playerRect.h);
	buoyancyForce.y = -(density * gravity.y * playerRect.w * playerRect.h);

	if (shipPos.x >= planetPos.x)
	{
		buoyancyForce.x = -(density * gravity.x * playerRect.w * playerRect.h);
	}
	else
	{
		buoyancyForce.x = density * gravity.x * playerRect.w * playerRect.h;
	}

	if (shipPos.y >= planetPos.y)
	{
		buoyancyForce.y = -(density * gravity.y * playerRect.w * playerRect.h);
	}
	else
	{
		buoyancyForce.y = density * gravity.y * playerRect.w * playerRect.h;
	}

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

Spaceship::Spaceship(fPoint position, float mass, CircleCollider* collider, fPoint acceleration, float frontalArea, int fuel, float rotation)
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