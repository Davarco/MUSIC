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
void identity(double *A, int n);
void copy(double *A, int m, int n, double *B);
void product(double *A, double *B, int m, int p, int n, double *C);
void product_complex(double *Ar, double *Ai, double *Br, double *Bi,
		int m, int p, int n, double *Cr, double *Ci);
void add(double *A, double *B, int m, int n, double *C);
void subtract(double *A, double *B, int m, int n, double *C);
void transpose(double *A, int m, int n, double *B);
void transpose_complex(double *Ar, double *Ai, int m, int n, 
		double *Br, double *Bi);
void scale(double *A, int m, int n, double k);
void slice(double *A, int n, int m1, int m2, int n1, int n2, double *B);
void inverse(double *A, int n, double *B);
void eigen(double *A, int n, double *val, double *vec);
void eigen_complex(double *Ar, double *Ai, int n, double *val, 
		double *vecr, double *veci);

#endif
