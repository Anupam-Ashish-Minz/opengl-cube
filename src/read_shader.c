#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#define SH_ERR_MAX_LEN 1000

GLuint readShader(const char *path, GLenum shaderType) {
	FILE *f = fopen(path, "r");
	char *buf;
	char log[SH_ERR_MAX_LEN];
	size_t fileSize;
	int status, logLen;

	if (f == NULL) {
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	fileSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = (char *)malloc(fileSize);
	fread(buf, fileSize, 1, f);

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, (const char **)&buf, (int *)&fileSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		glGetShaderInfoLog(shader, SH_ERR_MAX_LEN, &logLen, log);
		fprintf(stderr, "%s shader error: %s\n",
				shaderType == GL_VERTEX_SHADER ? "vertex" : "fragement", log);
		return 0;
	}
	return shader;
}
