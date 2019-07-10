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

/** @file matrix.h
 *  @brief Function declarations for real and complex matrix operations.
 *
 *  Matrices are stored in 1-D arrays. To access a cell, use [r*n+c] instead 
 *  of [r][c].
 *
 *  Most of the other parts don't require explanation, except for how complex
 *  matrices are handled. To create a complex matrix of order MxN, create two
 *  matrices of the same order. Use the first matrix to hold real components  
 *  and the other to hold imaginary components.
 *
 *  @author David Zhang (Davarco)
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <string>

/** @brief Print real matrix to terminal.
 *
 *  @param A The matrix that is printed.
 *  @param m The number of rows in A.
 *  @param n The number of columns in B.
 *  @param msg The header message preceding the matrix.
 */
void print(double *A, int m, int n, char *msg);

/** @brief Print complex matrix to terminal.
 *
 *  @param Ar The real components of the matrix that is printed.
 *  @param Ai The imaginary components of the matrix that is printed.
 *  @param m The number of rows in Ar and Ai.
 *  @param n The number of columns in Br and Bi.
 *  @param msg The header message preceding the matrix.
 */
void print_complex(double *Ar, double *Ai, int m, int n, char *msg);

/** @brief Create an identity matrix of order nxn.
 *
 *  @param A The address where the matrix is written.
 *  @param n The number of rows and columns of A.
 */
void identity(double *A, int n);

/** @brief Copies the elements from one matrix to another.
 *
 *  @param A The matrix from where elements are copied from.
 *  @param m The number of rows in A and B.
 *  @param n The number of columns in A and B.
 *  @param B The matrix where elements are written to.
 */
void copy(double *A, int m, int n, double *B);

/** @brief Multiplies two matrices together.
 *
 *  @param A The first matrix.
 *  @param B The second matrix.
 *  @param m The number of rows in A.
 *  @param p The number of columns in A and number of rows in B.
 *  @param n The number of columns in B.
 *  @param C The multiplied matrix of order mxn.
 */
void product(double *A, double *B, int m, int p, int n, double *C);

/** @brief Multiplies two complex matrices together.
 *
 *  @param Ar The real components of the first matrix.
 *  @param Ai The imaginary components of the first matrix.
 *  @param Br The real components of the second matrix.
 *  @param Bi The imaginary components of the second matrix.
 *  @param m The number of rows in A.
 *  @param p The number of columns in A and number of rows in B.
 *  @param n The number of columns in B.
 *  @param Cr The real components of the multiplied matrix.
 *  @param Ci The imaginary components of the multiplied matrix.
 */
void product_complex(double *Ar, double *Ai, double *Br, double *Bi,
		int m, int p, int n, double *Cr, double *Ci);

/** @brief Adds two matrices together.
 *
 *  @param A The first matrix.
 *  @param B The second matrix.
 *  @param m The number of rows in A and B.
 *  @param n The number of columns in A and B.
 *  @param C The added matrix.
 */
void add(double *A, double *B, int m, int n, double *C);

/** @brief Subtracts two matrices.
 *
 *  @param A The first matrix.
 *  @param B The second matrix.
 *  @param m The number of rows in A and B.
 *  @param n The number of columns in A and B.
 *  @param C The subtracted matrix.
 */
void subtract(double *A, double *B, int m, int n, double *C);

/** @brief Takes the transpose of a matrix.
 *
 *  @param A The input matrix to transpose.
 *  @param m The number of rows in A.
 *  @param n The number of columns in A.
 *  @param B The transposed matrix of order nxm.
 */
void transpose(double *A, int m, int n, double *B);

/** @brief Takes the transpose (complex conjugate) of a complex matrix.
 *
 *  @param Ar The real components of the first matrix.
 *  @param Ai The imaginary components of the first matrix.
 *  @param m The number of rows in A.
 *  @param n The number of columns in B.
 *  @param Br The real components of the transposed matrix.
 *  @param Bi The imaginary components of the transposed matrix.
 */
void transpose_complex(double *Ar, double *Ai, int m, int n, 
		double *Br, double *Bi);

/** @brief Multiplies a matrix by a scalar.
 *
 *  @param A The input matrix, where the results are written to as well.
 *  @param m The number of rows in A.
 *  @param n The number of columns in A.
 *  @param k The scalar value.
 */
void scale(double *A, int m, int n, double k);

/** @brief Slices a matrix.
 *
 *  The sliced matrix is equal to A[m1:m2-1, n1:n2-1].
 *
 *  @param A The input matrix.
 *  @param n The number of columns in A.
 *  @param m1 The first row to slice from.
 *  @param m2 The row after the stop slicing at.
 *  @param n1 The first column to slice from.
 *  @param n2 The column after the stop slicing at.
 *  @param B The sliced matrix.
 */
void slice(double *A, int n, int m1, int m2, int n1, int n2, double *B);

/** @brief Takes the inverse of a matrix.
 *
 *  @param A The input matrix, must be square.
 *  @param n The number of rows and columns in A.
 *  @param B The inverted matrix.
 */
void inverse(double *A, int n, double *B);

/** @brief Takes the eigenvalues and eigenvectors of a real matrix.
 *
 *  @param A The input matrix, must be square.
 *  @param n The number of rows and columns in A.
 *  @param val The address where the eigenvalues are stored.
 *  @param vec The address where the eigenvectors are stored.
 */
void eigen(double *A, int n, double *val, double *vec);

/** @brief Takes the eigenvalues and eigenvectors of a complex matrix.
 *
 *  @param Ar The real components of the input matrix.
 *  @param Ai The imaginary components of the input matrix.
 *  @param n The number of rows and columns in A.
 *  @param val The address where the eigenvalues are stored.
 *  @param vecr The address for the real components of the eigenvectors.
 *  @param veci The address for the imaginary components of the eigenvectors.
 */
void eigen_complex(double *Ar, double *Ai, int n, double *val, 
		double *vecr, double *veci);

#endif
