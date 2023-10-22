#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stdin_helpers.h"

double** construct_matrix(size_t x, size_t y) {
	double** matrix = malloc(x*sizeof(double*));
	matrix[0] = malloc(x*y*sizeof(double));
	memset(matrix[0], 0, x*y*sizeof(double));
	for(size_t i = 1; i < x; ++i)
		matrix[i] = matrix[0] + i*y;
	return matrix;
}

void cleanup(double** matrix) {
	free(matrix[0]);
	free(matrix);
}

void clear_screen(void) {
	system("clear");
}

size_t menu(void) {
	clear_screen();

	printf("Welcome to matrix determinant calculator\n");
	printf("1. Calculate detetminant\n");
	printf("2. Exit\n");

	unsigned choice = get_uint_from_stdin();
	
	clear_screen();

	switch(choice) {
		case 1:
			printf("Disclaimer: only real matrices are acceptable\n");
			printf("Provide matrix dimention: \n");
			size_t dim = get_sizet_from_stdin();
			if(dim == 1) {
				printf("That's pretty pointless, don't You think?\n");
				exit(0);
			}
			return dim;
		case 2:
			printf("Cya!\n");
			exit(0);
			break;
		default:
			break;
	}
	return -1;
}

void display(double** table, size_t size)
{
	// upper line
	for(size_t i = 0; i < size; ++i) {
        printf("======");
	}
	printf("\n");
	
	// matrix
	for(size_t i = 0; i < size; ++i) {
        for(size_t j = 0; j < size; ++j) {
            printf("%.2f\t", table[i][j]);
        }
        printf("\n");
    }
    // lower line
	for(size_t i = 0; i < size; ++i) {
		printf("======");
	}
	printf("\n");
}

double det2(double** matrix) {
	return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

double laplace2(double** matrix, size_t dim) {
	if (dim == 1) return matrix[0][0];
	if (dim == 2) return det2(matrix);

	// Laplace expansion column, algorithm always expands over k=0
	size_t laplace_k = 0;

	// create array of matrices[dim-1][dim-1]
	double*** matrices = malloc(dim*sizeof(double***));

	// loop over laplace submatrices
	for (size_t i = 0; i < dim; ++i) {
		matrices[i] = construct_matrix(dim-1, dim-1);
		// laplace_j = i;
		// loop over input matrix
		for (size_t j = 0; j < dim; ++j) {
			if (j == i) continue;
			for (size_t k = 0; k < dim; ++k) {
				if (k == laplace_k) continue;
				size_t j_output =  j>i ? j-1 : j;	// increment row if above expanded row, else do nothing
				size_t k_output = k-1;				// always increment column since we expand over k=0
				matrices[i][j_output][k_output] = matrix[j][k];
			}
		}
	}

	// calculate determinant by looping over matrices and applying algorithm recursively
	double result = 0;
	for (size_t i = 0; i < dim; ++i) {
		result += pow(-1, i)*matrix[i][0]*laplace2(matrices[i], dim-1);
	}

	// free matrices
	for (size_t i = 0; i < dim; ++i) {
		cleanup(matrices[i]);
	}
	free(matrices);

	return result;
}

int main() {

	size_t dim = menu();

	// dynamic allocation as a coherent block
	double** matrix = construct_matrix(dim, dim);

    //input
    for(size_t i = 0; i < dim; ++i) {
		for(size_t j = 0; j < dim; ++j) {
			clear_screen();
        	printf("Provide matrix cell values, left to right, from up to down\n");
        	printf("Provide matrix cell value no. %zu\n", i*dim+j+1);
			display(matrix, dim);
			matrix[i][j] = get_double_from_stdin();
		}  
    }
    clear_screen();
	printf("Your matrix: \n");
	display(matrix, dim);
	printf("Determinant equals %.2f\n", laplace2(matrix, dim));
	cleanup(matrix);
	return 0;
}

