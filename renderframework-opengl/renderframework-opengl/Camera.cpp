#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include "TransformHelperFunctions.h"
#include <iostream>

Camera* Camera::MainCamera = nullptr;

Camera::Camera()
{
	fov = glm::radians(45.0f);
	aspect = 800 / 600.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	view = glm::lookAt(transform.position, transform.position + transform.Forward(), transform.Up());
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);

	if (MainCamera == nullptr)
		MainCamera = this;
}

Camera::~Camera()
{
}

float Camera::FieldOfView() const
{
	return 0.0f;
}

float Camera::AspectRatio() const
{
	return 0.0f;
}

float Camera::NearPlane() const
{
	return 0.0f;
}

float Camera::FarPlane() const
{
	return 0.0f;
}

void Camera::FieldOfView(float degrees)
{
	fov = glm::radians(degrees);
}

glm::mat4 Camera::View() const
{
	return view;
}

glm::mat4 Camera::Projection() const
{
	return projection;
}

glm::mat4 Camera::ProjView() const
{
	return projection * /*glm::inverse*/(view);
}

void Camera::setAspectRatio(float width, float height)
{
	aspect = width / height;
}

void Camera::setClippingPlanes(float near, float far)
{
	this->nearPlane = near;
	this->farPlane = far;
}

void Camera::updateProjection()
{
	projection = glm::perspective(fov, aspect, nearPlane, farPlane);
}

void Camera::updateView()
{
	glm::vec3 lookat = transform.position + transform.Forward();
	view = glm::lookAt(transform.position, lookat, transform.Up());
}
