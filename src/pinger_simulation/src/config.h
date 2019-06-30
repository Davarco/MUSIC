/**	@file config.h
 *	@brief Constants to simulate a pinger, its environment, and sampling.
 *
 *	@author David Zhang (Davarco)
 *	@bugs No known bugs.
 */
#ifndef CONFIG_HPP 
#define CONFIG_HPP 

#include <math.h>

/*
 * This part is specific to the AVBotz AUV team. Our hydrophones are set up so 
 * that they are in a perfect square, as shown below.
 *
 * *******
 * * 2 1 *
 * * 4 3 *
 * ******* 
 *
 * NUM_PHONES = no explanation needed.
 * SPACING = the distance between two hydrophones (e.g 2 and 1) (meters).
 */
#define NUM_PHONES 4
#define SPACING 0.0127

/*
 * Environemnt settings.
 *
 * C = wave speed, set to speed of sound in water (m/s).
 */
#define C 1480.

/*
 * Pinger settings (North-East coordinate plane).
 *
 * PINGER_X_LOC = units north, or forward (meters).
 * PINGER_Y_LOC = units east, or right (meters).
 * F0 = pinger frequency (Hz).
 * T0 = pinger period (seconds).
 * NOISE = noise, expressed as a fraction of the signal (0.1 = 10%).
 * TIME_BETWEEN_PINGS = amount of time pinger is silent per burst (seconds).
 * PING_DURATION = length of ping burst (seconds).
 */
#define PINGER_X_LOC 16.
#define PINGER_Y_LOC 4.
#define F0 25000.
#define T0 1./F0
#define NOISE 0.0
#define TIME_BETWEEN_PINGS 0.5
#define PING_DURATION 0.005

/*
 * Sampling settings.
 *
 * FS = sampling rate (Hz).
 * TS = sampling period (seconds).
 */
#define FS 100000.
#define TS 1./FS

#endif 
