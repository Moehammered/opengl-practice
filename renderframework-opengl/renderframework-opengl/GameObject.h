#ifndef GAMEOBJECT__H_
#define GAMEOBJECT__H_

#include "Component.h"
#include "Transform.h"
#include "StaticMesh.h"
#include <vector>


typedef struct {
	int id;
	std::string name;
	std::vector<Component> components;
	Transform transform;
} GameObject;

#endif
