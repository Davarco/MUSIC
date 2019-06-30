/** @file config.h
 *  @brief Contains constants needed to calculate DOA (direction-of-arrival).
 *
 *  These values should match the simulated settings in pinger_simulation, or
 *  represent real world settings.
 *
 *  @author David Zhang (Davarco)
 */
#ifndef CONFIG_H
#define CONFIG_H

/*
 * Wave speed (m/s).
 */
const double C = 1480.;

/*
 * Sampling speed (Hz).
 */
const double FS = 100000.;

/*
 * Pinger frequency (Hz).
 */
const double F0 = 25000.;

/*
 * Signal receiver spacing (meters).
 */
const double SPACING = 0.0127;

/*
 * DOA precision (degrees).
 */
const double SEARCH_INTERVAL = 0.1;

/*
 * Total number of signal receivers.
 */
const int N_PHN = 4;

/*
 * Number of points in DFT.
 */
const int N_DFT = 2048;

/*
 * Number of points to simulate for signal.
 */
const int N = 16;

/*
 * Number of signal receivers per MUSIC calculation.
 */
const int M = 2;

/*
 * Log option.
 */
const int DEBUG = 1;

#endif 
