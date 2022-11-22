#pragma once
#include "Collider.h"
#include "Render.h"

class CollapseCube_Cell : public Object {
public:
	CollapseCube_Cell() {};
	~CollapseCube_Cell() {};

public:
	void Init() {
		Object::Init();
		Render::objectRenedr->AddObject(this);
	};
};

class CollapseCube : public Object
{
public:
	static ObjectBlock* collapseCube_Block;

public:
	CollapseCube();
	~CollapseCube();

public:
	void Init();
	void Update();
	void Handle_Evnet(unsigned char key);

private:
	void DistroyAnimation();

public:
	float defaultCameraDistance;

private:
	CollapseCube_Cell* cell;

	int delTime;
	bool isDistroy;
	int delCount;
};

