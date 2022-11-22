#include "Collider.h"

ObjectBlock* Collider::box_Block = nullptr;
list<Collider*> Collider::allCollider;
bool Collider::isPrint = false;

Collider::Collider()
{
	if (box_Block == nullptr)
	{
		box_Block = new ObjectBlock;
		ReadObj((char*)"Cube.obj", *box_Block);
	}

	cBlock.vertIndex = box_Block->vertIndex;
	cBlock.faceIndex = box_Block->faceIndex;
	cBlock.vertices = box_Block->vertices;
	cBlock.face = box_Block->face;

	tag = "NULL";
	color.R = 0;
	color.G = 0;

	isCollide = true;
	isTrigger = false;
	isMouseCollide = false;
	isWindowCollide = false;

	allCollider.push_back(this);
}

Collider::~Collider()
{
}

void Collider::Init()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glGenBuffers(1, &VAO_Index);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * cBlock.vertices.size(), &cBlock.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * cBlock.faceIndex, &cBlock.face[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);
}

void Collider::DrawBox()
{
	if (!isCollide)
		return;

	mat4 collideModel = scale(object->transform.model, size);

	glUniformMatrix4fv(Object::modelLocation, 1, GL_FALSE, value_ptr(collideModel));
	glUniform4f(Object::vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, cBlock.vertices.size());
	glDrawElements(GL_TRIANGLES, cBlock.faceIndex * 3, GL_UNSIGNED_SHORT, 0);
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

	rDistance = colliderBox[1] - colliderBox[0];
	rDistance.z = -rDistance.z;	// z�� ���� -�� �ٲپ���
}

void Collider::GetBox()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = translate(localModel, object->transform.localPosition);
	localModel = rotate(localModel, radians(object->transform.localRotation.y), vec3(0, 1.0, 0));
	localModel = translate(localModel, object->transform.localPivot);
	localModel = scale(localModel, object->transform.localScale);

	worldModel = translate(worldModel, object->transform.worldPosition);
	worldModel = rotate(worldModel, radians(object->transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = translate(worldModel, object->transform.worldPivot);
	worldModel = scale(worldModel, object->transform.worldScale);

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

// Right Front Top ���� �����ָ� �ȴ�.
// �� ���� ���� ������ ũ�⸦ �����ָ� �ȴ�.
void Collider::SetBox_OBB(vec3 d)
{
	size = d;
	for (int i = 0; i < 3; i++)
	{
		defaultAxis[i] = axis[i] = vec3(0);
		axisLen[i] = 0;
	}

	defaultAxis[0].x = axisLen[0] = d.x / 2;
	defaultAxis[1].y = axisLen[1] = d.y / 2;
	defaultAxis[2].z = axisLen[2] = d.z / 2;
}


void Collider::GetBox_OBB()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = rotate(localModel, radians(object->transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(object->transform.localRotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(object->transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, object->transform.localScale);

	worldModel = rotate(worldModel, radians(object->transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(object->transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(object->transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = scale(worldModel, object->transform.worldScale);

	mat4 model = localModel * worldModel;

	for (int i = 0; i < 3; i++)
	{
		axis[i] = model * vec4(defaultAxis[i],1);
		axisLen[i] = length(defaultAxis[i] * object->transform.worldScale * object->transform.localScale);
	}
		//axis[i] = object->transform.model * vec4(defaultAxis[i], 1);

	if (isPrint)
	{
		cout << this->tag << endl;
		for (int i = 0; i < 3; i++)
			cout << axis[i] << endl;
	}
}


// TODO
// �浹 üũ�� ������ �ȵ�
// �Ƹ� Vec3Dot ���� �����ε� ��
// dis�� axis �ʱ�ȭ ������ �ִ� ��
bool Collider::OBBCollision(const Collider& a,const Collider& b)
{
	color.SetColor({ 0, 0, 1, 1 });
	if (!a.isCollide || !b.isCollide)
		return false;

	vec3 dis; // a, b�� �Ÿ�
	double c[3][3];
	double absC[3][3];
	double d[3];
	const double cutoff = 0.999999; // �������͸� �÷��� ����
	double r, r1, r2;	// ������ ����
	bool isExitsParallelPair = false;

	//dis = abs(a.object->transform.model * vec4(0,0,0,1) - b.object->transform.model * vec4(0,0,0,1));
	dis = abs(a.object->transform.worldPosition - b.object->transform.worldPosition);
	for (int n = 0; n < 3; n++)
	{
		for (int i = 0; i < 3; i++)
		{
			c[n][i] = Vec3Dot(a.axis[n], b.axis[i]);
			absC[n][i] = abs(c[n][i]);
			if (absC[n][i] > cutoff)
				isExitsParallelPair = true;
		}
		d[n] = Vec3Dot(dis, a.axis[n]);
		r = abs(d[n]);
		r1 = a.axisLen[n];
		r2 = b.axisLen[0] * absC[n][0] + b.axisLen[1] * absC[n][1] + b.axisLen[2] * absC[n][2];
		if (r > r1 + r2)
			return false;

		r = abs(Vec3Dot(dis, b.axis[n]));
		r1 = a.axisLen[0] * absC[0][n] + a.axisLen[1] * absC[1][n] + a.axisLen[2] * absC[2][n];
		r2 = b.axisLen[n];
		if (r > r1 + r2)
			return false;
	}

	if (isExitsParallelPair)
		return true;

	{
		r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
		r1 = a.axisLen[1] * absC[2][0] + a.axisLen[2] * absC[1][0];
		r2 = b.axisLen[1] * absC[0][2] + b.axisLen[2] * absC[0][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
		r1 = a.axisLen[1] * absC[2][1] + a.axisLen[2] * absC[1][1];
		r2 = b.axisLen[0] * absC[0][2] + b.axisLen[2] * absC[0][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
		r1 = a.axisLen[1] * absC[2][2] + a.axisLen[2] * absC[1][2];
		r2 = b.axisLen[0] * absC[0][1] + b.axisLen[2] * absC[0][0];
		if (r > r1 + r2)
			return false;
	}

	{
		r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
		r1 = a.axisLen[0] * absC[2][0] + a.axisLen[2] * absC[0][0];
		r2 = b.axisLen[1] * absC[1][2] + b.axisLen[2] * absC[1][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
		r1 = a.axisLen[0] * absC[2][1] + a.axisLen[2] * absC[0][1];
		r2 = b.axisLen[0] * absC[1][2] + b.axisLen[2] * absC[1][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
		r1 = a.axisLen[0] * absC[2][2] + a.axisLen[2] * absC[0][2];
		r2 = b.axisLen[0] * absC[1][1] + b.axisLen[1] * absC[1][0];
		if (r > r1 + r2)
			return false;
	}

	{
		r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
		r1 = a.axisLen[0] * absC[1][0] + a.axisLen[1] * absC[0][0];
		r2 = b.axisLen[1] * absC[2][2] + b.axisLen[2] * absC[2][1];
		if (r > r1 + r2)
			return false;

		r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
		r1 = a.axisLen[0] * absC[1][1] + a.axisLen[1] * absC[0][1];
		r2 = b.axisLen[0] * absC[2][2] + b.axisLen[2] * absC[2][0];
		if (r > r1 + r2)
			return false;

		r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
		r1 = a.axisLen[0] * absC[1][2] + a.axisLen[1] * absC[0][2];
		r2 = b.axisLen[0] * absC[2][1] + b.axisLen[1] * absC[2][0];
		if (r > r1 + r2)
			return false;
	}

	color.SetColor({ 1, 0, 0, 1 });
	return true;
}