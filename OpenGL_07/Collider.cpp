#include "Collider.h"

Camera* Collider::camera = nullptr;
bool Collider::isPrint = false;

Collider::Collider()
{
	tag = "NULL";
	isCollide = false;
	isMouseCollide = false;
	isWindowCollide = false;
}

Collider::~Collider()
{
}

void Collider::InitTransform(Transform& t)
{
	transform = &t;
}

void Collider::SetBox(const vec3* box, int size)
{
	colliderBox[0] = colliderBox[1] = vec3(box[0]);

	for (int i = 1; i < size; i++)
	{
		if (colliderBox[0].x > box[i].x)
			colliderBox[0].x = box[i].x;
		else if (colliderBox[1].x < box[i].x)
			colliderBox[1].x = box[i].x;

		if (colliderBox[0].y > box[i].y)
			colliderBox[0].y = box[i].y;
		else if (colliderBox[1].y < box[i].y)
			colliderBox[1].y = box[i].y;

		if (colliderBox[0].z < box[i].z)
			colliderBox[0].z = box[i].z;
		else if (colliderBox[1].z > box[i].z)
			colliderBox[1].z = box[i].z;
	}
}

void Collider::GetBox()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = translate(localModel, transform->localPosition);
	localModel = rotate(localModel, radians(transform->localRotation.y), vec3(0, 1.0, 0));
	localModel = translate(localModel, transform->localPivot);
	localModel = scale(localModel, transform->localScale);

	worldModel = translate(worldModel, transform->worldPosition);
	worldModel = rotate(worldModel, radians(transform->worldRotation.y), vec3(0, 1.0, 0));
	worldModel = translate(worldModel, transform->worldPivot);
	worldModel = scale(worldModel, transform->worldScale);

	for (int i = 0; i < 2; i++)
		modelbox[i] = localModel * worldModel * vec4(colliderBox[i], 1);
	
	vec4 copybox[2] = { vec4(modelbox[0]), vec4(modelbox[1]) };
	for (int i = 0; i < 2; i++)
	{
		if (modelbox[0].x > copybox[i].x)
			modelbox[0].x = copybox[i].x;
		else if (modelbox[1].x < copybox[i].x)
			modelbox[1].x = copybox[i].x;

		if (modelbox[0].y > copybox[i].y)
			modelbox[0].y = copybox[i].y;
		else if (modelbox[1].y < copybox[i].y)
			modelbox[1].y = copybox[i].y;

		if (modelbox[0].z < copybox[i].z)
			modelbox[0].z = copybox[i].z;
		else if (modelbox[1].z > copybox[i].z)
			modelbox[1].z = copybox[i].z;
	}
}

bool Collider::Collide_XZ(Collider& other)
{
	GetBox();
	other.GetBox();
	
	if (isPrint)
	{
		cout << tag << "\n" << modelbox[0] << "\n" << modelbox[1] << endl;
		cout << other.tag << "\n" << other.modelbox[0] << "\n" << other.modelbox[1] << endl;
	}

	if (modelbox[0].x > other.modelbox[1].x) return false;
	if (modelbox[1].x < other.modelbox[0].x) return false;
	if (modelbox[0].z < other.modelbox[1].z) return false;
	if (modelbox[1].z > other.modelbox[0].z) return false;

	return true;
}


