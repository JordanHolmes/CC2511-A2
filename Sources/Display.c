/*
 * Display.c
 */

#include "Display.h"
#include "PE_Types.h"
#include "Term1.h"
#include "stdbool.h"


// Functions to create box lines
void hor_liner(x_pos, y_pos, length) {
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
