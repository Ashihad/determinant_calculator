#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "stdin_helpers.h"
#include "matrix.h"

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

#define MAX_BUFFER_LENGTH 80

#define MIN_FRACTAL_LENGTH 2
#define MAX_FRACTAL_LENGTH 8

void stringify(char* buffer, double number) {
	memset(buffer, 0, MAX_BUFFER_LENGTH);
	sprintf(buffer, "%.8f", number);
}

size_t fractional_part_length(char* buffer) {
	// printf("In %s\n", __func__);
	// printf("\tbuffer: ");
	// for (size_t i = 0; buffer[i] != '\0'; ++i) {
	// 	printf("%c", buffer[i]);
	// }
	// printf("\n");
	char* dot = strchr(buffer, '.');
	char* end = strchr(buffer, '\0');
	size_t len = end-dot;
	// printf("\titer_len %zu\n", (end-1) - (dot+MIN_FRACTAL_LENGTH-1));
	if ((end-1) - (dot+MIN_FRACTAL_LENGTH) <= MIN_FRACTAL_LENGTH) {
		return MIN_FRACTAL_LENGTH;
	}
	else {
		for (char* ptr = end-1; ptr > dot+MIN_FRACTAL_LENGTH-1; --ptr) {
			// printf("\tin loop, (*ptr) == %c\n", *ptr);
			if ((*ptr) == '0') --len;
			else break;
		}
		len--;
		// printf("\tending loop, len %zu\n", len);
		// above MAX_FRACTAL_LENGTH digits after dot assume periodic fraction in base 2 -> limit to MAX_FRACTAL_LENGTH digits
		return len < MAX_FRACTAL_LENGTH ? len : MAX_FRACTAL_LENGTH;
	}
	// printf("initial %p\n", end-1);
	// printf("ending %p\n", dot+MIN_FRACTAL_LENGTH);
	
}

size_t integer_part_length(char* buffer) {
	// printf("In %s\n", __func__);
	// printf("\tbuffer: ");
	// for (size_t i = 0; buffer[i] != '\0'; ++i) {
	// 	printf("%c", buffer[i]);
	// }
	// printf("\n");
	char* dot = strchr(buffer, '.');
	return dot-buffer;
}

// void display(double** table, size_t size)
// {
// 	// determine max string length of a double inside each matrix column
// 	char* buffer = malloc(MAX_BUFFER_LENGTH);

// 	size_t* max_lens = malloc(size*sizeof(size_t));
// 	memset(max_lens, 0, size*sizeof(size_t));
// 	size_t* max_fractional_lens = malloc(size*sizeof(size_t));
// 	memset(max_fractional_lens, 0, size*sizeof(size_t));

// 	for (size_t j = 0; j < size; ++j) {
// 		for (size_t i = 0; i < size; ++i) {
// 			stringify(buffer, table[i][j]);
// 			// find longest stringified number
// 			if (strlen(buffer) > max_lens[j]) {
// 				max_lens[j] = strlen(buffer);
// 			}
// 			// find longest fractional part
// 			if (fractional_part_length(buffer) > max_fractional_lens[j]) {
// 				max_fractional_lens[j] = fractional_part_length(buffer);
// 			}
// 		}
// 	}
// 	for (size_t j = 0; j < size; ++j) {
// 		printf("max_fractional_lens[%zu] %zu\n", j, max_fractional_lens[j]);
// 	}
// 	// print upper line
// 	for (size_t j = 0; j < size; ++j) {
// 		for (size_t c = 0; c < max_lens[j]+2; ++c) {
// 			printf("=");
// 		}
// 	}
// 	printf("\n");
	
// 	// print table elements
// 	for (size_t i = 0; i < size; ++i) {
//         for(size_t j = 0; j < size; ++j) {
//             printf("%*.*f", (int) max_lens[j]+2, (int) max_fractional_lens[j], table[i][j]);
//         }
//         printf("\n");
//     }

//     // print lower line
// 	for (size_t j = 0; j < size; ++j) {
// 		for (size_t c = 0; c < max_lens[j]+2; ++c) {
// 			printf("=");
// 		}
// 	}
// 	printf("\n");

// 	free(max_lens);
// 	free(max_fractional_lens);
// }

void display(double** table, size_t size)
{
	// determine max string length of a double inside each matrix column
	char* buffer = malloc(MAX_BUFFER_LENGTH);

	size_t* max_integer_lens = malloc(size*sizeof(size_t));
	memset(max_integer_lens, 0, size*sizeof(size_t));
	size_t* max_fractional_lens = malloc(size*sizeof(size_t));
	memset(max_fractional_lens, 0, size*sizeof(size_t));
	size_t* negative = malloc(size*sizeof(bool));
	memset(negative, 0, size*sizeof(size_t));

	for (size_t j = 0; j < size; ++j) {
		for (size_t i = 0; i < size; ++i) {
			if (table[i][j] < 0) negative[j] = 1;
			stringify(buffer, table[i][j]);
			// find longest integer part
			if (integer_part_length(buffer) > max_integer_lens[j]) {
				max_integer_lens[j] = integer_part_length(buffer);
			}
			// find longest fractional part
			if (fractional_part_length(buffer) > max_fractional_lens[j]) {
				max_fractional_lens[j] = fractional_part_length(buffer);
			}
		}
	}
	// for (size_t j = 0; j < size; ++j) {
	// 	printf("max_fractional_lens[%zu] %zu\n", j, max_fractional_lens[j]);
	// }

	// print upper line
	// printf("line printing\n");

	for (size_t j = 0; j < size; ++j) {
		// printf("\tmax_integer_lens[%zu] %zu\n", j, max_integer_lens[j]);
		// printf("\tmax_fractional_lens[%zu] %zu\n", j, max_fractional_lens[j]);
		// printf("\tadditional space %d\n", 3);
		// printf("\tsum %zu\n", max_integer_lens[j]+max_fractional_lens[j]+3);
		for (size_t c = 0; c < max_integer_lens[j]; ++c) {
			printf("=");
		}
		for (size_t c = 0; c < max_fractional_lens[j]; ++c) {
			printf("=");
		}
		// for dot and two spaces at the beginning and end of every number in table
		for (size_t c = 0; c < negative[j]+3; ++c) {
			printf("=");
		}
	}
	printf("\n"); 
	
	// print table elements
	for (size_t i = 0; i < size; ++i) {
        for(size_t j = 0; j < size; ++j) {
            printf("%*.*f", (int) max_integer_lens[j] + (int) max_fractional_lens[j] + 3, (int) max_fractional_lens[j], table[i][j]);
        }
        printf("\n");
    }

    // print lower line
	// printf("line printing\n");

	for (size_t j = 0; j < size; ++j) {
		// printf("\tmax_integer_lens[%zu] %zu\n", j, max_integer_lens[j]);
		// printf("\tmax_fractional_lens[%zu] %zu\n", j, max_fractional_lens[j]);
		// printf("\tadditional space %d\n", 3);
		// printf("\tsum %zu\n", max_integer_lens[j]+max_fractional_lens[j]+3);
		for (size_t c = 0; c < max_integer_lens[j]; ++c) {
			printf("=");
		}
		for (size_t c = 0; c < max_fractional_lens[j]; ++c) {
			printf("=");
		}
		// for dot and two spaces at the beginning and end of every number in table
		for (size_t c = 0; c < negative[j]+3; ++c) {
			printf("=");
		}
	}
	printf("\n"); 

	free(max_integer_lens);
	free(max_fractional_lens);
	free(negative);
}

double laplace2(double** matrix, size_t dim) {
	if (dim == 1) return matrix[0][0];

	// Laplace expansion column, algorithm always expands over k=0
	size_t laplace_k = 0;

	// create array of matrices[dim-1][dim-1]
	double*** matrices = malloc(dim*sizeof(double***));

	// loop over laplace submatrices
	for (size_t i = 0; i < dim; ++i) {
		matrices[i] = construct_matrix_d(dim-1, dim-1);
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
		destroy_matrix_d(matrices[i]);
	}
	free(matrices);

	return result;
}

int main() {

	size_t dim = menu();

	// dynamic allocation as a coherent block
	double** matrix = construct_matrix_d(dim, dim);

    //input
    for(size_t i = 0; i < dim; ++i) {
		for(size_t j = 0; j < dim; ++j) {
			clear_screen();
        	printf("Provide matrix cell values, left to right, from up to down\n");
        	printf("Provide matrix cell value no. %zu\n", i*dim + j+1);
			display(matrix, dim);
			matrix[i][j] = get_double_from_stdin();
		}  
    }
    clear_screen();
	printf("Your matrix: \n");
	display(matrix, dim);
	printf("Determinant equals %.2f\n", laplace2(matrix, dim));
	destroy_matrix_d(matrix);
	return 0;
}

