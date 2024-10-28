#include"../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include<util/delay.h>
#include"HSTEPPER_Interface.h"
#include"HSTEPPER_Config.h"
#include"HSTEPPER_Private.h"


void HSTEPPER_VidInit (STEPPER_t * Copy_Stepper )
{
	/*Setting Direction of Both Pins as Output*/
	MDIO_Error_State_SetPinDirection(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_OUTPUT);
}

void HSTEPPER_VidFullStepAntiClockwiseSequence (STEPPER_t * Copy_Stepper, u8 Copy_u8TimeDelay)
{
	if (Copy_u8TimeDelay >=1)
	{

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);

		_delay_ms(Copy_u8TimeDelay);


		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
		_delay_ms(Copy_u8TimeDelay);

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
		_delay_ms(Copy_u8TimeDelay);

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_LOW);

		_delay_ms(Copy_u8TimeDelay);
	}
	else
	{
		/*Do Nothing*/
		}


}

void HSTEPPER_VidFullStepClockwiseSequence (STEPPER_t * Copy_Stepper , u8 Copy_u8TimeDelay)
{
	if (Copy_u8TimeDelay >=1)
	{
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_LOW);
		_delay_ms(Copy_u8TimeDelay);

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
		_delay_ms(Copy_u8TimeDelay);

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
		_delay_ms(Copy_u8TimeDelay);

		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_LOW);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
		MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
		_delay_ms(Copy_u8TimeDelay);

	}
	else
	{
		/*Do Nothing*/


	}


}

void HSTEPPER_VidStop (STEPPER_t * Copy_Stepper)
{
	MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin1,Copy_Stepper->Copy_u8Pin1Port,PIN_HIGH);
	MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin2,Copy_Stepper->Copy_u8Pin2Port,PIN_HIGH);
	MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin3,Copy_Stepper->Copy_u8Pin3Port,PIN_HIGH);
	MDIO_Error_State_SetPinValue(Copy_Stepper->Copy_u8Pin4,Copy_Stepper->Copy_u8Pin4Port,PIN_HIGH);
}

void HSTEPPER_VidGoToAngle (STEPPER_t * Copy_Stepper , u16 Copy_u16DesiredAngle , u8 Copy_u8Direction , u8 Copy_u8TimeDelay)
{
	/*Calculates Number of Full Steps Needed To reach Desired Angle
	 * 1 Full Speed 		=====> 		0.176 degrees
	 * No of Steps required =======> Desired Angle
	 * No of Steps Required = Desired Angle / 0.176  */

	u16 Loc_u16_Steps_Required = Copy_u16DesiredAngle/0.176  ;

	/*Adding One To Compensate for the Fraction Neglected due to using integer variables*/
	u16 Loc_u16_SequenceIterations = Loc_u16_Steps_Required/4+1 ;
	u16 Loc_u8_Counter  ;

	switch (Copy_u8Direction)
	{
	case HSTEPPER_ANTICLOCKWISE:
		for(Loc_u8_Counter=Loc_u16_SequenceIterations ; Loc_u8_Counter>0 ; Loc_u8_Counter--)
		{
			HSTEPPER_VidFullStepAntiClockwiseSequence(Copy_Stepper ,Copy_u8TimeDelay)  ;
		}
		break  ;
	case HSTEPPER_CLOCKWISE:
		for(Loc_u8_Counter=Loc_u16_SequenceIterations ; Loc_u8_Counter>0 ; Loc_u8_Counter--)
		{
			HSTEPPER_VidFullStepClockwiseSequence(Copy_Stepper ,Copy_u8TimeDelay)  ;
		}
		break  ;
	default :
		/*Do Nothing */
		break  ;
	}
}



void HSTEPPER_VidRotateCycles(STEPPER_t * Copy_Stepper , u8 Copy_u8NoOfCycles , u8 Copy_u8Direction , u8 Copy_u8TimeDelay)
{
	u8 Loc_u8_Counter;
	for(Loc_u8_Counter=0;Loc_u8_Counter<Copy_u8NoOfCycles;Loc_u8_Counter++)
	{
		HSTEPPER_VidGoToAngle(Copy_Stepper,360,Copy_u8Direction,Copy_u8TimeDelay);
	}
}
