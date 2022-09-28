#include "GL_Triangle.h"

#define MainNumber 1

#if MainNumber == 1

void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid InitBuffer();
void InitShader();

GLint width, height;
GLuint shaderID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체
GLuint s_program;

//const float vertexData[] =
//{
//0.5, 1.0, 0.0, 1.0, 0.0, 0.0,
//0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
//1.0, 0.0, 0.0, 0.0, 0.0, 1.0
//};

GL_Triangle* obj = new GL_Triangle[4];
GLuint VAO[4], VBO_Dot[4], VBO_Color[4];

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	width = 500;
	height = 500;
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	vertexSource = filetobuf("Vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**) & vertexSource, 0);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
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

GLuint make_shaderProgram()
{
	GLuint ShaderProgramID;
	GLint result;
	GLchar errorLog[512];

	ShaderProgramID = glCreateProgram(); //--- 세이더 프로그램 만들기
	glAttachShader(ShaderProgramID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(ShaderProgramID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기
	glLinkProgram(ShaderProgramID); //--- 세이더 프로그램 링크하기
	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
		return false;
	}
	glUseProgram(ShaderProgramID);
	return ShaderProgramID;
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	//--- 변경된 배경색 설정
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(s_program);

	for (int i = 0; i < SapwnCount; i++)
	{
		//--- 사용할 VAO 불러오기
		glBindVertexArray(VAO[i]);
		//--- 삼각형 그리기
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid InitBuffer()
{
	//--- VAO 객체 생성 및 바인딩
	glGenVertexArrays(SapwnCount, VAO);
	glGenBuffers(SapwnCount, VBO_Dot);
	glGenBuffers(SapwnCount, VBO_Color);
	for (int i = 0; i < SapwnCount; i++)
	{
		glBindVertexArray(VAO[i]);

		GLint pAttribute = glGetAttribLocation(s_program, "vPos");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Dot[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector2) * 3, obj[i].GetDot(), GL_STATIC_DRAW);
		glVertexAttribPointer(pAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pAttribute);

		GLint cAttribute = glGetAttribLocation(s_program, "vColor");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Color[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Color) * 3, obj[i].GetColor(), GL_STATIC_DRAW);
		glVertexAttribPointer(cAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(cAttribute);
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
#endif