#include "Menu.h"
#include "Input.h"

Menu::Menu()
{
	shader = shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera = std::make_unique<Camera>();
	menu = std::make_unique<Background>();
	m_titleText = new TextLabel("Spaceball", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 + 100), glm::vec3(1, 1, 1));
	m_titleText->SetScale(2);
	m_playButtonText = new TextLabel("Start", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2 - 75), glm::vec3(0.6f, 0.6f, 0.6f));
	m_howToPlayButtonText = new TextLabel("How To Play", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2 - 125), glm::vec3(0.6f, 0.6f, 0.6f));
	m_exitButtonText = new TextLabel("Exit Game", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2 - 175), glm::vec3(0.6f, 0.6f, 0.6f));
}

Menu::~Menu()
{
}

void Menu::Init()
{
	menu->Init("Resources/Textures/Menu2.png", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
	SetCurrentScene(MENU);
}

void Menu::Update()
{
	m_world.Step(1 / 60, 6, 2);

	if (GetButtonDown('s') || GetButtonDown('k'))
	{
		if (m_iCurrMenuSelection == 2)
		{
			m_iCurrMenuSelection = 0;
		}
		else
		{
			m_iCurrMenuSelection++;
		}
	}
	if (GetButtonDown('w') || GetButtonDown('i'))
	{
		if (m_iCurrMenuSelection == 0)
		{
			m_iCurrMenuSelection = 2;
		}
		else
		{
			m_iCurrMenuSelection--;
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
			SetCurrentScene(GameState::HOWTOPLAY);
		}
		else if (m_iCurrMenuSelection == 2)
		{
			exit(0);
		}
	}

	if (m_iCurrMenuSelection == 0)
	{
		m_playButtonText->SetColor(1, 1, 1);
		m_howToPlayButtonText->SetColor(0.4f, 0.4f, 0.4f);
		m_exitButtonText->SetColor(0.4f, 0.4f, 0.4f);
	}
	else if (m_iCurrMenuSelection == 1)
	{
		m_playButtonText->SetColor(0.4f, 0.4f, 0.4f);
		m_howToPlayButtonText->SetColor(1, 1, 1);
		m_exitButtonText->SetColor(0.4f, 0.4f, 0.4f);
	}
	else if (m_iCurrMenuSelection == 2)
	{
		m_playButtonText->SetColor(0.4f, 0.4f, 0.4f);
		m_howToPlayButtonText->SetColor(0.4f, 0.4f, 0.4f);
		m_exitButtonText->SetColor(1, 1, 1);
	}

	CInput::Update();
}

void Menu::Render()
{
	m_titleText->Render();
	m_playButtonText->Render();
	m_howToPlayButtonText->Render();
	m_exitButtonText->Render();
}