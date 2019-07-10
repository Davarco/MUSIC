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

/** @file src/pinger_localization/src/config.h
 *  @brief Contains constants needed to calculate DOA (direction-of-arrival).
 *
 *  These values should match the simulated settings in pinger_simulation, or
 *  represent real world settings.
 *
 *  @author David Zhang (Davarco)
 */
#ifndef CONFIG_H
#define CONFIG_H

/** Wave speed (m/s).
 */
const double C = 1480.;

/** Sampling speed (Hz).
 */
const double FS = 400000.;

/** Pinger frequency (Hz).
 */
const double F0 = 25000.;

/** Signal receiver spacing (meters).
 */
const double SPACING = 0.0127;

/** DOA precision (degrees).
 */
const double SEARCH_INTERVAL = 0.1;

/** Total number of signal receivers.
 */
const int N_PHN = 4;

/** Number of points in DFT.
 */
const int N_DFT = 2048;

/** Number of points to simulate for signal.
 */
const int N = 16;

/** Number of signal receivers per MUSIC calculation.
 */
const int M = 2;

/** Log option.
 */
const int DEBUG = 0;

#endif 
