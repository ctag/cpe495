/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*
 * ======== main.c ========
 * "Simple Send"
 *
 * This example shows a very simplified way of sending.  This might be used in
 * an application where the main functionality doesn't change much if a USB
 * host is present or not.  It simply calls USBCDC_sendDataInBackground(); if no
 * host is present, it simply carries on.
 *
 * Simply build, run, and attach to a USB host.  Run a terminal application
 * and open the COM port associated with this device.  (In Windows, check the
 * Device Manager.)  The time should be displayed, every second.
 *
 * Note that this code is identical to example H9, except for one line of
 * code:  the call to USBCDC_sendDataInBackground() instead of
 * USBHID_sendDataInBackground().  This reflects the symmetry between writing
 * MSP430 code for CDC vs. HID-Datapipe.
 *
 *+----------------------------------------------------------------------------+
 * Please refer to the MSP430 USB API Stack Programmer's Guide, located
 * in the root directory of this installation for more details.
 * ---------------------------------------------------------------------------*/

#include <string.h>
#include "driverlib.h"

#include "itoa.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                     //USB-specific functions
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "USB_app/usbConstructs.h"

/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"

void blinkRedLED()
{
	uint16_t i;
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
	for (i = ((uint16_t)-1); i > 0; i--)
	{
		// cheap delay
		_NOP();
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    for (i = ((uint16_t)-1); i > 0; i--)
	{
		// cheap delay
		_NOP();
    }
}

void toggleRedLED()
{
	GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void blinkGreenLED()
{
	uint16_t i;
	GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
	for (i = ((uint16_t)-1); i > 0; i--)
	{
		// cheap delay
		_NOP();
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
    for (i = ((uint16_t)-1); i > 0; i--)
	{
		// cheap delay
		_NOP();
    }
}

void toggleGreenLED()
{
	GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN7);
}

bool bothPressed()
{
	bool left = P2IN;
	bool right = P3IN;
	if (left && right)
		return true;
	return false;
	//return (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS) && GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, RIGHT_BUTTONS_PINS));
}

bool onePressed()
{
	bool left = P2IN;
	bool right = P3IN;
	if ((left && !right) || (!left && right))
		return true;
	return false;
//	if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS) && !GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, RIGHT_BUTTONS_PINS))
//		return true;
//	else if (!GPIO_getInputPinValue(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS) && GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, RIGHT_BUTTONS_PINS))
//		return true;
//	else
//		return false;
}

bool leftPressed()
{
	bool left = P2IN&LEFT_BUTTONS_PINS;
	return left;
}

bool rightPressed()
{
	bool right = P3IN&RIGHT_BUTTONS_PINS;
	return right;
}

int getLeft()
{
	if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN0))
		return 0;
	else if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN2))
		return 1;
	else if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN3))
		return 2;
	else if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN4))
		return 3;
	else if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN5))
		return 4;
	else if (GPIO_getInputPinValue(LEFT_BUTTONS_PORT, GPIO_PIN6))
		return 5;
	else
		return -1;
}

int getRight()
{
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN0))
		return 0;
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN1))
		return 1;
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN2))
		return 2;
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN3))
		return 3;
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN4))
		return 4;
	if (GPIO_getInputPinValue(RIGHT_BUTTONS_PORT, GPIO_PIN5))
		return 5;
	else
		return -1;
}


// Function declarations
//void convertTimeBinToASCII(uint8_t* timeStr);
void initRTC(void);
//
//// Application globals
//volatile uint8_t hour = 4, min = 30, sec = 00;  // Real-time clock (RTC) values.  4:30:00
//volatile uint8_t bSendTimeToHost = FALSE;       // RTC-->main():  "send the time over USB"
uint8_t timeStr[9];                    // Stores the time as an ASCII string




/*
 * ======== main ========
 */
void main(void)
{
    WDT_A_hold(WDT_A_BASE); //Stop watchdog timer

    // Minimum Vcore setting required for the USB API is PMM_CORE_LEVEL_2
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)
    USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USB_setup(TRUE,TRUE);  // Init USB & events; if a host is present, connect
    initRTC();             // Start the real-time clock

    __enable_interrupt();  // Enable interrupts globally

    int prevLeft = getLeft();
    int prevRight = getRight();
    int left;
    int right;

    while (1)
    {
        // Enter LPM0, which keeps the DCO/FLL active but shuts off the
        // CPU.  For USB, you can't go below LPM0!
        __bis_SR_register(LPM0_bits + GIE);

        // If USB is present, sent the time to the host.  Flag is set every sec

        left = getLeft();
        right = getRight();
        timeStr[0] = '[';
        itoa(left, &timeStr[1], 10);
        itoa(right, &timeStr[2], 10);
        timeStr[3] = ']';
        timeStr[4] = '\n';
        timeStr[5] = '\0';
//
//        if (bSendTimeToHost)
//        {
//            bSendTimeToHost = FALSE;
//            convertTimeBinToASCII(timeStr);

            // This function begins the USB send operation, and immediately
            // returns, while the sending happens in the background.
            // Send timeStr, 9 bytes, to intf #0 (which is enumerated as a
            // COM port).  1000 retries.  (Retries will be attempted if the
            // previous send hasn't completed yet).  If the bus isn't present,
            // it simply returns and does nothing.
            if (USBCDC_sendDataInBackground(timeStr, 6, CDC0_INTFNUM, 1000))
            {
              _NOP();  // If it fails, it'll end up here.  Could happen if
                       // the cable was detached after the connectionState()
            }           // check, or if somehow the retries failed
//        }
    }  //while(1)
}  //main()


// Starts a real-time clock on TimerA_0.  Earlier we assigned ACLK to be driven
// by the REFO, at 32768Hz.  So below we set the timer to count up to 32768 and
// roll over; and generate an interrupt when it rolls over.
void initRTC(void)
{
    TA0CCR0 = 32768;
    TA0CTL = TASSEL_1+MC_1+TACLR; // ACLK, count to CCR0 then roll, clear TAR
    TA0CCTL0 = CCIE;              // Gen int at rollover (TIMER0_A0 vector)
}


// Timer0 A0 interrupt service routine.  Generated when TimerA_0 (real-time
// clock) rolls over from 32768 to 0, every second.
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
#else
#error Compiler not found!
#endif
{
//    if (sec++ == 60)
//    {
//        sec = 0;
//        if (min++ == 60)
//        {
//            min = 0;
//            if (hour++ == 24)
//            {
//                hour = 0;
//            }
//        }
//    }
//
//    bSendTimeToHost = TRUE;                 // Time to update
    __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM
}

/*
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
        switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG )) {
        case SYSUNIV_NONE:
                __no_operation();
                break;
        case SYSUNIV_NMIIFG:
                __no_operation();
                break;
        case SYSUNIV_OFIFG:

                UCS_clearFaultFlag(UCS_XT2OFFG);
                UCS_clearFaultFlag(UCS_DCOFFG);
                SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
                break;
        case SYSUNIV_ACCVIFG:
                __no_operation();
                break;
        case SYSUNIV_BUSIFG:
                // If the CPU accesses USB memory while the USB module is
                // suspended, a "bus error" can occur.  This generates an NMI.  If
                // USB is automatically disconnecting in your software, set a
                // breakpoint here and see if execution hits it.  See the
                // Programmer's Guide for more information.
                SYSBERRIV = 0;  // Clear bus error flag
                USB_disable();  // Disable
        }
}

//Released_Version_5_00_01
