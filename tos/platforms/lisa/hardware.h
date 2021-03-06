/*
 * Copyright (c) 2012 Eric B. Decker
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither the name of the copyright holders nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @author Eric B. Decker <cire831@gmail.com>
 */

#ifndef _H_hardware_h
#define _H_hardware_h

#include "msp430hardware.h"

/*
 * something screwy in .platform.   Processor not specified as expected
 */

#if !defined(__msp430x54xA)
#warning Expected Processor __msp430x54xA not found
#endif

/*
 * Main CPU clock 8 MHz.
 *
 * We are using the I2C single master driver.  Use the default configuration
 * so use UCMST instead of UCMM.
 *
 * 8MHz/80 -> 100KHz
 * 8MHz/20 -> 400KHz
 */
#define MSP430_I2C_MASTER_MODE UCMST
#define MSP430_I2C_DIVISOR 20

/*
 * Port definitions:
 *
 * Various codes for port settings: (<dir><usage><default val>: Is0 <input><spi><0, zero>)
 * another nomenclature used is <value><function><direction>, 0pO (0 (zero), port, Output),
 *    xpI (don't care, port, Input), mI (module input).
 *
 * port 1.0	0pO	led0    		port 4.0	0pO    gps_on_off
 *       .1	0pO	led1    		      .1	1pO    gps_reset_n (nRST)
 *       .2	0pO	             		      .2	1pO    gps_csn (nRTS)
 *       .3     0pO	          		      .3	0pI    gps_awake
 *       .4	0pO	             		      .4	0pO
 *       .5	1pO	             		      .5	0pO
 *       .6	1pO	            		      .6	1pO
 *       .7	1pO	         		      .7	0pO
 *
 * port 2.0	1pO	          		port 5.0	1pI
 *       .1	0pO	          		      .1	1pI
 *       .2	0pO	                 	      .2	1pI
 *       .3	1pO	           		      .3	1pI
 *       .4	0pO	        		      .4	1pI    gps_somi (tx,   B1SOMI)
 *       .5	0pO	        		      .5	1pI    gps_sclk (nCTS, B1CLK)
 *       .6	0pO	       			      .6	1pI
 *       .7	0pI	       			      .7	1pI
 *
 * port 3.0	0pO	      			port 6.0	0pI
 *       .1	0pI	                    	      .1	0pI
 *       .2	0pI	                    	      .2	0pI
 *       .3	0pI	                    	      .3	0pI
 *       .4	1pI	       			      .4	1pO
 *       .5	0pI	       			      .5	1pO
 *       .6	1pI	                	      .6	1pO
 *       .7	1pI	gps_simo (rx, B1SIMO)  	      .7	1pO
 *
 * Note: When we used 6.3 as tell we saw no pull down.   Do we need to
 * enable the resistors (fets).
 *
 *
 * port 10.0	0pO	accel_sclk (a3sclk)	port 11.0	0pI
 *        .1	1pI	xi2c_sda (b3sda)    	       .1	0pI
 *        .2	1pI	xi2c_scl (b3scl)    	       .2	0pI
 *        .3	0pI	                    	       .3	0pI
 *        .4	1pI	accel_mosi (a3mosi)	       .4	1pO
 *        .5	1pI	accel_miso (a3miso)	       .5	1pO
 *        .6	1pI	                	       .6	1pO
 *        .7	1pO	accel_csn		       .7	1pO
 */


// enum so components can override power saving,
// as per TEP 112.
enum {
  TOS_SLEEP_NONE = MSP430_POWER_ACTIVE,
};

/* Use the PlatformAdcC component, and enable 8 pins */
//#define ADC12_USE_PLATFORM_ADC 1
//#define ADC12_PIN_AUTO_CONFIGURE 1
//#define ADC12_PINS_AVAILABLE 8

/* @TODO@ Disable probe for XT1 support until the anomaly observed in
 * apps/bootstrap/LocalTime is resolved. */
#ifndef PLATFORM_MSP430_HAS_XT1
#define PLATFORM_MSP430_HAS_XT1 1
#endif /* PLATFORM_MSP430_HAS_XT1 */

/*
 * Platform LEDs,
 *
 * Eval board has two leads, P1.0 and P1.1.
 * We keep the Yellow LED on P4.6, which is on the header
 * but isn't connected to anything.
 */
TOSH_ASSIGN_PIN(RED_LED, 1, 0);
TOSH_ASSIGN_PIN(GREEN_LED, 1, 1);
TOSH_ASSIGN_PIN(YELLOW_LED, 4, 6);

#ifdef notdef
// CC2420 RADIO #defines
TOSH_ASSIGN_PIN(RADIO_CSN, 3, 0);
TOSH_ASSIGN_PIN(RADIO_VREF, 2, 6);
TOSH_ASSIGN_PIN(RADIO_RESET, 2, 5);
TOSH_ASSIGN_PIN(RADIO_FIFOP, 2, 3);
TOSH_ASSIGN_PIN(RADIO_SFD, 2, 1);
TOSH_ASSIGN_PIN(RADIO_GIO0, 5, 0);
TOSH_ASSIGN_PIN(RADIO_FIFO, 2, 2);
TOSH_ASSIGN_PIN(RADIO_GIO1, 5, 1);
TOSH_ASSIGN_PIN(RADIO_CCA, 2, 4);

TOSH_ASSIGN_PIN(CC_FIFOP, 2, 3);
TOSH_ASSIGN_PIN(CC_FIFO, 2, 2);
TOSH_ASSIGN_PIN(CC_SFD, 2, 1);
TOSH_ASSIGN_PIN(CC_VREN, 2, 6);
TOSH_ASSIGN_PIN(CC_RSTN, 2, 5);
#endif

#endif // _H_hardware_h
