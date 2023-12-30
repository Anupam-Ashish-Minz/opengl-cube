#version 330

out vec4 outColor;

void main() {
	vec3 color = vec3(0.5, 0.5, 0.7);
	outColor = vec4(color, 1.0);
}
