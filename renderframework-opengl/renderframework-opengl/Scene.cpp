#include "Scene.h"

#include "Timer.h"

Scene::Scene()
{
	objects.reserve(10);
}

Scene::~Scene()
{
	cleanup();
	objects.clear();
}

void Scene::addGameObject(GameObject& obj)
{
	objects.push_back(obj);
}

void Scene::removeGameObject(GameObject& obj)
{
	//objects.erase(obj);
	removeGameObject(obj.id);
}

void Scene::removeGameObject(int const & id)
{
	//find the id, remove it.
	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		if (objects[i].id == id)
		{
			objects.erase(objects.begin() + i);
			break;
		}
	}
}

GameObject& Scene::findGameObjectByID(int const & id)
{
	//find by id, return it
	unsigned int i = 0;
	for (i = 0; i < objects.size(); ++i)
	{
		if (objects[i].id == id)
			break;
	}
	return objects[i];
}

GameObject& Scene::findGameObjectByName(std::string const & name)
{
	//find by name, return it
	unsigned int i = 0;
	for (i = 0; i < objects.size(); ++i)
	{
		if (objects[i].name == name)
			break;
	}
	return objects[i];
}

void Scene::initialise()
{
	Timer::tick();
}

void Scene::start()
{
	Timer::tick();
}

void Scene::update(float deltaTime)
{

}

void Scene::cleanup()
{
}

void Scene::updateGameObjects()
{
	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		updateComponents(objects[i]);
	}
}

void Scene::updateComponents(GameObject& obj)
{
	for (unsigned int i = 0; i < obj.components.size(); ++i)
	{
		if(obj.components[i]->enabled)
			obj.components[i]->update(Timer::DeltaTime());
	}
}
