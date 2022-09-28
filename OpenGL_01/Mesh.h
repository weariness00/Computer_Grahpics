#pragma once

#include "Afx.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	
public:
	void InitVertax(Vector2 dot[2]);
	Vector2** GetMeshVertax() { return meshVertax; };
	Vector2** GetRealMeshVertax() { return Real_MeshVertax; };

public:
	void SetAllAcetive(bool value);

public:
	int xDot;
	int yDot;
	bool** isAcitve;

protected:
	Vector2** meshVertax;
	Vector2** Real_MeshVertax;
};