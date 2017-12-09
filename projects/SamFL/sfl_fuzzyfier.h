/*
 *  sfl_fuzzyfier.h
 *  samfl
 *
 *
 *      SamAI(umbrella) and SamFL provide a fuzzy-set-logic implementation in c.
 *      Copyright (C) 2005  Simon Andreas Menke
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 *      You can find the complete license in the lgpl-license.html(HTML version) and
 *      the lgpl-license.txt(TEXT version) files in the root directory of the project.
 *
 *
 *      e-mail: luinithil@luinithil.com
 *      site:   http://www.luinithil.com/
 *
 */


#ifndef _sfl_fuzzyfier_h_
#define _sfl_fuzzyfier_h_

//! linear @b A [ @b /\\ ] curve fuzzifier.
//! @param x            the input for the fuzzyfier.
//! @param start        the start of the curve. (bottom left)
//! @param middle       the middle of the curve. (top)
//! @param end          the end of the curve. (bottom right)
//! @return                     the fuzzyfied value.
double sfl_fuzzyfier_a(double x, double start, double middle, double end);

//! linear @b S [ @b \\ ] curve fuzzifier.
//! @param x            the input for the fuzzyfier.
//! @param start        the start of the curve. (top or left)
//! @param end          the end of the curve. (bottom or right)
//! @return                     the fuzzyfied value.
double sfl_fuzzyfier_s(double x, double start, double end);

//! linear @b Z [ @b / ] curve fuzzifier.
//! @param x            the input for the fuzzyfier.
//! @param start        the start of the curve. (bottom or left)
//! @param end          the end of the curve. (top or right)
//! @return                     the fuzzyfied value.
double sfl_fuzzyfier_z(double x, double start, double end);

#endif
