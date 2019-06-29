/**	@file config.h
 *	@brief Contains constants needed to calculate DOA (direction-of-arrival).
 *
 *	These values should match the simulated settings in pinger_simulation, or
 *  represent real world settings.
 *
 *  @author David Zhang (Davarco)
 *  @bug No known bugs.
 */
#ifndef CONFIG_H
#define CONFIG_H

const double C = 1480.;
const double FS = 100000.;
const double F0 = 25000.;
const double SPACING = 0.0127;
const double SEARCH_INTERVAL = 0.1;
const int N_PHN = 4;
const int N_DFT = 2048;
const int N = 16;
const int M = 2;

#endif 
