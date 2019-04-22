#ifndef RENDERCOMPONENT__H_
#define RENDERCOMPONENT__H_

#include "Component.h"
#include "StaticMesh.h"
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
	
	///these 2 need to be merged into "materials"
	//i.e.	TextureMaterial = shader + texture class,
	//		ColourMaterial = shader only
	//		MultiTextureMaterial = shader + textures, etc


	Shader* shaderMaterial;
	Texture* shaderTexture;

	void initialise() override;
	void draw();

private:

	unsigned int shaderTransformLoc;
};

#endif