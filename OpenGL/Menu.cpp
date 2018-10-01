#include "Menu.h"

Menu::Menu()
{
	shader = shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera = std::make_unique<Camera>();
	text = std::make_unique<TextLabel>("Timer", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50), glm::vec3(1, 1, 1));
	menu = std::make_unique<Background>();
}

Menu::~Menu()
{
}

void Menu::Init()
{
	menu->Init("Resources/Textures/MainMenu.bmp", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), shader, true, COLLIDER_CIRCLE, m_world);
}

void Menu::Update()
{
	text->Update("You Win!");
	m_world.Step(1 / 60, 6, 2);
}

void Menu::Render()
{
	text->Render();
	menu->Render();
}