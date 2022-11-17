#pragma once
#include "Object.h"
#include "Collider.h"
class Blade : public Object
{
public:
	static ObjectBlock* blade_Object;

public:
	Blade();
	~Blade();

public:
	void Init();

private:

public:
	Collider collider;

private:

};

