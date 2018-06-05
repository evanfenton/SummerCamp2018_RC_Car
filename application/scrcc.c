/**********************************************************************************************************************
File: scrcc.c                                                                

Description:
Implements RC Car with direct connection or ANT



**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xxScrcc"
***********************************************************************************************************************/
/* New variables */
u32 G_u32ScrccFlags;                                     /* Global state flags */
fnCode_type SCRCC_SM;

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */
extern volatile u32 G_u32BPEngenuicsFlags;             /* From bleperipheral_engenuics.c  */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Scrcc_" and be declared as static.
***********************************************************************************************************************/
static u32 Scrcc_u32Timeout;                             /* Timeout counter used across states */

static u32 Scrcc_u32CyclePeriod;                         /* Current base time for Scrcc modulation */

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*
Function: ScrccInitialize(void)

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void ScrccInitialize(void)
{
  
#if 1
  /* TEST CODE TO TEST BUTTONS */
  for (u8 i = 0; i < TOTAL_BUTTONS; i++)
  {
   if (WasButtonPressed(i))
   {
     LedToggle(STATUS_RED);
     ButtonAcknowledge(i);
     
   }
  }
#endif
  
  
  LedOn(STATUS_RED);
  LedOn(STATUS_YLW);
  LedOn(STATUS_GRN);
  
  nrf_gpio_pin_clear(16);             //FIND OUT WHAT THIS IS 
  
  SCRCC_SM = &ScrccSM_Idle;
  
} /* end ScrccInitialize(void) */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
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
    
   LedPWM(EN_LEFT, LED_PWM_100);              /* turn both motors on */
   LedPWM(EN_RIGHT, LED_PWM_100);
    
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
    
   LedPWM(EN_LEFT, LED_PWM_100);              /* turn both motors on */
   LedPWM(EN_RIGHT, LED_PWM_100);
    
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
    
   LedPWM(EN_LEFT, LED_PWM_0);              /* turn left motor off right motor on */
   LedPWM(EN_RIGHT, LED_PWM_100);
    
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
    
   LedPWM(EN_LEFT, LED_PWM_100);              /* turn right motor off left motor on */
   LedPWM(EN_RIGHT, LED_PWM_0);
    
   LedOff(IN_TOP);              /* signals for forward rotation */
   LedOn(IN_BOT);
    
} /* end Scrcc_RightTurn() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* State Machine definitions                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------


/*
Function: ScrccSM_Idle(void)

Description:
robot is waiting for user input

Requires:
  -

Promises:
  - 
*/
static void ScrccSM_Idle(void)
{
  LedOff(RIGHT_LED);            /* all Led's are off */
  LedOff(FRONT_LED);
  LedOff(BACK_LED);
  LedOff(LEFT_LED);
   
  LedPWM(EN_LEFT, LED_PWM_0);              /* make sure motors are off */
  LedPWM(EN_RIGHT, LED_PWM_0);
  
  ButtonInitialize();
  
  SCRCC_SM = ScrccSM_Active;
  
} /* end ScrccSM_Idle(void) */


/*
Function: ScrccSM_Active(void)

Description:
reacts to user input

Requires:
  -

Promises:
  - 
*/
static void ScrccSM_Active(void)
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
    SCRCC_SM = ScrccSM_Idle;
  }
  
  /* For the RC Car student guide
  
  Within the Super Loop 
  
  if(                               )
  {
    GoForward();
  }
  else if(                                )
  {
    GoBackward();
  }
  else if(                                )
  {
    TurnLeft();
  }
  else if(                                )
  {
    TurnRight();
  }
  else
  {
    NoAction();
  }
  
  */
  
  /* For the RC Car function section
  
  Fill in with the name of your function 
  
  void                  (void)
  {
    
    
  
    
  
  
   
             
  
  
  
  
  
  
  }  end */
  
  
} /* end ScrccSM_Active(void) */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
