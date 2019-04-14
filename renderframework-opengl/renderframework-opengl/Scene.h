#ifndef SCENE__H_
#define SCENE__H_

#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	void addGameObject(GameObject& obj);
	void removeGameObject(GameObject& obj);
	void removeGameObject(int const &id);
	GameObject& findGameObjectByID(int const &id);
	GameObject& findGameObjectByName(std::string const &name);

	virtual void initialise();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void cleanup();

	void updateGameObjects();

protected:
	std::vector<GameObject> objects;

	void updateComponents(GameObject& obj);
};

#endif