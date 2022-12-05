#include "Afx.h"

GLuint s_program;
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü

GLuint gui_s_program;
GLuint gui_vertexShader;
GLuint gui_fragmentShader;

char default_Cube[] = "Cube.obj";

int windowSize_W = 1600;
int windowSize_H = 900;

double aspect_ratio = windowSize_W / windowSize_H;

bool isFullScreen = false;
bool isOnTimer = false;

int Time_Duration;

float PI = 3.14159265;

#pragma region VectorFuntion

Face operator-(const Face my, int other)
{
	Face result;
	result.a = my.a - other;
	result.b = my.b - other;
	result.c = my.c - other;
	return result;
}


ostream& operator<< (ostream& outputStream, const Vector2& my)
{
	cout << my.x << ", " << my.y;
	return outputStream;
}


ostream& operator<< (ostream& outputStream, const vec3& my)
{
	cout << my.x << ", " << my.y << ", " << my.z;
	return outputStream;
}

ostream& operator<< (ostream& outputStream, const Face& my)
{
	cout << my.a << ", " << my.b << ", " << my.c;
	return outputStream;
}

bool operator== (const vec3 my, const float other)
{
	if (my.x != other) return false;
	if (my.y != other)return false;
	if (my.z != other)return false;

	return true;
}

#pragma endregion




#pragma region Defualt_Funtion

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	GLchar* gui_vertexSource;
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
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
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	GLchar* gui_fragmentSource;
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("Fragment.glsl"); // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return;
	}
}

void InitShader()
{
	GLint result;
	GLchar errorLog[512];

	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	s_program = glCreateProgram();
	gui_s_program = glCreateProgram();
	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);
	glGetProgramiv(s_program, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(s_program, 512, NULL, errorLog);
		cerr << "ERROR: shader program ���� ����\n" << errorLog << endl;
		return;
	}
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(s_program);
}

void FrameTimer(int value)
{
	glutPostRedisplay();
}


//void ReadObj(char* fileName, VertexBlock& block)
//{
//	FILE* obj;
//	vec3 min = vec3(10000), max = vec3(-10000);
//	char lineHeader[55350];
//	int groupNum = 0;
//
//	obj = fopen(fileName, "r");
//	while (!feof(obj)) {
//		fscanf(obj, "%s", lineHeader);
//		if (strcmp(lineHeader, "g") == 0) {
//			groupNum++;
//		}
//	}
//
//	//--- 2. �޸� �Ҵ�'
//	block.vertexIndices = new vector<Face>[groupNum];
//	block.normalIndices = new vector<Face>[groupNum];
//	block.uvIndices = new vector<Face>[groupNum];
//	
//	block.groupCount = -1;
//
//	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽� ���� �Է�
//	rewind(obj);
//	while (!feof(obj)) {
//		fscanf(obj, "%s", lineHeader);
//		if (strcmp(lineHeader, "v") == 0) {
//			vec3 vertex;
//			fscanf(obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//			block.vertices.push_back(vertex);
//			if (vertex.x < min.x) min.x = vertex.x;
//			if (vertex.y < min.y) min.y = vertex.y;
//			if (vertex.z < min.z) min.z = vertex.z;
//			if (vertex.x > max.x) max.x = vertex.x;
//			if (vertex.y > max.y) max.y = vertex.y;
//			if (vertex.z > max.z) max.z = vertex.z;
//		}
//		else if (strcmp(lineHeader, "vt") == 0) {
//			vec2 uv;
//			fscanf(obj, "%f %f\n", &uv.x, &uv.y);
//			block.vertices_uvs.push_back(uv);
//		}
//		else if (strcmp(lineHeader, "vn") == 0) {
//			vec3 normal;
//			fscanf(obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
//			block.vertices_normals.push_back(normal);
//		}
//		else if (strcmp(lineHeader, "f") == 0) {
//			Face vertexIndex, uvIndex, normalIndex;
//			int matches = fscanf(obj, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n", 
//				&vertexIndex.a, &uvIndex.a, &normalIndex.a,
//				&vertexIndex.b, &uvIndex.b, &normalIndex.b, 
//				&vertexIndex.c, &uvIndex.c, &normalIndex.c);
//			if (matches != 9) {
//				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//				return;
//			}
//			block.vertexIndices[block.groupCount].push_back(vertexIndex - 1);
//			block.uvIndices[block.groupCount].push_back(uvIndex - 1);
//			block.normalIndices[block.groupCount].push_back(normalIndex - 1);
//		}
//		else if (strcmp(lineHeader, "g") == 0) {
//			block.groupCount++;
//		}
//		memset(lineHeader, '\0', sizeof(lineHeader));
//	}
//	block.groupCount++;
//	vec3 scale = max - min;
//
//	for (auto& temp : block.vertices)
//	{
//		temp = temp - min;
//		temp = ((temp * 2.0f) / scale) - 1.0f;
//	}
//	block.max = max;
//	block.min = min;
//
//	fclose(obj);	// Player �ҷ��ö� ���� ���� ��� ���� ������ ��
//}

#pragma endregion
