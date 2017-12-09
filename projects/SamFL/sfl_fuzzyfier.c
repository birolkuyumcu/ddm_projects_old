/*
 *  sfl_fuzzyfier.c
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


#include "sfl_fuzzyfier.h"


        //////////////////////////////////////////////////////////////////////////////////////////
        //
        //
        // y = ax+b
        //
        //      s:
        //              y-1 = ((1-0)/(xa - xb))*(x - xa)
        //              y       = ( (1/(xa - xb)) * (x - xa) ) + 1
        //
        //      z:
        //              y-0     = ((0-1)/(xa - xb))*(x - xa)
        //              y       = ((-1)/(xa - xb))*(x - xa)
        //              y       = (1/(xb - xa))*(x - xa)
        //
        //      a:
        //              ya      = z(x)
        //              yb      = s(x)
        //              y       = min(ya, yb)
        //              y       = min( (1/(xb - xa))*(x - xa) , ( (1/(xb - xc)) * (x - xb) ) + 1 )
        //
        //
        //////////////////////////////////////////////////////////////////////////////////////////


#define max(x,y)        ((x > y) ? x : y)
#define min(x,y)        ((x < y) ? x : y)

#define cap(x)          max(min(x,1.0),0.0)

#define return_caped(x)\
        if (x <= 0.0) return 0.0;\
        if (x >= 1.0) return 1.0;\
        return x;

double sfl_fuzzyfier_a(double x, double start, double middle, double end) {
        double a =   (1.0/(middle - start)) * (x - start );
        double b = ( (1.0/(middle - end  )) * (x - middle) ) + 1.0;
        double c = min(a,b);
        return_caped(c);
}

double sfl_fuzzyfier_s(double x, double start, double end) {
        double a = ( (1.0/(start - end)) * (x - start) ) + 1.0;
        return_caped(a);
}

double sfl_fuzzyfier_z(double x, double start, double end) {
        double a  =   (1.0/(end - start)) * (x - start);
        return_caped(a);
}

