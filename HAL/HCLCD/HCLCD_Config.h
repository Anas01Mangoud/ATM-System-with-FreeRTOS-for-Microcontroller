

/*Configure RS,RW,E pin -->(PIN0 TO PIN7)*/
#define RS  PIN1
#define RW  PIN7
#define E   PIN2

/*Configure Control port -->(MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)*/
#define CONTROL_PORT   MDIO_PORTA

/*Configure Data port -->(MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD) */  
#define DATA_PORT      MDIO_PORTA

#define HCLCD_PINSTART  PIN3
#define HCLCD_PINEND    PIN6

/*Function set options:
* 1- FUNCTION_SET_8BITS_2LINES
* 2- FUNCTION_SET_8BITS_1LINES
* 3- FUNCTION_SET_4BITS_2LINES
* 4- FUNCTION_SET_4BITS_1LINES
*/
#define HCLCD_FUNCTION_SET    FUNCTION_SET_4BITS_2LINES

/*DISPLAY ON OFF options:
* 1- DISPLAY_ON_CURSOR_ON_BLINKING_ON
* 2- DISPLAY_ON_CURSOR_ON_BLINKING_OFF
* 3- DISPLAY_ON_CURSOR_OFF
* 4- DISPLAY_OFF
*/

#define HCLCD_DISPLAY_ON_OFF   DISPLAY_ON_CURSOR_ON_BLINKING_ON  

/*HCLCD ENTRY MODE SET Options:
* 1- ENTRY_MODE_SET_INCREASE_WITH_SHIFT
* 2- ENTRY_MODE_SET_INCREASE
* 3- ENTRY_MODE_SET_DECREASE_WITH_SHIFT
* 4- ENTRY_MODE_SET_DECREASE
*/
#define HCLCD_ENTRY_MODE_SET  ENTRY_MODE_SET_INCREASE 
 
