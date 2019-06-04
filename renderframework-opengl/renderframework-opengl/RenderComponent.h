#ifndef RENDERCOMPONENT__H_
#define RENDERCOMPONENT__H_

#include "Component.h"
#include "StaticMesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent();
	~RenderComponent();

	StaticMesh mesh;
	bool enabled;
	
	Material* material;

	void initialise() override;
	bool isActive() override;
	virtual void draw();
};

#endif