/******************************************************************
 * Copyright (C) 2004 by SG Software.
 ******************************************************************/

/* FILE NAME   : ru.c
 * PURPOSE     : SG MPFC. Russian charsets support plugin.
 * PROGRAMMER  : Sergey Galanov
 * LAST UPDATE : 31.01.2004
 * NOTE        : Module prefix 'ru'.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either version 2 
 * of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, 
 * MA 02111-1307, USA.
 */

#include "types.h"
#include "csp.h"

/* Charsets IDs */
#define RU_KOI8_R 0
#define RU_CP1251 1
#define RU_NUMBER 2

/* Codes table */
dword ru_table[RU_NUMBER][128] = 
{
	{ 
		0x2500, 0x2502, 0x250c, 0x2510, 0x2514, 0x2518, 0x251c, 0x2524, 
		0x252c, 0x2534, 0x253c, 0x2580, 0x2584, 0x2588, 0x258c, 0x2590,
		0x2591, 0x2592, 0x2593, 0x2320, 0x25a0, 0x2022, 0x221a, 0x2248,
		0x2264, 0x2265, 0x0020, 0x2321, 0x25e6, 0x00b2, 0x00b7, 0x00f7,
		0x2550, 0x2551, 0x2552, 0x0451, 0x2553, 0x2554, 0x2555, 0x2556, 
		0x2557,	0x2558, 0x2559, 0x255a, 0x255b, 0x255c, 0x255d, 0x255e, 
		0x255f,	0x2560, 0x2561, 0x0401, 0x2562, 0x2563, 0x2564, 0x2565, 
		0x2566, 0x2567,	0x2568, 0x2569, 0x256a, 0x256b, 0x256c, 0x00a9,
		0x044e, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433,
		0x0445, 0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e,
		0x043f, 0x044f, 0x0440, 0x0441, 0x0442, 0x0443, 0x0436, 0x0432,
		0x044c, 0x044b, 0x0437, 0x0448, 0x044d, 0x0449, 0x0447, 0x044a,
		0x042e, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413,
		0x0425, 0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e,
		0x041f, 0x042f, 0x0420, 0x0421, 0x0422, 0x0423, 0x0416, 0x0412,
		0x042c, 0x042b, 0x0417, 0x0428, 0x042d, 0x0429, 0x0427, 0x042a
	},
	{
		0x0402, 0x0403, 0x201a, 0x0453, 0x201e, 0x2026, 0x2020, 0x2021,
		0x0000, 0x2030, 0x0409, 0x2039, 0x040a, 0x040c, 0x040b, 0x040f,
		0x0452, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
		0x0000, 0x2122, 0x0459, 0x203a, 0x045a, 0x045c, 0x045b, 0x045f,
		0x0020, 0x040e, 0x045e, 0x0408, 0x00a4, 0x0490, 0x00a6, 0x00a7,
		0x0401, 0x00a9, 0x0404, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x0407,
		0x00b0, 0x00b1, 0x0406, 0x0456, 0x0491, 0x00b5, 0x00b6, 0x00b7,
		0x0451, 0x2116, 0x0454, 0x00bb, 0x0458, 0x0405, 0x0455, 0x0457,
		0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417,
		0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e, 0x041f,
		0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427,
		0x0428, 0x0429, 0x042a, 0x042b, 0x042c, 0x042d, 0x042e, 0x042f,
		0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437,
		0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e, 0x043f,
		0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
		0x0448, 0x0449, 0x044a, 0x044b, 0x044c, 0x044d, 0x044e, 0x044f
	}
};

/* Get number of charsets supportde */
int ru_get_num_sets( void )
{
	return RU_NUMBER;
} /* End of 'ru_get_num_sets' function */

/* Get charset name */
bool_t ru_get_cs_name( char *name, int index )
{
	switch (index)
	{
	case RU_KOI8_R:
		strcpy(name, "koi8-r");
		return TRUE;
	case RU_CP1251:
		strcpy(name, "cp1251");
		return TRUE;
	}
	return FALSE;
} /* End of 'ru_get_cs_name' function */

/* Get symbol unicode */
dword ru_get_code( byte ch, int index )
{
	if (index < 0 || index >= RU_NUMBER)
		return 0;

	if (ch < 128)
		return ch;
	else
		return ru_table[index][ch - 128];
} /* End of 'ru_get_code' function */

/* Get functions list */
void csp_get_func_list( csp_func_list_t *fl )
{
	fl->m_get_num_sets = ru_get_num_sets;
	fl->m_get_cs_name = ru_get_cs_name;
	fl->m_get_code = ru_get_code;
} /* End of 'inp_get_func_list' function */

/* End of 'ru.c' file */
