#include "GameOver.h"

GameOver::GameOver()
{
	shader = shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera = std::make_unique<Camera>();
	text = std::make_unique<TextLabel>("Timer", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50), glm::vec3(1, 1, 1));
	gameover = std::make_unique<Background>();
}

GameOver::~GameOver()
{
}

void GameOver::Init(int winner)
{
	switch (winner)
	{
	case 1:
		gameover->Init("Resources/Textures/player1wins.bmp", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
		break;

	case 2:
		gameover->Init("Resources/Textures/player2wins.bmp", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
		break;

	default:
		gameover->Init("Resources/Textures/draw.bmp", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
		break;
	}
}

void GameOver::Update()
{
	text->Update("You Win!");
	m_world.Step(1 / 60, 6, 2);
}

void GameOver::Render()
{
	text->Render();
	gameover->Render();

}