#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 col;

out vec3 colour;

void main() {
  gl_Position = vec4(vp, 1.0);
  colour = col;
}
