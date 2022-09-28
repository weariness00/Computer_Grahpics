
#define MainNumber 2

#if MainNumber == 1
#include "GL_Rectangle.h"

GL_Rectangle* rect_Obj = new GL_Rectangle[1];
Vector2 startMouse_Pos;

Color color = {1,1,1,1};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timer(int value);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

void SetRandomWindowColor();

void main(int argc,char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Glew 없음" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "Glew 있음" << endl;

	rect_Obj[0].transform.SetScale({ 10,10 });

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, Timer, 1);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(windowColor.R, windowColor.G, windowColor.B, windowColor.A);
	glClear(GL_COLOR_BUFFER_BIT);

	rect_Obj[0].Update();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	windowSize_W = w;
	windowSize_H = h;
	glViewport(0, 0, w, h);
}

void Timer(int value)
{
	if (!isOnTimer)
		return;

	SetRandomWindowColor();
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 1);
}

void KeyBoard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'f1':
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case 'r':
		color = { 1,0,0 ,color.A };
		break;
	case 'g':
		color = { 0,1,0 ,color.A };
		break;
	case 'b':
		color = { 0,0,1 ,color.A };
		break;
	case 'a':
		rect_Obj[0].SetColor();
		glutPostRedisplay();
		return;
	case 'w':
		color = { 1,1,1 ,color.A };
		break;
	case 'k':
		color = { 0,0,0 ,color.A };
		break;
	case 't':
		isOnTimer = !isOnTimer;
		glutTimerFunc(100, Timer, 1);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
	rect_Obj[0].SetColor(color);
	
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	startMouse_Pos = { (float)x,(float)y };
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (rect_Obj[0].collider.OnMouseCollide(startMouse_Pos))
		{
			rect_Obj[0].SetColor();
			return;
		}
		SetRandomWindowColor();
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Vector2 ChangeSacle;
		if (rect_Obj[0].collider.OnMouseCollide(startMouse_Pos))
			ChangeSacle = { 1,1 };
		else
			ChangeSacle = { -1,-1 };
		rect_Obj[0].transform.SetScale(rect_Obj[0].transform.Scale + ChangeSacle);
	}
}

void SetRandomWindowColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLclampf> randomcolor(0.0f, 1.0f);

	windowColor = { randomcolor(gen),randomcolor(gen),randomcolor(gen), windowColor.A };
}

#elif MainNumber == 2

#include "GL_Rectangle.h"

GL_Rectangle* rect_Obj = new GL_Rectangle[MaxSpawnCount];
GL_Rectangle eraes_Obj;
Vector2 startMouse_Pos;
Vector2 sethaPos[MaxSpawnCount];

Vector2 zigzagSpeed[MaxSpawnCount];
int zigzagCount[MaxSpawnCount] = {0,};

bool isRandomScale = false;
bool isRandomSetha = false;
bool isRandomZigzag = false;
bool moveZigzagXY[MaxSpawnCount] = {false, };

GLvoid drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void FrameTimer(int value);
void RandomSetha(int i);
void RandomZigzag(int i);
int SpawnRectangleObject();

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Glew 없음" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "Glew 있음" << endl;

	Start_Time = time(NULL);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(windowColor.R, windowColor.G, windowColor.B, windowColor.A);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < MaxSpawnCount; i++)
	{
		if (!rect_Obj[i].collider.isAllCollide)
			continue;

		rect_Obj[i].collider.CheckAllColider();
	}


	if (isRandomScale)
	{
		for (int i = 0; i < MaxSpawnCount; i++)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			rect_Obj[i].transform.SetScale();
		}
	}

	if (isRandomSetha)
	{
		for (int i = 0; i < MaxSpawnCount; i++)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			if (rect_Obj[i].collider.WindowColider())
			{
				rect_Obj[i].transform.SetPosition(rect_Obj[i].transform.Pivot - sethaPos[i]);
				RandomSetha(i);
			}

			rect_Obj[i].transform.SetPosition(sethaPos[i] + rect_Obj[i].transform.Pivot);
		}
	}

	if (isRandomZigzag)
	{
		Vector2 pos = {0,0};
		for (int i = 0; i < MaxSpawnCount; i++)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			if (moveZigzagXY[i])
				pos = { zigzagSpeed[i].x, 0 };
			else
				pos = { 0, zigzagSpeed[i].y };

			rect_Obj[i].transform.SetPosition(pos + rect_Obj[i].transform.Pivot);
			zigzagCount[i]++;

			if (rect_Obj[i].collider.WindowColider())
			{
				rect_Obj[i].transform.SetPosition(rect_Obj[i].transform.Pivot - pos);
				zigzagCount[i] = 0;
				RandomZigzag(i);
			}

			if (zigzagCount[i] > 20)
			{
				zigzagCount[i] = 0;
				moveZigzagXY[i] = !moveZigzagXY[i];
			}			
		}
	}

	glutPostRedisplay();

	for (int i = 0; i < MaxSpawnCount; i++)
	{
		if (!rect_Obj[i].collider.isAllCollide)
			continue;

		rect_Obj[i].Update();
	}
	if (isErase)
	{
		eraes_Obj.Update();
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
	case 't':
		glutFullScreenToggle();
		if (isFullScreen)
			glutLeaveFullScreen();
		isFullScreen = !isFullScreen;
		break;
	case 'a':
		isRandomSetha = !isRandomSetha;
		for (int i = 0; i < MaxSpawnCount; i++)
			RandomSetha(i);
		break;
	case 'i':
		isRandomZigzag = !isRandomZigzag;
		for (int i = 0; i < ObjectSpawnCount; i++)
			RandomZigzag(i);
		break;
	case 'c':
		isRandomScale = !isRandomScale;
		break;
	case 's':
		isRandomScale = false;
		isRandomSetha = false;
		isRandomZigzag = false;
		break;
	case 'm':
		for (int count = 0; count < ObjectSpawnCount; count++)
		{
			rect_Obj[count].transform.ResetPosition();
		}
		break;
	case 'r':
		for (int i = 0; i < MaxSpawnCount - 1; i++)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			rect_Obj[i].collider.isAllCollide = false;
			rect_Obj[i].transform.SetAllAcetive(false);
			rect_Obj[i].collider.SetAllColider(false);
		}
		break;
	case 'z':
		SpawnRectangleObject();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	startMouse_Pos = {(float)x,(float)y};
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		left_button = true;
		int isAnythingCollide = true;

		for (int i = MaxSpawnCount - 1; i >= 0; i--)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			if (rect_Obj[i].collider.OnMouseCollide(startMouse_Pos))
				return;
		}

		if (isAnythingCollide && ObjectSpawnCount <= MaxSpawnCount)
		{
			int num = SpawnRectangleObject();
			rect_Obj[num].transform.InitPivot(Coordinate(startMouse_Pos));
			ObjectSpawnCount++;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		left_button = false;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isErase = true;

		if (isErase)
		{
			eraes_Obj.transform.InitPivot(Coordinate(startMouse_Pos));
			eraes_Obj.SetColor({0.5f,0.5f,0.5f,1});
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isErase = false;
		right_button = false;
	}
}

void Motion(int x, int y)
{
	Vector2 movePos;
	if (left_button == true)
	{
		movePos.x = (x - startMouse_Pos.x);
		movePos.y = (y - startMouse_Pos.y);

		for (int i = MaxSpawnCount - 1; i >= 0; i--)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			if (!rect_Obj[i].collider.isMouseCollide)
				continue;

			rect_Obj[i].transform.SetPosition(movePos + rect_Obj[i].transform.Pivot);
			break;
		}
	}

	if (isErase)
	{
		movePos = { (float)x, (float)y };
		eraes_Obj.transform.SetPosition(Coordinate(movePos));

		for (int i = MaxSpawnCount - 1; i >= 0; i--)
		{
			if (!rect_Obj[i].collider.isAllCollide)
				continue;

			eraes_Obj.collider.OnCollider(rect_Obj[i].collider);
		}
	}

	startMouse_Pos = { (float)x,(float)y };

	glutPostRedisplay();
}

void FrameTimer(int value)
{
	glutPostRedisplay();
}

void RandomSetha(int i)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> randSetha(-360.0f, 360.0f);

	float setha;

	setha = randSetha(gen);

	sethaPos[i] = {floor(cos(setha) * 10), floor(sin(setha) * 10)};
}

void RandomZigzag(int i)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randZigzag(1, 5);
	uniform_int_distribution<int> plus_minus(0, 1);

	zigzagSpeed[i] = { (float)randZigzag(gen) ,(float)randZigzag(gen) };
	zigzagSpeed[i].x *= plus_minus(gen) == 0 ? -1 : 1;
	zigzagSpeed[i].y *= plus_minus(gen) == 0 ? -1 : 1;
}

int SpawnRectangleObject()
{
	for (int i = 0; i < MaxSpawnCount; i++)
	{
		if (rect_Obj[i].collider.isAllCollide)
			continue;

		rect_Obj[i].collider.isAllCollide = true;
		rect_Obj[i].transform.SetAllAcetive(true);
		rect_Obj[i].collider.SetAllColider(true);
		rect_Obj[i].SetColor();

		return i;
	}
}

#endif