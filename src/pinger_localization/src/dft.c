#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "config.h"


void dft(double *ps, double **x)
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
		fscanf(in, "%lf %lf %lf %lf %lf", &t, &x[0][n], &x[1][n], &x[2][n], &x[3][n]);
		fprintf(out, "%f,%f,%f,%f,%f\n", t, x[0][n], x[1][n], x[2][n], x[3][n]);
		if (n == 0) printf("\ntime: %f\n", t);

		double angle = 2*M_PI*n*F0/FS;
		for (int h = 0; h < N_PHN; h++)
		{
			real[h] += cos(angle)*x[h][n];
			imag[h] -= sin(angle)*x[h][n];
		}
	}

	for (int h = 0; h < N_PHN; h++)
	{
		ps[h] = atan(imag[h]/real[h]);
		ps[h] = (real[h] > 0) ? ps[h]+M_PI/2. : ps[h]+3.*M_PI/2.;
		tdoa[h] = ps[h]/2./M_PI/F0;
		// printf("Component %i: real=%0.06f imag=%0.06f\n", h+1, real[h], imag[h]);
	}
	printf("Phase Shifts (radians): %f %f %f %f\n", 
			ps[0], ps[1], ps[2], ps[3]);
	printf("Phase Shifts (degrees): %f %f %f %f\n", 
			ps[0]*180./M_PI, ps[1]*180./M_PI, 
			ps[2]*180./M_PI, ps[3]*180./M_PI);
	printf("Phase Shifts (seconds): %0.12f %0.12f %0.12f %0.12f\n", 
			tdoa[0], tdoa[1], tdoa[2], tdoa[3]);

	fclose(in);
	fclose(out);
}
