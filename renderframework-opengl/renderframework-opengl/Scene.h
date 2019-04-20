#ifndef SCENE__H_
#define SCENE__H_

#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	GameObject* const findGameObjectByID(int const &id);
	GameObject* const findGameObjectByName(std::string const &name);

	virtual void initialise();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void cleanup();

	//void updateGameObjects();

protected:
	friend void GameObject::UpdateGameObjects();
	//void updateComponents(GameObject& obj);
};

#endif