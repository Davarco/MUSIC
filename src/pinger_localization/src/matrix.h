#ifndef MATRIX_H
#define MATRIX_H

void prt(double *A, int m, int n);
void mul(double *A, double *B, int m, int p, int n, double *C);
void add(double *A, double *B, int m, int n, double *C);
void sub(double *A, double *B, int m, int n, double *C);
void trp(double *A, int m, int n, double *C);
void scl(double *A, int m, int n, double k);

#endif
