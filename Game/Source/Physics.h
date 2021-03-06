#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Module.h"
#include "List.h"
#include "Collisions.h"
#include "Point.h"
#include "SString.h"

struct SDL_Texture;
class SDL_Rect;

class Spaceship
{
public:

	fPoint position;
	float mass;
	float rotation;

	SString name;
	CircleCollider* collider;

	fPoint velocity, acceleration;
	List<fPoint> forces;
	fPoint totalForce;

	float frontalArea;
	float fuel;


public:

	Spaceship(fPoint position, float mass, CircleCollider* collider, fPoint velocity, fPoint acceleration, float frontalArea, int fuel, float rotation);

	fPoint ForceGravity(float shipMass, float planetMass, fPoint shipPos, fPoint planetPos);
	fPoint ForceAeroDrag(float density, fPoint shipVel, float frontalArea, float dragCoefficient);
	fPoint ForceHydroDrag(fPoint shipVel);
	fPoint ForceHydroBuoy(float density, fPoint gravity, SDL_Rect playerRect, fPoint shipPos, fPoint planetPos);
	void ApplyForce(fPoint force);
	void Rotate(Spaceship body, float angle);
	void SolveCollision();
	void NewtonLaw(fPoint totalForce, float mass);
};

class Planet
{
public:
	Planet(fPoint position, float mass, int id, CircleCollider* collider, fPoint gravity, int fluidRad, int planetRad, int orbitRad, float density, float dragCoefficient);
	~Planet();

	fPoint position;
	float mass;

	int id;
	CircleCollider* collider;
	SDL_Texture* texture;

	fPoint gravity;
	int fluidRad;
	int orbitRad;
	int planetRad;
	float density;
	float dragCoefficient;
};

class Physics : public Module
{
public:

	Physics();
	virtual ~Physics();

	void Init();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:

	void Step(float dt);
	void Integrate(float dt);

	int timer = 0;

};

#endif
