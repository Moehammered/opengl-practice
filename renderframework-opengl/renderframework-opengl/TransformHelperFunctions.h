#ifndef TRANSFORMHELPERFUNCTIONS__H_
#define TRANSFORMHELPERFUNCTIONS__H_

///might be better merged into the transform class....

#include "Transform.h"
#include <glm\glm.hpp>
#include <string>

glm::mat4 transformToMatrix(Transform const &tr);
glm::mat4 transformRotationToMatrix(Transform const &tr);
std::string vec3ToString(glm::vec3 const &v3);

#endif
