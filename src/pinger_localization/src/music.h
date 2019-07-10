/** @file music.h
 *  @brief Function declarations for MUSIC (Multiple Signal Classification).
 *
 *  @author David Zhang (Davarco)
 *  @bugs No known bugs.
 */
#ifndef MUSIC_H
#define MUSIC_H 

/** @brief Computes a DFT at the pinger frequency for phase shifts.
 *
 *  @param ps The address where the M phase shifts (radians) will be written.
 */
void dft(double *ps);

/** @brief Computes the TDOA (time difference of arrival) between phase shifts.
 *
 *  The first TDOA value should be 0, as all the TDOAs are calculated relative
 *  to the first phase shift.
 *
 *  @param ps The M phase shifts (radians).
 *  @param tdoa The address where the M TDOAs (periods) will be written.
 */
void tdoa(double *ps, double *tdoa);

/** @brief Computes the DOA (direction of arrival) using TDOAs. 
 *
 *  MUSIC is limited to a [-90, 90] degree window. 0 is north, or X. 
 *
 *  @param tdoa The M TDOAs (periods).
 *  @param angle The address where the DOA (degrees) will be written.
 */
void music(double *tdoa, double *angle);

#endif
