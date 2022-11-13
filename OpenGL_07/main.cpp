
#include "GL_Cube.h"
#include "GL_Robot.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();

Camera mainCamera;

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

GL_Cube cube_Object;
Cube obstacle_Objcet;
Collider obstacle_Collider;
GL_Robot robot_Object;

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
	obstacle_Objcet.Draw();
	robot_Object.Draw();

	for (int i = 0; i < 4; i++)
	{
		robot_Object.OnCollision(cube_Object.collider[i]);
	}
	robot_Object.OnCollision(obstacle_Collider);
	

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
	case 'a':
		Collider::isPrint = !Collider::isPrint;
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

	case 'z':
		mainCamera.transform.worldPosition.z += 0.1;
		break;
	case 'Z':
		mainCamera.transform.worldPosition.z -= 0.1;
		break;

	case 'x':
		mainCamera.transform.worldPosition.x += 0.1f;
		break;
	case 'X':
		mainCamera.transform.worldPosition.x -= 0.1f;
		break;

	case 'y':
		mainCamera.yRotate++;
		mainCamera.cameraPos.x = 2 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 2 * cos(radians(mainCamera.yRotate));
		break;
	case 'Y':
		mainCamera.yRotate--;
		mainCamera.cameraPos.x = 2 * sin(radians(mainCamera.yRotate));
		mainCamera.cameraPos.z = 2 * cos(radians(mainCamera.yRotate));
		break;

	case 'i':
		cube_Object.ReSet();
		robot_Object.ReSet();
		mainCamera.yRotate = 0;
		mainCamera.cameraPos.z = 2;
		mainCamera.transform.ReSet();
		break;

	case 'j':
		robot_Object.worldSpeed.y = 0.02;
		break;
		
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		robot_Object.worldSpeed.x = 0;
		robot_Object.worldSpeed.z = 0;
		robot_Object.worldSpeed.x -= 0.01;
		robot_Object.transform.worldRotation.y = -90;
		robot_Object.movingRotateSpeed = 1;
		break;
	case GLUT_KEY_RIGHT:
		robot_Object.worldSpeed.x = 0;
		robot_Object.worldSpeed.z = 0;
		robot_Object.worldSpeed.x += 0.01;
		robot_Object.transform.worldRotation.y = 90;
		robot_Object.movingRotateSpeed = 1;
		break;

	case GLUT_KEY_DOWN:
		robot_Object.worldSpeed.x = 0;
		robot_Object.worldSpeed.z = 0;
		robot_Object.worldSpeed.z += 0.01;
		robot_Object.transform.worldRotation.y = 0;
		robot_Object.movingRotateSpeed = 1;
		break;
	case GLUT_KEY_UP:
		robot_Object.worldSpeed.x = 0;
		robot_Object.worldSpeed.z = 0;
		robot_Object.worldSpeed.z -= 0.01;
		robot_Object.transform.worldRotation.y = 180;
		robot_Object.movingRotateSpeed = 1;
		break;
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

	Object::camera = &mainCamera;
	Collider::camera = &mainCamera;

	mainCamera.isProjection = true;

	cube_Object.Init();
	cube_Object.isActive = true;

	obstacle_Objcet.Init();
	obstacle_Objcet.isActive = true;
	obstacle_Objcet.transform.worldScale *= 0.1;
	obstacle_Objcet.transform.worldScale.x *= 1.5;
	obstacle_Objcet.transform.worldScale.y *= 1.5;
	obstacle_Objcet.transform.worldPosition.y = -0.4f;
	obstacle_Objcet.transform.worldPosition.x = 0.3f;
	obstacle_Objcet.transform.worldPosition.z = 0.3f;
	obstacle_Collider.InitTransform(obstacle_Objcet.transform);
	vec3 box[2] = { vec3(0.5,0,0.5), vec3(-0.5,0, -0.5) };
	obstacle_Collider.SetBox(box,2);
	obstacle_Collider.tag = "Obstacle";
	

	robot_Object.Init();
	robot_Object.isActive = true;
	robot_Object.transform.worldScale *= 0.1;
}