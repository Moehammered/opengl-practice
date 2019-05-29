#pragma once
#include "RenderComponent.h"
#include "BoundingVolume.h"
#include "DynamicMesh.h"

class VolumeVisualiser :
	public RenderComponent
{
public:
	VolumeVisualiser();
	~VolumeVisualiser();

	BoxVolume volumeToRender;
	unsigned int lineWidth;

	void initialise() override;
	void updateRenderVolume();
	void draw() override;

private:
	DynamicMesh volumeMesh;
	Vertex vertices[8];
	void buildLineVerts();
	void buildLineMesh();
};

