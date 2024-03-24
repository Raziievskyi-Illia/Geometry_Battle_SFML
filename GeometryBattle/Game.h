#pragma once
#include "EntityManager.h"

#include "SFML/Graphics.hpp"

#include <iostream>

struct PlayerConfig
{
	int shape_radius =32; 
	int collision_radius=32;
	float speed = 5;

	sf::Color fillColor{ 10 , 10 , 10 };
	
	sf::Color outLineColor{ 255 , 0 , 0 };
	
	bool vulnerable = true; 
	int outlineThickness = 4; 
	int nVertices = 8;
};


struct EnemyConfig
{
	int shape_radius = 32;
	int collision_radius = 32;
	int smallEnemiesSpeed = 2; 
	int minSpeed = 3; 
	int maxSpeed = 7; 
	sf::Uint8 outLinecolor_r = 255;
	sf::Uint8 outLinecolor_g = 255;
	sf::Uint8 outLinecolor_b = 255;
	int outlineThickness = 2;
	int minVertices = 3; 
	int maxVertices = 7; 
	int smallEnemyLifespan = 80; 
	int spawnInterval = 60; 
};

struct BulletConfig
{
	int shape_radius = 10;
	int collision_radius = 10;
	float speed = 15;
	sf::Uint8 fillcolor_r = 255;
	sf::Uint8 fillcolor_g = 255;
	sf::Uint8 fillcolor_b = 255;
	sf::Uint8 outLinecolor_r = 255;
	sf::Uint8 outLinecolor_g = 0;
	sf::Uint8 outLinecolor_b = 0;
	int outlineThickness = 2;
	int nVertices = 20;
	int lifeSpan = 70;    // frames till disapear
};


struct SpecialWeaponConfig
{
	int shape_radius = 20;
	int collision_radius = 20;
	int nVertices = 20;
	sf::Color fillColor{ 10 , 10 , 10 };
	sf::Color outLineColor{ 255 , 0 , 0 };
	int outlineThickness = 3;
	float spinningRadius = 130.f; 
	int nSpheres = 3; 
	float angularSpeed = 1.f; 
	int CD = 1200; 
	int duration = 510; 
	bool over = false; 
};

class Game
{
	sf::RenderWindow m_window; 
	EntityManager m_manager; 
	PlayerConfig m_Player_CFG;
	EnemyConfig m_Enemy_CFG;
	BulletConfig m_Bullet_CFG;
	SpecialWeaponConfig m_weapon_CFG; 

	std::shared_ptr<Entity> m_player; 


	int m_score = 0; 
	int m_currentframe = 0; 
	int m_lastTimeSpecWeaponUsed = 0; 
	int m_lastTimeEnemySpawned = 0; 
	bool m_paused = false; 
	bool m_running = true; 

	void setPaused(bool flag); 

	sf::Font m_font;
	sf::Text m_Scoretext;

	sf::Texture m_crosshairTexture; 
	sf::Sprite m_crosshairSprite; 

	/*sf::Texture m_backgroundTexture; 
	sf::Sprite m_backgroundSprite; */

	void sMovement(); 
	void sUserInput(); 
	void sCollision(); 
	void sRender(); 
	void sLifeSpan(); 
	void sEnemySpawner(); 

	void SpawnPlayer(); 
	void SpawnEnemy(); 
	void SpawnSmallEnemies(std::shared_ptr<Entity> ent); 
	void SpawnBullet(const std::shared_ptr<Entity> ent, const Vec2& mousePos);
	void SpawnSpecialWeapon(std::shared_ptr<Entity> ent); 

public:
	Game(); 
	void run(); 


};