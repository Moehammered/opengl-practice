#ifndef CAMERA__H_
#define CAMERA__H_

#include <glm\glm.hpp>
#include "Transform.h"
///add static accessor to the main active camera later.

class Camera
{
public:
	Camera();
	~Camera();

	static Camera* MainCamera;

	Transform transform;

	float FieldOfView() const;
	float AspectRatio() const;
	float NearPlane() const;
	float FarPlane() const;

	void FieldOfView(float degrees);

	glm::mat4 View() const;
	glm::mat4 Projection() const;
	glm::mat4 ProjView() const;

	void setAspectRatio(float width, float height);
	void setClippingPlanes(float near, float far);
	void updateProjection(); //called when changes are made to FOV, aspect, or clipping planes
	void updateView();

private:
	glm::mat4 view, projection;
	float fov, aspect;
	float nearPlane;
	float farPlane;
};

#endif