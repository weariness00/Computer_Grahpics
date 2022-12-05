#pragma once
#include "Afx.h"

typedef struct VertexBlock {
	vector<Face>* vertexIndices, * uvIndices, * normalIndices;
	vector<vec3> vertices;
	vector<vec2> vertices_uvs;
	vector<vec3> vertices_normals;
	vec3 max, min;
	int groupCount;
}VertexBlock;

typedef struct MaterialBlock {
	char name[32];
	int illum;
	float Ni;
	vec3 Ka;
	vec3 Kd;
	vec3 Tf;

	char map_Kd[32];
	unsigned int texture;
}MaterialBlock;

class OBJ
{
public:
	OBJ();
	~OBJ();
public:
	void ReadObj(char* fileName);

private:	// obj 관련
	void PushVertex(FILE* obj);
	void PushUV(FILE* obj);
	void PushNormal(FILE* obj);
	void PushFaceIndex(FILE* obj);

private:	// tml 관련
	void PushMaterial(FILE* obj);

public:
	VertexBlock vBlock;
	MaterialBlock mBlock;

private:
	string objName;
	string materialName;
};

