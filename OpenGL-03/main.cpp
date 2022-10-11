#define MainNumber 1

#include "GL_Cube.h"
#include "GL_Tetrahedron.h"

void drawScene();
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ReadObj(char* fileName);

void InitMain();

Color windowColor;

Vector2 Dot[] = {
	{-0.5f,0},
	{0.5f,0},
	{0,0.5f}
};

GLuint VAO, VAO_Dot;

GL_Cube cube_Object;
GL_Tetrahedron diamond_Object;

#if MainNumber == 1

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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

	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VAO_Dot);
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Dot), Dot, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0)
	

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(s_program);
	//glm::mat4 model = glm::mat4(1.0f);
	////--- 적용할 모델링 변환 행렬 만들기
	//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); //--- model 행렬에 이동 변환 적용
	////--- 세이더 프로그램에서 modelTransform 변수 위치 가져오기
	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	////--- modelTransform 변수에 변환 값 적용하기
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	////--- 도형 그리기
	//int vColorLocation = glGetUniformLocation(s_program, "vColor");
	//glUniform4f(vColorLocation, 1,1,1,1);
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	cube_Object.Draw();
	diamond_Object.Draw();

	glutSwapBuffers();
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'b':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	case 'z':
		cube_Object.isActiveFace[0] = !cube_Object.isActiveFace[0];
		cube_Object.isActiveFace[5] = !cube_Object.isActiveFace[5];
		break;
	case 'x':
		cube_Object.isActiveFace[1] = !cube_Object.isActiveFace[1];
		cube_Object.isActiveFace[4] = !cube_Object.isActiveFace[4];
		break;
	case 'c':
		cube_Object.isActiveFace[2] = !cube_Object.isActiveFace[2];
		cube_Object.isActiveFace[3] = !cube_Object.isActiveFace[3];

	case '7':
		diamond_Object.isActiveFace[0] = !diamond_Object.isActiveFace[0];
		break;
	case '8':
		diamond_Object.isActiveFace[1] = !diamond_Object.isActiveFace[1];
		break;
	case '9':
		diamond_Object.isActiveFace[2] = !diamond_Object.isActiveFace[2];
		break;
	case '0':
		diamond_Object.isActiveFace[3] = !diamond_Object.isActiveFace[3];
		break;
	case 'q':
		diamond_Object.isActiveFace[0] = !diamond_Object.isActiveFace[0];
		diamond_Object.isActiveFace[1] = !diamond_Object.isActiveFace[1];
		break;
	case 'w':
		diamond_Object.isActiveFace[0] = !diamond_Object.isActiveFace[0];
		diamond_Object.isActiveFace[2] = !diamond_Object.isActiveFace[2];
		break;
	case 'e':
		diamond_Object.isActiveFace[0] = !diamond_Object.isActiveFace[0];
		diamond_Object.isActiveFace[3] = !diamond_Object.isActiveFace[3];
		break;
	}

	glutPostRedisplay();
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

	cube_Object.isActive = true;
	diamond_Object.isActive = true;
}


#endif

