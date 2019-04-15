#pragma once

#include "Scene.h"
#include "Line.h"
#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture.h"

class FPSDemo : public Scene
{
public:
	FPSDemo();
	~FPSDemo();

	void initialise();
	void update(float deltaTime);
	void cleanup();
	
protected:
	Line xAxis, yAxis, zAxis;
	Shader* transformShader;
	Texture* containerTexture;

	GameObject player;
	Transform groundTransform;
	StaticMesh playerMesh, ground;
	Camera mainCam;
};
