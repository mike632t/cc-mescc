/**
 * @file   rand.h
 * @brief  Pseudo-random number generation.
 * @author Miguel I. Garcia Lopez / FloppySoftware
 *
 * Pseudo-random number generation, for MESCC (Mike's Enhanced
 * Small C Compiler for Z80 & CP/M).
 *
 * Revisions:
 *  - 18 Mar 2015 : 1st version.
 *  - 23 Mar 2015 : Trying to improve rand().
 *  - 15 Aug 2016 : Documented. GPL v3.
 *  - 13 Sep 2026 : Allow negative numbers - MT
 *
 * Defined macros:
 *  - RAND_MAX
 *
 * Copyright (c) 2015-2016 Miguel I. Garcia Lopez / FloppySoftware.
 *
 * Licensed under the GNU General Public License v3.
 *
 * http://www.floppysoftware.es
 * floppysoftware@gmail.com
 */
 
#ifndef RAND_H

#define RAND_H
#define RAND_MAX 32767

unsigned int xs_seed = 1; /* Initial value for seed */

/**
 * @fn     int rand(void)
 * @brief  Generate a 16-bit pseudo-random integer value.
 * @return value
 * 
 * Generates  a psudo  random  number  using  George  MARSAGLIA's  xorshift 
 * algorithm.	This  generates a 16-bit pseudo-random number  by  applying 
 * three  successive  xorshift	 operations, where  the	 current  value	 is
 * exclusive-ORed with a shifted copy of itself.
 * 
 * This  version is implemented in C using _unsigned_ 16 bit  integers.  In
 * terms  of performance it is less than 10% slower then the version  below 
 * using assembler which shows how efficient the compiler is.
 */
rand()
{
      xs_seed ^= xs_seed << 7;
      xs_seed ^= xs_seed >> 9;
      xs_seed ^= xs_seed << 8;
      return xs_seed;
}

/**
 * @fn     int rand(void)
 * @brief  Generate a 16-bit pseudo-random integer value.
 * @return value
 * 
 * Generates  a psudo  random  number  using  George  MARSAGLIA's  xorshift 
 * algorithm.	This  generates a 16-bit pseudo-random number  by  applying 
 * three  successive  xorshift	 operations, where  the	 current  value	 is
 * exclusive-ORed with a shifted copy of itself.
 * 
 * This version was implemented in Z80 assembly by John METCALF. 
 * 
 * http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html
 * 
 */
rand2()
{
#asm
;   unsigned xorshift(n)
;   {
;       n ^= n << 7;
;       n ^= n >> 9;
;       n ^= n << 8;
;       return n;
;   }
;
; Implemented using assembler.
;
;		POP	DE		; Pop the 16-bit Return Address off the stack into DE.
;		EX	(SP),HL		; Get current seed from the stack
;		PUSH	DE		; Put the Return Address back on the stack.

		LD	HL, (xs_seed)	; Get current seed...
		LD	A,H	
		RRA
		LD	A,L
		RRA
		XOR	H
		LD	H,A
		LD	A,L
		RRA
		LD	A,H
		RRA
		XOR	L
		LD	L,A
		XOR	H
		LD	H,A
		LD 	(xs_seed), HL	; Save seed.
		RET
;
#endasm
}

/**
 * @fn     void srand(unsigned int seed)
 * @brief  Seeds the pseudo-random number generator used by rand().
 * @param  seed - value
 */
srand(seed)
unsigned int seed;
{
	xs_seed = seed;
}

#endif

