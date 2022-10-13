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
};

bool is_Polygon = false;
bool is_CullFace = false;

GL_Cube cube_Object;
GL_Tetrahedron tetrahedron_Object;
GL_Coordinate coordinate_Object;
GLUquadricObj *cone_Object, *cylinder_Object, *sphere_Object;
#define maxGLUindex 3

Shape_Objet shape_Object[maxGLUindex];
bool isChangeShape = false;

#if MainNumber == 1

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowSize_W, windowSize_H);
	glutCreateWindow("Example1");
	
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW); // 시계 반대 방향으로 구성된 폴리곤을 전면으로 설정

	//// 픽셀 블렌딩 연산 지정
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	coordinate_Object.Draw();
	cube_Object.Draw();
	tetrahedron_Object.Draw();
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
		if(is_CullFace)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
		break;
	case 'o':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].obj.isActive = !shape_Object[i].obj.isActive;
		coordinate_Object.isActive = !coordinate_Object.isActive;
		break;

	case'a':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.z = 10;
		break;
	case 'A':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.z = -10;
		break;
	case 'b':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.y = 10;
		break;
	case 'B':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed.y = -10;
		break;
	case 'c':
		isChangeShape = !isChangeShape;
		break;
	case 'r':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].coordinateRotateSpeed.y = -10;
		coordinate_Object.rotateSpeed.y = -10;
		break;
	case 'R':
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].coordinateRotateSpeed.y = 10;
		coordinate_Object.rotateSpeed.y = 10;
		break;


	case 's':
		cube_Object.transform.Position = cube_Object.transform.Rotation = cube_Object.rotateSpeed = { 0,0,0 };
		tetrahedron_Object.transform.Position = tetrahedron_Object.transform.Rotation = tetrahedron_Object.rotateSpeed = { 0,0,0 };
		for (int i = 0; i < maxGLUindex; i++)
			shape_Object[i].rotateSpeed = shape_Object[i].coordinateRotateSpeed = coordinate_Object.rotateSpeed = { 0,0,0 };
		break;
	case 'x':
		cube_Object.rotateSpeed.z = 10;
		tetrahedron_Object.rotateSpeed.z = 10;
		break;
	case 'X':
		cube_Object.rotateSpeed.z = -10;
		tetrahedron_Object.rotateSpeed.z = -10;
		break;
	case 'y':
		cube_Object.rotateSpeed.y = 10;
		tetrahedron_Object.rotateSpeed.y = 10;
		break;
	case 'Y':
		cube_Object.rotateSpeed.y = -10;
		tetrahedron_Object.rotateSpeed.y = -10;
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
		cube_Object.transform.Position.x -= 0.01f;
		tetrahedron_Object.transform.Position.x -= 0.01f;
		break;
	case GLUT_KEY_RIGHT:
		cube_Object.transform.Position.x += 0.01f;
		tetrahedron_Object.transform.Position.x += 0.01f;
		break;
	case GLUT_KEY_DOWN:
		cube_Object.transform.Position.y -= 0.01f;
		tetrahedron_Object.transform.Position.y -= 0.01f;
		break;
	case GLUT_KEY_UP:
		cube_Object.transform.Position.y += 0.01f;
		tetrahedron_Object.transform.Position.y += 0.01f;
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

	cube_Object.isActive = false;
	tetrahedron_Object.isActive = false;

	cone_Object = gluNewQuadric();
	gluQuadricDrawStyle(cone_Object, GLU_LINE);
	cylinder_Object = gluNewQuadric();
	gluQuadricDrawStyle(cylinder_Object, GLU_LINE);
	sphere_Object = gluNewQuadric();
	gluQuadricDrawStyle(sphere_Object, GLU_LINE);

	for (int i = 0; i < maxGLUindex; i++)
	{
		shape_Object[i].obj.isActive = false;
		shape_Object[i].obj.transform.Scale *= 0.2;
		shape_Object[i].obj.transform.Rotation += 10;

		shape_Object[i].coordinateRotate = shape_Object[i].rotateSpeed = shape_Object[i].coordinateRotateSpeed = {0,0,0};
	}
	shape_Object[0].obj.transform.Position += 0.2;
	shape_Object[1].obj.transform.Position -= 0.2;
}

void DrawGLU_Object()
{
	glUseProgram(s_program);

	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	for (int i = 0; i < 2; i++)
	{
		if (!shape_Object[i].obj.isActive)
			continue;

		shape_Object[i].obj.transform.Rotation += shape_Object[i].rotateSpeed;
		shape_Object[i].coordinateRotate += shape_Object[i].coordinateRotateSpeed;

		mat4 model = mat4(1.0);
		model = rotate(model, radians(shape_Object[i].coordinateRotate.x), vec3(0, 0, 1.0));
		model = rotate(model, radians(shape_Object[i].coordinateRotate.y), vec3(0, 1.0, 0));
		model = rotate(model, radians(shape_Object[i].coordinateRotate.z), vec3(1.0, 0, 0));
		model = translate(model, shape_Object[i].obj.transform.Position);
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.x), vec3(0, 0, 1.0));
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.y), vec3(0, 1.0, 0));
		model = rotate(model, radians(shape_Object[i].obj.transform.Rotation.z), vec3(1.0, 0, 0));
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
			}
			else
			{
				gluCylinder(cone_Object, 1.0, 0.0, 2.0, 20, 8);
				cube_Object.isActive = false;
			}
			break;
		case 1:
			if (!isChangeShape)
				gluCylinder(cylinder_Object, 1.0, 1.0, 2.0, 20, 8);
			else
				gluSphere(sphere_Object, 1.0, 20, 20);
			break;
		}
	}
}


#endif

