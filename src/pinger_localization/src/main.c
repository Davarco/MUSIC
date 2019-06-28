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
#include "music.h"
#include "config.h"
#include "matrix.h"


int main()
{
	// while (true) 
	{
		double ps[N_PHN];
		dft(ps);
		printf("Phase Shifts (radians): %f %f %f %f\n", ps[0], ps[1], ps[2], ps[3]);
		printf("Phase Shifts (degrees): %f %f %f %f\n", 
				ps[0]*180./M_PI, ps[1]*180./M_PI, ps[2]*180./M_PI, ps[3]*180./M_PI);

		double ps1[M] = { ps[0], ps[1] };
		double tdoa1[M];
		tdoa(ps1, tdoa1);
		prt(tdoa1, 1, M, "\nTDOA for NE/NW");

		music(tdoa1);
	}

	return 0;
}
