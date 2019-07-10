/*
 * Acoustic-MUSIC
 * Copyright (C) 2019 David Zhang
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ================================================================== */

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
