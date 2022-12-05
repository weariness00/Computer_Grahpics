
#include "GL_Crane.h"
#include "Light.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();

list<Object*> Object::allObject;
list<Mesh*> Mesh::allMesh;

Render objectRender;

Camera camera;
Camera xyCamera;
Camera xzCamera;

Color windowColor;
GL_Crane crane_Object;
Cube plan_Object;

Light light;

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
	glewInit();

	InitShader();
	glewExperimental = GL_TRUE;
	Mesh::modelLocation = glGetUniformLocation(s_program, "modelTransform");
	Mesh::vColorLocation = glGetUniformLocation(s_program, "vColor");
	Light::lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	Light::lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	Camera::viewPosLocation = glGetUniformLocation(s_program, "viewPos");

	Render::meshtRender = &objectRender;
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

	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->Update();
	}

	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;

		obj->SetMatrix();
	}

	if (isPressA)
		camera.transform.worldRotation.y += 1;
	if (isPress_t)
	{
		if (crane_Object.cube_Object[Cube_Right].zRotate <= 90 && crane_Object.cube_Object[Cube_Right].zRotate > 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += -1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = -0.0002;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0.0005;
			crane_Object.cube_Object[Cube_Right].zRotate += 1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = -0.0002;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = -0.0005;
		}
		else if (crane_Object.cube_Object[Cube_Right].zRotate <= 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += -1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0.0002;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0.0005;
			crane_Object.cube_Object[Cube_Right].zRotate += 1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0.0002;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = -0.0005;
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
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0.0002;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = -0.0005;
			crane_Object.cube_Object[Cube_Right].zRotate += -1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0.0002;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0.0005;
		}
		else if (crane_Object.cube_Object[Cube_Right].zRotate >= -90 && crane_Object.cube_Object[Cube_Right].zRotate < 0)
		{
			crane_Object.cube_Object[Cube_Left].zRotate += 1;
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = -0.0002;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = -0.0005;
			crane_Object.cube_Object[Cube_Right].zRotate += -1;
			crane_Object.cube_Object[Cube_Right].worldSpeed.y = -0.0002;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0.0005;
		}
		else
		{
			crane_Object.cube_Object[Cube_Left].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Left].worldSpeed.x = 0;

			crane_Object.cube_Object[Cube_Right].worldSpeed.y = 0;
			crane_Object.cube_Object[Cube_Right].worldSpeed.x = 0;
		}
	}

	{
		/*glViewport(50, windowSize_H/5, windowSize_W /2 , windowSize_H / 2);*/
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = &camera;

		Render::meshtRender->Draw();
	}
	
	//{
	//	glViewport(windowSize_W * 3 / 5, windowSize_H / 2, windowSize_W * 3 / 10, windowSize_H * 3 / 10);
	//	Camera::mainCamera = &xyCamera;

	//	Render::meshtRender->Draw();

	//}

	//{
	//	glViewport(windowSize_W * 3/ 5, 100, windowSize_W * 3 / 10, windowSize_H * 3 / 10);
	//	Camera::mainCamera = &xzCamera;

	//	Render::meshtRender->Draw();
	//}

	glutSwapBuffers();
	glutTimerFunc(0, FrameTimer, 1);
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
	//case 'p': // 직각 투영
	//	isProjection = !isProjection;
	//	break;

	case 'z':
		camera.transform.worldPosition.z += speed;
		break;
	case 'Z':
		camera.transform.worldPosition.z -= speed;
		break;

	case 'x':
		camera.transform.worldPosition.x += speed;
		break;
	case 'X':
		camera.transform.worldPosition.x -= speed;
		break;

	case 'y':
		camera.isRotate = false;
		camera.transform.localRotation.y += 1;
		break;
	case 'Y':
		camera.isRotate = false;
		camera.transform.localRotation.y -= 1;
		break;

	case 'r':
		camera.yRotate++;
		camera.cameraPos.x = cos(radians(camera.yRotate));
		camera.cameraPos.z = sin(radians(camera.yRotate));
		break;
	case 'R':
		camera.yRotate--;
		camera.cameraPos.x = cos(radians(camera.yRotate));
		camera.cameraPos.z = sin(radians(camera.yRotate));
		break;

	case 'a':
		camera.isRotate = true;
		isPressA = true;
		break;
	case 'A':
		isPressA = false;
		break;

	case 's':
		isPressA = false;
		isPress_T = false;
		isPress_t = false;

		crane_Object.worldSpeed.x = 0;
		for (int i = 0; i < Cube_MaxIndex; i++)
		{
			crane_Object.cube_Object[i].worldRotateSpeed.y = 0;
			crane_Object.cube_Object[i].worldSpeed.y = 0;
			crane_Object.cube_Object[i].worldSpeed.x = 0;
		}
		break;
	case 'c':
		isPressA = false;
		camera.transform.ReSet();
		camera.transform.localRotation.x = 45;
		camera.transform.localPivot.y = -3;
		camera.transform.worldPosition.z = -4.5;

		crane_Object.ReSet();
		break;
		
	case 'b':
		if(crane_Object.worldSpeed.x == 0)
			crane_Object.worldSpeed.x = speed;
		else
			crane_Object.worldSpeed.x = 0;
		break;	
	case 'B':
		if (crane_Object.worldSpeed.x == 0)
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
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	glutPostRedisplay();
}

void InitMain() 
{
	windowColor.R = windowColor.G = windowColor.B = 0;
	for (const auto& obj : Object::allObject)
		obj->Init();
	for (const auto& mesh : Mesh::allMesh)
		mesh->MeshInit();

	light.transform.worldPosition.x = 1;

	camera.isPitch = true;
	camera.target_Pos = new Transform;
	camera.cameraPos.y = 1;
	camera.cameraPos.z = 1;

	xyCamera.isProjection_XY = true;
	xzCamera.isProjection_XZ = true;

	plan_Object.color.SetRandomColor();
	plan_Object.transform.worldScale.x *= 10;
	plan_Object.transform.worldScale.z *= 10;
	plan_Object.transform.worldPosition.y = -1;
}