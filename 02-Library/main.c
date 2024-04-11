#include <stdio.h>
#include "calculator.h"

int main() {
	int x = 5, y = 9;
	printf("add: %d + %d = %d\n", x, y, add(x, y));
	printf("sub: %d - %d = %d\n", x, y, sub(x, y));
	printf("mul: %d * %d = %d\n", x, y, mul(x, y));
	printf("div: %d / %d = %d\n", x, y, div(x, y));
	return 0;
}
