#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <memory>

using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();
	m_scene = new Scene();
	m_scene->SetGame(this);

	nu::Engine::Get().GetAudio().AddSound("alert", "alert.mp3");
	nu::Engine::Get().GetAudio().AddSound("scream", "scream.mp3");
	
	m_titleText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 64.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Asteriods Cpp edition", Color{ 1.0f, 1.0f, 1.0f });


	m_gameOverText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 64.0f));
	m_gameOverText->Create(Engine::Get().GetRenderer(), "GAME OVER", Color{ 1.0f, 0.0f, 0.0f });

	m_scoreText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));
	m_livesText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));
	m_healthText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));


	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case GameState::Title:
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_health = 100;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		if (m_health == 0)
		{
			m_health = 100;
		}
		m_scene->RemoveAllActors();
		SpawnPlayer();
		m_gameState = GameState::Game;
		break;
	case GameState::Game:
		m_spawntimer -= dt;

		if (m_spawntimer <= 0)
		{
			m_spawntimer = nu::Randomfloat(3.0f, 5.0f);
			SpawnEnemy();
			for (int i = 0; i < 3; i++)
			{
				SpawnAsteriods();
			}
		}
		break;
	case GameState::GameOver:
		nu::Engine::Get().GetAudio().PlaySound("scream");
		m_scene->RemoveAllActors();
		if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;
	}

	Game::Update(dt);

}

void SpaceGame::Draw(nu::Renderer& renderer)
{
	res_t<Texture> background = Resources().Get<Texture>("textures/background.jpg", Engine::Get().GetRenderer());

	//use to draw background later
	renderer.DrawTexture(*background, 0.0f, 0.0f, 0.0f, 2.0f);

	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		m_titleText->Draw(renderer, 400, 400);
		break;
	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
		break;
	case SpaceGame::GameState::Game:
		//draw score/lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f,1.0f,1.0f });
		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f,1.0f,1.0f });
		m_healthText->Create(renderer, "Health " + std::to_string(m_health), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 32, 32);
		m_livesText->Draw(renderer, 1020, 32);
		m_healthText->Draw(renderer, 640, 32);
		break;
	case SpaceGame::GameState::GameOver:
		m_gameOverText->Draw(renderer, 400, 400);
		break;
	default:
		break;
	}

	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	m_health -= 25;
	if (m_health == 0)
	{
		m_lives--;
	}
	if (m_lives == 0)
	{
		m_gameState = GameState::GameOver;
	}
	else
	{
		m_gameState = GameState::StartLevel;
	}
}

void SpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.tag = "Enemy";
	//enemyDesc.model = Assets::enemyModel;
	enemyDesc.texture = Resources().Get<Texture>("textures/enemy.png", Engine::Get().GetRenderer());
	enemyDesc.transform =  nu::Transform{ nu::Vector2{nu::Randomfloat(1280), nu::Randomfloat(1024)}, 90.0f, 1.0f};
	enemyDesc.speed = 450.0f;
	enemyDesc.damping = 1.0f;
	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnAsteriods()
{
	EnemyDesc asteriod;
	asteriod.name = "Asteriod";
	asteriod.tag = "Enemy";
	//asteriod.model = Assets::asteriodModel;
	asteriod.texture = Resources().Get<Texture>("textures/asteroid.png", Engine::Get().GetRenderer());
	asteriod.transform = nu::Transform{ nu::Vector2{nu::Randomfloat(1280), nu::Randomfloat(1024)}, 90.0f, nu::Randomfloat(1.0f, 5.0f)};
	asteriod.speed = 100.0f;
	asteriod.damping = 1.0f;
	m_scene->AddActor(std::move(std::make_unique<Enemy>(asteriod)));
}

void SpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	//playerDesc.model = Assets::playerModel;
	playerDesc.texture = Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());
	playerDesc.transform = nu::Transform{ nu::Vector2{640.0f, 512.0f}, 0.0f, 1.0f };
	playerDesc.speed = 800.0f;
	playerDesc.damping = 1.0f;
	std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
	m_scene->AddActor(std::move(player));
}
