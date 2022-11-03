#include "GL_Atom.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();

Color windowColor;

GL_Atom sunAtom_Object;
GL_Atom starAtom_Object[3];
GL_Atom moonAtom_Object[3];

bool is_Polygon = false;
bool is_CullFace = false;

float ro = 45.0f;

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
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].radian += starAtom_Object[i].radianSpeed;
		}

		starAtom_Object[0].transform.worldPivot.x = cos(radians(starAtom_Object[0].radian));
		starAtom_Object[0].transform.worldPivot.y = sin(radians(starAtom_Object[0].radian));

		starAtom_Object[1].transform.worldPivot.x = 0.75 * cos(radians(starAtom_Object[1].radian));
		starAtom_Object[1].transform.worldPivot.z = 0.75 * sin(radians(starAtom_Object[1].radian + 80));
													
		starAtom_Object[2].transform.worldPivot.x = 0.75 *cos(radians(starAtom_Object[2].radian));
		starAtom_Object[2].transform.worldPivot.z = 0.75 *sin(radians(starAtom_Object[2].radian - 80));

		for (int i = 0; i < 3; i++)
		{
			moonAtom_Object[i].radian += moonAtom_Object[i].radianSpeed;
		}

		moonAtom_Object[0].transform.worldPivot.x = 10 * cos(radians(moonAtom_Object[0].radian));
		moonAtom_Object[0].transform.worldPivot.y = 10 * sin(radians(moonAtom_Object[0].radian));

		moonAtom_Object[1].transform.worldPivot.x = 34 * 0.75 * cos(radians(moonAtom_Object[1].radian));
		moonAtom_Object[1].transform.worldPivot.z = 20 * 0.75 * sin(radians(moonAtom_Object[1].radian + 85));

		moonAtom_Object[2].transform.worldPivot.x = 34 * 0.75 * cos(radians(moonAtom_Object[2].radian));
		moonAtom_Object[2].transform.worldPivot.z = 20 * 0.75 * sin(radians(moonAtom_Object[2].radian - 85));
	}


	sunAtom_Object.Draw();
	for (int i = 0; i < 3; i++)
	{
		starAtom_Object[i].Draw();
		moonAtom_Object[i].Draw();
	}

	glutSwapBuffers();
	Time_Duration = floor(difftime(time(NULL), Start_Time));
	glutTimerFunc(1000 / 60 - Time_Duration, FrameTimer, 1);
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
	switch (key)
	{
	case 'T':
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case 'u':
		is_Polygon = !is_Polygon;

		sunAtom_Object.shpere_Object.SetDrawStyle(is_Polygon);
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].shpere_Object.SetDrawStyle(is_Polygon);
			moonAtom_Object[i].shpere_Object.SetDrawStyle(is_Polygon);
		}
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
	case 'p': // 직각 투영
		isProjection = !isProjection;
		break;

	case 'y':
		sunAtom_Object.shpere_Object.rotateSpeed.z = 1;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].shpere_Object.rotateSpeed.z = 1;
			moonAtom_Object[i].shpere_Object.rotateSpeed.z = 1;
		}
		break;
	case 'Y':
		sunAtom_Object.shpere_Object.rotateSpeed.z = -1;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].shpere_Object.rotateSpeed.z = -1;
			moonAtom_Object[i].shpere_Object.rotateSpeed.z = -1;
		}
		break;

	case 'z':
		sunAtom_Object.transform.worldPosition.z += 0.1;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.z += 0.1;
			moonAtom_Object[i].transform.worldPosition.z += 0.1;
		}
		break;
	case 'x':
		sunAtom_Object.transform.worldPosition.z += -0.1;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.z += -0.1;
			moonAtom_Object[i].transform.worldPosition.z += -0.1;
		}
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	float s = 0.01f;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		sunAtom_Object.transform.worldPosition.x += -s;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.x += -s;
			moonAtom_Object[i].transform.worldPosition.x += -s;
		}
		break;
	case GLUT_KEY_RIGHT:
		sunAtom_Object.transform.worldPosition.x += s;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.x += s;
			moonAtom_Object[i].transform.worldPosition.x += s;
		}
		break;
	case GLUT_KEY_UP:
		sunAtom_Object.transform.worldPosition.y += s;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.y += s;
			moonAtom_Object[i].transform.worldPosition.y += s;
		}
		break;
	case GLUT_KEY_DOWN:
		sunAtom_Object.transform.worldPosition.y += -s;
		for (int i = 0; i < 3; i++)
		{
			starAtom_Object[i].transform.worldPosition.y += -s;
			moonAtom_Object[i].transform.worldPosition.y += -s;
		}
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

	sunAtom_Object.Init();
	sunAtom_Object.isActive = true;
	sunAtom_Object.shpere_Object.transform.worldScale *= 0.2;

	for (int i = 0; i < 3; i++)
	{
		starAtom_Object[i].Init();
		starAtom_Object[i].isActive = true;
		starAtom_Object[i].circle_Objcet[1].isActive = false;
		starAtom_Object[i].circle_Objcet[2].isActive = false;
		
		starAtom_Object[i].circle_Objcet[0].transform.worldScale *= 0.5;
		starAtom_Object[i].shpere_Object.transform.worldScale *= 0.5 * 0.2;

		starAtom_Object[i].radianSpeed = 1 + i;
	}

	for (int i = 0; i < 3; i++)
	{
		moonAtom_Object[i].Init();
		moonAtom_Object[i].isActive = true;
		for (int j = 0; j < 3; j++)
			moonAtom_Object[i].circle_Objcet[j].isActive = false;

		moonAtom_Object[i].transform.worldScale *= 0.2 * 0.5 * 0.5;

		moonAtom_Object[i].radianSpeed = 1 + i;
	}
}