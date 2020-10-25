#include <stdlib.h>

#define new(type) malloc(sizeof(type))

int main() {
	int* a = new(int);
	free(a);
	free(a);
	return 0;
}
