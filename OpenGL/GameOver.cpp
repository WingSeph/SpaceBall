#include "GameOver.h"

GameOver::GameOver()
{
	shader = shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera = std::make_unique<Camera>();
	m_titleText = new TextLabel("Player Wins", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 + 100), glm::vec3(1.0f, 1.0f, 1.0f));
	m_titleText->SetScale(2);
	text = std::make_unique<TextLabel>("Timer", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50), glm::vec3(1, 1, 1));
	m_retryButtonText = new TextLabel("Retry", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH /2 - 75, WINDOW_HEIGHT / 2 - 75), glm::vec3(0.6f, 0.6f, 0.6f));
	m_quitButtonText = new TextLabel("Quit", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 - 125), glm::vec3(0.6f, 0.6f, 0.6f));
	gameover = std::make_unique<Background>();
}

GameOver::~GameOver()
{
}

void GameOver::Init(int winner)
{
	m_iCurrMenuSelection = 0;

	SetCurrentScene(GameState::GAMEOVER);

	switch (winner)
	{
	case 1:
		m_titleText->Update("Player 1 Wins!");
		m_titleText->SetPosition(WINDOW_WIDTH / 8 - 10, WINDOW_HEIGHT / 2 + 100);
		m_titleText->SetColor(0, 1, 0);
		break;

	case 2:
		m_titleText->Update("Player 2 Wins!");
		m_titleText->SetPosition(WINDOW_WIDTH / 8 - 10, WINDOW_HEIGHT / 2 + 100);
		m_titleText->SetColor(1, 0, 0);
		break;

	default:
		m_titleText->Update("It's a Draw!");
		m_titleText->SetPosition(WINDOW_WIDTH / 4 - 35, WINDOW_HEIGHT / 2 + 100);
		m_titleText->SetColor(1, 1, 1);
		break;
	}
}

void GameOver::Update()
{
	m_world.Step(1 / 60, 6, 2);

	if (CInput::GetButtonDown('s') || CInput::GetButtonDown('k'))
	{
		if (m_iCurrMenuSelection == 1)
		{
			m_iCurrMenuSelection = 0;
		}
		else if (m_iCurrMenuSelection == 0)
		{
			m_iCurrMenuSelection = 1;
		}
	}
	if (CInput::GetButtonDown('w') || CInput::GetButtonDown('i'))
	{
		if (m_iCurrMenuSelection == 0)
		{
			m_iCurrMenuSelection = 1;
		}
		else if (m_iCurrMenuSelection == 1)
		{
			m_iCurrMenuSelection = 0;
		}
	}

	if (CInput::GetButtonDown(32) || CInput::GetButtonDown(13))
	{
		if (m_iCurrMenuSelection == 0)
		{
			SetCurrentScene(GameState::GAME);
		}
		else if (m_iCurrMenuSelection == 1)
		{
			CInput::Update();
			SetCurrentScene(GameState::MENU);
		}
	}

	if (m_iCurrMenuSelection == 0)
	{
		m_retryButtonText->SetColor(1, 1, 1);
		m_quitButtonText->SetColor(0.4f, 0.4f, 0.4f);
	}
	else if (m_iCurrMenuSelection == 1)
	{
		m_retryButtonText->SetColor(0.4f, 0.4f, 0.4f);
		m_quitButtonText->SetColor(1, 1, 1);
	}

	CInput::Update();
}

void GameOver::Render()
{
	m_titleText->Render();
	m_retryButtonText->Render();
	m_quitButtonText->Render();
}