/*
 * @file music.c
 * @brief Functions used to compute DOA (direction-of-arrival) using MUSIC.
 *
 * @author David Zhang (Davarco)
 * @bug No known bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "music.h"
#include "matrix.h"
#include "config.h"


void dft(double *ps)
{
	FILE *in = fopen("datapipe", "r");
	FILE *out = fopen("data.txt", "w");

	double real[N_PHN], imag[N_PHN], tdoa[N_PHN];
	for (int i = 0; i < N_PHN; i++)
	{
		real[i] = 0.0;
		imag[i] = 0.0;
		ps[i] = 0.0;
		tdoa[i] = 0.0;
	}
	for (int n = 0; n < N_DFT; n++)
	{
		double t;
		double phones[4];
		fscanf(in, "%lf %lf %lf %lf %lf", &t, 
				&phones[0], &phones[1], &phones[2], &phones[3]);
		fprintf(out, "%f,%f,%f,%f,%f\n", t, 
				phones[0], phones[1], phones[2], phones[3]);
		// if (n == 0) printf("\ntime: %f\n", t);

		double angle = 2*M_PI*n*F0/FS;
		for (int h = 0; h < N_PHN; h++)
		{
			real[h] += cos(angle)*phones[h];
			imag[h] -= sin(angle)*phones[h];
		}
	}

	for (int h = 0; h < N_PHN; h++)
	{
		ps[h] = atan(imag[h]/real[h]);
		ps[h] = (real[h] > 0) ? ps[h]+M_PI/2. : ps[h]+3.*M_PI/2.;
		tdoa[h] = ps[h]/2./M_PI/F0;
		// printf("Component %i: real=%0.06f imag=%0.06f\n", h+1, real[h], imag[h]);
	}

	fclose(in);
	fclose(out);
}

void tdoa(double *ps, double *tdoa)
{
	for (int i = 0; i < M; i++) 
		tdoa[i] = (ps[i]-ps[0])/2./M_PI;
}

void music(double *tdoa)
{
	double *Xr = (double*) malloc(M*N*sizeof(double));
	double *Xi = (double*) malloc(M*N*sizeof(double));
	double *Ar = (double*) malloc(M*sizeof(double));
	double *Ai = (double*) malloc(M*sizeof(double));
	double *Sr = (double*) malloc(N*sizeof(double));
	double *Si = (double*) malloc(N*sizeof(double));
	for (int i = 0; i < M; i++)
	{
		double angle = 2.*M_PI*tdoa[i];
		Ar[i] = cos(angle);
		Ai[i] = sin(angle);
	}
	// print_complex(Ar, Ai, M, 1, "\nA: ");
	for (int i = 0; i < N; i++)
	{	
		double angle = 2.*M_PI*F0*i;
		Sr[i] = cos(angle);
		Si[i] = sin(angle);
	}
	// print_complex(Sr, Si, 1, N, "\nS: ");
	product_complex(Ar, Ai, Sr, Si, M, 1, N, Xr, Xi);	
	// print_complex(Xr, Xi, M, N, "\nX: ");	
	free(Ar); 
	free(Ai);
	free(Sr); 
	free(Si);

	double *XTr = (double*) malloc(N*M*sizeof(double));
	double *XTi = (double*) malloc(N*M*sizeof(double));
	double *Rr = (double*) malloc(M*M*sizeof(double));
	double *Ri = (double*) malloc(M*M*sizeof(double));
	transpose_complex(Xr, Xi, M, N, XTr, XTi);
	// print_complex(XTr, XTi, N, M, "\nX (Transpose): ");
	product_complex(Xr, Xi, XTr, XTi, M, N, M, Rr, Ri);
	free(XTr);
	free(XTi);
	free(Xr);
	free(Xi); 
	print_complex(Rr, Ri, M, M, "\nCovariance Matrix: ");

	double *Eval = (double*) malloc(M*sizeof(double));
	double *Evecr = (double*) malloc(M*M*sizeof(double));
	double *Eveci = (double*) malloc(M*M*sizeof(double));
	eigen_complex(Rr, Ri, M, Eval, Evecr, Eveci);
	print(Eval, M, 1, "\nEigenvalues: ");
	print_complex(Evecr, Eveci, M, M, "\nEigenvectors: ");
	free(Rr);
	free(Ri);
	free(Eval);

	double *NSr = (double*) malloc(M*(M-1)*sizeof(double));
	double *NSi = (double*) malloc(M*(M-1)*sizeof(double));
	double *NSTr = (double*) malloc((M-1)*M*sizeof(double));
	double *NSTi = (double*) malloc((M-1)*M*sizeof(double));
	slice(Evecr, M, 0, M, 0, M-1, NSr);
	slice(Eveci, M, 0, M, 0, M-1, NSi);
	transpose_complex(NSr, NSi, M, M-1, NSTr, NSTi);
	free(Evecr);
	free(Eveci);
	print_complex(NSr, NSi, M, M-1, "\nNoise Subspace: ");

	int n = 180./SEARCH_INTERVAL+1;
	double theta = -90.;
	double *Y = (double*) malloc(n*sizeof(double));
	for (int i = 0; i < n; i++)
	{
		double *SSr = (double*) malloc(M*sizeof(double));
		double *SSi = (double*) malloc(M*sizeof(double));
		for (int j = 0; j < M; j++)
		{
			SSr[j] = cos(2.*M_PI*SPACING*sin(theta*M_PI/180.)*F0/C*j);
			SSi[j] = sin(2.*M_PI*SPACING*sin(theta*M_PI/180.)*F0/C*j);
		}
		double *SSTr = (double*) malloc(M*sizeof(double));
		double *SSTi = (double*) malloc(M*sizeof(double));
		transpose_complex(SSr, SSi, 1, M, SSTr, SSTi);
		
		double *temp1r = (double*) malloc((M-1)*sizeof(double));
		double *temp1i = (double*) malloc((M-1)*sizeof(double));
		product_complex(SSr, SSi, NSr, NSi, 1, M, M-1, temp1r, temp1i);
		double *temp2r = (double*) malloc(M*sizeof(double));
		double *temp2i = (double*) malloc(M*sizeof(double));
		product_complex(temp1r, temp1i, NSTr, NSTi, 1, M-1, M, temp2r, temp2i);
		double *temp3r = (double*) malloc(1*sizeof(double));
		double *temp3i = (double*) malloc(1*sizeof(double));
		product_complex(temp2r, temp2i, SSTr, SSTi, 1, M, 1, temp3r, temp3i);
		Y[i] = fabs(1./temp3r[0]);
		free(SSr);
		free(SSi);
		free(SSTr);
		free(SSTi);
		free(temp1r);
		free(temp1i);
		free(temp2r);
		free(temp2i);
		free(temp3r);
		free(temp3i);
		
		theta += SEARCH_INTERVAL;
	}
	free(NSr);
	free(NSi);
	free(NSTr);
	free(NSTi);

	double max = 0.;
	for (int i = 0; i < n; i++)
		max = (Y[i] > max) ? Y[i] : max;
	for (int i = 0; i < n; i++)
		Y[i] = 10.*log10(Y[i]/max);

	max = -DBL_MAX;
	int max_idx = 0;
	for (int i = 0; i < n; i++)
	{
		if (Y[i] > max)
		{
			max = Y[i];
			max_idx = i;
		}
	}
	double angle = -90.+max_idx*SEARCH_INTERVAL;
	printf("\nDOA: %f\n", angle);
}


