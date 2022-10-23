#define MainNumber 1

#include "GL_Cube.h"
#include "GL_Tetrahedron.h"
#include "GL_Coordinate.h"
#include "GL_Whirlwind.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void SpecialKeyBoard(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();
void DrawGLU_Object();

Color windowColor;

Vector2 Dot[] = {
	{-0.5f,0},
	{0.5f,0},
	{0,0.5f}
};

typedef struct Shape_Objet {
	Object obj;
	vec3 rotateSpeed;

	vec3 coordinateRotate;
	vec3 coordinateRotateSpeed;
	vec3 nowPosition;	// 현재 위치
	vec3 otherPosition; // 다른 도형의 위치
	Position2 whirlwindVertexNumber; // 회오리 버텍스 요소 번호
	int whirwindImaginary;	// 회오리 이동 방향의 증가폭
};

#if MainNumber == 1

bool is_Polygon = false;
bool is_CullFace = false;

GL_Cube cube_Object;
GL_Tetrahedron tetrahedron_Object;
GL_Coordinate coordinate_Object;
GL_Whirlwind whirlwind_Object;
GLUquadricObj* cone_Object, * cylinder_Object, * sphere_Object;
#define maxGLUindex 3

Shape_Objet shape_Object[maxGLUindex];
int selectShapeNumber = 0;

vec3 originScale;	// 원점에 대한 신축에 사용할 scale
vec3 changeScale;	// 신축의 증가폭
int scaleImaginary;

int positionImaginary;

bool isChangeShape = false;
bool isExpensionScale = false; // 각 도형의 제자리에서 신축 체크
bool isOriginScale = false;	// 원점으로 신축
bool isOriginPosition = false; // 원점으로 이동
bool isOtherShapePosition = false;	// 서로 다른 도형의 위치로 이동
bool isWhirlwindAni = false; // 회오리 방향으로 도형이 이동

int staticRoteteSpeed = 1;

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

	if (isExpensionScale)
	{
		cube_Object.ExpensionScale();

		for (int i = 0; i < 2; i++)
		{
			shape_Object[i].obj.ExpensionScale();
		}
	}


	coordinate_Object.Draw();
	cube_Object.Draw();
	tetrahedron_Object.Draw();
	whirlwind_Object.Draw();
	DrawGLU_Object();

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
	case 'u':
		is_Polygon = !is_Polygon;
		if(is_Polygon)
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
	case 'o':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].obj.isActive = !shape_Object[i].obj.isActive;
		coordinate_Object.isActive = !coordinate_Object.isActive;
		break;

	case 'O':
		whirlwind_Object.isActive = !whirlwind_Object.isActive;
		break;
	case ']':
		selectShapeNumber = (selectShapeNumber + 1) % 2;
		break;

	case 'a':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.z = staticRoteteSpeed;
		break;
	case 'A':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.z = -staticRoteteSpeed;
		break;
	case 'b':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.y = staticRoteteSpeed;
		break;
	case 'B':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.y = -staticRoteteSpeed;
		break;
	case 'c':
		isChangeShape = !isChangeShape;
		break;
	case 'r':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].coordinateRotateSpeed.y = -staticRoteteSpeed;
		break;
	case 'R':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].coordinateRotateSpeed.y = staticRoteteSpeed;
		break;


	case 's':
		cube_Object.transform.Position = cube_Object.transform.Rotation = cube_Object.rotateSpeed = { 0,0,0 };
		tetrahedron_Object.transform.Position = tetrahedron_Object.transform.Rotation = tetrahedron_Object.rotateSpeed = { 0,0,0 };
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed = shape_Object[i].coordinateRotateSpeed = coordinate_Object.rotateSpeed = { 0,0,0 };
		break;
	case 'x':
		cube_Object.rotateSpeed.z = staticRoteteSpeed;
		tetrahedron_Object.rotateSpeed.z = staticRoteteSpeed;
		break;
	case 'X':
		cube_Object.rotateSpeed.z = -staticRoteteSpeed;
		tetrahedron_Object.rotateSpeed.z = -staticRoteteSpeed;
		break;
	case 'y':
		cube_Object.rotateSpeed.y = staticRoteteSpeed;
		tetrahedron_Object.rotateSpeed.y = staticRoteteSpeed;
		break;
	case 'Y':
		cube_Object.rotateSpeed.y = -staticRoteteSpeed;
		tetrahedron_Object.rotateSpeed.y = -staticRoteteSpeed;
		break;
	case 'z':
		tetrahedron_Object.isActive = !tetrahedron_Object.isActive;
		break;
	case 'Z':
		cube_Object.isActive = !cube_Object.isActive;
		break;

	case '1':
		cube_Object.isActiveFace[0] = !cube_Object.isActiveFace[0];
		break;
	case '2':
		cube_Object.isActiveFace[1] = !cube_Object.isActiveFace[1];
		break;
	case '3':
		cube_Object.isActiveFace[2] = !cube_Object.isActiveFace[2];
		break;
	case '4':
		cube_Object.isActiveFace[3] = !cube_Object.isActiveFace[3];
		break;
	case '5':
		cube_Object.isActiveFace[4] = !cube_Object.isActiveFace[4];
		break;
	case '6':
		cube_Object.isActiveFace[5] = !cube_Object.isActiveFace[5];
		break;
	case 'q':
		cube_Object.isActiveFace[0] = !cube_Object.isActiveFace[0];
		cube_Object.isActiveFace[5] = !cube_Object.isActiveFace[5];
		break;
	case 'w':
		cube_Object.isActiveFace[1] = !cube_Object.isActiveFace[1];
		cube_Object.isActiveFace[4] = !cube_Object.isActiveFace[4];
		break;
	case 'e':
		cube_Object.isActiveFace[2] = !cube_Object.isActiveFace[2];
		cube_Object.isActiveFace[3] = !cube_Object.isActiveFace[3];
		break;

	case '7':
		tetrahedron_Object.isActiveFace[0] = !tetrahedron_Object.isActiveFace[0];
		break;
	case '8':
		tetrahedron_Object.isActiveFace[1] = !tetrahedron_Object.isActiveFace[1];
		break;
	case '9':
		tetrahedron_Object.isActiveFace[2] = !tetrahedron_Object.isActiveFace[2];
		break;
	case '0':
		tetrahedron_Object.isActiveFace[3] = !tetrahedron_Object.isActiveFace[3];
		break;
	case 'Q':
		tetrahedron_Object.isActiveFace[0] = !tetrahedron_Object.isActiveFace[0];
		tetrahedron_Object.isActiveFace[1] = !tetrahedron_Object.isActiveFace[1];
		break;
	case 'W':
		tetrahedron_Object.isActiveFace[0] = !tetrahedron_Object.isActiveFace[0];
		tetrahedron_Object.isActiveFace[2] = !tetrahedron_Object.isActiveFace[2];
		break;
	case 'E':
		tetrahedron_Object.isActiveFace[0] = !tetrahedron_Object.isActiveFace[0];
		tetrahedron_Object.isActiveFace[3] = !tetrahedron_Object.isActiveFace[3];
		break;

	case 'p':
		cube_Object.isPrismColor = !cube_Object.isPrismColor;
		tetrahedron_Object.isPrismColor = !tetrahedron_Object.isPrismColor;
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyBoard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.x -= 0.01f;

		cube_Object.transform.Position.x -= 0.01f;
		tetrahedron_Object.transform.Position.x -= 0.01f;
		break;
	case GLUT_KEY_RIGHT:
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.x += 0.01f;

		cube_Object.transform.Position.x += 0.01f;
		tetrahedron_Object.transform.Position.x += 0.01f;
		break;
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.y -= 0.01f;

		cube_Object.transform.Position.y -= 0.01f;
		tetrahedron_Object.transform.Position.y -= 0.01f;
		break;
	case GLUT_KEY_UP:
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.y += 0.01f;

		cube_Object.transform.Position.y += 0.01f;
		tetrahedron_Object.transform.Position.y += 0.01f;
		break;

	// shape 한 개가 축으로 이동
	// 	// x 이동
	case GLUT_KEY_END:
		shape_Object[selectShapeNumber].obj.transform.Position.x -= 0.01f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		shape_Object[selectShapeNumber].obj.transform.Position.x += 0.01f;
		break;
	// 	// y 이동
	case GLUT_KEY_SHIFT_L:
		shape_Object[selectShapeNumber].obj.transform.Position.y -= 0.01f;
		break;
	case GLUT_KEY_SHIFT_R:
		shape_Object[selectShapeNumber].obj.transform.Position.y += 0.01f;
		break;
	// 	// y 이동
	case GLUT_KEY_HOME:
		shape_Object[selectShapeNumber].obj.transform.Position.z -= 0.01f;
		break;
	case GLUT_KEY_PAGE_UP:
		shape_Object[selectShapeNumber].obj.transform.Position.z += 0.01f;
		break;

	case GLUT_KEY_F1: // 전체 도형의 이동
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.z -= 0.01f;
		break;
	case GLUT_KEY_F2: // 전체 도형의 이동
		for (int i = 0; i < 2; i++)
			shape_Object[i].obj.transform.Position.z += 0.01f;
		break;
	case GLUT_KEY_F3: // 각 도형의 제자리에서 신축
		isExpensionScale = !isExpensionScale;

		if (!isExpensionScale)
		{
			cube_Object.ReSet();
			originScale = vec3(1, 1, 1);
			for (int i = 0; i < maxGLUindex; i++)
			{
				shape_Object[i].obj.transform.Scale = vec3(0.2,0.2,0.2);
				shape_Object[i].obj.transform.Rotation = vec3(10,10,10);

				shape_Object[i].rotateSpeed = shape_Object[i].coordinateRotateSpeed = { 0,0,0 };
				shape_Object[i].coordinateRotate = coordinate_Object.transform.Rotation;
			}
		}
		break;
	case GLUT_KEY_F4:	// 도형이 원점에 대하여 신축
		isOriginScale = !isOriginScale;
		break;
	case GLUT_KEY_F5:	// 도형이 원점으로 이동
		isOriginPosition = !isOriginPosition;

		if (isOriginPosition)
			for (int i = 0; i < 2; i++)
				shape_Object[i].nowPosition = shape_Object[i].obj.transform.Position;
		break;
	case GLUT_KEY_F6:	// 각 도형의 현재 위치로 까지 이동
		isOtherShapePosition = !isOtherShapePosition;

		if (isOtherShapePosition)
		{
			for (int i = 0; i < 2; i++)
			{
				shape_Object[i].nowPosition = shape_Object[i].obj.transform.Position;
				shape_Object[i].otherPosition = shape_Object[(i + 1) % 2].obj.transform.Position;
			}
		}
		break;
	case GLUT_KEY_F7:
		isWhirlwindAni = !isWhirlwindAni;

		shape_Object[0].obj.transform.Rotation = whirlwind_Object.transform.Rotation;
		shape_Object[0].whirlwindVertexNumber.x = 0;
		shape_Object[0].whirlwindVertexNumber.y = 0;

		shape_Object[1].obj.transform.Rotation = whirlwind_Object.transform.Rotation;
		shape_Object[1].whirlwindVertexNumber.x = 0;
		shape_Object[1].whirlwindVertexNumber.y = 0;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	StartMouse = { (float)x, (float)y };
	StartMouse = Coordinate(StartMouse);
	StartMouse.y = -StartMouse.y;

	Vector2 realStartMouse = RealPosition(StartMouse);

	cube_Object.transform.Position = vec3(realStartMouse.x, realStartMouse.y, cube_Object.transform.Position.z);

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
	tetrahedron_Object.Init();
	coordinate_Object.Init();
	whirlwind_Object.Init();

	cube_Object.isActive = false;
	tetrahedron_Object.isActive = false;
	whirlwind_Object.isActive = false;

	coordinate_Object.transform.Rotation.y += 30;
	coordinate_Object.transform.Rotation.x -= 45;

	//whirlwind_Object.transform.Rotation += 20;
	whirlwind_Object.coordinateRotate = coordinate_Object.transform.Rotation;

	cone_Object = gluNewQuadric();
	gluQuadricDrawStyle(cone_Object, GLU_LINE);
	cylinder_Object = gluNewQuadric();
	gluQuadricDrawStyle(cylinder_Object, GLU_LINE);
	sphere_Object = gluNewQuadric();
	gluQuadricDrawStyle(sphere_Object, GLU_LINE);

	originScale = vec3(1, 1, 1);
	changeScale = vec3(0.01, 0.01, 0.01);
	for (int i = 0; i < maxGLUindex; i++)
	{
		shape_Object[i].obj.isActive = false;
		shape_Object[i].obj.transform.Scale *= 0.2;
		shape_Object[i].obj.transform.Rotation += 10;

		shape_Object[i].obj.now_S = shape_Object[i].obj.transform.Scale.x;

		shape_Object[i].rotateSpeed = shape_Object[i].coordinateRotateSpeed = {0,0,0};
		shape_Object[i].coordinateRotate = coordinate_Object.transform.Rotation;
		shape_Object[i].whirwindImaginary = 1;
	}
	shape_Object[0].obj.transform.Position += 0.5;
	shape_Object[1].obj.transform.Position -= 0.5;	
}

void DrawGLU_Object()
{
	glUseProgram(s_program);

	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	if (isOriginScale) // 제자리에서 신축
	{
		if (originScale.x >= 1)
			scaleImaginary = -1;
		else if (originScale.x <= 0)
			scaleImaginary = 1;

		originScale += changeScale * scaleImaginary;
	}

	for (int i = 0; i < 2; i++)
	{
		if (!shape_Object[i].obj.isActive)
			continue;

		shape_Object[i].obj.transform.Rotation += shape_Object[i].rotateSpeed;
		shape_Object[i].coordinateRotate += shape_Object[i].coordinateRotateSpeed;

		if (isOriginPosition)	// 원점으로 신축
		{
			if (DistanceVec3(shape_Object[i].obj.transform.Position, vec3(0,0,0)) >= DistanceVec3(shape_Object[i].nowPosition, vec3(0, 0, 0)))
				positionImaginary = -1;
			else if (DistanceVec3(shape_Object[i].obj.transform.Position, vec3(0, 0, 0)) <= 0.001)
				positionImaginary = 1;
			shape_Object[i].obj.transform.Position += shape_Object[i].nowPosition / 100 * positionImaginary;
		}

		if (isOtherShapePosition) // 서로 다른 도형으로 이동
		{
			if (DistanceVec3(shape_Object[i].obj.transform.Position, shape_Object[i].otherPosition) > 0.0001)
				shape_Object[i].obj.transform.Position -= shape_Object[i].nowPosition / 100;
			else
				isOtherShapePosition = false;
		}

		if (isWhirlwindAni)	// 회오리 방향으로 이동
		{
			// 이동
			shape_Object[i].obj.transform.Position = whirlwind_Object.vertex[shape_Object[i].whirlwindVertexNumber.x][shape_Object[i].whirlwindVertexNumber.y];
			cout << shape_Object[i].whirlwindVertexNumber.x << ", " << shape_Object[i].whirlwindVertexNumber.y << endl;

			// 정점 변경
			shape_Object[i].whirlwindVertexNumber.y += shape_Object[i].whirwindImaginary;
			if (shape_Object[i].whirlwindVertexNumber.y < 0 || shape_Object[i].whirlwindVertexNumber.y >= whirlwind_Object.count[shape_Object[i].whirlwindVertexNumber.x])
			{
				shape_Object[i].whirlwindVertexNumber.x += shape_Object[i].whirwindImaginary;
				
				// 증가폭 검사
				if (shape_Object[i].whirlwindVertexNumber.x < 0)
				{
					shape_Object[i].whirwindImaginary = 1;
					shape_Object[i].whirlwindVertexNumber.x = 0;
				}
				else if (shape_Object[i].whirlwindVertexNumber.x >= 8)
				{
					shape_Object[i].whirwindImaginary = -1;
					shape_Object[i].whirlwindVertexNumber.x = 7;
				}

				if (shape_Object[i].whirwindImaginary == 1)
					shape_Object[i].whirlwindVertexNumber.y = 0;
				else
					shape_Object[i].whirlwindVertexNumber.y = whirlwind_Object.count[shape_Object[i].whirlwindVertexNumber.x];
			}
		}
		mat4 model = mat4(1.0);

		// 공전
		model = rotate(model, radians(shape_Object[i].coordinateRotate.x), vec3(1.0, 0, 0));
		model = rotate(model, radians(shape_Object[i].coordinateRotate.y), vec3(0, 1.0, 0));
		model = rotate(model, radians(shape_Object[i].coordinateRotate.z), vec3(0, 0, 1.0));

		model = scale(model, originScale);	// 원점에 대한 신축

		model = translate(model, shape_Object[i].obj.transform.Position);
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.x), vec3(1.0, 0, 0));
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.y), vec3(0, 1.0, 0));
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.z), vec3(0, 0, 1.0));
		model = scale(model, shape_Object[i].obj.transform.Scale);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		switch (i)
		{
		case 0:
			if (!isChangeShape)
			{
				cube_Object.isActive = true;
				cube_Object.transform.Position = shape_Object[i].obj.transform.Position;
				cube_Object.transform.Rotation = shape_Object[i].obj.transform.Rotation;
				cube_Object.coordinateRotate = shape_Object[i].coordinateRotate;

				cube_Object.originScale = originScale;
			}
			else
			{
				glUniform4f(vColorLocation, shape_Object[i].obj.color.R, shape_Object[i].obj.color.G, shape_Object[i].obj.color.B, shape_Object[i].obj.color.A);
				gluCylinder(cone_Object, 1.0, 0.0, 2.0, 20, 8);
				cube_Object.isActive = false;
			}
			break;
		case 1:
			glUniform4f(vColorLocation, shape_Object[i].obj.color.R, shape_Object[i].obj.color.G, shape_Object[i].obj.color.B, shape_Object[i].obj.color.A);
			if (!isChangeShape)
				gluCylinder(cylinder_Object, 1.0, 1.0, 2.0, 20, 8);
			else
				gluSphere(sphere_Object, 1.0, 20, 20);
			break;
		}
	}
}


#endif

