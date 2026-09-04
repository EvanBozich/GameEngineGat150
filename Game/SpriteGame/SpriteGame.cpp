#include "SpriteGame.h"
#include "Engine.h"
#include <SDL3/SDL.h>
#include <memory>

using namespace nu;

bool SpriteGame::Initialize()
{
	SetWorkingDirectory("SpriteGame");

	Game::Initialize();
	m_scene = std::make_unique<Scene>();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");



	nu::Engine::Get().GetAudio().AddSound("alert", "alert.mp3");
	nu::Engine::Get().GetAudio().AddSound("scream", "scream.mp3");
	
	m_titleText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 64.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Platformer", Color{ 1.0f, 1.0f, 1.0f });


	m_gameOverText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 64.0f));
	m_gameOverText->Create(Engine::Get().GetRenderer(), "GAME OVER", Color{ 1.0f, 0.0f, 0.0f });

	m_scoreText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));
	m_livesText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));
	m_healthText = new Text(Resources().Get<nu::Font>("Fonts/ArcadeClassic.ttf", 20.0f));



	return true;
}

void SpriteGame::Update(float dt)
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
		m_health = 0;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		if (m_health == 0)
		{
			m_health = 100;
		}
		m_scene->RemoveAllActors();
		m_scene->Load("data/level.json");
		SpawnPlayer();
		m_gameState = GameState::Game;
		break;
	case GameState::Game:
		m_spawntimer -= dt;

		if (m_spawntimer <= 0)
		{
			m_spawntimer = nu::Randomfloat(3.0f, 5.0f);
			SpawnEnemy();
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

void SpriteGame::Draw(nu::Renderer& renderer)
{
	res_t<Texture> background = Resources().Get<Texture>("textures/bg03.png", Engine::Get().GetRenderer());

	renderer.EnableCamera(false);

	//use to draw background later
	renderer.DrawTexture(*background, 0.0f, 0.0f, 0.0f, 2.0f);

	switch (m_gameState)
	{
	case SpriteGame::GameState::Title:
		m_titleText->Draw(renderer, 400, 400);
		break;
	case SpriteGame::GameState::StartGame:
		break;
	case SpriteGame::GameState::StartLevel:
		break;
	case SpriteGame::GameState::Game:
		//draw score/lives
		m_scoreText->Create(renderer, "Score  " + std::to_string(m_score), { 1.0f,1.0f,1.0f });
		m_livesText->Create(renderer, "Lives  " + std::to_string(m_lives), { 1.0f,1.0f,1.0f });
		m_healthText->Create(renderer, "Health  " + std::to_string(m_health), { 1.0f,1.0f,1.0f });
		m_scoreText->Draw(renderer, 32, 32);
		m_livesText->Draw(renderer, 1020, 32);
		m_healthText->Draw(renderer, 500, 32);
		break;
	case SpriteGame::GameState::GameOver:
		m_gameOverText->Draw(renderer, 400, 400);
		break;
	default:
		break;
	}

	renderer.EnableCamera();

	Game::Draw(renderer);
}

void SpriteGame::OnPlayerDead()
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

void SpriteGame::SpawnEnemy()
{
	int rand = nu::RandomInt(2);

	if (rand == 1)
	{
		auto enemy = Factory::Instance().Create<nu::Actor>("FlyingEnemyPrototype");
		enemy->SetPosition({ nu::Randomfloat(1280), nu::Randomfloat(1024) });
		m_scene->AddActor(std::move(enemy));
	}
	else
	{
		auto enemy = Factory::Instance().Create<nu::Actor>("EnemyPrototype");
		enemy->SetPosition({ nu::Randomfloat(1280), nu::Randomfloat(1024) });
		m_scene->AddActor(std::move(enemy));
	}

}


void SpriteGame::SpawnPlayer()
{
	auto player = Factory::Instance().Create<nu::Actor>("PlayerPrototype");
	m_scene->AddActor(std::move(player));

}
