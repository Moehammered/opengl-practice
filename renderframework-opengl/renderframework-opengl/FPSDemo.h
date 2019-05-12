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
	void update() override;
	void cleanup();
	
protected:
	Line xAxis, yAxis, zAxis;

	GameObject player;
	GameObject bigBox;
	GameObject ground;
	Camera mainCam;
};

