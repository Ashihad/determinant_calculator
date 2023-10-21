#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdin_helpers.h"

double** construct_matrix(size_t x, size_t y) {
	double** matrix = malloc(x*sizeof(double*));
	matrix[0] = malloc(x*y*sizeof(double));
	memset(matrix[0], 0, x*y*sizeof(double));
	for(size_t i = 1; i < x; ++i)
		matrix[i] = matrix[0] + i*y;
	return matrix;
}

double sum_d(double* arr, size_t size) {
	double sum = 0;
	for (size_t i = 0; i < size; ++i) {
		sum += arr[i];
	}
	return sum;
}

void clear_screen(void) {
	system("clear");
}
 
void cleanup(double** matrix) {
	free(matrix[0]);
	free(matrix);
}

unsigned menu(void) {
	clear_screen();

	puts("Welcome to matrix determinant calculator");
	puts("1. Calculate detetminant");
	puts("2. Exit");

	unsigned choice = get_uint_from_stdin();
	
	clear_screen();

	switch(choice) {
		case 1:
			puts("Disclaimer: max dimentions are currently 4x4");
			puts("Provide matrix dimention: ");
			unsigned dim = get_int_from_stdin();
			if(dim == 1) {
				printf("That's pretty pointless, don't You think?");
				exit(0);
			}
			return dim;
		case 2:
			puts("Cya!");
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
	
	// macierz
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

double det3(double** matrix)
{
	double temp[6];
	temp[0] = matrix[0][0]*matrix[1][1]*matrix[2][2];
	temp[1] = matrix[0][1]*matrix[1][2]*matrix[2][0];
	temp[2] = matrix[0][2]*matrix[1][0]*matrix[2][1];
	temp[3] = matrix[0][2]*matrix[1][1]*matrix[2][0];
	temp[4] = matrix[0][1]*matrix[1][0]*matrix[2][2];
	temp[5] = matrix[0][0]*matrix[1][2]*matrix[2][1];
	return sum_d(temp, 3)-sum_d(temp+3, 3);
}

double laplace(double** matrix, int dim)
{
    if(dim == 2)
        return det2(matrix);
    if(dim == 3)
        return det3(matrix);
    if(dim == 4)
    {
		// rozwinięcie względem kolumny 0
		double** matrix1 = construct_matrix(3, 3);
		double** matrix2 = construct_matrix(3, 3);
		double** matrix3 = construct_matrix(3, 3);
		double** matrix4 = construct_matrix(3, 3);

		matrix1[0][0] = matrix[1][1];
		matrix1[0][1] = matrix[1][2];
		matrix1[0][2] = matrix[1][3];
		matrix1[1][0] = matrix[2][1];
		matrix1[1][1] = matrix[2][2];
		matrix1[1][2] = matrix[2][3];
		matrix1[2][0] = matrix[3][1];
		matrix1[2][1] = matrix[3][2];
		matrix1[2][2] = matrix[3][3];

		matrix2[0][0] = matrix[0][1];
		matrix2[0][1] = matrix[0][2];
		matrix2[0][2] = matrix[0][3];
		matrix2[1][0] = matrix[2][1];
		matrix2[1][1] = matrix[2][2];
		matrix2[1][2] = matrix[2][3];
		matrix2[2][0] = matrix[3][1];
		matrix2[2][1] = matrix[3][2];
		matrix2[2][2] = matrix[3][3];

		matrix3[0][0] = matrix[0][1];
		matrix3[0][1] = matrix[0][2];
		matrix3[0][2] = matrix[0][3];
		matrix3[1][0] = matrix[1][1];
		matrix3[1][1] = matrix[1][2];
		matrix3[1][2] = matrix[1][3];
		matrix3[2][0] = matrix[3][1];
		matrix3[2][1] = matrix[3][2];
		matrix3[2][2] = matrix[3][3];

		matrix4[0][0] = matrix[0][1];
		matrix4[0][1] = matrix[0][2];
		matrix4[0][2] = matrix[0][3];
		matrix4[1][0] = matrix[1][1];
		matrix4[1][1] = matrix[1][2];
		matrix4[1][2] = matrix[1][3];
		matrix4[2][0] = matrix[2][1];
		matrix4[2][1] = matrix[2][2];
		matrix4[2][2] = matrix[2][3];
        // double matrix1[3][3] = {{ matrix[1][1], matrix[1][2], matrix[1][3] },
        //                  		{ matrix[2][1], matrix[2][2], matrix[2][3] },
        //                  		{ matrix[3][1], matrix[3][2], matrix[3][3]}};
        // double matrix2[3][3] = {{ matrix[0][1], matrix[0][2], matrix[0][3] },
        //                  		{ matrix[2][1], matrix[2][2], matrix[2][3] },
        //                  		{ matrix[3][1], matrix[3][2], matrix[3][3]}};
        // double matrix3[3][3] = {{ matrix[0][1], matrix[0][2], matrix[0][3] },
		// 						{ matrix[1][1], matrix[1][2], matrix[1][3] },
        //                  		{ matrix[3][1], matrix[3][2], matrix[3][3]}};
        // double matrix4[3][3] = {{ matrix[0][1], matrix[0][2], matrix[0][3] },
		// 						{ matrix[1][1], matrix[1][2], matrix[1][3] },
		// 						{ matrix[2][1], matrix[2][2], matrix[2][3] }};
        return 	  matrix[0][0] * laplace(matrix1, 3) 
				- matrix[0][1] * laplace(matrix2, 3) 
				+ matrix[0][2] * laplace(matrix3, 3) 
				- matrix[0][3] * laplace(matrix4, 3);
    }
	else {
		puts("Invalid dimensions provided, exiting");
		exit(0);
		return 0;
	}
}

int main() {

	unsigned dim = menu();

	// dynamic allocation as a coherent block
	double** matrix = construct_matrix(dim, dim);

    //input
    for(size_t i = 0; i < dim; ++i) {
		for(size_t j = 0; j < dim; ++j) {
			clear_screen();
        	puts("Provide matrix cell values, left to right, from up to down");
        	printf("Provide matrix cell value no. %lld\n", i*dim+j+1);
			display(matrix, dim);
			matrix[i][j] = get_double_from_stdin();
		}  
    }
    clear_screen();
	puts("Your matrix:");
	display(matrix, dim);
	printf("Determinant equals %.2f\n", laplace(matrix, dim));
	cleanup(matrix);
	return 0;
}

