#pragma once
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <memory>
#include "Menu.h"
#include "Scene.h"
#include "GameOver.h"
#include "Input.h"
#include "Dependencies/Box2D/Box2D.h"

std::unique_ptr<Menu> menu;
std::unique_ptr<Scene> scene;
std::unique_ptr<GameOver> gameover;

GameState gamestate = MENU;

bool MenuButtons()
{
	// 'e' = EXIT
	if (GetButtonDown('e'))
	{
		exit(0);
	}
	// 'g' = MENU
	if (GetButtonDown('g'))
	{
		return true;
	}
	return false;
}

void Init()
{
	gameover = std::make_unique<GameOver>();
	switch (gamestate)
	{
	case MENU:
		menu = std::make_unique<Menu>();
		menu->Init();
		break;

	case SCENE:
		scene = std::make_unique<Scene>();
		scene->Init();
		break;

	case GAMEOVER:
		break;

	default:
		break;
	}
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	switch (gamestate)
	{
	case MENU:
		menu->Render();
		break;
	case SCENE:
		scene->Render();
		break;
	case GAMEOVER:
		gameover->Render();
		break;
	default:
		break;
	}
	glutSwapBuffers();
}

void Update()
{
	switch (gamestate)
	{
	case MENU:
		menu->Update();
		if (MenuButtons() == true)
		{
			gamestate = SCENE;
			Init();
		}
		break;

	case SCENE:
		scene->Update();
		if (scene->GameOver() == true)
		{
			gamestate = GAMEOVER;
			switch (scene->WhoWon())
			{
			case 1:
				gameover->Init(1);
				break;

			case 2:
				gameover->Init(2);
				break;

			default:
				gameover->Init(0);
				break;
			}
		}
		break;

	case GAMEOVER:
		gameover->Update();
		if (MenuButtons() == true)
		{
			gamestate = SCENE;
			Init();
		}
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