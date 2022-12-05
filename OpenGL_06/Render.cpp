#include "Render.h"

Render* Render::meshtRender = nullptr;

Render::Render()
{
}

Render::~Render()
{
	for (auto& list : renderList)
		list.second.clear();
	renderList.clear();
}

void Render::Draw()
{
	glUseProgram(s_program);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Camera::mainCamera->Draw();
	for (auto& layer : renderList)
	{
		for (auto& mesh : layer.second)
		{
			if (!mesh->isDraw)
				continue;

			if (!mesh->object->ActiveSelf())
				continue;

			mesh->Draw();
		}
	}
}

void Render::AddObject(Mesh* mesh, string layoutName)
{
	renderList[layoutName].push_back(mesh);
}