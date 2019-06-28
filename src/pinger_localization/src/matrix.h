/**
 * @file matrix.h
 * @brief Function declarations for real and complex matrix operations.
 * 
 * @author David Zhang (Davarco)
 * @bug No known bugs.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <string>

void print(double *A, int m, int n, char *msg);
void print_complex(double *Ar, double *Ai, int m, int n, char *msg);
void product(double *A, double *B, int m, int p, int n, double *C);
void product_complex(double *Ar, double *Ai, double *Br, double *Bi,
		int m, int p, int n, double *Cr, double *Ci);
void add(double *A, double *B, int m, int n, double *C);
void subtract(double *A, double *B, int m, int n, double *C);
void transpose(double *A, int m, int n, double *C);
void transpose_complex(double *Ar, double *Ai, int m, int n, 
		double *Cr, double *Ci);
void scale(double *A, int m, int n, double k);
void eigen(double *A, int n, double *val, double *vec);
void eigenvalues(double *A, int n, double *val);

#endif
