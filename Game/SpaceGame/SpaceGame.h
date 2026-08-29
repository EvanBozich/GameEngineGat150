#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"

class SpaceGame : public nu::Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};
public:
	SpaceGame() = default;

	bool Initialize() override;

	 void Update(float dt) override;
	 void Draw(class nu::Renderer& renderer) override;

	 void OnPlayerDead();
	 void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnAsteriods();
	int m_score = 0;
	int m_lives = 0;
	int m_health = 0;
	float m_spawntimer = 0;
	float m_stateTimer = 0;

	GameState m_gameState = GameState::Title;

	nu::res_t <nu::Font> m_titleFont;
	nu::res_t <nu::Font> m_gameFont;
	nu::res_t <nu::Font> m_gameOverFont;

	 //nu::Font* m_titleFont = nullptr;
	 nu::Text* m_titleText = nullptr;

	 //nu::Font* m_gameOverFont = nullptr;
	 nu::Text* m_gameOverText = nullptr;

	// nu::Font* m_gameFont = nullptr;
	 nu::Text* m_livesText = nullptr;
	 nu::Text* m_scoreText = nullptr;
	 nu::Text* m_healthText = nullptr;
};