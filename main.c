/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: 
 */
#include "LIB/LSTD_TYPES.h"

#include "MCAL/MDIO/MDIO_Interface.h"

#include "HAL/HCLCD/HCLCD_Interface.h"
#include "HAL/HKPD/HKPD_Interface.h"
#include"HAL/HSTEPPER/HSTEPPER_Interface.h"

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/queue.h"

/* Definitions */
/***** Button Definitions *****/
#define BTN_PRESSED			0
#define BTN_NOT_PRESSED		1

/***** LCD Definitions *****/
#define LCD_INIT						0
#define LCD_USER_DATA_ID				1
#define LCD_USER_DATA_PASS				2
#define LCD_WRONG_ID					3
#define LCD_WRONG_PASS					4
#define LCD_DRAW_OPTION					6
#define LCD_BANK_BALANCE_NOT_ENOUGH		8
#define LCD_USER_BALANCE_NOT_ENOUGH		9
#define LCD_BALANCE_AFTER_DRAW			10
#define LCD_PROCESS_DONE				11

/***** Keypad Definitions *****/
#define KEYPAD_ID						0
#define KEYPAD_PASS						1
#define KEYPAD_MAIN_OPTIONS				2
#define KEYPAD_FAWRY_OPTIONS			3
#define KEYPAD_PHONE					4
#define KEYPAD_DRAW_VALUE				5


/* Test Data Base */
typedef struct{
	u8 id;
	u16 pass;
	u16 Balance;
}user_t;

typedef struct{
	u32 Total_Balance;
	u8 _200_Papers;
	u8 _100_Papers;
	u16 _50_Papers;
}Bank_t;

Bank_t BANK_DATA = {200000,200,200,2800};

user_t USER_ARR[] = {{10,1111,10000},{20,2222,10000},{30,3333,10000},
		{40,4444,10000},{50,5555,10000}};


/* Semaphore */
xSemaphoreHandle Entry_sem;

/* Queues */
xQueueHandle Keypad_To_LCD_Queue;				// Pressed key		Keypad 				-> LCD
xQueueHandle Keypad_To_CheckData_Queue1;		// Id				keypad 				-> checking data
xQueueHandle Keypad_To_CheckData_Queue2;		// Pass				keypad 				-> checking data
xQueueHandle Keypad_To_CheckBalance_Queue;		// Draw value		keypad 				-> checking balance
xQueueHandle CheckData_To_Balance_Queue;		// Location			checking data 		-> checking balance
xQueueHandle CheckBalance_To_Calculation_Queue; // Draw value		checking balance	-> calculation


/* Tasks */
void Credit_Entry_Button(void *pv);
void Get_Pressed_Key(void *pv);
void Check_User_Data(void *pv);
void Check_Balance(void *pv);
void Calc(void *pv);
void LCD_Display(void *pv);
void APP_Output_Money(void *pv);

/* Global Flags */
u8 LCD_FLAG = LCD_INIT;
u8 KEYPAD_FLAG ;

/* Global variables */
u8 _200_papers =  0;
u8 _100_papers =  0;
u16 _50_papers =  0;

STEPPER_t Stepper={PIN1,MDIO_PORTC,PIN2,MDIO_PORTC,PIN3,MDIO_PORTC,PIN4,MDIO_PORTC} ;

int main(void)
{
	/* DIO_Initialization */
	MDIO_Error_State_SetPinDirection(PIN0,MDIO_PORTC,PIN_INPUT);
	/* In case of simulation */
	MDIO_Error_State_SetPinValue(PIN0,MDIO_PORTC,PIN_HIGH);
	MDIO_Error_State_SetPinDirection(PIN5,MDIO_PORTC,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN6,MDIO_PORTC,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN7,MDIO_PORTC,PIN_OUTPUT);

	/* Initialize Stepper*/
	HSTEPPER_VidInit(&Stepper);

	/* Initialize LCD */
	HCLCD_Vid4Bits_Init();

	/* Initialize Keypad */
	HKPD_VidInit();

	/* Create Semaphore */
	Entry_sem =xSemaphoreCreateCounting(1,0);

	/* Create Queues */
	Keypad_To_LCD_Queue 		 		= xQueueCreate(1,sizeof(u8));
	Keypad_To_CheckData_Queue1   		= xQueueCreate(1,sizeof(u8));
	Keypad_To_CheckData_Queue2  		= xQueueCreate(1,sizeof(u16));
	Keypad_To_CheckBalance_Queue 		= xQueueCreate(1,sizeof(u32));
	CheckData_To_Balance_Queue 			= xQueueCreate(1,sizeof(u8));
	CheckBalance_To_Calculation_Queue 	= xQueueCreate(1,sizeof(u32));

	/* Create_Tasks */
	xTaskCreate(LCD_Display			  ,NULL,150,NULL,2,NULL);
	xTaskCreate(Credit_Entry_Button   ,NULL,50 ,NULL,0,NULL);
	xTaskCreate(Get_Pressed_Key  	  ,NULL,100,NULL,1,NULL);
	xTaskCreate(Check_User_Data  	  ,NULL,100,NULL,3,NULL);
	//xTaskCreate(Check_Balance	 	  ,NULL,100,NULL,4,NULL);
	//xTaskCreate(Calc	  			  ,NULL,120,NULL,5,NULL);
	//xTaskCreate(APP_Output_Money	  ,NULL,200,NULL,6,NULL);

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}

void Credit_Entry_Button(void*pv)
{
	static u8 Loc_u8Btn_State = BTN_NOT_PRESSED;
	while(1)
	{
		MDIO_Error_State_GetPinValue(PIN0,MDIO_PORTC,&Loc_u8Btn_State);
		if(Loc_u8Btn_State == BTN_PRESSED)
		{
			xSemaphoreGive(Entry_sem);
			LCD_FLAG = LCD_USER_DATA_ID;
			KEYPAD_FLAG = KEYPAD_ID;
		}
		else
		{
			/* Do Nothing */
		}

		vTaskDelay(100);
	}
}

void Get_Pressed_Key(void *pv){

	u8 Loc_u8PressedKey;
	u8 Loc_u8Entry_semState = 2;
	static u8 Loc_u8Entry_count = 1;
	static u8 Loc_u8ID = 0 ;
	static u16 Loc_u16Pass = 0;
	static u32 Loc_u32DrawValue = 0;
	u8 x;

	while(1)
	{

		Loc_u8Entry_semState = xSemaphoreTake(Entry_sem,5);
		if(Loc_u8Entry_semState == pdPASS)
		{
			Loc_u8PressedKey = HKPD_u8GetKeyPressed();

			if(Loc_u8PressedKey != NOT_PRESSED)
			{
				if(Loc_u8PressedKey != '='){
					xQueueSend(Keypad_To_LCD_Queue,&Loc_u8PressedKey,0);
				}
				switch(KEYPAD_FLAG){
				case KEYPAD_ID:
					Loc_u8PressedKey -= 48;
					Loc_u8ID = (Loc_u8ID * 10) + Loc_u8PressedKey;

					Loc_u8Entry_count ++;

					if (Loc_u8Entry_count == 3)
					{

						xQueueSend(Keypad_To_CheckData_Queue1,&Loc_u8ID,0);
						Loc_u8ID = 0;
						Loc_u8Entry_count = 1;
					}
					break;

				case KEYPAD_PASS:
					//HCLCD_VidWriteNumber_4Bits(Loc_u8Entry_count);
					LCD_FLAG  = LCD_USER_DATA_PASS;

					Loc_u8PressedKey -= 48;
					Loc_u16Pass = (Loc_u16Pass * 10) + Loc_u8PressedKey;
					Loc_u8Entry_count ++;
					if (Loc_u8Entry_count == 5)
					{

						x = xQueueSend(Keypad_To_CheckData_Queue2,&Loc_u16Pass,0);
						if(x==pdPASS){
							HCLCD_VidWriteNumber_4Bits(Loc_u16Pass);
						}
						Loc_u8Entry_count = 1;
						Loc_u16Pass = 0;
					}
					break;

				case KEYPAD_DRAW_VALUE:
					LCD_FLAG = LCD_DRAW_OPTION;
					if(Loc_u8PressedKey != '=')
					{
						Loc_u8PressedKey -= 48;
						Loc_u32DrawValue = (Loc_u32DrawValue * 10) + Loc_u8PressedKey;
					}
					else
					{
						xQueueSend(Keypad_To_CheckBalance_Queue,&Loc_u32DrawValue,0);
						Loc_u32DrawValue = 0;
						KEYPAD_FLAG = KEYPAD_ID;
					}
					break;
				}

			}
			xSemaphoreGive(Entry_sem);
		}
		vTaskDelay(100);
	}
}

void Check_User_Data(void *pv){

	u8 Loc_u8QueueState;
	u8 Loc_u8ID = 0;
	u16 Loc_u16Password = 0;
	u8 Loc_u8Location_of_User;
	u8 Loc_u8UserOrder;
	static u8 Loc_u8UserAvailableFlag = 2;

	while(1)
	{
		//Receive ID From the Keypad
		Loc_u8QueueState = xQueueReceive(Keypad_To_CheckData_Queue1,&Loc_u8ID,5);
		if(Loc_u8QueueState == pdPASS)
		{
			//ID Received Successfully
			/*1-Checking ID is Existing*/
			for(Loc_u8UserOrder =0 ; Loc_u8UserOrder < (sizeof(USER_ARR) / sizeof(USER_ARR[0])) ; Loc_u8UserOrder ++)
			{
				if(Loc_u8ID == USER_ARR[Loc_u8UserOrder].id)
				{
					//User is  Found
					Loc_u8UserAvailableFlag = 1;
					//Save The user order form database
					Loc_u8Location_of_User = Loc_u8UserOrder;
					break;
				}
			}

			if(Loc_u8UserAvailableFlag == 2){
				LCD_FLAG = LCD_WRONG_ID;
			}
			else {
				KEYPAD_FLAG = KEYPAD_PASS;
			}
		}

		//Receive Password From the Keypad
		Loc_u8QueueState = xQueueReceive(Keypad_To_CheckData_Queue2,&Loc_u16Password,0);
		if(Loc_u8QueueState == pdPASS)
		{
			//HCLCD_VidWriteNumber_4Bits(Loc_u16Password);
			//ID Received Successfully
			if(Loc_u8UserAvailableFlag == 1)
			{
				//User is Found in Database
				//Check For Password
				if(Loc_u16Password == USER_ARR[Loc_u8Location_of_User].pass)
				{
					//Password matches
					//Send The Successful user ID to Next Stages
					xQueueSend(CheckData_To_Balance_Queue,&Loc_u8Location_of_User,0);
					KEYPAD_FLAG = KEYPAD_DRAW_VALUE;
					//GO On To Next Stage
				}
				else
				{
					//Password is wrong
					LCD_FLAG = LCD_WRONG_PASS;
				}
			}

		}
		vTaskDelay(200);
	}
}

void Check_Balance(void *pv)
{
	u8 Loc_u8QueuState;
	static u32 Loc_u32Draw = 0;
	static u32 Loc_u32Balance;
	static u8 Loc_u8Location_Of_User;

	while(1){
		Loc_u8QueuState = xQueueReceive(Keypad_To_CheckBalance_Queue,&Loc_u32Draw,5);
		if(Loc_u8QueuState == pdPASS){

			Loc_u8QueuState = xQueueReceive(CheckData_To_Balance_Queue,&Loc_u8Location_Of_User,5);
			if(Loc_u8QueuState == pdPASS){
				/* Get User Balance */
				Loc_u32Balance = USER_ARR[Loc_u8Location_Of_User].Balance;
				/* Checking Draw Value */
				if(Loc_u32Draw > BANK_DATA.Total_Balance){
					LCD_FLAG = LCD_BANK_BALANCE_NOT_ENOUGH;
				}

				else if(Loc_u32Draw > Loc_u32Balance){
					LCD_FLAG = LCD_USER_BALANCE_NOT_ENOUGH;
				}

				else
				{
					xQueueSend(CheckBalance_To_Calculation_Queue,&Loc_u32Draw,0);
					xQueueSend(CheckData_To_Balance_Queue,&Loc_u8Location_Of_User,5);
				}

			}
		}
		vTaskDelay(300);
	}
}

void Calc(void *pv)
{
	u8 Loc_u8QueueState  = 0;
	u32 Loc_u32DrawValue = 0;
	static u8 Loc_u8UserLocation = 0;

	while(1){

		Loc_u8QueueState= xQueueReceive(CheckBalance_To_Calculation_Queue,&Loc_u32DrawValue,5);
		if(Loc_u8QueueState == pdPASS){
			Loc_u8QueueState = xQueueReceive(CheckData_To_Balance_Queue,&Loc_u8UserLocation,5);
			if(Loc_u8QueueState == pdPASS){

				BANK_DATA.Total_Balance -= Loc_u32DrawValue;
				USER_ARR[Loc_u8UserLocation].Balance -= Loc_u32DrawValue;
				while((BANK_DATA._200_Papers > 0) && (Loc_u32DrawValue >= 200)){
					_200_papers ++;
					Loc_u32DrawValue -= 200;
					BANK_DATA._200_Papers --;
				}
				while((BANK_DATA._100_Papers > 0) && (Loc_u32DrawValue >= 100)){
					_100_papers ++;
					Loc_u32DrawValue -= 100;
					BANK_DATA._100_Papers --;
				}
				while((BANK_DATA._50_Papers > 0) && (Loc_u32DrawValue >= 50)){
					_50_papers ++;
					Loc_u32DrawValue -= 50;
					BANK_DATA._50_Papers --;
				}
			}
		}
		vTaskDelay(400);
	}
}

void APP_Output_Money(void *pv)
{
	while(1)
	{
		//200 Papers Passed
		MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_HIGH);
		MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_LOW);
		MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_LOW);

		HSTEPPER_VidRotateCycles(&Stepper,_200_papers,HSTEPPER_CLOCKWISE,1);

		//100 Papers Passed
		MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_LOW);
		MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_HIGH);
		MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_LOW);

		HSTEPPER_VidRotateCycles(&Stepper,_100_papers,HSTEPPER_CLOCKWISE,1);

		MDIO_Error_State_SetPinValue(PIN5,MDIO_PORTC,PIN_LOW);
		MDIO_Error_State_SetPinValue(PIN6,MDIO_PORTC,PIN_LOW);
		MDIO_Error_State_SetPinValue(PIN7,MDIO_PORTC,PIN_HIGH);

		HSTEPPER_VidRotateCycles(&Stepper,_50_papers,HSTEPPER_CLOCKWISE,1);

		_100_papers  = 0;
		_200_papers = 0;
		_50_papers = 0;

		vTaskDelay(1000);
	}
}

void LCD_Display(void*pv)
{
	u8 Loc_u8QueueState;
	u8 Loc_u8Pressed_key;
	static u8 pos=4;
	static u8 pos2=6;
	static u8 pos3=10;
	static u8 prev_state = LCD_INIT;
	while(1)
	{
		if (LCD_FLAG !=prev_state)
		{
			HCLCD_VidWriteCommand_4Bits(0x01>>4);
			HCLCD_VidWriteCommand_4Bits(0x01);
		}
		switch(LCD_FLAG)
		{
		case LCD_INIT :
			HCLCD_VidSetPosition_4BitsMode(1,2);
			HCLCD_VidWriteString_4Bits("Welcome to");
			HCLCD_VidSetPosition_4BitsMode(2,3);
			HCLCD_VidWriteString_4Bits("NTI Bank");

			prev_state=LCD_FLAG;
			break;
		case LCD_USER_DATA_ID:

			HCLCD_VidSetPosition_4BitsMode(1,0);
			HCLCD_VidWriteString_4Bits("ID:");
			Loc_u8QueueState=xQueueReceive(Keypad_To_LCD_Queue,&Loc_u8Pressed_key,5);
			prev_state=LCD_FLAG;

			if(Loc_u8QueueState ==pdPASS)
			{

				HCLCD_VidSetPosition_4BitsMode(1,pos);
				pos++ ;
				HCLCD_VidSendChar_4Bits(Loc_u8Pressed_key);
				if(pos == 6)
					pos=4;
			}
			break;

		case LCD_USER_DATA_PASS:
			HCLCD_VidSetPosition_4BitsMode(1,0);
			HCLCD_VidWriteString_4Bits("pass:");
			Loc_u8QueueState=xQueueReceive(Keypad_To_LCD_Queue,&Loc_u8Pressed_key,5);
			prev_state=LCD_FLAG;

			if(Loc_u8QueueState ==pdPASS)
			{

				HCLCD_VidSetPosition_4BitsMode(1,pos2);
				pos2 ++ ;
				HCLCD_VidSendChar_4Bits(Loc_u8Pressed_key);
				if (pos2 == 10)
					pos2 = 6;
			}
			break;

		case LCD_DRAW_OPTION:
			HCLCD_VidSetPosition_4BitsMode(1,0);
			HCLCD_VidWriteString_4Bits("withdraw:");
			Loc_u8QueueState=xQueueReceive(Keypad_To_LCD_Queue,&Loc_u8Pressed_key,5);
			prev_state=LCD_FLAG;

			if(Loc_u8QueueState ==pdPASS)
			{

				HCLCD_VidSetPosition_4BitsMode(1,pos3);
				pos3++ ;
				HCLCD_VidSendChar_4Bits(Loc_u8Pressed_key);
			}

			break;
		case LCD_PROCESS_DONE :
			HCLCD_VidSetPosition_4BitsMode(1,0);
			HCLCD_VidWriteString_4Bits("Process Done.");
			prev_state=LCD_FLAG;
			break;

		case LCD_WRONG_ID:
			HCLCD_VidSetPosition_4BitsMode(1,3);
			HCLCD_VidWriteString_4Bits("Wrong ID");
			prev_state=LCD_FLAG;
			LCD_FLAG = LCD_INIT;
			xSemaphoreTake(Entry_sem,5);
			break;

		case LCD_WRONG_PASS:
			HCLCD_VidSetPosition_4BitsMode(1,3);
			HCLCD_VidWriteString_4Bits("Wrong Password");
			prev_state=LCD_FLAG;
			LCD_FLAG = LCD_INIT;
			xSemaphoreTake(Entry_sem,5);
			break;

			/*	case LCD_USER_BALANCE_NOT_ENOUGH:
			HCLCD_VidSetPosition_4BitsMode(1,0);
			HCLCD_VidWriteString_4Bits("Your Balance is");
			HCLCD_VidSetPosition_4BitsMode(2,2);
			HCLCD_VidWriteString_4Bits("not enough");
			prev_state=LCD_FLAG;
			LCD_FLAG = LCD_INIT;
			xSemaphoreTake(Entry_sem,5);
			break;*/
		}

		vTaskDelay(150);
	}
}
