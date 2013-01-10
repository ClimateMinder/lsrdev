/*
 * Copyright (c) 2012-2013 Eric B. Decker
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
 */

/*
 * PlatformSerial for the lsrdev platform.
 *
 * UART0 (Port A0)
 * pin 35, 36 lsr proflex module, P3.4, P3.5
 * 115200, 8N1
 *
 * 8MHz (8,000,000) main processor clock.
 */

module PlatformSerialP {
  provides {
    interface StdControl;
    interface Msp430UsciConfigure;
  }
  uses interface Resource;
}

implementation {

  command error_t StdControl.start(){
    return call Resource.immediateRequest();
  }

  command error_t StdControl.stop(){
    return call Resource.release();
  }

  event void Resource.granted() { }

  const msp430_usci_config_t lsrdev_uart_config = {
    /*
     * 8MHz (8,000,000 Hz), 115200 baud
     * UCBR 69, UCBRS 4, UCBRF 0, UCOS16 0
     */
    ctl0 : 0,
    ctl1 : UCSSEL__SMCLK,
    br0  : 69,
    br1  : 0,
    mctl : UCBRF_0 | UCBRS_4,
  };

  async command const msp430_usci_config_t *Msp430UsciConfigure.getConfiguration() {
    return &lsrdev_uart_config;
  }
}
