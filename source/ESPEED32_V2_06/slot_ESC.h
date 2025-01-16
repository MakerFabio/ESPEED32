#ifndef SLOT_ESC_H_
#define SLOT_ESC_H_

/*********************************************************************************************************************/
/*------------------------------------------------------Includes-----------------------------------------------------*/
/*********************************************************************************************************************/
#include <OneBitDisplay.h>
#include <AiEsp32RotaryEncoder.h>
#include <AiEsp32RotaryEncoderNumberSelector.h>

#include "half_bridge.h"
#include "HAL.h"
#include <Preferences.h>

/*********************************************************************************************************************/
/*-------------------------------------------------------Macros------------------------------------------------------*/
/*********************************************************************************************************************/

#define MENU_ITEMS_COUNT    7   /* Number of items in the main menu, if you add a item(E.G.parameter) in the main menu, add +1 here*/
#define MENU_ACCELERATION   0   /* Encoder acceleration when in the main menu */
#define SEL_ACCELERATION    100 /* Encoder acceleration when selecting parameter value */
#define ITEM_NO_CALLBACK    0   /* For when a item has no callback */
#define ITEM_NO_VALUE       0   /* For when an item has no value to be displayed */
#define MAX_ITEMS           10  /* Max Item on a menu, it will be used on all menus (including car selections) */

#define MIN_SPEED_DEFAULT         20  /* [%]  minSpeed (SENSI) default value. */               
#define BRAKE_DEFAULT             95  /* [%]  brake (BRAKE) default value. */
#define DRAG_BRAKE_DEFAULT        100 /* [%]  drag brake (DBRAKE) default value. */
#define ANTISPIN_DEFAULT          30  /* [ms] antispin (ANTIS) default value. */
#define MAX_SPEED_DEFAULT         100 /* [%]  max speed (LIMIT) default value. */
#define THROTTLE_CURVE_INPUT_THROTTLE_DEFAULT   THROTTLE_NORMALIZED/2 /* X coordinate (input throttle [norm]) of the throttle curve vertex point */
#define THROTTLE_CURVE_SPEED_DIFF_DEFAULT       50                    /* Y coordinate (output speed [%]) of the throttle curve vertex point */
#define PWM_FREQ_DEFAULT          30  /* [100*Hz] Output PWM frequency (PWM_F) default value. */

/* Max and Min user parameter values. If Min is not specified, then it's 0 */
#define MIN_SPEED_MAX_VALUE 90    /* [%]  minSpeed (SENSI) max value. */
#define DRAG_MAX_VALUE      100   /* [%]  drag brake (DBRAKE) max value. */
#define FREQ_MAX_VALUE      5000  /* [Hz] Output PWM frequency (PWM_F) max value. */
#define BRAKE_MAX_VALUE     100   /* [%]  brake (BRAKE) max value. */
#define THROTTLE_CURVE_SPEED_DIFF_MAX_VALUE  90 /* [%]  minSpeed (SENSI) max value. */
#define THROTTLE_CURVE_SPEED_DIFF_MIN_VALUE  10 /* [%]  minSpeed (SENSI) default value. */
#define ANTISPIN_MAX_VALUE  255   /* [ms] antispin (ANTIS) max value. */
#define FREQ_MIN_VALUE      1000   /* [%]  Output PWM frequency (PWM_F) min value. */
#define MAX_UINT16          32767 /* Max 16-bit value. */  

#define HEIGHT12x16 16  /* height of 12x16 characters */
#define HEIGHT8x8   8   /* height of 12x16 characters */
#define WIDTH8x8    8   /* height of 12x16 characters */
#define WIDTH12x16  12  /* width of 12x16 characters  */

#define LOOPTIME_MAX_CHECK  100     /* TODO: not used, verify */
#define TIMER_FREQ          1000000 /* frequency of the timer interrupt in Hz (1MHz)*/
#define ESC_PERIOD_US       500     /* Period of the ESC alarm in microseconds */

#define CAR_MAX_COUNT       10 /* How many different car model setting can be stored */
#define CAR_NAME_MAX_SIZE   5 /* 4 char + terminator \0 */

#define CAR_OPTION_SELECT   0
#define CAR_OPTION_RENAME   1
#define CAR_OPTION_SAVE     2 /* DEPRECATED - NOT USED */

#define RENAME_CAR_SELECT_OPTION_MODE 0
#define RENAME_CAR_SELECT_CHAR_MODE   1
#define RENAME_CAR_MIN_ASCII    33
#define RENAME_CAR_MAX_ASCII    122

#define DRAG_BRAKE_T_FULL     0
#define DRAG_BRAKE_T_DEC      1

#define TRIG_AVG_TIME_ms 25
#define TRIG_AVG_COUNT (TRIG_AVG_TIME_ms * 1000 / (ESC_PERIOD_US))
/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/

/* Enum definition for the Finite State Machine */
typedef enum
{ 
  INIT, 
  CALIBRATION,
  WELCOME,
  RUNNING, 
  FAULT
} StateMachine_enum;


/* Enum definition for the Main Menu state machine */
typedef enum
{
  ITEM_SELECTION,
  VALUE_SELECTION
} MenuState_enum;


/* Enum definition for what kind of value is going to be displayed next to the item name */
/* On representation of decimal values in the menu: the value must be represented as integer, and it must be specified where the decimal point is placed:
   e.g.: PWM freq is a value that we want represented in kHz, ranging from 0.2 to 5.0. We are gonna create the menu item type with the following fields:
         type: VALUE_TYPE_DECIMAL;
         maxValue: 50;
         minValue: 2;
         decimalPoint: 1;
         meaning that internally the values ranges from 2 to 50. When selected with the encoder in the main menu the value can be increased 1 by 1.
         The value that is displayed will be divided by 10^decimalPoint, to show values that ranges from 0.2 to 5.0.
         The application must take into account that the stored value will range from 2 to 50 during the calculations. */
typedef enum
{
  VALUE_TYPE_INTEGER,
  VALUE_TYPE_DECIMAL,
  VALUE_TYPE_STRING,
} ItemValueType_enum;


/* ThrottleCurveVertex_type: struct definition of the Throttle curve vertex 
   The Throttle curve is composed by two consecutive segments, connected by a single point called vertex.
   The throttle curve is placed in a XY plane, where the X axis corresponds to the input throttle and the Y axis
   corresponds to the duty cycle output (sometimes referred to as "speed").
   This struct describe the vertex of the throttle curve */
typedef struct {
  uint16_t inputThrottle;      /* Input throttle, corresponds to the X coordinate of the vertex. From 0% to 100% - fixed by default at 50% */
  uint16_t curveSpeedDiff;     /* Describes the Y coordinate of the vertex by % of the difference between the min and max speed.
                                  A value of 50% makes the throttle curve a straight line (i.e., the Y coordinate of the vertex is the middle point 
                                  between the max and min speed) */
} ThrottleCurveVertex_type;


/* CarParam_type: struct definition of the car param. Contains all the parameter that defines the behaviour of the controller */
typedef struct {
  uint16_t minSpeed;    /* [%]  SENSI, from 0% to 90%                  */
  uint16_t brake;       /* [%]  BRAKE, from 0% to 100%                 */ 
  uint16_t dragBrake;   /* [%]  DRAGB, from 0% to 100%                 */
  uint16_t maxSpeed;    /* [%]  LIMIT, from max(5, SENSI + 5)% to 100% */
  ThrottleCurveVertex_type throttleCurveVertex; 
  uint16_t antiSpin;    /* [ms] ANTIS, from 0ms to 250ms               */
  char     carName[CAR_NAME_MAX_SIZE]; /* Name of the CAR, size include terminator character  */
  uint16_t carNumber;   /* Simply to identify the position in the array, not to be changed    */
  uint16_t freqPWM;     /* [100*Hz] PWM_F, motor PWM frequency, from 2 to 50                  */
}CarParam_type;


/* Struct definition for variables stored in the EEPROM */
typedef struct {
  CarParam_type carParam[CAR_MAX_COUNT];    /* Array of CarParam_type */ 
  uint16_t  selectedCarNumber;              /* Currently selected car  */
  int16_t   minTrigger_raw;                 /* Min trigger raw value, calibration parameter */
  int16_t   maxTrigger_raw;                 /* Max trigger raw value, calibration parameter */
} StoredVar_type;


/* ESC_type: struct that contains all the charger variables */
typedef struct {
  uint16_t  outputSpeed_pct;  /* [%] Output speed (duty cycle) obtained after the throttle -> speed pipeline */
  int16_t   trigger_raw;      /* [raw] trigger reading */
  uint16_t  trigger_norm;     /* Trigger value, normalized between 0 and THROTTLE_NORMALIZED, to increase granularity */
  uint16_t  encoderPos;       /* Current encoder value */
  uint16_t  Vin_mV;           /* [mV] Voltage */
  bool      dualCurve;        /* dragBrake set higher than 100%-minSpeed so deceleration curve is diferent from accel*/
} ESC_type;


/* Define a pointer to a void function that takes no arguments */
typedef void (*FunctionPointer_type)(void);


/* MenuItem_type: struct that defines an item of the menu */
typedef struct {
  char name[10];                  /* Name of the item that is displayed in the menu */
  void *value;                    /* Pointer to the variable that contains the value of the item. When assign, must cast to (void *). It's a generic void pointer so that it can be used to print any type of value specified by the type field */
  ItemValueType_enum type;      /* What kind of variable is value pointing to. Only applies if value is not ITEM_NO_VALUE. STRING type of value must be 5 letters, for INTEGER type of values can be up to 4 digits, for DECIMAL type of values can be up to 3 digits */
  uint16_t maxValue;              /* Maximum possible value fo the item. Only applies if  type is VALUE_TYPE_INTEGER or VALUE_TYPE_DECIMAL */
  uint16_t minValue;              /* Minimum possible value fo the item. Only applies if  type is VALUE_TYPE_INTEGER or VALUE_TYPE_DECIMAL */
  char unit;                      /* Measurement unit of the item, that's gonna be displayed next to the value. Must be one character */
  uint8_t decimalPoint;           /* Indicates where is placed the decimal point. Only applies if  type is VALUE_TYPE_DECIMAL. Possible values are 1, and 2. */
  FunctionPointer_type callback; /* Pointer to a callback that is called when the item is clicked in the menu. If no callback, then set to ITEM_NO_CALLBACK */
} MenuItem_type;


typedef struct {
  MenuItem_type item[MAX_ITEMS];      /* Array of pointers to menu_item_type */
  uint16_t lines;                     /* How many lines displayed at a time */
} Menu_type;


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/



#endif