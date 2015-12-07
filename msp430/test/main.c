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
 * Keyboard HID Demo:
 *
 * This example functions as a keyboard on the host. Once enumerated, pressing
 * one of the target board’s buttons causes a string of six characters –
 * "msp430" -- to be "typed" at the PC’s cursor, wherever that cursor is.
 * If the other button is held down while this happens, it acts as a shift key,
 * causing the characters to become "MSP$#)".
 * Unlike the HID-Datapipe examples, this one does not communicate with the
 * HID Demo Application.
  +----------------------------------------------------------------------------+
 * Please refer to the Examples Guide for more details.
 *----------------------------------------------------------------------------*/
#include <string.h>

#include "driverlib.h"
#include "gpio.h"

#include "itoa.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"

#include "USB_app/keyboard.h"
/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"



/*********** Application specific globals **********************/
volatile uint8_t leftSwitchPressed = FALSE;
volatile uint8_t keySendComplete = TRUE;
char charBuf[2] = "Z";
uint8_t charBufLen;

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

/*
 * ======== main ========
 */
void main (void)
{
	uint8_t i;

	 WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

	// Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
	PMM_setVCore(PMM_CORE_LEVEL_2);
	USBHAL_initPorts();           // Config GPIOS for low-power (output low)
	USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
	USBHAL_initButtons();         // Init the two buttons
	Keyboard_init();       // Init keyboard report
	USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

	__enable_interrupt();  // Enable global interrupts

	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
	GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
	GPIO_setAsInputPinWithPullDownResistor(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS);
	GPIO_setAsInputPinWithPullDownResistor(RIGHT_BUTTONS_PORT, RIGHT_BUTTONS_PINS);
	/*GPIO_enableInterrupt(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS);
	GPIO_clearInterrupt(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS);
	GPIO_selectInterruptEdge(LEFT_BUTTONS_PORT, LEFT_BUTTONS_PINS, GPIO_LOW_TO_HIGH_TRANSITION);
	*/

	while (1)
	{
		switch(USB_getConnectionState())
		{
			// This case is executed while your device is enumerated on the
			// USB host

			case ST_ENUM_ACTIVE:

				// Enter LPM0 w/interrupt, until a keypress occurs
				//__bis_SR_register(LPM0_bits + GIE);

				/************* HID keyboard portion ************************/

				GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
				GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
				if (leftPressed())
				{
					inputDebounce();
					if (leftPressed())
					{
						GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
						while (leftPressed() && !rightPressed()); // spin wait for both paddles to hit a switch
						inputDebounce();
						if (leftPressed() && rightPressed())
						{
							GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
							int left = getLeft();
							int right = getRight();
							if (left < 0 || right < 0)
								continue;
							int dataInt = (left*6)+right+97;
							//itoa(dataInt, charBuf, 10);
							charBuf[0] = dataInt;
							charBuf[1] = '\0';
							charBufLen = strlen((const char *)charBuf);
							for (i=0; i<charBufLen; i++) {
								Keyboard_press(charBuf[i]);
								while(!keySendComplete);
								keySendComplete = FALSE;
								Keyboard_release(charBuf[i]);
								while(!keySendComplete);
								keySendComplete = FALSE;
							}
							blinkGreenLED();
							GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
						}
						GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
					}
				}
				while (leftPressed() && rightPressed()) // reset first
				{
					inputDebounce();
				}


//					button1StringLength = strlen((const char *)button1Buf);
//                    if (button2Pressed) {
//                        Keyboard_press(KEY_LEFT_SHIFT);
//                        while(!keySendComplete);
//                        keySendComplete = FALSE;
//                    }
//					for (i=0; i<button1StringLength; i++) {
//						Keyboard_press(button1Buf[i]);
//						while(!keySendComplete);
//						keySendComplete = FALSE;
//						Keyboard_release(button1Buf[i]);
//						while(!keySendComplete);
//						keySendComplete = FALSE;
//					}
//                    Keyboard_release(KEY_LEFT_SHIFT);
//                    while(!keySendComplete);
//					keySendComplete = FALSE;
//					button1Pressed = FALSE;
//					button2Pressed = FALSE;
//				}


				break;
			// These cases are executed while your device is disconnected from
			// the host (meaning, not enumerated); enumerated but suspended
			// by the host, or connected to a powered hub without a USB host
			// present.
			case ST_PHYS_DISCONNECTED:
			case ST_ENUM_SUSPENDED:
			case ST_PHYS_CONNECTED_NOENUM_SUSP:
				//__bis_SR_register(LPM3_bits + GIE);
				_NOP();
				break;

			// The default is executed for the momentary state
			// ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
			// seconds.  Be sure not to enter LPM3 in this state; USB
			// communication is taking place here, and therefore the mode must
			// be LPM0 or active-CPU.
			case ST_ENUM_IN_PROGRESS:
			default:;
		}
	}  //while(1)
} //main()

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
	switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
	{
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
			SYSBERRIV = 0; //clear bus error flag
			USB_disable(); //Disable
	}
}

//Released_Version_5_00_01
