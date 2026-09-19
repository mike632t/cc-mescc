/*
 * echo.c
 *
 * Copyright(C) 2026 - MT
 *
 * Prints the command line arguments on the console.
 *
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by  the
 * Free  Software Foundation, either version 3 of the License, or (at  your
 * option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful,  but
 * WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *
 * 12 Sep 26   0.1   - Initial version - MT
 *
 */

#define   NAME      "echo"

#include "mescc.h"
#include "printf.h"   /* Provides printf() for printing output */

int main(argc, argv)
int argc;
int *argv;    /* Small C handles this as an integer pointer */
{
   int i_count;

   /* Print each argument, adding a newline after the last one */
   for (i_count = 1; i_count < argc; i_count++)  
      printf("'%s' ", argv[i_count]);
   if (--argc > 0) printf ("\n");
}

