#pragma once
#include "RenderComponent.h"
#include "Line.h"
#include "DynamicMesh.h"

class TransformVisualiser :
	public RenderComponent
{
public:
	TransformVisualiser();
	~TransformVisualiser();

	void initialise() override;
	void draw() override;

private:
	Vertex* vertBuffer;
	//Line forward, right, up;
	DynamicMesh forward, right, up;
	Colour lineColours[3];

	void setupLine(DynamicMesh& mesh, Vertex * const vertBuffer);
	void drawAxis(DynamicMesh& forward, DynamicMesh& right, DynamicMesh& up);
};

