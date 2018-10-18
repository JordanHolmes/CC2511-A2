/* ###################################################################
 **     Filename    : main.c
 **     Project     : Assignment 2
 **     Processor   : MK20DX128VLH5
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2018-10-12, 09:24, # CodeGen: 0
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
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */

	/* Attempt at simplifying box functions*/
//	void hor_line(add, x, y, length) {
//		do {
//			Term1_MoveTo(x, y);
//			Term1_SetColor(clBlack, clYellow);
//			Term1_SendStr(" ");
//			if (add == 1) {
//				x += 1;
//			} else {
//				x -= 1;
//			}
//		} while (x != length);
//	}
//
//	void ver_line(add, x, y, length) {
//		do {
//			Term1_MoveTo(x, y);
//			Term1_SetColor(clBlack, clYellow);
//			Term1_SendStr(" ");
//			if (add == 1) {
//				y += 1;
//			} else {
//				y -= 1;
//			}
//		} while (y != length);
//	}
	/*Functions from week 7 */
	void hor_liner(x_pos, y_pos, length){
		  do {
			  Term1_MoveTo(x_pos, y_pos);
			  Term1_SetColor(clBlack, clYellow);
			  Term1_SendStr(" ");
			  x_pos += 1;
			  } while (x_pos <= length);
	  }
	  	  void ver_lined(x_pos, y_pos, length){
		  do {
			  Term1_MoveTo(x_pos, y_pos);
			  Term1_SetColor(clBlack, clYellow);
			  Term1_SendStr(" ");
			  y_pos += 1;
			  } while (y_pos <= length);
	  }
	  	  void hor_linel(x_pos, y_pos, length){
		  do {
			  Term1_MoveTo(x_pos, y_pos);
			  Term1_SetColor(clBlack, clYellow);
			  Term1_SendStr(" ");
			  x_pos -= 1;

			  } while (x_pos >= length);
	  }
	  	  void ver_lineu(x_pos, y_pos, length){
		  do {
			  Term1_MoveTo(x_pos, y_pos);
			  Term1_SetColor(clBlack, clYellow);
			  Term1_SendStr(" ");
			  y_pos -= 1;
			  } while (y_pos >= length);
	  }

	  	  /*Function to create box*/
	  	  void create_box(tlx, tly, trx, try, brx, bry, blx, bly) {
	  		  hor_liner(tlx, tly, trx);
	  		  ver_lined(trx, try, bry);
	  		  hor_linel(brx, bry, blx);
	  		  ver_lineu(blx, bly, tly);
	  	  }

	  	  void text(text, x_pos, y_pos, title){
	  		  Term1_MoveTo(x_pos, y_pos);
	  		  if (title == 1){
	  			  Term1_SetColor(clBlack, clYellow);
	  		  } else if (title == 0){
	  			  Term1_SetColor(clWhite, clBlack);
	  		  } else {
	  			  Term1_SetColor(clYellow, clBlack);
	  		  }
	  		  Term1_SendStr(text);
	  	  }


	  	  /*Initial set up*/
	  	  text("CC2511 Assignment 2", 0, 0, 2);

	  	  create_box(0, 3, 19, 3, 19, 14, 0, 14);
	  	  create_box(22, 3, 50, 3, 50, 14, 22, 14);
	  	  create_box(52, 3, 80, 3, 80, 14, 52, 14);

	  	  text("+--Tool Location--+", 0, 3, 1);
		  text("X:   20", 6, 5, 0);
	  	  text("Y:   50", 6, 6, 0);
	  	  text("Z:   16", 6, 7, 0);
	  	  text("Speed: 0", 5, 10, 0);

	  	  text("+------Manual Control------+", 22, 3, 1);
	  	  text("W - Decrease x-axis value", 23, 5, 0);
	  	  text("S - Increase x-axis value", 23, 6, 0);
	  	  text("A - Decrease y-axis value", 23, 7, 0);
	  	  text("D - Increase y-axis value", 23, 8, 0);
	  	  text("K - Decrease z-axis value", 23, 9, 0);
	  	  text("I - Increase z-axis value", 23, 10, 0);
	  	  text("J - Decrease speed value", 23, 11, 0);
	  	  text("L - Increase speed value", 23, 12, 0);

	  	  text("+---Directional  Control---+", 52, 3, 1);
	  	  text("Use the following commands", 53, 5, 0);
	  	  text("> x: n - Change x-axis to n", 53, 7, 0);
	  	  text("> y: n - Change y-axis to n", 53, 8, 0);
		  text("> z: n - Change z-axis to n", 53, 9, 0);
		  text("> Speed: n - Set speed to n", 53, 10, 0);

	  	  text("Command prompt: ", 0, 16, 0);
	  	  text("> ", 0, 17, 0);
	  	  Term1_MoveTo(3, 17);

	  	  byte c, err;
	  	  for(;;){
	  		  do {
	  		  err = Inhr1_RecvChar(&c);
	  	  } while (err != ERR_OK);
	  	  Term1_SendChar(c);
	  	  }
		/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
		/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
		PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
		/*** End of RTOS startup code.  ***/
		/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
		for (;;) {
		}
		/*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
	} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

	/* END main */
	/*!
	 ** @}
	 */
	/*
	 ** ###################################################################
	 **
	 **     This file was created by Processor Expert 10.5 [05.21]
	 **     for the Freescale Kinetis series of microcontrollers.
	 **
	 ** ###################################################################
	 */