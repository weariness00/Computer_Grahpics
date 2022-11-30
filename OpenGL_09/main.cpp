#include "Cube.h"
#include "GL_Tetrahedron.h"
#include "Light.h"
#include "Circle.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseEntry(int state);

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

// 마우스
bool isMouseRight = false;

Camera* fristCamera;
Camera camera;
Render objectRender;

list<Object*> Object::allObject;
Light light;

Cube cube;
GL_Tetrahedron tetrahedron;
Sphere sphere[3];
Circle circle;

bool isProblem = true; // true : 22, false : 23 
bool isDrawShape = false; // true : cube, false : 사각뿔
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("22");
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	{
		windowColor.R = windowColor.G = windowColor.B = 0;
		
		Render::objectRenedr = &objectRender;
		fristCamera = &camera;
		camera.name = "Main";
		camera.cameraPos.y = 0.5;
		camera.cameraPos.z = 0.5;
		camera.isProjection = true;

		Object::modelLocation = glGetUniformLocation(s_program, "modelTransform");
		Object::vColorLocation = glGetUniformLocation(s_program, "vColor");
		Light::lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		Light::lightColorLocation = glGetUniformLocation(s_program, "lightColor");
		Camera::viewPosLocation = glGetUniformLocation(s_program, "viewPos");
		FrameTime::currentTime = clock();

		cube.transform.worldScale *= 0.1;
		tetrahedron.transform.worldScale *= 0.1;
		tetrahedron.transform.worldPosition.z = 1;

		light.transform.worldPosition.z = 0.5;
		light.dis = 0.5;
		int i = 1;
		for (auto& obj : sphere)
		{
			obj.SetActive(false);
			obj.color.SetRandomColor();
			obj.transform.worldScale *= 0.1 * i;
			obj.transform.worldPosition.x = (i - 1) * (0.3f * i);
			i++;
		}
		for (const auto& obj : Object::allObject)
			obj->Init();
		//for (const auto& collider : Collider::allCollider)
		//	collider->Init();
	}

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKeyBoard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutEntryFunc(MouseEntry);
	glutMainLoop();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// 모든 오브젝트 업데이트
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

	//// 모든 콜라이더 위치 업데이트
	//for (const auto& collider : Collider::allCollider)
	//{
	//	if (!collider->isCollide)
	//		continue;
	//	collider->GetBox_OBB();
	//}

	//// 모든 충돌 처리
	//for (const auto& obj : Object::allObject)
	//{
	//	if (!obj->ActiveSelf())
	//		continue;
	//	obj->Collision();
	//}

	// 충돌한 물체들의 밀림 처리
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	{
		// 현재 Viewport
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		
		objectRender.Draw();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//for (const auto& collider : Collider::allCollider)
		//	collider->DrawBox();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	Camera::mainCamera = fristCamera;
	Object::key = -1;
	Object::specialKey = -1;

	FrameTime::oneFrame = (clock() - FrameTime::currentTime) / 1000.0f;
	FrameTime::currentTime += FrameTime::oneFrame * 1000.0f;

	glutSwapBuffers();
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	windowSize_W = w;
	windowSize_H = h;
}

void KeyBoard(unsigned char key, int x, int y)	
{
	vec3 norm;
	float dis;
	Object::key = key;
	switch (key)
	{
	case 'q':
		exit(1);
		break;

	case 'n':
		isDrawShape = !isDrawShape;

		cube.SetActive(false);
		tetrahedron.SetActive(false);

		if (isDrawShape)
			cube.SetActive(true);
		else
			tetrahedron.SetActive(true);
		break;

	case 'm':
		light.SetActive(!light.ActiveSelf());
		break;

	case 'o':
		fristCamera = &camera;
		camera.isProjection = false;
		camera.isProjection_XY = true;
		camera.cameraPos.z = 2;
		break;
	case 'p':
		fristCamera = &camera;
		camera.isProjection = true;
		camera.isProjection_XY = false;
		break;

	case 'y':
		camera.yRotate++;
		camera.cameraPos.x = 5 * sin(radians(camera.yRotate));
		camera.cameraPos.z = 5 * cos(radians(camera.yRotate));
		break;
	case 'Y':
		camera.yRotate--;
		camera.cameraPos.x = 5 * sin(radians(camera.yRotate));
		camera.cameraPos.z = 5 * cos(radians(camera.yRotate));
		break;

	case 'r':
		light.yRotate++;
		light.transform.worldPosition.x = light.dis * sin(radians(light.yRotate));
		light.transform.worldPosition.z = light.dis * cos(radians(light.yRotate));
		break;
	case 'R':
		light.yRotate--;
		light.transform.worldPosition.x = light.dis * sin(radians(light.yRotate));
		light.transform.worldPosition.z = light.dis * cos(radians(light.yRotate));
		break;

	case 'z':
		norm = normalize(light.transform.worldPosition) * FrameTime::oneFrame;
		dis = length(norm);
		light.transform.worldPosition -= norm;
		light.dis -= dis;
		circle.radius = light.dis;
		break;
	case 'Z':
		norm = normalize(light.transform.worldPosition) * FrameTime::oneFrame;
		dis = length(norm);
		light.transform.worldPosition += norm;
		light.dis += dis;
		circle.radius = light.dis;
		break;


	// 23
	case 'c':
		light.color.SetRandomColor();
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	Object::specialKey = key;

	switch (key)
	{
	case GLUT_KEY_F1:
		isProblem = !isProblem;
		if (!isProblem)
		{
			cube.SetActive(false);
			tetrahedron.SetActive(false);
			for (auto& obj : sphere)
			{
				obj.SetActive(true);
			}
		}
		else
		{
			cube.SetActive(true);
			tetrahedron.SetActive(true);
			for (auto& obj : sphere)
			{
				obj.SetActive(false);
			}
		}
		
		break;
	case GLUT_KEY_F11:
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
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

void MouseEntry(int state)
{

}