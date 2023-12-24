#include "Header.h"
#include "MyCamera.h"
#include "Background.h"
#include "AnimationPro.h"
#include "Zombie.h"

//Global Variables
//-------------------------------------------------------------------------------------------------------------------------------
Background background;
MyCamera camera;

std::vector<Zombie> zombies;
int target = 0;
//-------------------------------------------------------------------------------------------------------------------------------

void SetUpZombies()
{
	float scale{ 3.0f };
	float updateTime{ 1 / 12.0 };

	float speed = 300.0f;
	bool facingLeft = false;
	float health = 100.0f;
	float damage = 15.0f;

	// Wild Zombie
	Zombie wildZombie;
	{
		AnimationPro idle = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Idle.png"), scale, updateTime, 1, 9, 9);
		AnimationPro walk = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Walk.png"), scale, updateTime * 3 / 2, 1, 10, 10);
		AnimationPro run = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Run.png"), scale, updateTime, 1, 8, 8);
		AnimationPro attack1 = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Attack_1.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro attack2 = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Attack_2.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro attack3 = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Attack_3.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro special = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Eating.png"), scale, updateTime * 4 / 3, 1, 11, 11);
		AnimationPro jump = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Jump.png"), scale, updateTime * 2, 1, 6, 6);
		AnimationPro hurt = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Hurt.png"), scale, updateTime * 2, 1, 5, 5);
		AnimationPro death = AnimationPro(LoadTexture("textures/zombie/Wild Zombie/Death.png"), scale, updateTime, 1, 5, 5);
		wildZombie = Zombie("Wild Zombie", idle, walk, run, attack1, attack2, attack3, special, jump, hurt, death, speed, facingLeft, damage, health);
	}

	// Zombie Man
	Zombie zombieMan;
	{
		AnimationPro idle = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Idle.png"), scale, updateTime, 1, 8, 8);
		AnimationPro walk = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Walk.png"), scale, updateTime * 3 / 2, 1, 8, 8);
		AnimationPro run = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Run.png"), scale, updateTime, 1, 7, 7);
		AnimationPro attack1 = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Attack_1.png"), scale, updateTime * 4 / 3, 1, 5, 5);
		AnimationPro attack2 = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Attack_2.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro attack3 = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Attack_3.png"), scale, updateTime * 4 / 3, 1, 5, 5);
		AnimationPro special = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Bite.png"), scale, updateTime * 4 / 3, 1, 11, 11);
		AnimationPro jump = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Jump.png"), scale, updateTime * 2, 1, 8, 8);
		AnimationPro hurt = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Hurt.png"), scale, updateTime * 2, 1, 3, 3);
		AnimationPro death = AnimationPro(LoadTexture("textures/zombie/Zombie Man/Death.png"), scale, updateTime, 1, 5, 5);
		zombieMan = Zombie("Zombie Man", idle, walk, run, attack1, attack2, attack3, special, jump, hurt, death, speed, facingLeft, damage, health);
	}

	// Zombie Woman
	Zombie zombieWoman;
	{
		AnimationPro idle = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Idle.png"), scale, updateTime, 1, 5, 5);
		AnimationPro walk = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Walk.png"), scale, updateTime * 3 / 2, 1, 7, 7);
		AnimationPro run = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Run.png"), scale, updateTime, 1, 7, 7);
		AnimationPro attack1 = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Attack_1.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro attack2 = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Attack_2.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro attack3 = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Attack_3.png"), scale, updateTime * 4 / 3, 1, 4, 4);
		AnimationPro special = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Scream.png"), scale, updateTime * 4 / 3, 1, 5, 5);
		AnimationPro jump = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Jump.png"), scale, updateTime * 2, 1, 6, 6);
		AnimationPro hurt = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Hurt.png"), scale, updateTime * 2, 1, 3, 3);
		AnimationPro death = AnimationPro(LoadTexture("textures/zombie/Zombie Woman/Death.png"), scale, updateTime, 1, 5, 5);
		zombieWoman = Zombie("Zombie Woman", idle, walk, run, attack1, attack2, attack3, special, jump, hurt, death, speed, facingLeft, damage, health);
	}

	zombies.push_back(wildZombie);
	zombies.push_back(zombieMan);
	zombies.push_back(zombieWoman);
	zombies.at(0).setPos({ SCREEN_WIDTH / 4, 1000});
	zombies.at(1).setPos({ SCREEN_WIDTH * 2/ 4, 1000 });
	zombies.at(2).setPos({ SCREEN_WIDTH * 3/4, 1000 });
}

void SetUp()
{
	background = Background(LoadTexture("textures/DarkForest.png"), { 0,0 }, 1.1f);
	camera = MyCamera({ 0,0 }, 500.0f, false);
	
	SetUpZombies();
}

void PrintInfo()
{
	char message[100];
	int offsetX = 10;
	int offsetY = 0;
	int fontSize = 30;
	Color color = WHITE;

	strcpy_s(message, zombies.at(0).getName());
	strcat_s(message, "| VelY: ");
	strcat_s(message, std::to_string((int)zombies.at(0).getVelY()).c_str());
	strcat_s(message, "| VelX: ");
	strcat_s(message, std::to_string((int)zombies.at(0).getVelX()).c_str());
	strcat_s(message, "| InAir: ");
	strcat_s(message, std::to_string((int)zombies.at(0).getInAir()).c_str());

	DrawText(message, offsetX, offsetY, fontSize, color);
	offsetY += fontSize;
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	background.draw(camera.getPos());
	for (auto& zombie : zombies)
	{
		zombie.draw(camera.getPos());

		//zombie.drawHitbox(camera.getPos());
		//zombie.drawAttackbox(camera.getPos());
	}
	PrintInfo();
	EndDrawing();
	
}

void Input()
{
	if (IsMouseButtonPressed(1)) target++;
	if (target == zombies.size()) target = 0;
	zombies.at(target).takeInput();

	camera.takeInput();
}

void Logic()
{
	for (auto& zombie : zombies)
	{
		zombie.changeAnimation();
		zombie.updatePosition();
	}

	if (camera.getLocked()) camera.setPos(zombies.at(target).getSyncCameraPos());
	//camera.checkTopDownBound(background.getScaledSize());
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Zombies Flat-Platformer");
	SetWindowState(FLAG_VSYNC_HINT);
	srand(time(0));

	SetUp();
	while (!WindowShouldClose())
	{
		Draw();
		Input();
		Logic();
	}
	background.unloadTexture();
	CloseWindow();
}