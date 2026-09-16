/*
 * calendar.c - Example program for MESCC.
 *
 * Copyright(C) 2023   MT
 *
 * Displays the calendar for a single month or whole year.
 * 
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by the
 * Free  Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful, but
 * WITHOUT   ANY   WARRANTY;   without even   implied   warranty   of any
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 03 Sep 23   0.1   - Initial version - MT
 * 08 Sep 23   0.2   - Get month/year from command line - MT
 * 16 Sep 26   0.3   - Prints multiple months one week at a time - MT
 *             0.4   - Do all the hard work in print_months() - MT
 *             0.5   - Modified to compile on CP/M using MESCC - MT
 * 
 * ToDo              -
 *
 */

#define  NAME        "calendar"
#define  VERSION     "0.5"
#define  BUILD       "0005"
#define  AUTHOR      "MT"
#define  COPYRIGHT   (__DATE__ + 7)  /* Extract copyright year from date */
 
#include "mescc.h"
#include "printf.h"

int i_lookup[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
int i_length[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int i_isLeapYear(i_year) 
int i_year;
/*
 * Returns true if the year is a leap year for years > 1752.
 * 
 */
{
   return(i_year % 4 == 0 && i_year % 100 != 0 || i_year % 400 == 0);
}


int i_weekday(i_day, i_month, i_year)
int i_day;
int i_month;
int i_year;
/*
 * Returns the day of the week (Sun = 0, Mon = 1, etc) for a given date 
 * for 1 <= i_month <= 12,  i_year > 1752.
 * 
 * https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods
 * 
 */
{

   if (i_month < 3) 
   {
      i_year -= 1;
   }
   return (i_year + i_year / 4 - i_year / 100 + i_year / 400 + i_lookup[i_month - 1] + i_day) % 7;
}


v_print_months(i_first_month, i_months, i_year)
int i_first_month;
int i_months;
int i_year;
{
   int s_month[12];
   int i_month;
   int i_current_year;
   int i_week;
   int i_count;
   int i_start;
   int i_day;
   int i_day_count;
   int i_row;

   s_month[0] = "    January";
   s_month[1] = "   February";
   s_month[2] = "     March";
   s_month[3] = "     April";
   s_month[4] = "      May";
   s_month[5] = "     June";
   s_month[6] = "     July";
   s_month[7] = "    August";
   s_month[8] = "   September";
   s_month[9] = "    October";
   s_month[10] = "   November";
   s_month[11] = "   December";

   while (i_months > 0)
   {
      i_row = i_months;
      if (i_row > 3)
      {
         i_row = 3;
      }

      for (i_week = 0; i_week < 6; i_week++)
      {
         for (i_count = 0; i_count < i_row; i_count++)
         {
            /* Calculate the month and year, allowing the month to wrap into the next year. */
            i_month = i_first_month + i_count;
            i_current_year = i_year + (i_month - 1) / 12;
            i_month = (i_month - 1) % 12 + 1;

            i_length[1] = 28 + i_isLeapYear(i_current_year);
            i_start = i_weekday(1, i_month, i_current_year);

            if (i_week == 0)  /* Print heading (month and year) and days of the week. */
            {
               printf("%11s %4d    ",s_month[i_month - 1], i_current_year);
               if (i_count < i_row - 1)
               {
                  printf("  ");
               }
            }
         }

         if (i_week == 0)
         {
            printf("\n");

            for (i_count = 0; i_count < i_row; i_count++)
            {
               printf("Su Mo Tu We Th Fr Sa");
               if (i_count < i_row - 1)
               {
                  printf("  ");
               }
            }
            printf("\n");
         }

         for (i_count = 0; i_count < i_row; i_count++)
         {
            /* Calculate the month and year, allowing the month to wrap into the next year. */
            i_month = i_first_month + i_count;
            i_current_year = i_year + (i_month - 1) / 12;
            i_month = (i_month - 1) % 12 + 1;

            i_length[1] = 28 + i_isLeapYear(i_current_year);
            i_start = i_weekday(1, i_month, i_current_year);

            for (i_day_count = 0; i_day_count < 7; i_day_count++)
            {
               i_day = i_week * 7 + i_day_count - i_start + 1;

               if (i_day >= 1 && i_day <= i_length[i_month - 1])
               {
                  printf("%2d ", i_day);
               }
               else
               {
                  printf("   ");
               }
            }

            if (i_count < i_row - 1)
            {
               printf(" ");
            }
         }
         printf("\n");
      }
      printf("\n");

      i_first_month += 3;
      i_months -= i_row;
   }
}


int main(argc, argv)
int argc;
int *argv;
{
   int i_month;
   int i_year;

   if (argc == 2)
   {
      i_year = atoi(argv[1]);

      if (i_year > 1752)
      {
         v_print_months(1, 12, i_year);
      }
      else
         printf("Year out of range.\n");
   }
   else if (argc == 3)
   {
      i_month = atoi(argv[1]);
      i_year = atoi(argv[2]);

      if (i_month > 0 && i_month < 13 && i_year > 1752)
      {
         v_print_months(i_month, 1, i_year);
      }
      else
         printf("Year or month out of range.\n");
   }
   else
      printf("Usage: cal [month] year\n");

   return 0;
}
