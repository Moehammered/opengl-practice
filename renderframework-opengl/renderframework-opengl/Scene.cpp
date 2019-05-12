#include "Scene.h"

#include "Timer.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	cleanup();
}

GameObject& const Scene::findGameObjectByID(int const & id)
{
	//find by id, return it
	unsigned int i = 0;
	for (i = 0; i < GameObject::activeObjects.size(); ++i)
	{
		if (GameObject::activeObjects[i]->id == id)
			break;
	}
	return GameObject::activeObjects[i][0];
}

GameObject& const Scene::findGameObjectByName(std::string const & name)
{
	//find by name, return it
	unsigned int i = 0;
	for (i = 0; i < GameObject::activeObjects.size(); ++i)
	{
		if (GameObject::activeObjects[i]->name == name)
			break;
	}
	return GameObject::activeObjects[i][0];
}

void Scene::initialise()
{
	Timer::tick();
}

void Scene::start()
{
	Timer::tick();
}

void Scene::update()
{
}

void Scene::cleanup()
{
}

//void Scene::updateGameObjects()
//{
//	for (unsigned int i = 0; i < objects.size(); ++i)
//	{
//		updateComponents(objects[i]);
//	}
//}
//
//void Scene::updateComponents(GameObject& obj)
//{
//	for (unsigned int i = 0; i < obj.components.size(); ++i)
//	{
//		if(obj.components[i]->enabled)
//			obj.components[i]->update(Timer::DeltaTime());
//	}
//}
