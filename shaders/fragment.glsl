#version 330

out vec4 outColor;
uniform vec2 screenSize;

void main() {
	vec2 uv = gl_FragCoord.xy / screenSize;
	vec3 color = vec3(0.0, 0.0, 0.70);
	color.rg = uv.xy;

	outColor = vec4(color, 1.0);
}
