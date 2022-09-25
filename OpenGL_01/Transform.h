#pragma once

#include "Mesh.h"

class Transform : public Mesh {
public:
	Transform();
	Transform(Vector2 pos, Vector2 scale);
	~Transform();

public:
	void Update();
	void InitPivot(Vector2 pivot);
	void SetPosition(Vector2 pos);
	void SetScale(Vector2 scale);
	void SetScale();
	void ResetPosition();

private:
	void SetVertax();

public:
	Vector2 Pivot;
	Vector2 Scale;

private:
	Vector2 Init_Pivot;
};