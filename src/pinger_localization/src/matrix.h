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

void prt(double *A, int m, int n, char *msg);
void prt_complex(double *Ar, double *Ai, int m, int n, char *msg);
void mul(double *A, double *B, int m, int p, int n, double *C);
void mul_complex(double *Ar, double *Ai, double *Br, double *Bi,
		int m, int p, int n, double *Cr, double *Ci);
void add(double *A, double *B, int m, int n, double *C);
void sub(double *A, double *B, int m, int n, double *C);
void trp(double *A, int m, int n, double *C);
void trp_complex(double *Ar, double *Ai, int m, int n, double *Cr, double *Ci);
void scl(double *A, int m, int n, double k);

#endif
