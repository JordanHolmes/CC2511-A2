/* ###################################################################
**     Filename    : main.c
**     Project     : WTF
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-10-25, 17:47, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "XDirection.h"
#include "BitIoLdd1.h"
#include "YDirection.h"
#include "BitIoLdd2.h"
#include "ZDirection.h"
#include "BitIoLdd3.h"
#include "XStepper.h"
#include "PwmLdd1.h"
#include "YStepper.h"
#include "PwmLdd2.h"
#include "ZStepper.h"
#include "PwmLdd3.h"
#include "SpindleSpeed.h"
#include "PwmLdd4.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "TU1.h"

/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int spindleSpeed = 0x0000;
	int speedCount = 0x0000;

	int xStep = 0x0000;
	int yStep = 0x0000;
	int zStep = 0x0000;
	int counter = 0x0000;

	int xPosition = 0x000;
	int yPosition = 0x000;
	int zPosition = 0x000;

	int xPos;
	int yPos;
	int zPos;

	byte c, err;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	// Updates position displays in Term
	// TODO use buffers instead
	void update_position_displays(int xPosition, int yPosition, int zPosition) {
		// Update x position display
		Term1_MoveTo(15, 5);
		Term1_SendStr("       ");
		Term1_MoveTo(15, 5);
		Term1_SendNum(xPosition);

		// Update y position display
		Term1_MoveTo(15, 6);
		Term1_SendStr("       ");
		Term1_MoveTo(15, 6);
		Term1_SendNum(yPosition);

		//Update z position display
		Term1_MoveTo(15, 7);
		Term1_SendStr("       ");
		Term1_MoveTo(15, 7);
		Term1_SendNum(zPosition);

		text("                      ", 3, 8, 0);
	}

	// Returns all 'arms' to starting position (0, 0, 0)
	void return_to_start() {
		XDirection_SetVal();
		YDirection_SetVal();
		ZDirection_ClrVal();
		text("... Returning X to start ...", 0, 17, 0);
		Term1_MoveTo(0, 18);
		for (xPosition; xPosition > 0; xPosition--) {
			update_position_displays(xPosition, yPosition, zPosition);
			for (counter = 0; counter < 200000; counter++) {
				XStepper_SetRatio16(0xFFFF);
			}
			XStepper_SetRatio16(0x0000);

		}
		text("... Returning Y to start ...", 0, 18, 0);
		Term1_MoveTo(0, 19);
		for (yPosition; yPosition > 0; yPosition--) {
			update_position_displays(xPosition, yPosition, zPosition);
			for (counter = 0; counter < 20000; counter++) {
				YStepper_SetRatio16(0xFFFF);
			}
			YStepper_SetRatio16(0x0000);
		}
		text("... Returning Z to start ...", 0, 19, 0);
		Term1_MoveTo(0, 20);
		for (zPosition; zPosition > 0; zPosition--) {
			update_position_displays(xPosition, yPosition, zPosition);
			for (counter = 0; counter < 20000; counter++) {
				ZStepper_SetRatio16(0xFFFF);
			}
			ZStepper_SetRatio16(0x0000);
		}
		int xPosition = 0x000;
		int yPosition = 0x000;
		int zPosition = 0x000;
//		text("            ", 10, 7, 0);
//		text("            ", 10, 8, 0);
//		text("            ", 10, 9, 0);
		update_position_displays(xPosition, yPosition, zPosition);
	}

	// Changes the PWM ratio to increase or decrease spindle speed
	int change_ratio (int ratio, bool direction) {
		if (direction) {
			if (ratio >= 0x3333){
				ratio -= 0x3333;
			}
			else {
				ratio = 0;
			}
		}
		else {
			if (ratio <= 0xCCCC) {
				ratio += 0x3333;
			}
			else {
				ratio = 0xFFFF;
			}
		}
		return ratio;
	}

	void display_boundary_message() {
		text("-- Boundary Reached --", 3, 8, 0);
	}


	/* Initial Set Up */

	// Turn off all motors before start
	SpindleSpeed_SetRatio16(0xFFFF);
	XStepper_SetRatio16(0x0000);
	YStepper_SetRatio16(0x0000);
	ZStepper_SetRatio16(0x0000);

	Term1_Cls();
	text("CC2511 Group 4 - Assignment 2", 0, 0, 2);

	text("Manual Control (m) or Coordinate Control (c) ?", 0, 5, 0);
	text(">> ", 0, 6, 0);
	Term1_MoveTo(3, 6);

	for(;;) {
		do {err = Inhr1_RecvChar(&c);
		} while (err != ERR_OK);

		Term1_CRLF();
		Term1_SendChar(c);

		if ((c == 'm') || (c == 'M')) {
			// Manual Control
			Term1_Cls();
			text("CC2511 Group 4 - Assignment 2", 0, 0, 2);
			create_box(0, 3, 25, 3, 25, 15, 0, 15);
			create_box(28, 3, 60, 3, 60, 15, 28, 15);

			text("+-----Tool Location-----+", 0, 3, 1);
			text("X:   0", 10, 5, 0);
			text("Y:   0", 10, 6, 0);
			text("Z:   0", 10, 7, 0);
			text("Speed:  0", 9, 9, 0);
			text("--OFF--", 10, 10, 0);
			create_box(4, 11, 22, 11, 22, 13, 4, 13);

			text("+--------Manual Control---------+", 28, 3, 1);
			text("W - Increase x-axis value", 31, 5, 0);
			text("S - Decrease x-axis value", 31, 6, 0);
			text("E - Increase y-axis value", 31, 7, 0);
			text("D - Decrease y-axis value", 31, 8, 0);
			text("R - Increase z-axis value", 31, 9, 0);
			text("F - Decrease z-axis value", 31, 10, 0);
			text("+ - Increase Spindle Speed", 31, 11, 0);
			text("- - Decrease Spindle Speed", 31, 12, 0);
			text("Q - Quit Manual Control", 31, 13, 0);

			text("Enter Key:          ", 0, 16, 0);
			text("> ", 0, 17, 0);
			Term1_MoveTo(3, 17);

			for(;;) {
					do {err = Inhr1_RecvChar(&c);
					} while (err != ERR_OK);

					/* TODO
					 * Spindle Speed starts on zero but when + is pressed
					 * it goes straight to max speed until speedCount gets to max,
					 * then it behaves correctly
					 * I can't figure out why??
					 */

					if (c == '+') {
						spindleSpeed = change_ratio(spindleSpeed, 1);
						SpindleSpeed_SetRatio16(spindleSpeed);
						if (speedCount < 5) {
							speedCount++;
						}
						else {
							speedCount = 5;
						}
					}
					else if (c == '-') {
						spindleSpeed = change_ratio(spindleSpeed, 0);
						SpindleSpeed_SetRatio16(spindleSpeed);
						if (speedCount > 0) {
							speedCount--;
						}
						else {
							speedCount = 0;
						}
					}

					else if ((c == 'q') || (c == 'Q')) {
						text("... Quitting Manual Control ...", 0, 16, 0);
						return_to_start();
						break;
					}


					// X Stepper is PTD4, X Direction is PTA5
					else if ((c == 'w') || (c == 'W')) {
						XDirection_SetVal();
						if (xPosition < 70) {
							for (counter = 0; counter < 20000; counter++) {
								XStepper_SetRatio16(0xFFFF);
							}
							XStepper_SetRatio16(0x0000);
							xPosition++;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}


					else if ((c == 's') || (c == 'S')) {
						XDirection_ClrVal();
						if (xPosition > 0) {
							for (counter = 0; counter < 20000; counter++) {
								XStepper_SetRatio16(0xFFFF);
							}
							XStepper_SetRatio16(0x0000);
							xPosition--;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}


					// Y Stepper is PTA1, Y Direction is PTC8
					else if ((c == 'e') || (c == 'E')) {
						YDirection_ClrVal();
						if (yPosition < 45) {
							for (counter = 0; counter < 20000; counter++) {
								YStepper_SetRatio16(0xFFFF);
							}
							YStepper_SetRatio16(0x0000);
							yPosition++;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}
					else if ((c == 'd') || (c == 'D')) {
						YDirection_SetVal();
						if (yPosition > 0) {
							for (counter = 0; counter < 20000; counter++) {
								YStepper_SetRatio16(0xFFFF);
							}
							YStepper_SetRatio16(0x0000);
							yPosition--;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}


					// Z Stepper is PTC3, Z Direction is PTC4
					else if ((c == 'r') || (c == 'R')) {
						ZDirection_SetVal();
						if (zPosition < 20) {
							for (counter = 0; counter < 20000; counter++) {
								ZStepper_SetRatio16(0xFFFF);
							}
							ZStepper_SetRatio16(0x0000);
							zPosition++;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}
					else if ((c == 'f') || (c == 'F')) {
						ZDirection_ClrVal();
						if (zPosition > 0) {
							for (counter = 0; counter < 20000; counter++) {
								ZStepper_SetRatio16(0xFFFF);
							}
							ZStepper_SetRatio16(0x0000);
							zPosition--;
						}
						else {
							// do nothing
							display_boundary_message();
						}
					}

					if (speedCount == 0) {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clBlack);
						Term1_SendStr("                 ");
						text("Speed:  0", 9, 9, 0);
						text("--OFF--", 10, 10, 0);
					}
					else if (speedCount == 1) {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clRed);
						Term1_SendStr("   ");
						Term1_MoveTo(8, 12);
						Term1_SetColor(clBlack, clBlack);
						Term1_SendStr("              ");
						text("Speed:  1", 9, 9, 0);
						text("        ", 10, 10, 0);
					}
					else if (speedCount == 2) {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clRed);
						Term1_SendStr("      ");
						Term1_MoveTo(11, 12);
						Term1_SetColor(clBlack, clBlack);
						Term1_SendStr("           ");
						text("Speed:  2", 9, 9, 0);
						text("        ", 10, 10, 0);
					}
					else if (speedCount == 3) {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clRed);
						Term1_SendStr("          ");
						Term1_MoveTo(15, 12);
						Term1_SetColor(clBlack, clBlack);
						Term1_SendStr("       ");
						text("Speed:  3", 9, 9, 0);
						text("        ", 10, 10, 0);
					}
					else if (speedCount == 4) {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clRed);
						Term1_SendStr("             ");
						Term1_MoveTo(18, 12);
						Term1_SetColor(clBlack, clBlack);
						Term1_SendStr("    ");
						text("Speed:  4", 9, 9, 0);
						text("        ", 10, 10, 0);
					}
					else {
						Term1_MoveTo(5, 12);
						Term1_SetColor(clBlack, clRed);
						Term1_SendStr("                 ");
						text("Speed:  5", 9, 9, 0);
						text("--MAX--", 10, 10, 0);
					}

//					// Update x position display
//					Term1_MoveTo(15, 5);
//					Term1_SendStr("    ");
//					Term1_MoveTo(15, 5);
//	    			Term1_SendNum(xPosition);
//
//	    			// Update y position display
//					Term1_MoveTo(15, 6);
//					Term1_SendStr("    ");
//	    			Term1_MoveTo(15, 6);
//	    			Term1_SendNum(yPosition);
//
//	    			//Update z position display
//					Term1_MoveTo(15, 7);
//					Term1_SendStr("    ");
//	    			Term1_MoveTo(15, 7);
//	    			Term1_SendNum(zPosition);

					update_position_displays(xPosition, yPosition, zPosition);

					text("Enter Key:         ", 0, 16, 0);
					text("> ", 0, 17, 0);
					Term1_MoveTo(3, 17);
			}
		}



		else if((c == 'c') || (c == 'C')) {
			// Coordinate Control
			Term1_Cls();
			text("CC2511 Group 4 - Assignment 2", 0, 0, 2);
			create_box(0, 3, 25, 3, 25, 14, 0, 14);
			create_box(28, 3, 60, 3, 60, 14, 28, 14);

			text("+-----Tool Location-----+", 0, 3, 1);
			text("X:   20", 9, 5, 0);
			text("Y:   50", 9, 6, 0);
			text("Z:   16", 9, 7, 0);
			text("Speed: 0", 8, 9, 0);

			text("+----Coordinate Control----+", 28, 3, 1);
			text("Enter the following command:", 31, 5, 0);

			text("Enter Code: ", 0, 16, 0);
			text("> ", 0, 17, 0);
			Term1_MoveTo(3, 17);
		}

		else {
			// Invalid Entry
			Term1_Cls();
			text("Invalid Option, Try Again!", 0, 4, 0);
			text("Manual Control (m) or Coordinate Control (c) ?", 0, 5, 0);
			text(">> ", 0, 6, 0);
			Term1_MoveTo(3, 6);
		}

	  	  Term1_SendChar(c);
	}

		/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
  }
