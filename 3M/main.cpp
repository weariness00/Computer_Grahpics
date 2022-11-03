#include "GL_Maze.h"
#include "Player.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

void InitMain();

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

Camera mainCamera;
Camera mapCamera;

Player player;
GL_Maze maze_Object;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example1");
	
	glEnable(GL_DEPTH_TEST);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	InitMain();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Object::camera = &mainCamera;

		maze_Object.Draw();
	}

	{
		// Map ViewPort
		glViewport(windowSize_W * 3 / 4, windowSize_H * 3 / 4, windowSize_W / 4, windowSize_H / 4);
		Object::camera = &mapCamera;

		maze_Object.Draw();
	}


	glutSwapBuffers();
	Time_Duration = floor(difftime(time(NULL), Start_Time));
	if (Time_Duration > 0)
		glutTimerFunc(1000 / 60 - Time_Duration, FrameTimer, 1);
	else
		glutPostRedisplay();
	Start_Time = time(NULL);
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	windowSize_W = w;
	windowSize_H = h;
}

void KeyBoard(unsigned char key, int x, int y)	
{
	float speed = 0.01f;
	switch (key)
	{
	case 'q':
		exit(1);
		break;
	case 'u':
		is_Polygon = !is_Polygon;

		break;
	case 'h':
		is_CullFace = !is_CullFace;
		if (is_CullFace)
		{
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
		}
		break;

	case 'o':
		mainCamera.isProjection = false;
		mainCamera.isProjection_XY = true;
		break;
	case 'p':
		mainCamera.isProjection = true;
		mainCamera.isProjection_XY = false;
		break;

	case 'm':
		maze_Object.isRandomScaleMoveing = !maze_Object.isRandomScaleMoveing;
		break;

	case 'y':
		mainCamera.yRotate++;
		mainCamera.cameraPos.x = 5 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 5 * cos(radians(mainCamera.yRotate));
		break;
	case 'Y':
		mainCamera.yRotate--;
		mainCamera.cameraPos.x = 5 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 5 * cos(radians(mainCamera.yRotate));
		break;

	case 'r':
		maze_Object.MakeMaze();
		break;
	case 'v':
		maze_Object.SetWall_YScale(2.0f);
		break;
	case 's':
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	float speed = 0.01f;
	switch (key)
	{
	case GLUT_KEY_F1:
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case GLUT_KEY_LEFT:
		player.transform.worldPosition.x -= speed;
		break;
	case GLUT_KEY_RIGHT:
		player.transform.worldPosition.x += speed;
		break;
	case GLUT_KEY_UP:
		player.transform.worldPosition.z += speed;
		break;
	case GLUT_KEY_DOWN:
		player.transform.worldPosition.z -= speed;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	Vector2 realStartMouse = RealPosition(StartMouse);

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	Vector2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;
	glutPostRedisplay();
}

void InitMain() 
{
	windowColor.R = windowColor.G = windowColor.B = 0;

	mainCamera.isProjection = true;

	mapCamera.isProjection_XZ = true;

	maze_Object.Init();
	maze_Object.isActive = true;
}