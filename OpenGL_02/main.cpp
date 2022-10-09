#define MainNumber 2

#include "Afx.h"

void make_vertexShaders();
void make_fragmentShaders();
void InitShader();
void FrameTimer(int value);

GLvoid drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

GLuint shaderID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체


#if MainNumber == 1

#include "GL_Triangle.h"
#include "GL_Whirlwind.h"


GLvoid UpdateBuffer();

void InitObject();
void SetRandomWindowColor();

void Move();

Vector2 scale = { 1,1 };
bool isSizeUp = true;
int nowObjCount = 0;

bool isMove = false;
bool isOtehrWindow = false;

Vector2 otherWindow[4][2];
bool otherWindowActive = false;
GL_Triangle* obj = new GL_Triangle[SapwnCount];
GL_Whirlwind wObj;

GLuint VAO[SapwnCount], VBO_Dot[SapwnCount], VBO_Color;
GLuint BAO, BAO_Dot, BAO_Index;
GLuint WVAO, WVAO_Dot;

float vPositionList[] = {
0.5f, 0.5f,
0.5f, -0.5f, 
-0.5f, -0.5f,
-0.5f, 0.5f, 
};

Vector2 vOtherWindow[4];

unsigned int index[] = {
0,1,
1,2,
2,3,
3,0
};


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	InitObject();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'b':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'o':
		isMove = !isMove;
		for (int i = 0; i < SapwnCount; i++)
		{
			obj[i].SetRandomSpeed();
		}
		break;
	case 'i':
		isOtehrWindow = !isOtehrWindow;
		for (int i = 0; i < SapwnCount; i++)
		{
			obj[i].SetRandomZigZagRadius();
		}
		break;
	case 'w':
		otherWindowActive = !otherWindowActive;
		break;
	case 'z':
		for (int i = 0; i < SapwnCount; i++)
		{
			obj[i].isActive = !obj[i].isActive;
		}
		break;
	case 'x':
		wObj.isActive = !wObj.isActive;
		if (!wObj.isActive)
			windowColor = { 0,0,0,1 };
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'n':
		wObj.OnDrawAnimaiton = !wObj.OnDrawAnimaiton;
		break;
	case 'm':
		wObj.OnMoveAnimaiton = !wObj.OnMoveAnimaiton;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x,(float)y };
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		StartMouse = Coordinate(StartMouse);
		StartMouse.y = -StartMouse.y;
		left_button = true;
		if (wObj.isActive)
		{
			wObj.RandomWhirwindDir();
			wObj.transform.Position = StartMouse;
			SetRandomWindowColor();
		}

		if (obj[nowObjCount].isActive)
		{
			Vector2 up_down = { 0.2,0.2 };

			if (isSizeUp)
				scale = scale + up_down;
			else
				scale = scale - up_down;
			
			obj[nowObjCount].transform.Position = StartMouse;
			obj[nowObjCount].SetColor();
			obj[nowObjCount].transform.Scale = scale;
			obj[nowObjCount].transform.Rotation = { 0,0 };

			if (obj[nowObjCount].transform.Scale.x >= 2)
				isSizeUp = false;
			else if (obj[nowObjCount].transform.Scale.x <= 1)
				isSizeUp = true;

			nowObjCount = (nowObjCount + 1) % 4;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		left_button = false;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
			
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		right_button = false;
	}
}

void Motion(int x, int y)
{
	Vector2 movePos;
	if (left_button == true)
	{
		movePos.x = (x - StartMouse.x);
		movePos.y = (y - StartMouse.y);
	}

	glutPostRedisplay();
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	//--- 변경된 배경색 설정
	glClearColor(windowColor.R, windowColor.G, windowColor.B, windowColor.A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Move();

	UpdateBuffer();

	glUseProgram(s_program);
	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	
	if (wObj.isActive)
	{
		glUniform4f(vColorLocation, 1, 1, 1, 1);
		glBindVertexArray(WVAO);
		glPointSize(5.0f);
		if (wObj.OnDrawAnimaiton)
		{
			glDrawArrays(GL_POINTS, 0, wObj.DrawAniCount);
			wObj.DrawAniCount = (wObj.DrawAniCount + 1) % 200;
		}
		else
		{
			glDrawArrays(GL_POINTS, 0, wObj.GetPointCount());
		}
		glBindVertexArray(0);
		glEnableVertexAttribArray(0);
	}

	if (otherWindowActive)
	{
		glUniform4f(vColorLocation, 1, 1, 1, 1);
		glBindVertexArray(BAO);
		glDrawElements(GL_LINE_STRIP, 8, GL_UNSIGNED_INT, 0);
	}

	for (int i = 0; i < SapwnCount; i++)
	{
		if (!obj[i].isActive)
			continue;

		glUniform4f(vColorLocation, obj[i].color.R, obj[i].color.G, obj[i].color.B, obj[i].color.A);
		//--- 사용할 VAO 불러오기
		glBindVertexArray(VAO[i]);
		
		//--- 삼각형 그리기
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glEnableVertexAttribArray(0);
	}

	glutSwapBuffers();
	Time_Duration = floor(difftime(time(NULL), Start_Time));
	glutTimerFunc(1000 / 60 - Time_Duration, FrameTimer, 1);
	Start_Time = time(NULL);
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
	
	windowSize_W = w;
	windowSize_H = h;

	vOtherWindow[0] = { (float)w / 4, (float)h / 4 };
	vOtherWindow[1] = { (float)w / 4, (float)-h / 4 };
	vOtherWindow[2] = { (float)-w / 4, (float)-h / 4 };
	vOtherWindow[3] = { (float)-w / 4, (float)h / 4 };

	otherWindow[0][0] = vOtherWindow[3];
	otherWindow[0][1] = vOtherWindow[0];

	otherWindow[1][0] = vOtherWindow[3];
	otherWindow[1][1] = vOtherWindow[2];

	otherWindow[2][0] = vOtherWindow[0];
	otherWindow[2][1] = vOtherWindow[1];

	otherWindow[3][0] = vOtherWindow[2];
	otherWindow[3][1] = vOtherWindow[1];
}

GLvoid UpdateBuffer()
{
	GLint pAttribute = glGetAttribLocation(s_program, "vPos");

	if (wObj.isActive)
	{
		glGenVertexArrays(1, &WVAO);
		glGenBuffers(1, &WVAO_Dot);

		glBindVertexArray(WVAO);

		glBindBuffer(GL_ARRAY_BUFFER, WVAO_Dot);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * wObj.GetPointCount(), wObj.GetDot(), GL_STATIC_DRAW);
		glVertexAttribPointer(pAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pAttribute);
	}

	//--- VAO 객체 생성 및 바인딩
	glGenVertexArrays(SapwnCount, VAO);
	glGenBuffers(SapwnCount, VBO_Dot);
	//glGenBuffers(1, &VBO_Color);
	for (int i = 0; i < SapwnCount; i++)
	{
		if (!obj[i].isActive)
			continue;

		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_Dot[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * 3, obj[i].GetDot(), GL_STATIC_DRAW);
		glVertexAttribPointer(pAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pAttribute);
	}
}

void InitObject()
{
	glGenVertexArrays(1, &BAO);
	glGenBuffers(1, &BAO_Dot);
	glBindVertexArray(BAO);
	glBindBuffer(GL_ARRAY_BUFFER, BAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vPositionList), vPositionList, GL_STATIC_DRAW);
	glGenBuffers(1, &BAO_Index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	obj[0].transform.Position = { 0,0 };

	//obj[1].transform.Position = { 100,100 };
	//obj[1].transform.Rotation = { 90,0 };
	//obj[2].transform.Position = { 100,-100 };
	//obj[3].transform.Position = { -100,-100 };

	for (int i = 0; i < SapwnCount; i++)
	{
		obj[i].SetColor();
	}
}

void SetRandomWindowColor()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> radnomColor(0.0f, 1.0f);

	windowColor = { radnomColor(gen),radnomColor(gen) ,radnomColor(gen), 1.0f };
}

void Move()
{
	if (wObj.isActive && wObj.OnMoveAnimaiton)
	{
		wObj.transform.Rotation.x = ((int)wObj.transform.Rotation.x + 1) % 360 ;
	}

	for (int i = 0; i < SapwnCount; i++)
	{
		if (obj[i].transform.Position.x >= -windowSize_W/4 && obj[i].transform.Position.x <= windowSize_W / 4 &&
			obj[i].transform.Position.y >= -windowSize_H / 4 && obj[i].transform.Position.y <= windowSize_H / 4)
		{
			if (!isOtehrWindow)
				continue;

			obj[i].MoveZigZag();

			for (int j = 0; j < 4; j++)
			{
				if (!otherWindowActive)
					break;

				obj[i].collider.OnCollide(otherWindow[j]);

				if (obj[i].collider.isCollide)
					break;
			}

			if (obj[i].collider.isCollide)
			{
				obj[i].transform.LookAt(-15.0f);
				obj[i].SetRandomZigZagRadius();
			}
		}
		else
		{
			if (!isMove)
				continue;

			for (int j = 0; j < 4; j++)
			{
				if (!otherWindowActive)
					break;

				obj[i].collider.OnCollide(otherWindow[j]);

				if (obj[i].collider.isCollide)
					break;
			}

			if (obj[i].collider.isCollide)
			{
				obj[i].transform.LookAt(-30.0f);
				obj[i].SetRandomSpeed();
				obj[i].transform.SetRandomRotate();
				obj[i].GetDot();
			}

			obj[i].MoveWindow();
		}
	}
}


#elif MainNumber == 2

#include "Shape.h"
#include "GL_Window.h"

void InitObject();
void UpdateObject();

#define ShapeCount 4

Vector2 line_Dot[] = {
	{-1,0},
	{1, 0},
	{0, -1},
	{0, 1}
};

int line_Index[] = {
	0,1,
	2,3
};

int maxShapeSize = 15;

GLuint line_AVO, line_AVO_Dot, line_AVO_Index;

Shape* shape_Obj = new Shape[ShapeCount];
GL_Window window_Obj;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	InitObject();

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateObject();

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
		
	case 'z':
		for (int i = 0; i < ShapeCount; i++)
			shape_Obj[i].isActive = !shape_Obj[i].isActive;
		break;

	case '=':
		for (int i = 0; i < ShapeCount; i++)
		{
			shape_Obj[i].shapeSize++;
			if (shape_Obj[i].shapeSize > maxShapeSize)
				shape_Obj[i].shapeSize = 1;
		}
		break;
	case '-':
		for (int i = 0; i < ShapeCount; i++)
		{
			shape_Obj[i].shapeSize--;
			if (shape_Obj[i].shapeSize <= 0)
				shape_Obj[i].shapeSize = maxShapeSize;
		}
	case 'a':
		for (int i = 0; i < ShapeCount; i++)
		{
			shape_Obj[i].isChagneShapeAni = !shape_Obj[i].isChagneShapeAni;
		}
		break;
	case 'w':
		window_Obj.isActive = !window_Obj.isActive;
		break;
	}


	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	window_Obj.OnPointClick(StartMouse);
	window_Obj.CheckInBox(StartMouse);

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	Vector2 mouse_Pos = { (float)x, (float)y };
	mouse_Pos = Coordinate(mouse_Pos);
	mouse_Pos.y = -mouse_Pos.y;

	if (window_Obj.MouseDot != nullptr)
	{
		window_Obj.MouseDot->Position = mouse_Pos - window_Obj.transform.Position;
	}
	else if (window_Obj.RotateDot)
	{
		double dgree = atan2(mouse_Pos.x, mouse_Pos.y);
		window_Obj.transform.Rotation.x = dgree * 180 / PI;
		window_Obj.SetRotateDot();
	}
	else if (window_Obj.isInside)
	{
		Vector2 Move_Mouse_Pos = mouse_Pos - StartMouse;

		window_Obj.transform.Position = window_Obj.transform.Position + Move_Mouse_Pos;
	}

	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;
	glutPostRedisplay();
}

void InitObject()
{
	shape_Obj[0].transform.Position = { (float) -windowSize_W / 4, (float) -windowSize_H / 4};
	shape_Obj[1].transform.Position = { (float) windowSize_W / 4, (float) -windowSize_H / 4};
	shape_Obj[2].transform.Position = { (float) -windowSize_W / 4, (float)  windowSize_H / 4};
	shape_Obj[3].transform.Position = { (float) windowSize_W / 4, (float) windowSize_H / 4};

	for (int i = 0; i < ShapeCount; i++)
	{
		shape_Obj[i].SetColor();
		shape_Obj[i].RandomRadius();

		shape_Obj[i].shapeSize = i + 1;
		if (shape_Obj[i].shapeSize > maxShapeSize)
			shape_Obj[i].shapeSize = 1;
	}

	window_Obj.SetColor();

	glGenVertexArrays(1, &line_AVO);
	glGenBuffers(1, &line_AVO_Dot);
	glBindVertexArray(line_AVO);
	glBindBuffer(GL_ARRAY_BUFFER, line_AVO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_Dot), line_Dot, GL_STATIC_DRAW);
	glGenBuffers(1, &line_AVO_Index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, line_AVO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_Index), line_Index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void UpdateObject()
{
	for (int i = 0; i < ShapeCount; i++)
	{
		shape_Obj[i].Draw();
	}

	window_Obj.Draw();

	glBindVertexArray(line_AVO);
	glUniform4f(0, 1, 1, 1, 1);
	glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, 0);

	glutPostRedisplay();
}

#endif

#pragma region Defualt_Funtion

void make_vertexShaders()
{
	GLchar* vertexSource;
	//GLuint vertexShader;
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	vertexSource = filetobuf("Vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("Fragment.glsl"); // 프래그세이더 읽어오기

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void InitShader()
{
	GLint result;
	GLchar errorLog[512];

	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);
	glGetProgramiv(s_program, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(s_program, 512, NULL, errorLog);
		cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
		return;
	}
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(s_program);
}

void FrameTimer(int value)
{
	glutPostRedisplay();
}

#pragma endregion
