#ifndef PLAYER_H
#define PLAYER_H

#include "Module.h"
#include "Animation.h"
#include "Physics.h"
#include "List.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Font;

class Player : public Module
{
public:

    Player();

    void Init();

    // Destructor
    virtual ~Player();

    // Called before player is available
    bool Awake(pugi::xml_node& conf);

    // Called before the first frame
    bool Start();

    // Called each loop iteration
    bool PreUpdate();
    bool Update(float dt);
    bool PostUpdate();

    // Called before quitting
    bool CleanUp();

    bool LoadState(pugi::xml_node&);
    bool SaveState(pugi::xml_node&);

	Spaceship* ovni;
    int timer = 0;
    //SDL_Rect player;
    SDL_Texture* playerTexture;
    SDL_Rect playerRect;

    fPoint playerPos;
	fPoint playerAcceleration;
    fPoint playerVelocity;
	int playerFuel;
    float playerRotation;
    float propForce;
    float pi;
    float turnAngle;
    bool godMode = false;
	bool isDead = false; 
	bool scan = false;
	bool colliding = false;
    bool isWon;
    int lives;
	int scanTimer;

	Planet* weAreIn;

    Animation* currentAnimation = &idle;
    Animation idle;
    Animation scanPlanet;
    Animation scanNo;
    Animation scanYes;
    Animation impulse;
    Animation getFuel;

private:

    CircleCollider* playerCollider = nullptr;

    void OnCollision(CircleCollider* c1, CircleCollider* c2);

    Font* font;

};

#endif // PLAYER_H