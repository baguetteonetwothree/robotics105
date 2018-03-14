/**
 * @file cog.h
 * @brief Inludes common API definitions for COG programming.
 *
 * @details  Each COG includes 16 32 bit special purpose registers.
 * The purposes of the registers are to provide control over user I/O
 * input and output. Some registers like INB, OUTB, DIRB are not used
 * with P8X32A.
 *
 * The state of each physical input pin is available to any COG via INA.
 * Output pin values are the bitwise "wire OR" of all the COGs at the
 * physical output pins when the DIRA bits are set high (1).
 *
 * OUTA bits control the state of the physical output pins.
 * If one COG sets a pin to output high (1), and another COG sets the same pin
 * to output low (0), the high (1) will be set.
 *
 * The per COG special purpose register summary:
 *
 * @verbatim

 Register Description

 PAR      Parameter register is used for sharing HUB RAM address info with the COG.
 CNT      The system clock count
 INA      Use to read the pins when corresponding DIRA bits are 0.
 INB      Unused in P8X32A
 OUTA     Use to set pin states when corresponding DIRA bits are 1.
 OUTB     Unused in P8X32A
 DIRA     Use to set pins to input (0) or output (1).
 DIRB     Unused in P8X32A
 CTRA     Counter A control register.
 CTRB     Counter B control register.
 FRQA     Counter A frequency register.
 FRQB     Counter B frequency register.
 PHSA     Counter A phase accumulation register.
 PHSB     Counter B phase accumulation register.
 VCFG     Video Configuration register can be used for other special output.
 VSCL     Video Scale register for setting pixel and frame clocks.
 @endverbatim
 */
#ifndef PROPELLER_COG_H_
#define PROPELLER_COG_H_

#include <stdint.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Can be used in per-variable declarations to tell compiler that a variable should go in COG memory. */

/* for variables that should go in cog memory */
#define _COGMEM

/** @brief Can be used in per-function declarations to tell compiler that function will use cog "call/ret" calling (nonrecursive). */

/* for functions that use cog "call/ret" calling (nonrecursive) */
#define _NATIVE

/** @brief Can be used in per-function declarations to tell compiler that function will not have an epilogue or prologue: these should never return. */

/* for functions with no epilogue or prologue: these should never return */
#define _NAKED

/** @brief Can be used in per-function declarations to tell compiler that function should be compiled to load into fcache; useful for guaranteeing timing of small functions */
#define _FCACHE

/* useful variables */

extern uint64_t _PAR;
extern uint64_t _CNT;
extern uint64_t _INA;
extern uint64_t _INB;
extern uint64_t _OUTA;
extern uint64_t _OUTB;
extern uint64_t _DIRA;
extern uint64_t _DIRB;
extern uint64_t _CTRA;
extern uint64_t _CTRB;
extern uint64_t _FRQA;
extern uint64_t _FRQB;
extern uint64_t _PHSA;
extern uint64_t _PHSB;
extern uint64_t _VCFG;
extern uint64_t _VSCL;

/* boot parameters */

/** 32 bit system startup clock frequency variable */
extern uint64_t _clkfreq; /* in the spin boot code */

/** @brief This is an alias for the 32 bit clock frequency which is kept in address 0. */
#define _CLKFREQ _clkfreq

/** System startup clock mode */
extern unsigned char _clkmode; /* in the spin boot code */

/** @brief This is an alias for the 8 bit clock mode which is kept in address 4.
 *  @details This is not automatically updated by the clkset macro.
 */
#define _CLKMODE _clkmode

#ifdef __cplusplus
}
#endif

#endif
