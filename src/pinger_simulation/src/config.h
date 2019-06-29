#ifndef CONFIG_HPP 
#define CONFIG_HPP 

#include <math.h>

/*
 * Speed of sound in water (m/s).
 */
#define C 1480.

/*
 * Simulate phone offsets. Pretend that (0, 0) is the center of the phone box.
 * The phones are placed as a square around the center, equally spaced.
 *
 * *******
 * * 2 1 *
 * * 4 3 *
 * ******* 
 */
#define NUM_PHONES 4
#define SPACING 0.0127

/*
 * Pinger settings. North-East coordinate plane.
 */
#define PINGER_X_LOC 5.2
#define PINGER_Y_LOC 5.2
#define F0 25000.
#define T0 1./F0
#define NOISE 0.003
#define TIME_BETWEEN_PINGS 0.5
#define PING_DURATION 0.005

/*
 * Sampling settings.
 */
#define FS 100000.
#define TS 1./FS

#endif 

