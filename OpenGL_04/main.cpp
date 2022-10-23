#define MainNumber 1

#include "GL_Cube.h"
#include "GL_Tetrahedron.h"
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

bool is_Polygon = false;
bool is_CullFace = false;

GL_Cube cube_Object;
GL_Tetrahedron triangleCone_Object;
GL_Coordinate coordinate_Object;

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

	cube_Object.Draw();
	triangleCone_Object.Draw();
	coordinate_Object.Draw();

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
		if (is_Polygon)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	case 'z': // cube
		cube_Object.isActive = !cube_Object.isActive;
		break;
	case 'Z': // 삼각 뿔
		triangleCone_Object.isActive = !triangleCone_Object.isActive;
		break;

	case 'y': // 자전
		if (cube_Object.rotateSpeed.y == 0)
			cube_Object.rotateSpeed.y = 1;
		else
			cube_Object.rotateSpeed.y = 0;

		if (triangleCone_Object.rotateSpeed.y == 0)
			triangleCone_Object.rotateSpeed.y = 1;
		else
			triangleCone_Object.rotateSpeed.y = 0;
		break;
	case 't':	// 윗면 회전
		if (cube_Object.planObjet[Cube_Up].rotateSpeed.x == 0)
			cube_Object.planObjet[Cube_Up].rotateSpeed.x = 1;
		else
			cube_Object.planObjet[Cube_Up].rotateSpeed.x = 0;
		break;
	// 앞면 열기
	case 'f': 
		cube_Object.planObjet[Cube_Forward].rotateSpeed.x = 1;
		cube_Object.planObjet[Cube_Forward].transform.worldPivot.z = -0.5f;
		cube_Object.planObjet[Cube_Forward].transform.worldPosition.y = -0.5f;
		break;
	case 'F':
		cube_Object.planObjet[Cube_Forward].rotateSpeed.x = -1;
		cube_Object.planObjet[Cube_Forward].transform.worldPivot.z = -0.5f;
		cube_Object.planObjet[Cube_Forward].transform.worldPosition.y = -0.5f;
		break;
	// 옆면 열기
	case '1':
		cube_Object.planObjet[Cube_Left].speed.y = 0.01;
		cube_Object.planObjet[Cube_Right].speed.y = 0.01;
		break;
	case '2':
		cube_Object.planObjet[Cube_Left].speed.y = -0.01;
		cube_Object.planObjet[Cube_Right].speed.y = -0.01;
		break;

	case 'o':
		for (int i = 0; i < 4; i++)
			triangleCone_Object.triangleObject[i].rotateSpeed.x = 1;
		break;
	case 'O':
		for (int i = 0; i < 4; i++)
			triangleCone_Object.triangleObject[i].rotateSpeed.x = -1;

	case 'p': // 직각 투영
		isProjection = !isProjection;
		break;
		
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	Vector2 realStartMouse = RealPosition(StartMouse);

	cube_Object.transform.worldPosition = vec3(realStartMouse.x, realStartMouse.y, cube_Object.transform.worldPosition.z);

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

	cube_Object.Init();
	triangleCone_Object.Init();
	coordinate_Object.Init();

	cube_Object.isActive = true;
	triangleCone_Object.isActive = false;
	coordinate_Object.isActive = true;
}