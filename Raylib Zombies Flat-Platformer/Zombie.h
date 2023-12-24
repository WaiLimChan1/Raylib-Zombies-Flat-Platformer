#pragma once
#include "Header.h"
#include "AnimationPro.h"

enum Status {IDLE, WALK ,RUN, ATTACK1, ATTACK2, ATTACK3, SPECIAL, JUMP, HURT, DEATH}; //Special for eat, scream, and bite

class Zombie
{
private:
	const char* name;

	AnimationPro current;

	AnimationPro idle;
	AnimationPro walk;
	AnimationPro run;

	AnimationPro attack1;
	AnimationPro attack2;
	AnimationPro attack3;
	AnimationPro special;

	AnimationPro jump;
	AnimationPro hurt;
	AnimationPro death;

	Status lastStatus;
	Status status;

	Vector2 pos;
	Vector2 vel;

	float speed;

	bool inAir;

	bool facingLeft;

	float health;
	float damage;
	bool dead;

public:
	Zombie();
	Zombie(const char* name,
		AnimationPro idle, AnimationPro walk, AnimationPro run, AnimationPro attack1, AnimationPro attack2,
		AnimationPro attack3, AnimationPro special, AnimationPro jump, AnimationPro hurt, AnimationPro death,
		float speed, bool facingLeft, float damage, float health);

	const char* getName();
	Status getStatus();
	Vector2 getPos();
	void setPos(Vector2 pos);
	int getHealth();
	bool getDead();

	float getVelY();
	float getVelX();
	bool getInAir();

	Vector2 getSyncCameraPos();

	Rectangle getHitbox(Vector2 cameraPos);
	void drawHitbox(Vector2 cameraPos);

	Rectangle getAttackBox(Vector2 cameraPos);
	void drawAttackbox(Vector2 cameraPos);

	bool attackBoxesAreActive();
	bool isHitByRec(Rectangle attackBox, Vector2 cameraPos);
	bool checkDeath();

	void draw(Vector2 cameraPos, Color color = WHITE);
	void endPlayOnceAnimations();
	void takeInput();
	void aiRandomInput();
	void changeAnimation();

	void updatePosition();
	void checkBound();

	void unloadTexture();
};