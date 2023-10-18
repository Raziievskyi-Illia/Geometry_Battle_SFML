#include "Game.h"

void Game::setPaused(bool flag)
{
	m_paused = flag; 
}

void Game::sMovement()
{
	m_player->CTransform->velocity = { 0.f , 0.f };

	

	if (m_player->CInput->up)
	{
		m_player->CTransform->velocity.y =- m_Player_CFG.speed;
	}
	if (m_player->CInput->down)
	{
		m_player->CTransform->velocity.y = m_Player_CFG.speed;
	}
	if (m_player->CInput->up && m_player->CInput->down)
	{
		m_player->CTransform->velocity.y = 0; 
	}
	if (m_player->CInput->left)
	{
		m_player->CTransform->velocity.x = -m_Player_CFG.speed;
		m_player->CTransform->angle -= 6.0f;
	}
	if (m_player->CInput->right)
	{
		m_player->CTransform->velocity.x = m_Player_CFG.speed;
		m_player->CTransform->angle += 6.0f;
	}
	if (m_player->CInput->left && m_player->CInput->right)
	{
		m_player->CTransform->velocity.x = 0;
	}


	for (auto& e : m_manager.getEntities())
	{
		e->CTransform->pos.x += e->CTransform->velocity.x;
		e->CTransform->pos.y += e->CTransform->velocity.y;
	}

}

void Game::sUserInput()
{
	sf::Event event; 
	while (m_window.pollEvent(event))
	{
		if (m_paused)
		{
			switch (event.type)
			{

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				{
					m_running = false;
					break;
				}
				case sf::Keyboard::P:
				{
					if (m_paused)
					{
						setPaused(false);
					}
					else
					{
						setPaused(true);
					}
					break;
				}
				}
			}
			}
		}
		else
		{


			switch (event.type)
			{
			case sf::Event::MouseMoved:
			{
				
				m_crosshairSprite.setPosition(event.mouseMove.x, event.mouseMove.y); 
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{

				case sf::Keyboard::P:
				{
					if (m_paused)
					{
						setPaused(false);
					}
					else
					{
						setPaused(true);
					}
					break;
				}
				case sf::Keyboard::Escape:
				{
					m_running = false;
					break;
				}

				case sf::Keyboard::W:
				{
					m_player->CInput->up = true;
					break;
				}
				case sf::Keyboard::A:
				{
					m_player->CInput->left = true;
					break;
				}
				case sf::Keyboard::D:
				{
					m_player->CInput->right = true;
					break;
				}
				case sf::Keyboard::S:
				{
					m_player->CInput->down = true;
					break;
				}
				default:
					break;
				}
				break;
			}
			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					m_player->CInput->up = false;
					break;
				}
				case sf::Keyboard::A:
				{
					m_player->CInput->left = false;
					break;
				}
				case sf::Keyboard::D:
				{
					m_player->CInput->right = false;
					break;
				}
				case sf::Keyboard::S:
				{
					m_player->CInput->down = false;
					break;
				}
				default:break;

				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// std::cout << event.mouseButton.x << "\t" << event.mouseButton.y<<"\n";
					SpawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					SpawnSpecialWeapon(m_player); 
				}
				break;
			}


			default:break;
			}
		}
	}
}

void Game::sCollision()
{
	if (m_player->CTransform->pos.x <= m_player->CShape->circle.getRadius())
	{
		m_player->CTransform->pos.x = m_player->CShape->circle.getRadius();
	}
	if (m_player->CTransform->pos.x >= m_window.getSize().x - m_player->CShape->circle.getRadius())
	{
		m_player->CTransform->pos.x = m_window.getSize().x - m_player->CShape->circle.getRadius();
	}
	if (m_player->CTransform->pos.y <= m_player->CShape->circle.getRadius())
	{
		m_player->CTransform->pos.y = m_player->CShape->circle.getRadius();
	}
	if (m_player->CTransform->pos.y >= m_window.getSize().y - m_player->CShape->circle.getRadius())
	{
		m_player->CTransform->pos.y = m_window.getSize().y - m_player->CShape->circle.getRadius();
	}

	for (auto& e : m_manager.getEntities("Enemy"))
	{
		if (e->CTransform->pos.x <= e->CShape->circle.getRadius())
		{
			e->CTransform->velocity.x *= -1; 
		}
		if (e->CTransform->pos.x >= m_window.getSize().x - e->CShape->circle.getRadius())
		{
			e->CTransform->velocity.x *= -1;
		}
		if (e->CTransform->pos.y <= e->CShape->circle.getRadius())
		{
			e->CTransform->velocity.y *= -1;
		}
		if (e->CTransform->pos.y >= m_window.getSize().y - e->CShape->circle.getRadius())
		{
			e->CTransform->velocity.y *= -1;
		}
	}

	for (auto& b : m_manager.getEntities("Bullet"))
	{
		for (auto& e : m_manager.getEntities("Enemy"))
		{
			Vec2 D(b->CTransform->pos.x - e->CTransform->pos.x, b->CTransform->pos.y - e->CTransform->pos.y); 
			float L = std::sqrtf(D.x * D.x + D.y * D.y); 
			if (L <= b->CCollision->radius + e->CCollision->radius)
			{
				SpawnSmallEnemies(e); 
				m_score += e->CScore->score; 
				b->destroy();
				e->destroy();
			}
		}
	}

	for (auto& b : m_manager.getEntities("Bullet"))
	{
		for (auto& e : m_manager.getEntities("SmallEnemy"))
		{
			Vec2 D(b->CTransform->pos.x - e->CTransform->pos.x, b->CTransform->pos.y - e->CTransform->pos.y);
			float L = std::sqrtf(D.x * D.x + D.y * D.y);
			if (L <= b->CCollision->radius + e->CCollision->radius)
			{
				m_score += e->CScore->score;
				b->destroy();
				e->destroy();
			}
		}
	}


	for (auto& e : m_manager.getEntities("Enemy"))
	{
		Vec2 D(m_player->CTransform->pos.x - e->CTransform->pos.x, m_player->CTransform->pos.y - e->CTransform->pos.y);
		float L = std::sqrtf(D.x * D.x + D.y * D.y);
		if (L <= m_player->CCollision->radius + e->CCollision->radius)
		{
			m_player->CTransform->pos = Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2); 
			e->destroy(); 
		}
	}

	for (auto& e : m_manager.getEntities("SmallEnemy"))
	{
		Vec2 D(m_player->CTransform->pos.x - e->CTransform->pos.x, m_player->CTransform->pos.y - e->CTransform->pos.y);
		float L = std::sqrtf(D.x * D.x + D.y * D.y);
		if (L <= m_player->CCollision->radius + e->CCollision->radius)
		{
			m_player->CTransform->pos = Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2);
			e->destroy();
		}
	}

}

void Game::sRender()
{
	m_window.clear();

	
	for (auto& e : m_manager.getEntities())
	{
	e->CShape->circle.setPosition(e->CTransform->pos.x, e->CTransform->pos.y);
	if (e->tag()!="player")
	{
		e->CTransform->angle += 3.0f;
	}
	
	e->CShape->circle.setRotation(e->CTransform->angle); 
	m_window.draw(e->CShape->circle);
	}
	m_Scoretext.setString("Score: " + std::to_string(m_score));
	m_window.draw(m_crosshairSprite); 
	m_window.draw(m_Scoretext); 
	m_window.display();

}

void Game::sLifeSpan()
{
	
	for (auto& e : m_manager.getEntities("Bullet"))
	{	
		e->CLifespan->remain -= 1;
		if (e->CLifespan->remain == 0)
		{
			e->destroy(); 
		}
		int alpha = static_cast<int>(255 - (255 * e->CLifespan->remain / e->CLifespan->total));
		if (alpha < 0) alpha = 0;
		e->CShape->circle.setFillColor(sf::Color(m_Bullet_CFG.fillcolor_r, m_Bullet_CFG.fillcolor_g, m_Bullet_CFG.fillcolor_b, -alpha));
		e->CShape->circle.setOutlineColor(sf::Color(m_Bullet_CFG.outLinecolor_r, m_Bullet_CFG.outLinecolor_g, m_Bullet_CFG.outLinecolor_b, -alpha));
		
	}

	for (auto& e : m_manager.getEntities("SmallEnemy"))
	{
		e->CLifespan->remain -= 1;
		if (e->CLifespan->remain == 0)
		{
			e->destroy();
		}
		int alpha = static_cast<int>(255 - (255 * e->CLifespan->remain / e->CLifespan->total));
		if (alpha < 0) alpha = 0;
		e->CShape->circle.setFillColor(sf::Color(e->CShape->circle.getFillColor().r , e->CShape->circle.getFillColor().g  , e->CShape->circle.getFillColor().b, -alpha));
		e->CShape->circle.setOutlineColor(sf::Color(e->CShape->circle.getOutlineColor().r , e->CShape->circle.getOutlineColor().g , e->CShape->circle.getOutlineColor().b , -alpha));
	}


}

void Game::sEnemySpawner()
{
	if (m_score > 10000)
	{
		m_Enemy_CFG.spawnInterval = 50;
		if (m_score > 20000)
		{
			m_Enemy_CFG.spawnInterval = 40;
			if (m_score > 30000)
			{
				m_Enemy_CFG.spawnInterval = 30;
			}
		}
	}
	if (m_currentframe - m_lastTimeEnemySpawned == m_Enemy_CFG.spawnInterval)
	{
		SpawnEnemy(); 
		m_lastTimeEnemySpawned = m_currentframe; 
	}
}

void Game::SpawnPlayer()
{
	m_player = m_manager.addEntity("player"); 
	m_player->CShape = std::make_shared<CShape>(m_Player_CFG.shape_radius, m_Player_CFG.nVertices, m_Player_CFG.fillColor, m_Player_CFG.outLineColor, m_Player_CFG.outlineThickness);
	m_player->CCollision = std::make_shared<CCollision>(m_Player_CFG.collision_radius);
	m_player->CTransform =std::make_shared<CTransform>(Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2),Vec2(0.f , 0.f) , 0.f);
	m_player->CInput = std::make_shared<CInput>();
}

void Game::SpawnEnemy()
{
	auto e = m_manager.addEntity("Enemy"); 

	int vert = rand() % (m_Enemy_CFG.maxVertices - m_Enemy_CFG.minVertices) + m_Enemy_CFG.minVertices; 
	e->CShape = std::make_shared<CShape>(m_Enemy_CFG.shape_radius, vert, sf::Color(rand() % 255, rand() % 255, rand() % 255), sf::Color(m_Enemy_CFG.outLinecolor_r, m_Enemy_CFG.outLinecolor_g, m_Enemy_CFG.outLinecolor_b), m_Enemy_CFG.outlineThickness);
	e->CCollision = std::make_shared<CCollision>(m_Enemy_CFG.collision_radius); 
	
	float rx = rand() % (m_window.getSize().x - 2 * m_Enemy_CFG.shape_radius) + m_Enemy_CFG.shape_radius; 
	float ry = rand() % (m_window.getSize().y - 2 * m_Enemy_CFG.shape_radius) + m_Enemy_CFG.shape_radius;

	int xspeed = rand() %(m_Enemy_CFG.maxSpeed - m_Enemy_CFG.minSpeed) + m_Enemy_CFG.minSpeed;
	int signX = (rand() % 2 == 0) ? 1 : -1;
	xspeed *= signX;


	int yspeed = rand() % (m_Enemy_CFG.maxSpeed - m_Enemy_CFG.minSpeed) + m_Enemy_CFG.minSpeed;
	int signY = (rand() % 2 == 0) ? 1 : -1;
	yspeed *= signY;

	e->CTransform = std::make_shared<CTransform>(Vec2(rx, ry), Vec2(xspeed , yspeed), 4);
	e->CScore = std::make_shared<CScore>(e->CShape->circle.getPointCount() * 100); 

}

void Game::SpawnSmallEnemies(std::shared_ptr<Entity> ent)
{	
	int angle = 0; 
	int add = 360 / ent->CShape->circle.getPointCount(); 	
	
	float x, y; 
	for (int i = 0; i < ent->CShape->circle.getPointCount(); i++)
	{	 	
		auto e = m_manager.addEntity("SmallEnemy");
		e->CShape = std::make_shared<CShape>(ent->CShape->circle.getRadius() / 2, ent->CShape->circle.getPointCount(), ent->CShape->circle.getFillColor(), ent->CShape->circle.getOutlineColor(), ent->CShape->circle.getOutlineThickness()); 
		e->CCollision = std::make_shared<CCollision>(ent->CCollision->radius / 2); 
		e->CLifespan = std::make_shared<CLifespan>(m_Enemy_CFG.smallEnemyLifespan); 
		x = std::cos(angle)* m_Enemy_CFG.minSpeed;
		y = std::sin(angle)*m_Enemy_CFG.minSpeed;
		e->CScore = std::make_shared<CScore>( ent->CScore->score/ent->CShape->circle.getPointCount()); 
		e->CTransform = std::make_shared<CTransform>(ent->CTransform->pos, Vec2(x ,y), 0);	
		angle += add;	
	}


}

void Game::SpawnBullet(const std::shared_ptr<Entity> ent, const Vec2& mousePos)
{
	auto e = m_manager.addEntity("Bullet"); 
	e->CShape = std::make_shared<CShape>(m_Bullet_CFG.shape_radius, m_Bullet_CFG.nVertices, sf::Color(m_Bullet_CFG.fillcolor_r, m_Bullet_CFG.fillcolor_g, m_Bullet_CFG.fillcolor_b), sf::Color(m_Bullet_CFG.outLinecolor_r, m_Bullet_CFG.outLinecolor_g, m_Bullet_CFG.outLinecolor_b), m_Bullet_CFG.outlineThickness);
	e->CCollision = std::make_shared<CCollision>(m_Bullet_CFG.collision_radius);
	e->CLifespan = std::make_shared<CLifespan>(m_Bullet_CFG.lifeSpan);

	Vec2 D(mousePos.x - ent->CTransform->pos.x , mousePos.y - ent->CTransform->pos.y);
	D.normalize(); 

	e->CTransform = std::make_shared<CTransform>(ent->CTransform->pos, Vec2(m_Bullet_CFG.speed * D.x, m_Bullet_CFG.speed*D.y), 0); 
	
	

}

void Game::SpawnSpecialWeapon(std::shared_ptr<Entity> ent)
{
	
	std::vector<std::shared_ptr<Entity>> container; 
	for (int i = 0; i < m_weapon_CFG.nSpheres; i++)
	{
		container.push_back(m_manager.addEntity("Special")); 
		container[i]->CShape = std::make_shared<CShape>(m_weapon_CFG.shape_radius, m_weapon_CFG.nVertices, m_weapon_CFG.fillColor, m_weapon_CFG.outLineColor, m_weapon_CFG.outlineThickness);
		float angle = 2 * 3.14159265 * i / m_weapon_CFG.nSpheres; // Равномерное распределение сфер вокруг круга	
		float x = ent->CTransform->pos.x + m_weapon_CFG.spinningRadius * std::cos(angle);
		float y = ent->CTransform->pos.y + m_weapon_CFG.spinningRadius * std::sin(angle);

		//float vx = m_weapon_CFG.spinningRadius * std::cos(angle * 3.14159265 / 180); 
		//float vy = m_weapon_CFG.spinningRadius * std::sin(angle * 3.14159265 / 180);

		//container[i]->CTransform = std::make_shared<CTransform>(Vec2(x, y), Vec2(vx , vy), 0.f); 
	}
}

Game::Game()
{
	m_window.create(sf::VideoMode(1280, 760), "GB" , sf::Style::Fullscreen);// sf::Style::Fullscreen); 
	m_window.setFramerateLimit(60); 
	m_window.setMouseCursorVisible(false);

	m_crosshairTexture.loadFromFile("crosshair.png"); 
	m_crosshairSprite.setTexture(m_crosshairTexture); 
	m_crosshairSprite.setOrigin(m_crosshairSprite.getLocalBounds().width / 2, m_crosshairSprite.getLocalBounds().height / 2);
	m_crosshairSprite.setScale(0.5f, 0.5f);

	if (!m_font.loadFromFile("my.otf"))
	{
	//	std::cout << "not open";
	}
	m_Scoretext.setFont(m_font);
	m_Scoretext.setFillColor(sf::Color::White);
	m_Scoretext.setCharacterSize(35);
	SpawnPlayer(); 
}

void Game::run()
{
	while (m_running)
	{
		if (!m_paused) {
			m_manager.update();
			sEnemySpawner(); 
			sLifeSpan();
			sMovement();
			sCollision();
			sUserInput();
			sRender();
			m_currentframe++; 
		}
		else
		{
			sUserInput(); 
			sRender(); 
		}
		 
		
	}
}
