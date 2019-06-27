#ifndef CONFIG_H
#define CONFIG_H

/*
 * These constants should either match the ones in sub_simulation or the
 * specifications of a real localization system. Note how the localization code
 * does NOT have access to the pinger location.
 */
const double C = 1480.;
const double FS = 100000.;
const double F0 = 25000.;
const double SPACING = 0.0127;
const int N = 2048;
const int N_PHN = 4;
const int M = 2;

#endif 
