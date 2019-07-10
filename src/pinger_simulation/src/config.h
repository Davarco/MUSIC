/** @file src/pinger_simulation/src/config.h
 *  @brief Constants to simulate a pinger, its environment, and sampling.
 *
 *  @author David Zhang (Davarco)
 *  @bugs No known bugs.
 */
#ifndef CONFIG_H 
#define CONFIG_H 

#include <math.h>

/*! \name Signal receiver configuration.
 */
///@{
/** Total number of signal receivers.
 */
#define NUM_PHONES 4

/** Spacing between two signal receivers.
 */
#define SPACING 0.0127
///@}

/*! \name Environment settings.
 */
///@{
/** Wave speed, set to speed of sound in water (m/s).
 */
#define C 1480.
///@}

/*! \name Environment settings.
 */
///@{
/** Units north (meters).
 */
#define PINGER_X_LOC 4.

/** Units east (meters).
 */
#define PINGER_Y_LOC -1.

/** Pinger freq (Hz).
 */
#define F0 25000.

/** Pinger period (seconds).
 */
#define T0 1./F0

/** Noise, expressed as a fraction of the signal (0.1=10%).
 */
#define NOISE 0.0

/** Amount of time pinger is silent per burst (seconds).
 */
#define TIME_BETWEEN_PINGS 0.5

/** Length of a ping burst (seconds).
 */
#define PING_DURATION 0.005
///@}

/*! \name Sampling settings.
 */
//@{
/** Sampling rate (Hz).
 */
#define FS 400000.

/** Sampling period (seconds).
 */
#define TS 1./FS
///@}

#endif 
