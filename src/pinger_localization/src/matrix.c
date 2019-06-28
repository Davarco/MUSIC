/**	@file matrix.c
 * 	@brief Functions used for real and complex matrix operations.
 *
 *	@author David Zhang (Davarco)
 *	@bugs Eigen method doesn't produce correct result. Using just eigenvalues
 *	for now, since eigenvectors aren't needed, but a fix would be nice. Also,
 *	the eigen method uses Jacobi transformations which isn't the most efficient
 *	for large matrices.
 */
#include <stdio.h>
#include <math.h>
#include "matrix.h"


void print(double *A, int m, int n, char *msg)
{
	printf("%s\n", msg);
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%0.15f  ", A[n*r+c]);
		printf("\n");
	}
}

void print_complex(double *Ar, double *Ai, int m, int n, char *msg)
{
	printf("%s\n", msg);
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
			printf("%0.15f + %0.15fi  ", Ar[n*r+c], Ai[n*r+c]);
		printf("\n");
	}
}

void product(double *A, double *B, int m, int p, int n, double *C)
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

void product_complex(double *Ar, double *Ai, double *Br, double *Bi,
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

void subtract(double *A, double *B, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[n*r+c] = A[n*r+c] - B[n*r+c];
}

void transpose(double *A, int m, int n, double *C)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			C[m*c+r] = A[n*r+c];
}

void transpose_complex(double *Ar, double *Ai, int m, int n, 
		double *Cr, double *Ci)
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

void scale(double *A, int m, int n, double a)
{
	for (int r = 0; r < m; r++)
		for (int c = 0; c < n; c++)
			A[n*r+c] = a*A[n*r+c];
}

void eigen(double *A, int n, double *val, double *vec)
{
	int CONVERGENCE_LIMIT = 50;

	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			vec[n*r+c] = (r == c) ? 1. : 0.;

	double *temp_val = (double*) malloc(n*sizeof(double));
	double *dval = (double*) malloc(n*sizeof(double));
	for (int i = 0; i < n; i++)
	{
		val[i] = A[i*n+i];
		temp_val[i] = A[i*n+i];
		dval[i] = 0.;
	}

	for (int i = 0; i < CONVERGENCE_LIMIT; i++)
	{
		double sum = 0.;
		for (int r = 0; r < n-1; r++)
			for (int c = r+1; c < n; c++)
				sum += fabs(A[r*n+c]);

		if (sum == 0.) 
		{
			free(temp_val);
			free(dval);
			return;
		}

		double threshold = (i < 3) ? 0.2*sum/(n*n) : 0.;

		for (int r = 0; r < n-1; r++)
		{
			for (int c = r+1; c < n; c++)
			{
				double g = 100.*fabs(A[r*n+c]);
				if (i > 3 && fabs(val[r])+g == fabs(val[r]) && 
						fabs(val[c])+g == fabs(val[c]))
					A[r*n+c] = 0.;
				else if (fabs(A[r*n+c]) > threshold)
				{
					double h = val[c]-val[r];
					double t = 0.;
					if (fabs(h)+g == fabs(h))
						t = A[r*n+c]/h;
					else 
					{
						double theta = h/(2.*A[r*n+c]);
						t = 1./(fabs(theta)+sqrt(1.+theta*theta));
						if (theta < 0.) t *= -1.;
					}
					double cosrot = 1./sqrt(1.+t*t);
					double sinrot = t*cosrot;
					double tau = sinrot/(1.+cosrot);

					dval[r] -= t*A[r*n+c];
					dval[c] += t*A[r*n+c];
					val[r] -= t*A[r*n+c];
					val[c] += t*A[r*n+c];

					A[r*n+c] = 0.;
					for (int j = 0; j < r-1; j++)
					{
						double temp1 = A[j*n+r];
						double temp2 = A[j*n+c];
						A[j*n+r] = temp1 - sinrot*(temp2+temp1*tau);
						A[j*n+c] = temp2 + sinrot*(temp1-temp2*tau);
					}
					for (int j = r+1; j < c-1; j++)
					{
						double temp1 = A[r*n+j];
						double temp2 = A[j*n+c];
						A[r*n+j] = temp1 - sinrot*(temp2+temp1*tau);
						A[j*n+c] = temp2 + sinrot*(temp1-temp2*tau);
					}
					for (int j = c+1; j < n; j++)
					{
						double temp1 = A[r*n+j];
						double temp2 = A[c*n+j];
						A[r*n+j] = temp1 - sinrot*(temp2+temp1*tau);
						A[c*n+j] = temp2 + sinrot*(temp1-temp2*tau);
					}
					for (int j = 0; j < n; j++)
					{
						double temp1 = vec[j*n+r];
						double temp2 = vec[j*n+c];
						vec[j*n+r] = temp1 - sinrot*(temp2+temp1*tau);
						vec[j*n+c] = temp2 + sinrot*(temp1-temp2*tau);
					}
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			temp_val[i] += dval[i];
			val[i] = temp_val[i];
			dval[i] = 0.;
		}
	}

	printf("Eigen calculations exceeded convergence limit.\n");
}

void eigenvalues(double *A, int n, double *val)
{

}
