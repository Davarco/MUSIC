/**	@file matrix.c
 * 	@brief Functions used for real and complex matrix operations.
 *
 *	@author David Zhang (Davarco)
 *	@bugs No known bugs.
 */
#include <stdio.h>
#include "matrix.h"


void prt(double *A, int m, int n, char *msg)
{
	printf("%s\n", msg);
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%0.15f  ", A[n*r+c]);
		printf("\n");
	}
}

void prt_complex(double *Ar, double *Ai, int m, int n, char *msg)
{
	printf("%s\n", msg);
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%0.15f + %0.15fi  ", Ar[n*r+c], Ai[n*r+c]);
		printf("\n");
	}
}

void mul(double *A, double *B, int m, int p, int n, double *C)
{
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
		{
			C[n*r+c] = 0.;
			for (int k = 0; k < p; k++)
				C[n*r+c] += A[p*r+k] * B[n*k+c];
		}
	}
}

void mul_complex(double *Ar, double *Ai, double *Br, double *Bi,
		int m, int p, int n, double *Cr, double *Ci)
{
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
		{
			Cr[n*r+c] = 0.;
			Ci[n*r+c] = 0.;
			for (int k = 0; k < p; k++)
			{
				// FOIL: (a+bi) * (c+di) = (a*c)-(b*d) + (a*d)+(b*c)i
				double r1 = Ar[p*r+k];
				double i1 = Ai[p*r+k];
				double r2 = Br[n*k+c];
				double i2 = Bi[n*k+c];
				Cr[n*r+c] += r1*r2;
				Cr[n*r+c] -= i1*i2;
				Ci[n*r+c] += r1*i2;
				Ci[n*r+c] += r2*i1;
			}
		}
	}
}

void add(double *A, double *B, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[n*r+c] = A[n*r+c] + B[n*r+c];
}

void sub(double *A, double *B, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[n*r+c] = A[n*r+c] - B[n*r+c];
}

void trp(double *A, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[m*c+r] = A[n*r+c];
}

void trp_complex(double *Ar, double *Ai, int m, int n, double *Cr, double *Ci)
{
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++) 
		{
			// When transposing a complex matrix, the imaginary component is
			// multiplied by -1.
			Cr[m*c+r] = Ar[n*r+c];
			Ci[m*c+r] = -Ai[n*r+c];
		}
	}
}

void scl(double *A, int m, int n, double a)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			A[n*r+c] = a*A[n*r+c];
}

