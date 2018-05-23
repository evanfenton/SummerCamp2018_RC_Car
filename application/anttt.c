/**********************************************************************************************************************
File: anttt.c                                                                

Description:
Implements TIC-TAC-TOE using data input from ANT or BLE.



**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xxAnttt"
***********************************************************************************************************************/
/* New variables */
u32 G_u32AntttFlags;                                     /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Anttt_" and be declared as static.
***********************************************************************************************************************/
static u32 Anttt_u32Timeout;                             /* Timeout counter used across states */

static u32 Anttt_u32CyclePeriod;                         /* Current base time for Anttt modulation */

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*
Function: Scrcc_Forward()

Description:
sends appropriate signals to robot for forward movement

Requires:
  -

Promises:
  - 
*/
static void Scrcc_Forward(void)
{
   LedOn(FRONT_LED);            /* visual confirmation */
   LedOff(RIGHT_LED);
   LedOff(BACK_LED);
   LedOff(LEFT_LED);
    
   LedOn(EN_LEFT);              /* turn both motors on */
   LedOn(EN_RIGHT);
    
   LedOff(IN_TOP);              /* signals for forward rotation */
   LedOn(IN_BOT);
    
} /* end Scrcc_Forward() */


/*
Function: Scrcc_Backward()

Description:
sends appropriate signals to robot for backward movement

Requires:
  -

Promises:
  - 
*/
static void Scrcc_Backward(void)
{
   LedOn(BACK_LED);             /* visual confirmation */
   LedOff(FRONT_LED);
   LedOff(RIGHT_LED);
   LedOff(LEFT_LED);
    
   LedOn(EN_LEFT);              /* turn both motors on */
   LedOn(EN_RIGHT);
    
   LedOn(IN_TOP);               /* signals for backward rotation */
   LedOff(IN_BOT);
    
} /* end Scrcc_Backward() */


/*
Function: Scrcc_LeftTurn()

Description:
sends appropriate signals to robot for left turn

Requires:
  -

Promises:
  - 
*/
static void Scrcc_LeftTurn(void)
{
   LedOn(LEFT_LED);              /* visual confirmation */
   LedOff(FRONT_LED);
   LedOff(BACK_LED);
   LedOff(RIGHT_LED);
    
   LedOff(EN_LEFT);              /* turn left motor off right motor on */
   LedOn(EN_RIGHT);
    
   LedOff(IN_TOP);               /* signals for forward rotation */
   LedOn(IN_BOT);
    
} /* end Scrcc_LeftTurn() */


/*
Function: Scrcc_RightTurn()

Description:
sends appropriate signals to robot for right turn

Requires:
  -

Promises:
  - 
*/
static void Scrcc_RightTurn(void)
{
   LedOn(RIGHT_LED);            /* visual confirmation */
   LedOff(FRONT_LED);
   LedOff(BACK_LED);
   LedOff(LEFT_LED);
    
   LedOn(EN_LEFT);              /* turn right motor off left motor on */
   LedOff(EN_RIGHT);
    
   LedOff(IN_TOP);              /* signals for forward rotation */
   LedOn(IN_BOT);
    
} /* end Scrcc_RightTurn() */



/*
Function: Scrcc_Standby()

Description:
turns robot "off" while it waits for the users commands

Requires:
  -

Promises:
  - 
*/
static void Scrcc_Standby(void)
{
   LedOff(RIGHT_LED);            /* all Led's are off */
   LedOff(FRONT_LED);
   LedOff(BACK_LED);
   LedOff(LEFT_LED);
   
   LedOff(EN_LEFT);              /* make sure motors are off */
   LedOff(EN_RIGHT);
   
} /* end Scrcc_Standby() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: AntttInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void AntttInitialize(void)
{
  Scrcc_Standby();
 
} /* end AntttInitialize() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------------------------------------------------*/
/* State Machine definitions                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: AntttSM_Idle
*/
void AntttSM_Idle(void)
{
  
  if(IsButtonPressed(BUTTON_F)){
    Scrcc_Forward();
  }
  else if(IsButtonPressed(BUTTON_B)){
    Scrcc_Backward();
  }
  else if(IsButtonPressed(BUTTON_L)){
    Scrcc_LeftTurn();
  }
  else if(IsButtonPressed(BUTTON_R)){
    Scrcc_RightTurn();
  }
  else{
    Scrcc_Standby();
  }
  
} /* end AntttSM_Idle() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
