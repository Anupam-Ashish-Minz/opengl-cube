#version 330

layout(location = 0) in vec3 pos;

void main() {
	gl_Position.xyz = pos.xyz;
	gl_Position.w = 1.0;
}
