#pragma once
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <memory>
#include "Menu.h"
#include "Scene.h"
#include "GameOver.h"
#include "HowToPlay.h"
#include "Input.h"
#include "Dependencies/Box2D/Box2D.h"

std::unique_ptr<Menu> menuScene;
std::unique_ptr<Scene> gameScene;
std::unique_ptr<HowToPlay> howToPlayScene;
std::unique_ptr<GameOver> gameoverScene;

GameState g_currentScene = MENU;
bool g_bIsChangingScene = false;

void Init()
{
	gameoverScene = std::make_unique<GameOver>();
	switch (g_currentScene)
	{
	case MENU:
		menuScene = std::make_unique<Menu>();
		menuScene->Init();
		break;

	case GAME:
		gameScene = std::make_unique<Scene>();
		gameScene->Init();
		break;

	case HOWTOPLAY:
		howToPlayScene = std::make_unique<HowToPlay>();
		howToPlayScene->Init();
		break;

	case GAMEOVER:
		gameoverScene = std::make_unique<GameOver>();
		gameoverScene->Init(gameScene->WhoWon());
		break;

	default:
		break;
	}
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	switch (g_currentScene)
	{
	case MENU:
		menuScene->Render();
		break;
	case GAME:
		gameScene->Render();
		break;
	case HOWTOPLAY:
		howToPlayScene->Render();
		break;
	case GAMEOVER:
		gameoverScene->Render();
		break;
	default:
		break;
	}

	switch (g_currentScene)
	{
	case MENU:
		if (g_currentScene != menuScene->GetCurrentScene())
		{
			g_currentScene = menuScene->GetCurrentScene();
			g_bIsChangingScene = true;
		}
		break;

	case GAME:
		if (g_currentScene != gameScene->GetCurrentScene())
		{
			g_currentScene = gameScene->GetCurrentScene();
			g_bIsChangingScene = true;
		}
		break;

	case GAMEOVER:
		if (g_currentScene != gameoverScene->GetCurrentScene())
		{
			g_currentScene = gameoverScene->GetCurrentScene();
			g_bIsChangingScene = true;
		}
		break;

	case HOWTOPLAY:
		if (g_currentScene != howToPlayScene->GetCurrentScene())
		{
			g_currentScene = howToPlayScene->GetCurrentScene();
			g_bIsChangingScene = true;
		}
		break;
	}

	glutSwapBuffers();
}

void Update()
{
	if (g_bIsChangingScene)
	{
		Init();
		g_bIsChangingScene = false;
	}

	switch (g_currentScene)
	{
	case MENU:
		menuScene->Update();
		break;

	case GAME:
		gameScene->Update();
		break;

	case HOWTOPLAY:
		howToPlayScene->Update();
		break;

	case GAMEOVER:
		gameoverScene->Update();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	srand(glutGet(GLUT_ELAPSED_TIME));
	glutInit(&argc, argv);
	glutInitDisplayMode(
		GLUT_DEPTH |
		GLUT_DOUBLE |
		GLUT_RGBA |
		GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL");
	glewInit();
	Init();

	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutMainLoop();
	return(0);
}