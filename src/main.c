/*
 * This code is meant to all fit into one file and run on the FPGA. The actual
 * code will require optimizations and direct reading of the registers to ensure
 * the sampling speed in high enough.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


const double C = 1480.;
const double N = 2048.;
const double FS = 100000.;
const double F0 = 25000.;
const double SPACING = 0.0127;

int main()
{
	FILE *in = fopen("datapipe", "r");
	FILE *out = fopen("data.txt", "w");

	// while (true) 
	{
		double dftReal[4], dftImag[4], phaseShifts[4], tdoa[4];
		for (int i = 0; i < 4; i++)
		{
			dftReal[i] = 0.0;
			dftImag[i] = 0.0;
			phaseShifts[i] = 0.0;
			tdoa[i] = 0.0;
		}
		for (int n = 0; n < N; n++)
		{
			double time;
			double phones[4];
			fscanf(in, "%lf %lf %lf %lf %lf", &time, &phones[0], &phones[1], &phones[2], &phones[3]);
			fprintf(out, "%f,%f,%f,%f,%f\n", time, phones[0], phones[1], phones[2], phones[3]);
			if (n == 0) printf("\nTime: %f\n", time);
			if (time > 2.5) return 0;

			double angle = 2*M_PI*n*F0/FS;
			for (int h = 0; h < 4; h++)
			{
				dftReal[h] += cos(angle)*phones[h];
				dftImag[h] -= sin(angle)*phones[h];
			}
		}

		for (int h = 0; h < 4; h++)
		{
			phaseShifts[h] = atan(dftImag[h]/dftReal[h]);
			phaseShifts[h] = (dftReal[h] > 0) ? phaseShifts[h]+M_PI/2. : phaseShifts[h]+3.*M_PI/2.;
			tdoa[h] = phaseShifts[h]/2./M_PI/F0;
			printf("Component %i: real=%0.06f imag=%0.06f\n", h+1, dftReal[h], dftImag[h]);
		}
		printf("Phase Shifts (radians): %f %f %f %f\n", 
				phaseShifts[0], phaseShifts[1], phaseShifts[2], phaseShifts[3]);
		printf("Phase Shifts (degrees): %f %f %f %f\n", 
				phaseShifts[0]*180./M_PI, phaseShifts[1]*180./M_PI, 
				phaseShifts[2]*180./M_PI, phaseShifts[3]*180./M_PI);
		printf("Phase Shifts (seconds): %f %f %f %f\n", tdoa[0], tdoa[1], tdoa[2], tdoa[3]);
	}

	return 0;
}
