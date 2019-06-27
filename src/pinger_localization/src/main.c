/*
 * Acoustic-MUSIC: Underwater pinger localization using Multiple Signal
 * Classification.
 *
 * Developed for the AVBotz AUV team. (www.avbotz.com)
 *
 * @author David Zhang
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "config.h"


int main()
{
	// while (true) 
	{
		double *ps = (double*) malloc(N_PHN*sizeof(double));
		double **x = (double**) malloc(N_PHN*N_DFT*sizeof(double));
		dft(ps, x);

		free(ps);
		free(x);
	}

	return 0;
}
