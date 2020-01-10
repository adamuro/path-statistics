#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double atofCoord (const char *str) {
	double coord = 0;
	double div = 10;
	int i;
	for(i = 0 ; str[i] != '.' ; i++) {
		coord *= 10;
		coord += str[i] - 48;
	}
	while(i++ < strlen(str)) {
		coord += ((double)str[i] - 48) / div;
		div *= 10;
	}
	return coord;
}