/*
 * main.c
 *
 *  Created on: Aug 30, 2023
 *      Author: user
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEY_PAD/KP_int.h"
#include <util/delay.h>

int main(void)
{
	u8  L_u8Num        = 255 ;
	u32 L_u32EnterPass = 0 ;
	u32 L_u32CheckPass = 1234 ;
	u8 col = 1 ;
	u8 Max_enter = 0 ;
	HLCD_voidInit() ;
	HKP_voidKpInt() ;
	HLCD_voidDispStr((u8*)"Enter Your pass:") ;
	HLCD_voidMovCursor(2,1) ;
	while(1)
	{
		L_u8Num = HKP_u8GetPressedKey() ;
		if (L_u8Num >= '0' && L_u8Num <= '9' && Max_enter < 10)
		{
			L_u32EnterPass *= 10 ;
			L_u32EnterPass += L_u8Num - '0' ;
			HLCD_voidDispStr((u8*)"*") ;
			col ++ ;
			Max_enter ++ ;
		}
		if (L_u8Num == '-')
		{
			col -- ;
			Max_enter -- ;
			L_u32EnterPass /= 10 ;
			HLCD_voidMovCursor(2,col) ;
			HLCD_voidDispStr((u8*)" ") ;
			HLCD_voidMovCursor(2,col) ;
		}
		if (L_u8Num == '=' && L_u32EnterPass == L_u32CheckPass)
		{
			HLCD_voidClrScreen() ;
			HLCD_voidDispStr((u8*)"Correct pass") ;
			L_u8Num        = 255 ;
			L_u32EnterPass = 0 ;
			col = 1 ;
			Max_enter = 0 ;
			_delay_ms(1000) ;
			HLCD_voidClrScreen() ;
		}
		else if (L_u8Num == '=' && L_u32EnterPass != L_u32CheckPass)
		{
			HLCD_voidClrScreen() ;
			HLCD_voidDispStr((u8*)"Wrong pass") ;
			L_u8Num        = 255 ;
			L_u32EnterPass = 0 ;
			col = 1 ;
			Max_enter = 0 ;
			_delay_ms(1000) ;
			HLCD_voidClrScreen() ;
			HLCD_voidDispStr((u8*)"Enter Your pass:") ;
			HLCD_voidMovCursor(2,1) ;
		}
	}
	return 0;
}
