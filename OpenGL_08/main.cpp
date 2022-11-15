
#include "GL_Cube.h"
#include "Cube.h"
#include "Sphere.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

Color windowColor;

Camera mainCamera;

Render objectRender;

bool is_Polygon = false;
bool is_CullFace = false;

bool isMouseLeft = false;

int ballCount = 0;

int main(int argc, char** argv)
{
	GL_Cube wall_Objcet;
	Cube cube_Object[3];
	Sphere sphere_Object[5];

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
	{
		windowColor.R = windowColor.G = windowColor.B = 0;

		Camera::mainCamera = &mainCamera;

		mainCamera.isProjection = true;

		Render::mainRender = &objectRender;

		Object::modelLocation = glGetUniformLocation(s_program, "modelTransform");
		Object::vColorLocation = glGetUniformLocation(s_program, "vColor");

		for (const auto& obj : Object::allObject)
		{
			obj->Init();
		}

		for (int i = 0; i < 3; i++)
		{
			cube_Object[i].transform.worldScale *= 0.05 * (i + 1);
			cube_Object[i].transform.worldPosition.x = (i + 1) * 0.1;
			cube_Object[i].transform.worldPosition.y = -(i + 1) * 0.1;
			cube_Object[i].transform.worldPosition.z = -(i + 1) * 0.1;
			cube_Object[i].color.SetRandomColor();
		}
	}

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
	
	// 모든 오브젝트 업데이트
	for (const auto& obj : Object::allObject)
		obj->Update();

	// 모든 콜라이더 위치 업데이트
	for (const auto& collider : Collider::allCollider)
		collider->GetBox();

	// 모든 충돌 처리
	for (const auto& obj : Object::allObject)
		obj->Collision();

	// 충돌한 물체들의 밀림 처리
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	objectRender.Draw();

	glutSwapBuffers();
	glutPostRedisplay();
	//Time_Duration = floor(difftime(time(NULL), Start_Time));
	//glutTimerFunc(0, FrameTimer, 1);
	//Start_Time = time(NULL);
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

	case 'z':
		mainCamera.transform.worldRotation.z += 1;
		break;
	case 'Z':
		mainCamera.transform.worldRotation.z -= 1;
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

	case 'b':
		if (ballCount >= 5)
			break;

		for (const auto& obj : Object::allObject)
		{
			if (obj->name == "Sphere" && obj->isActive == false)
			{
				obj->isActive = true;
				obj->transform.worldPosition.z = RandomFloat(-0.3f, 0.3f);
				break;
			}
		}
		ballCount++;
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_UP:

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

	if (button == GLUT_LEFT_BUTTON)
		isMouseLeft = !isMouseLeft;

	Vector2 realStartMouse = RealPosition(StartMouse);

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	Vector2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	if (isMouseLeft)
	{
		Vector2 gapDis = mouse_Pos - StartMouse;
		mainCamera.transform.worldRotation.z += gapDis.x;
	}

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;
	glutPostRedisplay();
}


