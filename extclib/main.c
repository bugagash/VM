#include <stdio.h>
#include <stdint.h>

extern int8_t readvm_src(FILE *output, FILE *input);
extern int32_t readvm_exc(FILE *input);

int32_t runvm_exc(const char *filename);
int8_t compilevm_src(const char *outputf, const char *inputf);

int main(void) {
	compilevm_src("main.vme", "main.vms");
	printf("%d\n", runvm_exc("main.vme"));
	return 0;
}

int32_t runvm_exc(const char *filename) {
	FILE *input = fopen(filename, "r");
	if (!input) {
		fprintf(stderr, "%s\n", "error: opening the file");
		return -1;
	}
	int32_t res = readvm_exc(input);
	fclose(input);
	return res;
}

int8_t compilevm_src(const char *outputf, const char *inputf) {
	FILE *input = fopen(inputf, "r");
	if (!input) {
		fprintf(stderr, "%s\n", "error: opening the file");
		return -1;
	}
	FILE *output = fopen(outputf, "wb");
	if (!output) {
		fprintf(stderr, "%s\n", "error: opening the file");
		return -1;
	}
	readvm_src(output, input);
	fclose(inputf);
	fclose(outputf);
}