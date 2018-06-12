/**********************************************************************************************************************
File: anttt.h                                                                
**********************************************************************************************************************/

#ifndef __ANTTTT_H
#define __ANTTTT_H



/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
/* Game flags */
#define _U16_ANTTT_WIN_FLAG             (u16)0x0200

#define U16_ANTTT_DRAW                  (u16)0x1FF
#define U8_AWAY_POSITION_OFFSET         (u8)9

#define ANTTT_DEVICE_TYPE               (u8)20

#define ANTTT_COMMAND_SIZE              (u8)3
#define ANTTT_COMMAND_ID_OFFSET         (u8)0x00
#define ANTTT_COMMAND_POSITION_OFFSET   (u8)0x01
#define ANTTT_COMMAND_SOURCE_OFFSET     (u8)0x02

#define ANTTT_COMMAND_ID_MOVE           (u8)0xCC
#define ANTTT_COMMAND_ID_MOVE_ACK       (u8)0xAC   
#define ANTTT_COMMAND_ID_MOVE_NACK      (u8)0xBC   



#define SCRCC_COMMAND_SIZE              (u8)8

#define SCRCC_COMMAND_FORWARD           (u8)0x00
#define SCRCC_COMMAND_BACKWARD          (u8)0x01
#define SCRCC_COMMAND_LEFT              (u8)0x02
#define SCRCC_COMMAND_RIGHT             (u8)0x03

#define FRONT_LED                       AWAY2
#define BACK_LED                        AWAY4
#define LEFT_LED                        AWAY6
#define RIGHT_LED                       AWAY8

#define EN_LEFT                         AWAY1
#define EN_RIGHT                        HOME1

#define IN_TOP                          AWAY3
#define IN_BOT                          HOME3

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/
typedef enum {ANTTT_POS1 = 0, ANTTT_POS2, ANTTT_POS3, ANTT_POS4, ANTTT_POS5, ANTTT_POS6,
              ANTTT_POS7, ANTTT_POS8, ANTTT_POS9} ANTTT_POSITIONS;


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
void AntttIncomingMessage(u8* pu8Data_, u8 u8Length_);

void ScrccIncomingMessage(u8* pu8Data_, u8 u8Length_);

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void AntttInitialize(void);
void AntttHandleIncomingMessage(u8* pu8Data_, u8 u8Length_);

void ScrccHandleIncomingMessage(u8* pu8Data_, u8 u8Length_);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
static bool AntttIsGameOver(void);
static void Anttt_reset_rx_buffer(void);

static void Scrcc_reset_rx_buffer(void);



/*--------------------------------------------------------------------------------------------------------------------*/
/* SM functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
static void AntttSM_Idle(void);
static void AntttSM_Wait(void);
static void AntttSM_Active(void);
static void AntttSM_Gameover(void);

static void ScrccSM_Idle(void);
static void ScrccSM_Wait(void);
static void ScrccSM_Active(void);

static void Scrcc_Forward(void);
static void Scrcc_Backward(void);
static void Scrcc_LeftTurn(void);
static void Scrcc_RightTurn(void);

#endif /* __ANTTT_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
