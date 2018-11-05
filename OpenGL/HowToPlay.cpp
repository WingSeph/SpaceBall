#include "HowToPlay.h"
#include "Dependencies/freeglut/freeglut.h"

HowToPlay::HowToPlay()
{
	shader = shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera = std::make_unique<Camera>();
	controls = std::make_unique<Background>();
	m_titleText = new TextLabel("Spaceball", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 + 100), glm::vec3(1, 1, 1));
	m_titleText->SetScale(2);
	m_backButtonText = new TextLabel("Back", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2 - 175), glm::vec3(1, 1, 1));
	m_camera = std::make_unique<Camera>();
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::Init()
{
	controls->Init("Resources/Textures/Menu.png", glm::vec3(0, 0, 0), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
	SetCurrentScene(GameState::HOWTOPLAY);
}

void HowToPlay::Update()
{
	m_world.Step(1 / 60, 6, 2);

	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	m_deltaTime = (currentTime - m_previousTime) * 0.001f;
	m_previousTime = currentTime;

	if (CInput::GetButtonDown(32) || CInput::GetButtonDown(13))
	{
		SetCurrentScene(GameState::MENU);
	}

	CInput::Update();
}

void HowToPlay::Render()
{
	controls->Render();
}