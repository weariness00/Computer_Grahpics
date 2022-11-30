#include "GL_Maze.h"
#include "Player.h"
#include "Collapse_Cube.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseEntry(int state);

void PrintCMD();

Color windowColor;

bool is_Polygon = false;
bool is_CullFace = false;

// ���콺
bool isMouseRight = false;

Camera* fristCamera;
Camera camera;
Camera mapCamera;
Camera playerPitchCamera;
Render objectRender;

list<Object*> Object::allObject;

GL_Maze maze_Object;
CollapseCube collapseCube_Object;

Cube plan_Obj;
Player player;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("21");
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	{
		windowColor.R = windowColor.G = windowColor.B = 0;
		
		int x, y;
		cout << "ũ�⸦ �Է����ֽʽÿ� (x, y �� �� 3 �̻��� ũ�⸸ �����մϴ�.)" << endl;
		cin >> x >> y;

		Render::objectRenedr = &objectRender;
		fristCamera = &camera;
		camera.name = "Main";
		camera.cameraPos.y = 0.5;
		camera.cameraPos.z = (x+y)/4;
		camera.isProjection = true;

		mapCamera.isProjection_XZ = true;
		mapCamera.target_Pos = &player.transform;

		playerPitchCamera.isPitch = true;
		playerPitchCamera.name = "Pitch";
		playerPitchCamera.target_Pos = &player.transform;

		
		Object::modelLocation = glGetUniformLocation(s_program, "modelTransform");
		Object::vColorLocation = glGetUniformLocation(s_program, "vColor");
		FrameTime::currentTime = clock();


		maze_Object.wall_number = { x,y };
		collapseCube_Object.transform.worldScale *= 0.1;
		collapseCube_Object.transform.worldScale *= (x + y) / 1.5;
		collapseCube_Object.defaultCameraDistance = camera.cameraPos.z;

		for (const auto& obj : Object::allObject)
			obj->Init();
		for (const auto& collider : Collider::allCollider)
			collider->Init();

		player.transform.worldScale *= 0.1;

		plan_Obj.collider.isCollide = false;
		plan_Obj.transform.worldScale *= 0.2;
		plan_Obj.transform.worldScale.x *= x;
		plan_Obj.transform.worldScale.z *= y;
		plan_Obj.transform.worldPosition.y = -0.1;
		plan_Obj.color.SetColor({ 1,1,1,1 });

		if (x % 2 == 1)
			plan_Obj.transform.worldPosition.x = 0.1;
		if (y % 2 == 1)
			plan_Obj.transform.worldPosition.z = 0.1;

		PrintCMD();
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


	// ��� ������Ʈ ������Ʈ
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

	// ��� �ݶ��̴� ��ġ ������Ʈ
	for (const auto& collider : Collider::allCollider)
	{
		if (!collider->isCollide)
			continue;
		collider->GetBox_OBB();
	}

	// ��� �浹 ó��
	for (const auto& obj : Object::allObject)
	{
		if (!obj->ActiveSelf())
			continue;
		obj->Collision();
	}

	// �浹�� ��ü���� �и� ó��
	//for (const auto& collider : Collider::allCollider)
	//	collider->OnTrigger();

	{
		// ���� Viewport
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, windowSize_W, windowSize_H);
		Camera::mainCamera = fristCamera;

		objectRender.Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (const auto& collider : Collider::allCollider)
			collider->DrawBox();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	{	// Map ViewPort
		glDisable(GL_DEPTH_TEST);
		glViewport(windowSize_W * 3 / 4, windowSize_H * 3 / 4, windowSize_W / 4, windowSize_H / 4);
		Camera::mainCamera = &mapCamera;

		objectRender.Draw();
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
	Object::key = key;
	switch (key)
	{
	case 'q':
		exit(1);
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
		maze_Object.MakeMaze();
		break;
	case 'e':
		player.SetActive(true);
		player.transform.worldPosition.x = 0;
		player.transform.worldPosition.z = 0;
		break;

	case 'c':
		player.SetActive(false);
		fristCamera = &camera;
		camera.cameraPos = vec3(0, 0, 5);
		camera.yRotate = 0;
		maze_Object.ReSet();
		
		break;
	case '1':
		fristCamera = &playerPitchCamera;
		playerPitchCamera.target_Pos = &player.transform;
		playerPitchCamera.cameraDirection = vec3(0, 30, 20);	// scale�� �� target�� ũ�⋚���� ������ ������ ũ�� �����
		playerPitchCamera.cameraPos = vec3(0,30,0);
		break;
	case '2':
		fristCamera = &playerPitchCamera;
		playerPitchCamera.target_Pos = &player.transform;
		playerPitchCamera.cameraDirection = vec3(0, 0, 40);
		playerPitchCamera.cameraPos = vec3(0,50,-30);
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
		Collider::isPrint = !Collider::isPrint;
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

	//if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	//	isMouseLeft = true;
	//else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	//	isMouseLeft = false;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isMouseRight = !isMouseRight;
	}

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	Vector2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	ShowCursor(isMouseRight);
	if (!isMouseRight)
	{
		Vector2 diffPos = (mouse_Pos - StartMouse) / 10;
		playerPitchCamera.cameraDirection.y += diffPos.y;
		player.transform.worldRotation.y -= diffPos.x;
	}

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	glutPostRedisplay();
}

void MouseEntry(int state)
{
	if (state == GLUT_LEFT)
	{
		if (!isMouseRight)
		{
			glutWarpPointer(windowSize_W / 2, windowSize_H / 2);
			StartMouse = { (float)windowSize_W / 2, (float)windowSize_H / 2 };
			StartMouse = Coordinate(StartMouse);
			StartMouse.y = -StartMouse.y;
		}
	}
}

void PrintCMD()
{
	cout << "Player�� ���� ���� �𵨸��� ������ ��ġ�ε� Metrial�� �������� ���� ���� �Ͼ�� �Դϴ�.;;" << endl;
	cout << endl;
	cout << "q : ���α׷� ����" << endl;
	cout << "f : �տ� ���̴� ������ü�� �μ�����. (f�� �ѹ� �� ������ ���h)" << endl;
	cout << endl;
	cout << "e : Player ����" << endl;
	cout << "ĳ���� �̵� w a s d" << endl;
	cout << "Space Bar : �÷��̾� �뽬" << endl;
	cout << "���콺 ��Ŭ���ϸ� ȭ�� ȸ���� ���߸� ���콺 ���αⰡ ���� " << endl;
	cout << endl;
	cout << "1 : 1��Ī ī�޶�" << endl;
	cout << "p : ���� ����" << endl;
	cout << "o : ���� ����" << endl;
	cout << "y/Y : ����� �������� ī�޶� y������ ��/�� ȸ��" << endl;
	cout << endl;
	cout << "+/- : ����� �ӵ��� ����/���� �Ѵ�." << endl;
	cout << "m : ����� �� �Ʒ��� �����δ�." << endl;
	cout << "v : ����� ������ �����ȴ�. ���� ����� �������� �����/�ٽ� �����δ�." << endl;
	cout << "r : ���ο� �̷� ����" << endl;
	cout << endl;
	cout << "c : ��� �ʱ�ȭ" << endl;
}