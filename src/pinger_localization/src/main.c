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
		/*
		 * 2 1
		 * 4 3
		 */
		printf("Calculating DOA (direction-of-arrival) using MUSIC.\n");
		double ps[N_PHN];
		dft(ps);
		printf("\nPhase Shifts (degrees):\n%f %f %f %f\n", 
				ps[0]*180./M_PI, ps[1]*180./M_PI, 
				ps[2]*180./M_PI, ps[3]*180./M_PI);

		double ps1[M] = { ps[0], ps[1] };
		double tdoa1[M];
		tdoa(ps1, tdoa1);
		print(tdoa1, 1, M, "\nTDOA for NE/NW: ");

		double doa1;
		music(tdoa1, &doa1);
		printf("\nDOA for NE/NW: %f\n", doa1);
		
		double ps2[M] = { ps[2], ps[3] };
		double tdoa2[M];
		tdoa(ps2, tdoa2);
		print(tdoa2, 1, M, "\nTDOA for SE/SW: ");

		double doa2;
		music(tdoa2, &doa2);
		printf("\nDOA for SE/SW: %f\n", doa2);
	}

	return 0;
}
