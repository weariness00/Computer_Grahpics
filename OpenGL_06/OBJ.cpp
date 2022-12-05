#include "OBJ.h"

OBJ::OBJ()
{
}

OBJ::~OBJ()
{
}

void OBJ::ReadObj(char* fileName)
{
	FILE* obj;
	FILE* mtl;
	char lineHeader[55350];
	int groupNum = 0;
	char mtlName[100];

	obj = fopen(fileName, "r");
	while (!feof(obj)) {
		fscanf(obj, "%s", lineHeader);
		if (strcmp(lineHeader, "g") == 0) groupNum++;
		else if(strcmp(lineHeader, "mtllib") == 0) fscanf(obj, "%s", mtlName);
	}
	mtl = fopen(mtlName, "r");

	vBlock.vertexIndices = new vector<Face>[groupNum];
	vBlock.normalIndices = new vector<Face>[groupNum];
	vBlock.uvIndices = new vector<Face>[groupNum];
	vBlock.groupCount = -1;
	vBlock.min = vec3(10000); vBlock.max = vec3(-10000);

	rewind(obj);
	while (!feof(obj)) {
		fscanf(obj, "%s", lineHeader);
		if (strcmp(lineHeader, "v") == 0) PushVertex(obj);
		else if (strcmp(lineHeader, "vt") == 0) PushUV(obj);
		else if (strcmp(lineHeader, "vn") == 0) PushNormal(obj);
		else if (strcmp(lineHeader, "f") == 0) PushFaceIndex(obj);
		else if (strcmp(lineHeader, "g") == 0) vBlock.groupCount++;
		memset(lineHeader, '\0', sizeof(lineHeader));
	}
	vBlock.groupCount++;
	vec3 scale = vBlock.max - vBlock.min;

	for (auto& temp : vBlock.vertices)
	{
		temp = temp - vBlock.min;
		temp = ((temp * 2.0f) / scale) - 1.0f;
	}

	objName = fileName;
	//fclose(obj);	// 모호하다네 왜?
}

void OBJ::PushVertex(FILE* obj)
{
	vec3 vertex;
	vec3 min = vBlock.min; vec3 max = vBlock.max;
	fscanf(obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
	vBlock.vertices.push_back(vertex);
	if (vertex.x < min.x) min.x = vertex.x;
	if (vertex.y < min.y) min.y = vertex.y;
	if (vertex.z < min.z) min.z = vertex.z;
	if (vertex.x > max.x) max.x = vertex.x;
	if (vertex.y > max.y) max.y = vertex.y;
	if (vertex.z > max.z) max.z = vertex.z;

	vBlock.min = min;
	vBlock.max = min;
}

void OBJ::PushUV(FILE* obj)
{
	vec2 uv;
	fscanf(obj, "%f %f\n", &uv.x, &uv.y);
	vBlock.vertices_uvs.push_back(uv);
}

void OBJ::PushNormal(FILE* obj)
{
	vec3 normal;
	fscanf(obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	vBlock.vertices_normals.push_back(normal);
}

void OBJ::PushFaceIndex(FILE* obj)
{
	Face vertexIndex, uvIndex, normalIndex;
	int matches = fscanf(obj, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu\n",
		&vertexIndex.a, &uvIndex.a, &normalIndex.a,
		&vertexIndex.b, &uvIndex.b, &normalIndex.b,
		&vertexIndex.c, &uvIndex.c, &normalIndex.c);
	if (matches != 9) {
		printf("File can't be read by our simple parser : ( Try exporting with other options\n");
		return;
	}
	vBlock.vertexIndices[vBlock.groupCount].push_back(vertexIndex - 1);
	vBlock.uvIndices[vBlock.groupCount].push_back(uvIndex - 1);
	vBlock.normalIndices[vBlock.groupCount].push_back(normalIndex - 1);
}
