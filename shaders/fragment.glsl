#version 330

out vec4 outColor;
uniform vec2 screenSize;
uniform float sinWave;

void main() {
	vec2 uv = gl_FragCoord.xy / screenSize;
	vec3 color = vec3(0.0, 0.0, 0.70);
	color.g = uv.y;
	color.r = sinWave + uv.x;

	outColor = vec4(color, 1.0);
}
