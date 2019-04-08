/* Source/Library/Function Root Finder Algorithms/steffensenAlgorithm.h
 *
 * ASL - Azadeh Scientific Library in C
 *
 * Copyright (C) 2019 Mohammad Mahdi Baghbani Pourvahid
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef __ASL_STEFFENSENALGORITHM_H__
#define __ASL_STEFFENSENALGORITHM_H__

// To ensure that the names declared in this portion of code have C linkage,
// and thus C++ name mangling is not performed while using this code with C++.
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

double asl_steffenson_root(const char *expression, double x, double ete, double ere, double tol, unsigned int maxiter,
                           int verbose, int *state);
/*
 * In numerical analysis, Steffensen's method is a root-finding technique similar to Newton's method,
 * named after Johan Frederik Steffensen. Steffensen's method also achieves quadratic convergence,
 * but without using derivatives as Newton's method does.
 *
 * PURPOSE:
 * asl_steffensen_root a root of a function F(X).
 *
 * DISCUSSION:
 * Nothing.
 *
 * LICENSING:
 * This code is distributed under the GNU Affero General Public License v3.0 (AGPL).
 *
 * Permissions of this strongest copyleft license are conditioned on making available complete source code
 * of licensed works and modifications, which include larger works using a licensed work, under the same license.
 * Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.
 * When a modified version is used to provide a service over a network, the complete source code of
 * the modified version must be made available.
 *
 * AGPL Permissions:
 * Commercial use
 * Modification
 * Distribution
 * Patent use
 * Private use
 *
 * AGPL Limitations:
 * Liability
 * Warranty
 *
 * AGPL Conditions:
 * License and copyright notice
 * State changes
 * Disclose source
 * Network use is distribution
 * Same license
 *
 * AUTHOR(S):
 * Mohammad Mahdi Baghbani Pourvahid
 *
 * MODIFIED:
 * 6 April 2019
 *
 * REFERENCE(S):
 * https://en.wikipedia.org/wiki/Steffensen%27s_method
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x            starting point
 * ete          estimated true error
 * ere          estimated relative error
 * tol          tolerance error
 * maxiter      maximum iteration threshold
 * verbose      show process {0: no, 1: yes}
 * state        is answer found or not, will set value of state to 0 if no answers been found
 *
 */

__END_DECLS

#endif //__ASL_STEFFENSENALGORITHM_H__