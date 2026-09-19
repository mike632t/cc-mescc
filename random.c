/*
 * random.c
 *
 * Copyright(C) 2026 - MT
 *
 * Prints 500,000 pseudo random numbers on the console.  
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 12 Sep 26   0.1   - Initial version - MT
 *
 */

#include "mescc.h"
#include "printf.h"    /* Provides printf() for printing output */
#include "rand.h"      /* Provides the rand() and srand() functions */

int main() 
{
   unsigned int i_count;  /* Unsigned allows range 0-65535 */ 
   int i_counter;

   for( i_count=1; i_count<=50000; i_count++)  
   {
      for( i_counter=0; i_counter<10; i_counter++)
         printf("%6d\t", rand());
      printf("\n");
   }
}

