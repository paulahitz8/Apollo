#include "Physics.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
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


	return true;
}

bool Physics::PreUpdate()
{
	return true;
}


bool Physics::Update(float dt)
{

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
	
}

void Physics::Integrate(Spaceship* body, float dt)
{
	body->position.x += body->velocity.x * dt + 0.5f * body->acceleration.x * dt * dt;
	body->velocity.x += body->acceleration.x * dt;

	body->position.y += body->velocity.y * dt + 0.5f * body->acceleration.y * dt * dt;
	body->velocity.y += body->acceleration.y * dt;
}

fPoint PhysicsEngine::ForceGravity(float shipMass, float planetMass, iPoint shipPos, iPoint planetPos)
{
	float G = 6.674 * (10 ^ -11);

	fPoint gravityForce;

	float rx = sqrt(((shipPos.x - planetPos.x) ^ 2));
	float ry = sqrt(((shipPos.y - planetPos.y) ^ 2));

	gravityForce.x = -G * ((shipMass * planetMass) / (rx * rx));
	gravityForce.y = -G * ((shipMass * planetMass) / (ry * ry));

	return gravityForce;
}

fPoint PhysicsEngine::ForceAeroDrag(float density, fPoint shipVel, float frontalArea, float dragCoefficient)
{
	fPoint aeroDragForce;

	aeroDragForce.x = 0.5 * density * shipVel.x * shipVel.x * frontalArea * dragCoefficient;
	aeroDragForce.y = 0.5 * density * shipVel.y * shipVel.y * frontalArea * dragCoefficient;

	return aeroDragForce;
}

fPoint PhysicsEngine::ForceHydroDrag(fPoint shipVel)
{
	float b = 1.0f;
	fPoint hydroDragForce;

	hydroDragForce.x = -b * shipVel.x;
	hydroDragForce.y = -b * shipVel.y;

	return hydroDragForce;
}

fPoint PhysicsEngine::ForceHydroBuoy(float density, fPoint gravity, float fluidVolume, float shipMass)
{
	fPoint buoyancyForce;

	buoyancyForce.x = density * gravity.x * fluidVolume - shipMass * gravity.x;
	buoyancyForce.y = density * gravity.y * fluidVolume - shipMass * gravity.y;

	return buoyancyForce;
}

// Constructors
Planet::Planet(fPoint position, float mass, int id, Collider* collider, fPoint gravity, float fluidRad, float planetRad, float density)
{
	this->position = position;
	this->mass = mass;

	this->id = id;
	this->collider = collider;

	this->gravity = gravity;
	this->fluidRad = fluidRad;
	this->planetRad = planetRad;
	this->density = density;
}