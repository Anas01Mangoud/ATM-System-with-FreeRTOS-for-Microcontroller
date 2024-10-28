/*This Driver is written by me as an assignment
 * it is written to control a uni-polar Stepper Motor 28byj48 */
#ifndef HSTEPPER_INTERFACE_H 
#define HSTEPPER_INTERFACE_H 

#define HSTEPPER_ANTICLOCKWISE 1
#define HSTEPPER_CLOCKWISE 2

/*Creating a Struct to define the Stepper Motor Datatype */
typedef struct
{
	/*The Stepper Motor Have 4 Pins that are activated*/
	u8 Copy_u8Pin1  ;
	u8 Copy_u8Pin1Port ;

	u8 Copy_u8Pin2  ;
	u8 Copy_u8Pin2Port ;

	u8 Copy_u8Pin3  ;
	u8 Copy_u8Pin3Port ;

	u8 Copy_u8Pin4   ;
	u8 Copy_u8Pin4Port ;

}STEPPER_t ;

void HSTEPPER_VidInit (STEPPER_t * Copy_Stepper)  ;

/*Rotate AntiClockwise*/
void HSTEPPER_VidFullStepAntiClockwiseSequence (STEPPER_t * Copy_Stepper, u8 Copy_u8TimeDelay);

/*Rotate Clockwise*/
void HSTEPPER_VidFullStepClockwiseSequence (STEPPER_t * Copy_Stepper , u8 Copy_u8TimeDelay) ;
void HSTEPPER_VidStop (STEPPER_t * Copy_Stepper) ;

void HSTEPPER_VidGoToAngle (STEPPER_t * Copy_Stepper , u16 Copy_u16DesiredAngle , u8 Copy_u8Direction , u8 Copy_u8TimeDelay);

void HSTEPPER_VidRotateCycles(STEPPER_t * Copy_Stepper , u8 Copy_u8NoOfCycles , u8 Copy_u8Direction , u8 Copy_u8TimeDelay);



#endif 
