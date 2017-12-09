/*
 *  sfl.h
 *  samai
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


#ifndef _sfl_h_
#define _sfl_h_
#ifdef __cplusplus
extern "C"
{

#ifndef __cplusplus
} /* to fool automatic indention engines */
#endif
#endif	/* __cplusplus */

#ifdef __SamAI__
        #include <sfl_defuzzyfier.h>
        #include <sfl_fuzzyfier.h>
        #include <sfl_fuzzyset.h>
#else
        #include <sfl_defuzzyfier.h>
        #include <sfl_fuzzyfier.h>
        #include <sfl_fuzzyset.h>
#endif
#ifdef __cplusplus
#ifndef __cplusplus
/* to fool automatic indention engines */
{

#endif
}
#endif	/* __cplusplus */

#endif

