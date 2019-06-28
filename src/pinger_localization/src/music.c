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
		fscanf(in, "%lf %lf %lf %lf %lf", &t, &phones[0], &phones[1], &phones[2], &phones[3]);
		fprintf(out, "%f,%f,%f,%f,%f\n", t, phones[0], phones[1], phones[2], phones[3]);
		if (n == 0) printf("\ntime: %f\n", t);

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
	for (int r = 0; r < M; r++)
	{
		double angle = 2.*M_PI*tdoa[r];
		Ar[r] = cos(angle);
		Ai[r] = sin(angle);
	}
	// prt_complex(Ar, Ai, M, 1, "\nA: ");
	for (int r = 1; r <= N; r++)
	{	
		double angle = 2.*M_PI*F0*r;
		Sr[r-1] = cos(angle);
		Si[r-1] = sin(angle);
	}
	// prt_complex(Sr, Si, 1, N, "\nS: ");
	mul_complex(Ar, Ai, Sr, Si, M, 1, N, Xr, Xi);	
	// prt_complex(Xr, Xi, M, N, "\nX: ");	
	free(Ar); 
	free(Ai);
	free(Sr); 
	free(Si);

	double *XTr = (double*) malloc(N*M*sizeof(double));
	double *XTi = (double*) malloc(N*M*sizeof(double));
	double *Rr = (double*) malloc(M*M*sizeof(double));
	double *Ri = (double*) malloc(M*M*sizeof(double));
	trp_complex(Xr, Xi, M, N, XTr, XTi);
	prt_complex(XTr, XTi, N, M, "\nX (Transpose): ");
	mul_complex(Xr, Xi, XTr, XTi, M, N, M, Rr, Ri);
	free(XTr);
	free(XTi);
	free(Xr);
	free(Xi); 
	prt_complex(Rr, Ri, M, M, "\nCovariance Matrix: ");


}


