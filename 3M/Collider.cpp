#include "Collider.h"

list<Collider*> Collider::allCollider;
bool Collider::isPrint = false;

Collider::Collider()
{
	tag = "NULL";

	rDistance = vec3(0);

	isCollide = true;
	isTrigger = false;
	isMouseCollide = false;
	isWindowCollide = false;

	allCollider.push_back(this);
}

Collider::~Collider()
{
}

void Collider::InitTransform(Transform& t)
{
	transform = &t;
}

void Collider::SetBox(const vector<vec3> box)
{
	colliderBox[0] = colliderBox[1] = vec3(box[0]);

	for (int i = 1; i < box.size(); i++)
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

	rDistance = colliderBox[1] - colliderBox[0];
	rDistance.z = -rDistance.z;	// z만 값이 -라 바꾸어줌
}

void Collider::CheckCollision()
{
	if (!isCollide)
		return;

	onCollideList.clear();

	int i = 0;
	for (auto& other: allCollider)
	{
		if (!other->isCollide)
			continue;

		if (other == this)
			continue;

		if (this->Collide_XY(*other))
			onCollideList.push_back(other);
	}
}

void Collider::OnTrigger()
{
	if (!isCollide || !isTrigger)
		return;
		
	vec3 this_Pos = transform->model * vec4(0, 0, 0, 1);
	vec3 this_RDis = rDistance * transform->localScale * transform->worldScale;
		//cameraPos = -Collide.MainCamera.transform.Position + Instance.windowSize / 2
		/*thisRDis = self.rDistance * self.transform.Scale*/

	for (auto& other : this->onCollideList)
	{
		if (!other->isCollide || !other->isTrigger)
			return;

		vec3 other_Pos = other->transform->model * vec4(0, 0, 0, 1);
		vec3 other_RDis = other->rDistance * transform->localScale * transform->worldScale;

		vec3 AB_Dis = abs(this_RDis - other_RDis);

		if (AB_Dis.x + AB_Dis.y + AB_Dis.z <=
			this_RDis.x + this_RDis.y + this_RDis.z +
			other_RDis.x + other_RDis.y + other_RDis.z)
			return;



		//			if gapDistance[0] < gapDistance[1]:
//	if moveDir[0] > 0:
//	self.transform.Position[0] -= gapDistance[0] + 1
//		elif moveDir[0] < 0 :
//		self.transform.Position[0] += gapDistance[0] + 1
//		if gapDistance[0] > gapDistance[1] :
//			if moveDir[1] > 0:
//	self.transform.Position[1] -= gapDistance[1] + 1
//		elif moveDir[1] < 0 :
//		self.transform.Position[1] += gapDistance[1] + 1
	}


//
//			# 박스기리 충돌된 공간만큼 뒤로 감
//			# TODO Triger는 모든 Object의 OnCollider가 끝난뒤 실행
//			gapDistance = (thisRDis + otherRDis) - ABDis
//			moveDir = self.transform.direction
//
//			if gapDistance[0] < gapDistance[1]:
//	if moveDir[0] > 0:
//	self.transform.Position[0] -= gapDistance[0] + 1
//		elif moveDir[0] < 0 :
//		self.transform.Position[0] += gapDistance[0] + 1
//		if gapDistance[0] > gapDistance[1] :
//			if moveDir[1] > 0:
//	self.transform.Position[1] -= gapDistance[1] + 1
//		elif moveDir[1] < 0 :
//		self.transform.Position[1] += gapDistance[1] + 1
//		pass
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

bool Collider::Collide_XY(Collider& other)
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
	if (modelbox[0].y > other.modelbox[1].y) return false;
	if (modelbox[1].y < other.modelbox[0].y) return false;

	return true;
}



