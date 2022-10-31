
#include "GL_Crane.h"
#include "GL_Coordinate.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();

Color windowColor;

GL_Coordinate coordinate_Object;

GL_Crane crane_Object;
Cube plan_Object;

bool is_Polygon = false;
bool is_CullFace = false;

// 문제를 풀기 위한 임시 변수

bool isPressA = false;
bool isPress_t = false;
bool isPress_T = false;


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

	if (isPressA)
		mainCamera.transform.worldRotation.y += 1;
	if (isPress_t)
	{
		if (crane_Object.cube_Object[Cube_Right].zRotate <= 90 && crane_Object.cube_Object[Cube_Right].zRotate > 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += -1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = -0.001;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0.001;
			crane_Object.cube_Object[Cube_Right].zRotate += 1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = -0.001;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = -0.001;
		}
		else if (crane_Object.cube_Object[Cube_Right].zRotate <= 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += -1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0.001;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0.001;
			crane_Object.cube_Object[Cube_Right].zRotate += 1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0.001;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = -0.001;
		}
		else
		{
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0;

			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0;
		}
	}

	if (isPress_T)
	{
		if (crane_Object.cube_Object[Cube_Right].zRotate >= 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += 1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0.001;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = -0.001;
			crane_Object.cube_Object[Cube_Right].zRotate += -1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0.001;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0.001;
		}
		else if (crane_Object.cube_Object[Cube_Right].zRotate >= -90 && crane_Object.cube_Object[Cube_Right].zRotate < 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += 1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = -0.001;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = -0.001;
			crane_Object.cube_Object[Cube_Right].zRotate += -1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = -0.001;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0.001;
		}
		else
		{
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0;

			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0;
		}
	}

	coordinate_Object.Draw();
	crane_Object.Draw();
	plan_Object.Draw();

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
	case 'p': // 직각 투영
		isProjection = !isProjection;
		break;

	case 'z':
		mainCamera.transform.worldPosition.z += speed;
		break;
	case 'Z':
		mainCamera.transform.worldPosition.z -= speed;
		break;

	case 'x':
		mainCamera.transform.worldPosition.x += speed;
		break;
	case 'X':
		mainCamera.transform.worldPosition.x -= speed;
		break;

	case 'y':
		mainCamera.isRotate = false;
		mainCamera.transform.localRotation.y += 1;
		break;
	case 'Y':
		mainCamera.isRotate = false;
		mainCamera.transform.localRotation.y -= 1;
		break;

	case 'r':
		mainCamera.isRotate = true;
		mainCamera.transform.worldRotation.y += 1;
		break;
	case 'R':
		mainCamera.isRotate = true;
		mainCamera.transform.worldRotation.y -= 1;
		break;

	case 'a':
		mainCamera.isRotate = true;
		isPressA = true;
		break;
	case 'A':
		isPressA = false;
		break;

	case 's':
		isPressA = false;
		break;
	case 'c':
		isPressA = false;
		mainCamera.transform.ReSet();
		mainCamera.transform.localRotation.x = 45;
		mainCamera.transform.localPivot.y = -3;
		mainCamera.transform.worldPosition.z = -4.5;

		crane_Object.ReSet();
		break;
		
	case 'b':
		if(crane_Object.worldSpeed.x != 1)
			crane_Object.worldSpeed.x = speed;
		else
			crane_Object.worldSpeed.x = 0;
		break;	
	case 'B':
		if (crane_Object.worldSpeed.x != -1)
			crane_Object.worldSpeed.x = -speed;
		else
			crane_Object.worldSpeed.x = 0;
		break;

	case 'm':
		for (int i = Cube_Handle; i < Cube_MaxIndex; i++)
		{
			if(crane_Object.cube_Object[i].worldRotateSpeed.y == 0)
				crane_Object.cube_Object[i].worldRotateSpeed.y = 1;
			else
				crane_Object.cube_Object[i].worldRotateSpeed.y = 0;
		}
		break;
	case 'M':
		for (int i = Cube_Handle; i < Cube_MaxIndex; i++)
		{
			if (crane_Object.cube_Object[i].worldRotateSpeed.y == 0)
				crane_Object.cube_Object[i].worldRotateSpeed.y = -1;
			else
				crane_Object.cube_Object[i].worldRotateSpeed.y = 0;
		}
		break;
	case 't':
		isPress_t = !isPress_t;
		isPress_T = false;
		if (!isPress_t || !isPress_T)
		{
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0;

			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0;
		}
		break;
	case 'T':
		isPress_T = !isPress_T;
		isPress_t = false;
		if (!isPress_T || !isPress_t)
		{
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0;

			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0;
		}
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

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

	mainCamera.transform.localRotation.x = 45;
	mainCamera.transform.localPivot.y = -3;
	mainCamera.transform.worldPosition.z = -4.5;

	coordinate_Object.Init();
	coordinate_Object.isActive = true;

	crane_Object.Init();
	crane_Object.isActive = true;

	plan_Object.Init();
	plan_Object.color.SetRandomColor();
	plan_Object.isActive = true;
	plan_Object.transform.worldScale.x *= 10;
	plan_Object.transform.worldScale.z *= 10;
	plan_Object.transform.worldPosition.y = -1;
}