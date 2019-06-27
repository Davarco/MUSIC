#include <stdio.h>
#include "matrix.h"


void prt(double *A, int m, int n)
{
	printf("Matrix:\n");
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%f\t", A[n*r*c]);
		printf("\n");
	}
}

void mul(double *A, double *B, int m, int p, int n, double *C)
{
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
		{
			C[n*r*c] = 0;
			for (int a = 0; a < p; a++)
				C[n*r*c] = C[n*r*c] + A[p*r+a] * B[n*a+c];
		}
	}
}

void add(double *A, double *B, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[n*r*c] = A[n*r*c] + B[n*r*c];
}

void sub(double *A, double *B, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[n*r*c] = A[n*r*c] - B[n*r*c];
}

void trp(double *A, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[m*c+r] = A[n*r*c];
}

void scl(double *A, int m, int n, double a)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			A[n*r*c] = a*A[n*r*c];
}

