#include "Zombie.h"

Zombie::Zombie() {}
Zombie::Zombie(const char* name,
	AnimationPro idle, AnimationPro walk, AnimationPro run, AnimationPro attack1, AnimationPro attack2,
	AnimationPro attack3, AnimationPro special, AnimationPro jump, AnimationPro hurt, AnimationPro death,
	float speed, bool facingLeft, float damage, float health)
	: name(name), current(idle), idle(idle), walk(walk), run(run), attack1(attack1), attack2(attack2), attack3(attack3), special(special), jump(jump), hurt(hurt), death(death),
	speed(speed), facingLeft(facingLeft), damage(damage), health(health)
{
	lastStatus = IDLE;
	status = IDLE;

	this->pos = { SCREEN_WIDTH / 2 - current.getWidth() / 2, SCREEN_HEIGHT - current.getHeight() };
	vel = { 0.0f, 0.0f };

	inAir = false;
	dead = false;
}

const char* Zombie::getName() { return name; }
Status Zombie::getStatus() { return status; }
Vector2 Zombie::getPos() { return pos; }
void Zombie::setPos(Vector2 pos) { this->pos = pos; }
int Zombie::getHealth() { return health; }
bool Zombie::getDead() { return dead; }

float Zombie::getVelY() { return vel.y; }
float Zombie::getVelX() { return vel.x; }
bool Zombie::getInAir() { return inAir; }


Vector2 Zombie::getSyncCameraPos() { return { pos.x - (SCREEN_WIDTH / 2 - current.getWidth() / 2), pos.y - (SCREEN_HEIGHT - current.getHeight() * 4 / 3) }; }

Rectangle Zombie::getHitbox(Vector2 cameraPos) //1) Three different hitboxes for three zombies
{
	float hitboxWidth;
	float hitboxHeight;
	float hitboxX;
	float hitboxY;
	if (name == "Wild Zombie")
	{
		hitboxWidth = current.getWidth() * 1 / 3;
		hitboxHeight = current.getHeight() * 1 / 2;
		hitboxX = pos.x - cameraPos.x + hitboxWidth;
		hitboxY = pos.y - cameraPos.y + hitboxHeight;
	}
	else if (name == "Zombie Man")
	{
		hitboxWidth = current.getWidth() * 1 / 3;
		hitboxHeight = current.getHeight() * 3 / 4;
		hitboxX = pos.x - cameraPos.x + hitboxWidth;
		hitboxY = pos.y - cameraPos.y + current.getHeight() * 1 / 4;
	}
	else if (name == "Zombie Woman")
	{
		hitboxWidth = current.getWidth() * 1 / 3;
		hitboxHeight = current.getHeight() * 3 / 4;
		hitboxX = pos.x - cameraPos.x + hitboxWidth;
		hitboxY = pos.y - cameraPos.y + current.getHeight() * 1 / 4;
	}
	return Rectangle{ hitboxX, hitboxY, hitboxWidth, hitboxHeight };
}
void Zombie::drawHitbox(Vector2 cameraPos) { DrawRectangleRec(getHitbox(cameraPos), { 230, 41, 55, 150 }); }

Rectangle Zombie::getAttackBox(Vector2 cameraPos) //2) Three different attackboxes for three zombies
{
	float attackBoxWidth;
	float attackBoxHeight;
	float attackBoxX;
	float attackBoxY;
	if (name == "Wild Zombie")
	{
		attackBoxWidth = current.getWidth() / 2;
		attackBoxHeight = current.getHeight() / 2;
		attackBoxX = pos.x - cameraPos.x;
		attackBoxY = pos.y - cameraPos.y + attackBoxHeight;
		if (!facingLeft) attackBoxX += attackBoxWidth;
	}
	else if (name == "Zombie Man")
	{
		attackBoxWidth = current.getWidth() / 2;
		attackBoxHeight = current.getHeight() * 3 / 4;
		attackBoxX = pos.x - cameraPos.x;
		attackBoxY = pos.y - cameraPos.y + current.getHeight() / 4;
		if (!facingLeft) attackBoxX += attackBoxWidth;
	}
	else if (name == "Zombie Woman")
	{
		attackBoxWidth = current.getWidth() / 2;
		attackBoxHeight = current.getHeight() * 3 / 4;
		attackBoxX = pos.x - cameraPos.x;
		attackBoxY = pos.y - cameraPos.y + current.getHeight() / 4;
		if (!facingLeft) attackBoxX += attackBoxWidth;
	}
	return Rectangle{ attackBoxX, attackBoxY, attackBoxWidth, attackBoxHeight };
}
void Zombie::drawAttackbox(Vector2 cameraPos) { if (attackBoxesAreActive()) DrawRectangleRec(getAttackBox(cameraPos), { 255, 161, 0, 150 }); }

bool Zombie::attackBoxesAreActive() //3) Three different attack boxes active frames for three zombies
{
	if (name == "Wild Zombie") return ((status == ATTACK1 || status == ATTACK2 || status == ATTACK3) && current.getFrame() == 3);
	else if (name == "Zombie Man") return ((status == ATTACK1 && current.getFrame() == 4)|| (status == ATTACK2 && current.getFrame() == 3) || (status == ATTACK3 && current.getFrame() == 4));
	else if (name == "Zombie Woman") return ((status == ATTACK1 || status == ATTACK2 || status == ATTACK3) && current.getFrame() == 3);
}
//bool Zombie::isHitByRec(Rectangle attackBox, Vector2 cameraPos);

bool Zombie::checkDeath() 
{
	if (health <= 0)
	{
		dead = true;
		status = DEATH;
	}
	return dead;
}

void Zombie::draw(Vector2 cameraPos, Color color)
{
	current.draw({ pos.x - cameraPos.x, pos.y - cameraPos.y }, facingLeft, color);

	//Stop animation
	//1) At the last frame of the death animation
	//2) At the last frame of jump while in air
	if (!(status == DEATH && current.atLastFrame()) && !(status == JUMP && current.atLastFrame() && inAir)) current.updateFrame();
	endPlayOnceAnimations();
}
void Zombie::endPlayOnceAnimations() 
{
	if (current.atLastFrame())
	{
		if (status == ATTACK1 || status == ATTACK2 || status == ATTACK3 || (status == JUMP && !inAir) || status == SPECIAL || status == HURT)
			status = IDLE;
	}
}

void Zombie::takeInput() 
{
	if (status != ATTACK1 && status != ATTACK2 && status != ATTACK3 && status != JUMP && !inAir && status != HURT && status != DEATH)
	{
		if (IsKeyPressed(KEY_F) || IsKeyDown(KEY_F))
		{
			int temp = rand() % 3 + 1;
			if (temp == 1) status = ATTACK1;
			else if (temp == 2) status = ATTACK2;
			else status = ATTACK3;
		}
		else if (IsKeyDown(KEY_S)) status = SPECIAL;
		else if (IsKeyPressed(KEY_SPACE)) status = JUMP;
		else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) status = IDLE;
		else if (IsKeyDown(KEY_A))
		{
			facingLeft = true;
			if (IsKeyDown(KEY_W)) status = RUN;
			else status = WALK;
		}
		else if (IsKeyDown(KEY_D))
		{
			facingLeft = false;
			if (IsKeyDown(KEY_W)) status = RUN;
			else status = WALK;
		}
		else
		{
			status = IDLE;
		}
	}

	if (IsKeyPressed(KEY_Y)) status = HURT;
	if (IsKeyPressed(KEY_U)) health = 0;
	if (IsKeyPressed(KEY_R)) //Reset
	{
		lastStatus = IDLE;
		status = IDLE;
		health = 100;
		dead = false;
	}

}
void Zombie::aiRandomInput() {}
void Zombie::changeAnimation() 
{
	checkDeath();
	if (lastStatus != status)
	{
		if (status == IDLE) current = idle;
		if (status == WALK) current = walk;
		if (status == RUN) current = run;
		if (status == ATTACK1) current = attack1;
		if (status == ATTACK2) current = attack2;
		if (status == ATTACK3) current = attack3;
		if (status == SPECIAL) current = special;
		if (status == JUMP && !inAir) current = jump;
		if (status == HURT) current = hurt;
		if (status == DEATH) current = death;
	}
	lastStatus = status;
}

void Zombie::updatePosition() 
{
	float dt = GetFrameTime();
	if (status == WALK)
	{
		if (facingLeft) pos.x -= speed * dt;
		else pos.x += speed * dt;
	}
	else if (status == RUN)
	{
		if (facingLeft) pos.x -= 2 * speed * dt;
		else pos.x += 2 * speed * dt;
	}
	else if (status == JUMP && current.getFrame() == 3) 
	{ 
		if (facingLeft) vel.x = -2 * speed;
		else vel.x = 2 * speed;

		vel.y = - 2 * speed; 
		inAir = true;
	}
	if (inAir)
	{
		if (IsKeyDown(KEY_A)) vel.x -= 3 * speed * dt;
		else if (IsKeyDown(KEY_D)) vel.x += 3 * speed * dt;

		if (vel.x < 0) facingLeft = true;
		else if (vel.y > 0) facingLeft = false;
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
		vel.y += GRAVITY * dt;
	}

	checkBound();

	if (pos.y == SCREEN_HEIGHT - current.getHeight())
	{
		vel.y = 0;
		vel.x = 0;
		inAir = false;
	}
	else inAir = true;
	
}
void Zombie::checkBound() 
{
	if (pos.y < 0) pos.y = 0;
	else if (pos.y > SCREEN_HEIGHT - current.getHeight()) pos.y = SCREEN_HEIGHT - current.getHeight();
}

void Zombie::unloadTexture() 
{
	idle.unloadTexture();
	walk.unloadTexture();
	run.unloadTexture();
	attack1.unloadTexture();
	attack2.unloadTexture();
	attack3.unloadTexture();
	special.unloadTexture();
	jump.unloadTexture();
	hurt.unloadTexture();
	death.unloadTexture();
}