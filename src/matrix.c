#include <stdlib.h>
#include <stddef.h>

double** construct_matrix_d(size_t x, size_t y) {
	double** matrix = malloc(x*sizeof(double*));
	matrix[0] = malloc(x*y*sizeof(double));
	memset(matrix[0], 0, x*y*sizeof(double));
	for(size_t i = 1; i < x; ++i)
		matrix[i] = matrix[0] + i*y;
	return matrix;
}

void destroy_matrix_d(double** matrix) {
	free(matrix[0]);
	free(matrix);
}
