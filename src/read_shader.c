#include <stdio.h>
#include <stdlib.h>

struct ShaderFile {
	char *buf;
	size_t size;
};

struct ShaderFile *readFile(const char *path) {
	FILE *f = fopen(path, "r");
	struct ShaderFile *sf =
		(struct ShaderFile *)malloc(sizeof(struct ShaderFile));
	if (f == NULL) {
		fprintf(stderr, "file not found\n");
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	sf->size = ftell(f);
	fseek(f, 0, SEEK_SET);
	sf->buf = (char *)malloc(sf->size);
	fread(sf->buf, sf->size, 1, f);
	return sf;
}

void readShader(const char *path) {
	struct ShaderFile *sf = readFile(path);
	printf("%s\n", sf->buf);
}
