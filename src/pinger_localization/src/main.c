/**	@file main.c
 * 	@brief Runs MUSIC for an acoustic localization system.
 * 	
 * 	@author David Zhang (Davarco)
 * 	@bugs No known bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "music.h"
#include "config.h"
#include "matrix.h"


/** @brief Localization start.
 * 
 * 	@return Should not return.
 */
int main()
{
	// while (true) 
	{
		printf("Calculating DOA (direction-of-arrival) using MUSIC.\n");
		double ps[N_PHN];
		dft(ps);
		printf("\nPhase Shifts (radians): %f %f %f %f\n", 
				ps[0], ps[1], ps[2], ps[3]);
		printf("\nPhase Shifts (degrees): %f %f %f %f\n", 
				ps[0]*180./M_PI, ps[1]*180./M_PI, 
				ps[2]*180./M_PI, ps[3]*180./M_PI);

		double ps1[M] = { ps[0], ps[1] };
		double tdoa1[M];
		tdoa(ps1, tdoa1);
		print(tdoa1, 1, M, "\nTDOA for NE/NW: ");

		double doa;
		music(tdoa1, &doa);
		printf("\nDOA for NE/NW: %f\n", doa);
	}

	return 0;
}
