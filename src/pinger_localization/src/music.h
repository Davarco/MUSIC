/**
 * @file music.h
 * @brief Function declarations for MUSIC (Multiple Signal Classification).
 *
 * @author David Zhang (Davarco)
 * @bugs No known bugs.
 */
#ifndef MUSIC_H
#define MUSIC_H 

void dft(double *ps);
void tdoa(double *ps, double *tdoa);
void music(double *tdoa);

#endif
