/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: CLCD			  *******************/
/*************** Date: 12/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef CLCD_PRAVITE_H_
#define CLCD_PRAVITE_H_

#define MODE_8_BIT	  	8
#define MODE_4_BIT		4

#define  CLCD_SET_DDRAM_COMMAND        128   // AC Command is    1  Ac7--------Ac0 Look Page 16 in datasheet
#define  CLCD_SET_DDRAM_ROW1    	   64    //0x40  the first position in Line Two
#define  CLCD_SET_CGRAM_ADDRESS		   64
#endif /* CLCD_PRAVITE_H_ */
