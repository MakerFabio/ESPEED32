/*********************************************************************************************************************/
/*                                                   Includes                                                        */
/*********************************************************************************************************************/
#include "slot_ESC.h"
#include "screensaver_config.h"  /* Personal screensaver configuration (git-ignored) */

/*********************************************************************************************************************/
/*                                                   Version Control                                                 */
/*********************************************************************************************************************/
#define SW_MAJOR_VERSION 3
#define SW_MINOR_VERSION 0
#define STORED_VAR_VERSION 7  /* Stored variable version - increment when stored structure changes */

/* Last modified: 17/10/2024 */
/*********************************************************************************************************************/
/*                                                   Language Strings                                                */
/*********************************************************************************************************************/

/* Menu item names in different languages: [language][item] */
/* Order: BRAKE, SENSI, ANTIS, CURVE, PWM_F, B_BTN, LIMIT, SETTINGS, *CAR* */
const char* MENU_NAMES[][9] = {
  /* NOR */ {"BREMS", "SENSI", "ANTIS", "KURVE", "PWM_F", "B_KNP", "LIMIT", "INNSTILL", "*BIL*"},
  /* ENG */ {"BRAKE", "SENSI", "ANTIS", "CURVE", "PWM_F", "B_BTN", "LIMIT", "SETTINGS", "*CAR*"},
  /* ACD */ {"BRAKE", "ATTCK", "CHOKE", "PROFL", "PWM_F", "B_BTN", "LIMIT", "SETTINGS", "*CAR*"}
};

/* Settings menu item names: [language][item] */
/* Order: SCRSV, SOUND, VIEW, LANG, CASE, FSIZE, BACK */
const char* SETTINGS_MENU_NAMES[][7] = {
  /* NOR */ {"SKJSP", "LYD", "VISN", "SPRK", "STYL", "STRL", "TILBAKE"},
  /* ENG */ {"SCRSV", "SOUND", "VIEW", "LANG", "CASE", "FSIZE", "BACK"},
  /* ACD */ {"SCRSV", "SOUND", "VIEW", "LANG", "CASE", "FSIZE", "BACK"}
};

/* Race mode parameter labels: [language][param] */
/* Order: BRAKE, SENSI, ANTIS, CURVE */
const char* RACE_LABELS[][4] = {
  /* NOR */ {"BREMS", "SENSI", "ANTIS", "KURVE"},
  /* ENG */ {"BREAK", "SENSI", "ANTIS", "CURVE"},
  /* ACD */ {"BREAK", "ATTCK", "CHOKE", "PROFIL"}
};

/* Car menu option labels: [language][option] */
/* Order: SELECT, RENAME, RACESWP, COPY, RESET */
const char* CAR_MENU_OPTIONS[][5] = {
  /* NOR */ {"VELG", "NAVNGI", "RACESWP", "KOPIER", "NULLSTILL"},
  /* ENG */ {"SELECT", "RENAME", "RACESWP", "COPY", "RESET"},
  /* ACD */ {"SELECT", "RENAME", "RACESWP", "COPY", "RESET"}
};

/* View mode value labels: [language][mode] */
/* Order: OFF, FULL, SIMPLE */
const char* VIEW_MODE_LABELS[][3] = {
  /* NOR */ {"AV", "FULL", "ENKEL"},
  /* ENG */ {"OFF", "FULL", "SIMPLE"},
  /* ACD */ {"OFF", "FULL", "SIMPLE"}
};

/* Sound mode value labels: [language][mode] */
/* Order: OFF, BOOT, ALL */
const char* SOUND_MODE_LABELS[][3] = {
  /* NOR */ {"AV", "START", "ALT"},
  /* ENG */ {"OFF", "BOOT", "ALL"},
  /* ACD */ {"OFF", "BOOT", "ALL"}
};

/* ON/OFF labels: [language][state] */
/* Order: OFF, ON */
const char* ON_OFF_LABELS[][2] = {
  /* NOR */ {"AV", "PA"},
  /* ENG */ {"OFF", "ON"},
  /* ACD */ {"OFF", "ON"}
};

/* Language labels: [language_code] */
/* Order: NOR, ENG, ACD */
const char* LANG_LABELS[] = {"NOR", "ENG", "ACD"};

/* Text case style labels: [language][case_style] */
/* Order: UPPER, PASCAL */
const char* TEXT_CASE_LABELS[][2] = {
  /* NOR */ {"UPPER", "Pascal"},
  /* ENG */ {"UPPER", "Pascal"},
  /* ACD */ {"UPPER", "Pascal"}
};

/* Font size labels: [language][size] */
/* Order: LARGE, SMALL */
const char* FONT_SIZE_LABELS[][2] = {
  /* NOR */ {"STOR", "liten"},
  /* ENG */ {"LARGE", "small"},
  /* ACD */ {"LARGE", "small"}
};

/*********************************************************************************************************************/
/*                                    Pascal Case String Arrays                                                      */
/*********************************************************************************************************************/

/* Menu item names - Pascal Case: [language][item] */
const char* MENU_NAMES_PASCAL[][9] = {
  /* NOR */ {"Brems", "Sensi", "Antis", "Kurve", "Pwm_F", "B_Knp", "Limit", "Innstill", "*Bil*"},
  /* ENG */ {"Brake", "Sensi", "Antis", "Curve", "Pwm_F", "B_Btn", "Limit", "Settings", "*Car*"},
  /* ACD */ {"Brake", "Attck", "Choke", "Profl", "Pwm_F", "B_Btn", "Limit", "Settings", "*Car*"}
};

/* Settings menu item names - Pascal Case: [language][item] */
const char* SETTINGS_MENU_NAMES_PASCAL[][7] = {
  /* NOR */ {"Skjsp", "Lyd", "Visn", "Sprk", "Styl", "Strl", "Tilbake"},
  /* ENG */ {"Scrsv", "Sound", "View", "Lang", "Case", "Fsize", "Back"},
  /* ACD */ {"Scrsv", "Sound", "View", "Lang", "Case", "Fsize", "Back"}
};

/* Race mode parameter labels - Pascal Case: [language][param] */
const char* RACE_LABELS_PASCAL[][4] = {
  /* NOR */ {"Brems", "Sensi", "Antis", "Kurve"},
  /* ENG */ {"Break", "Sensi", "Antis", "Curve"},
  /* ACD */ {"Break", "Attck", "Choke", "Profil"}
};

/* Car menu option labels - Pascal Case: [language][option] */
const char* CAR_MENU_OPTIONS_PASCAL[][5] = {
  /* NOR */ {"Velg", "Navngi", "Raceswp", "Kopier", "Nullstill"},
  /* ENG */ {"Select", "Rename", "Raceswp", "Copy", "Reset"},
  /* ACD */ {"Select", "Rename", "Raceswp", "Copy", "Reset"}
};

/* View mode value labels - Pascal Case: [language][mode] */
const char* VIEW_MODE_LABELS_PASCAL[][3] = {
  /* NOR */ {"Av", "Full", "Enkel"},
  /* ENG */ {"Off", "Full", "Simple"},
  /* ACD */ {"Off", "Full", "Simple"}
};

/* Sound mode value labels - Pascal Case: [language][mode] */
const char* SOUND_MODE_LABELS_PASCAL[][3] = {
  /* NOR */ {"Av", "Start", "Alt"},
  /* ENG */ {"Off", "Boot", "All"},
  /* ACD */ {"Off", "Boot", "All"}
};

/* ON/OFF labels - Pascal Case: [language][state] */
const char* ON_OFF_LABELS_PASCAL[][2] = {
  /* NOR */ {"Av", "Pa"},
  /* ENG */ {"Off", "On"},
  /* ACD */ {"Off", "On"}
};

/* BACK button labels - UPPER CASE: [language] */
const char* BACK_LABELS[] = {
  /* NOR */ "TILBAKE",
  /* ENG */ "BACK",
  /* ACD */ "BACK"
};

/* BACK button labels - Pascal Case: [language] */
const char* BACK_LABELS_PASCAL[] = {
  /* NOR */ "Tilbake",
  /* ENG */ "Back",
  /* ACD */ "Back"
};

/*********************************************************************************************************************/
/*                                                   Global Variables                                                */
/*********************************************************************************************************************/

/* FreeRTOS Task Handles */
TaskHandle_t Task1;
TaskHandle_t Task2;

/* State Machine */
static StateMachine_enum g_currState = INIT;

/* Display Components */
#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

OBDISP g_obd;         /* OLED display instance */
char msgStr[50];      /* Display message buffer */

/* Car Selection */
uint16_t g_carSel;    /* Currently selected car model index */

/* Rotary Encoder */
AiEsp32RotaryEncoder g_rotaryEncoder = AiEsp32RotaryEncoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BUTTON_PIN, ENCODER_VCC_PIN, ENCODER_STEPS);

static uint8_t g_encoderMainSelector = 1;             /* Main menu item selector */
static uint8_t g_encoderSecondarySelector = 0;        /* Secondary value selector */
static uint16_t *g_encoderSelectedValuePtr = NULL;    /* Pointer to currently selected value */
static uint16_t g_originalValueBeforeEdit = 0;        /* Store original value when entering VALUE_SELECTION (for cancel) */
static bool g_isEditingCarSelection = false;          /* Flag to prevent g_carSel update during CAR edit */

/* Stored Variables (EEPROM/Preferences) */
StoredVar_type g_storedVar;

/*********************************************************************************************************************/
/*                                            Helper Functions for Text Case                                         */
/*********************************************************************************************************************/

/* Get menu name with current text case style */
inline const char* getMenuName(uint8_t lang, uint8_t item) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? MENU_NAMES_PASCAL[lang][item] : MENU_NAMES[lang][item];
}

/* Get settings menu name with current text case style */
inline const char* getSettingsMenuName(uint8_t lang, uint8_t item) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? SETTINGS_MENU_NAMES_PASCAL[lang][item] : SETTINGS_MENU_NAMES[lang][item];
}

/* Get race label with current text case style */
inline const char* getRaceLabel(uint8_t lang, uint8_t param) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? RACE_LABELS_PASCAL[lang][param] : RACE_LABELS[lang][param];
}

/* Get car menu option with current text case style */
inline const char* getCarMenuOption(uint8_t lang, uint8_t option) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? CAR_MENU_OPTIONS_PASCAL[lang][option] : CAR_MENU_OPTIONS[lang][option];
}

/* Get view mode label with current text case style */
inline const char* getViewModeLabel(uint8_t lang, uint8_t mode) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? VIEW_MODE_LABELS_PASCAL[lang][mode] : VIEW_MODE_LABELS[lang][mode];
}

/* Get sound mode label with current text case style */
inline const char* getSoundModeLabel(uint8_t lang, uint8_t mode) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? SOUND_MODE_LABELS_PASCAL[lang][mode] : SOUND_MODE_LABELS[lang][mode];
}

/* Get ON/OFF label with current text case style */
inline const char* getOnOffLabel(uint8_t lang, uint8_t state) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? ON_OFF_LABELS_PASCAL[lang][state] : ON_OFF_LABELS[lang][state];
}

/* Get BACK label with current text case style */
inline const char* getBackLabel(uint8_t lang) {
  return (g_storedVar.textCase == TEXT_CASE_PASCAL) ? BACK_LABELS_PASCAL[lang] : BACK_LABELS[lang];
}

/* Get number of visible menu lines based on font size */
inline uint8_t getMenuLines() {
  return (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? 5 : 3;
}

/* ESC Runtime Variables */
ESC_type g_escVar {
  .outputSpeed_pct = 0,
  .trigger_raw = 0,
  .trigger_norm = 0,
  .encoderPos = 1,
  .Vin_mV = 0,
  .dualCurve = false
};

/* Menu Structures */
Menu_type g_mainMenu {
  .lines = 3
};

Menu_type g_settingsMenu {
  .lines = 3
};

Menu_type g_carMenu {
  .lines = 3
};

/* Preferences (NVM storage) */
Preferences g_pref;

/* UI Timing */
static uint32_t g_lastEncoderInteraction = 0;  /* Timestamp of last encoder interaction for display power saving */

/* Menu Navigation State */
static bool g_inSettingsMenu = false;  /* Track if we're currently in the settings submenu */
static bool g_forceRaceRedraw = false; /* Force race mode display to redraw */

/*********************************************************************************************************************/
/*                                                Function Prototypes                                                */
/*********************************************************************************************************************/
void IRAM_ATTR readEncoderISR();

/*********************************************************************************************************************/
/*                                                Setup Function                                                     */
/*********************************************************************************************************************/

/**
 * @brief Main setup function - initializes hardware and creates FreeRTOS tasks
 */
void setup() {
  /* Pin and Serial Setup */
  HAL_PinSetup();

  /* HalfBridge & Hardware Setup */
  HalfBridge_Setup();

  /* Create FreeRTOS Tasks */
  /* Task 1: UI and state machine (low priority, core 0) */
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function */
    "Task1",     /* Task name */
    10000,       /* Stack size */
    NULL,        /* Parameters */
    1,           /* Priority */
    &Task1,      /* Task handle */
    0);          /* Core 0 */
    
  /* Task 2: Trigger reading and motor control (high priority, core 1) */
  xTaskCreatePinnedToCore(
    Task2code,   /* Task function */
    "Task2",     /* Task name */
    10000,       /* Stack size */
    NULL,        /* Parameters */
    2,           /* Priority */
    &Task2,      /* Task handle */
    1);          /* Core 1 */
}


/*********************************************************************************************************************/
/*                                                FreeRTOS Tasks                                                     */
/*********************************************************************************************************************/

/**
 * @brief Task 1: UI and State Machine
 * @details Manages OLED display, rotary encoder, and main state machine
 * @note Runs on Core 0 with lower priority
 */
void Task1code(void *pvParameters) {
  for (;;) {
    StateMachine_enum prevState = g_currState;
    static uint16_t prevFreqPWM = 0;
    static MenuState_enum menuState = ITEM_SELECTION;
    static uint8_t swMajVer, swMinVer, storedVarVersion;

    /* Read input voltage and motor current */
    g_escVar.Vin_mV = HAL_ReadVoltageDivider(AN_VIN_DIV, RVIFBL, RVIFBH);
    g_escVar.motorCurrent_mA = HAL_ReadMotorCurrent();

    /* Update selected car if initialization complete */
    if (g_currState != INIT) {
      g_carSel = g_storedVar.selectedCarNumber;
    }

    /* Task 1 state machine */
    switch (g_currState) {
      case INIT:

        g_pref.begin("stored_var", false); /* Open the "stored" namespace in read/write mode. If it doesn't exist, it creates it */

        if (g_pref.isKey("stored_var_ver") && g_pref.isKey("sw_maj_ver") && g_pref.isKey("sw_min_ver") && g_pref.isKey("user_param")) /* If all keys exists, then check their value */
        {
          /* Get the values of the sw version */
          swMajVer = g_pref.getUChar("sw_maj_ver");
          swMinVer = g_pref.getUChar("sw_min_ver");
          storedVarVersion = g_pref.getUChar("stored_var_ver");

          if ((storedVarVersion == STORED_VAR_VERSION) ) /* If the storedVariable version keys is equal to the STORED_VAR MACRO, then the stored param are already initialized woh the proper format*/
          {
            g_pref.getBytes("user_param", &g_storedVar, sizeof(g_storedVar)); /* Get the value of the stored user_param */
            initMenuItems();                                                  /* init menu items with EEPROM stored variables */

            /* If button is pressed at startup, go to CALIBRATION state */
            if (digitalRead(ENCODER_BUTTON_PIN) == BUTTON_PRESSED) 
            {
              g_currState = CALIBRATION;      /* Go to CALIBRATION state */
              /* Reset Min and Max to the opposite side, in order to have effective calibration */
              g_storedVar.minTrigger_raw = MAX_INT16;
              g_storedVar.maxTrigger_raw = MIN_INT16;
              if (g_storedVar.soundMode == SOUND_MODE_ALL || g_storedVar.soundMode == SOUND_MODE_BOOT) {
                calibSound();             /* Play calibration sound */
              }
              initDisplayAndEncoder();  /* init and clear OLED and Encoder */

              /* Wait until button is released, then go to CALIBRATION state */
              while (digitalRead(ENCODER_BUTTON_PIN) == BUTTON_PRESSED)
              {
                showScreenPreCalibration();
              }
              
              obdFill(&g_obd, OBD_WHITE, 1); /* Clear OLED */
            }
            else  /* If button is NOT pressed at startup, go to RUNNING state */
            {
              g_currState = WELCOME;                    /* Go to WELCOME state */
              g_carSel = g_storedVar.selectedCarNumber; /* now it is safe to address the proper car */
              initDisplayAndEncoder();  /* init and clear OLED and Encoder */
              if (g_storedVar.soundMode == SOUND_MODE_ALL || g_storedVar.soundMode == SOUND_MODE_BOOT) {
                onSound();                /* Play ON sound */
              }
            }

            g_pref.end(); /* Close the namespace */
            break;        /* Break the switch case: if code reaches here, it means that the stored user param and sw versions are OK */
          }
        }

        /* If the code reaches here it means that:
        - the sw version keys are not present --> stored var are not initialized
        - the sw version stored are not up to date --> stored var are initialized but might be outdated

        Calibration values are NOT stored, go to CALIBRATION state */
        initDisplayAndEncoder();  /* init and clear OLED and Encoder */
                              
        g_pref.clear();           /* Clear all the keys in this namespace */
        /* Store the correct SW version */
        g_pref.putUChar("sw_maj_ver", SW_MAJOR_VERSION);
        g_pref.putUChar("sw_min_ver", SW_MINOR_VERSION);
        
        g_pref.putUChar("stored_var_ver", STORED_VAR_VERSION);

        initStoredVariables();  /* Initialize stored variables with default values */

        /* Reset Min and Max to the opposite side, in order to have effective calibration */
        g_storedVar.minTrigger_raw = MAX_INT16;
        g_storedVar.maxTrigger_raw = MIN_INT16;
        if (g_storedVar.soundMode == SOUND_MODE_ALL || g_storedVar.soundMode == SOUND_MODE_BOOT) {
          calibSound();                   /* Play calibration sound */
        }
        g_currState = CALIBRATION;      /* Go to CALIBRATION state */
        obdFill(&g_obd, OBD_WHITE, 1); /* Clear OLED */
        /* Press and release button to go to CALIBRATION state */
        while (!g_rotaryEncoder.isEncoderButtonClicked()) /* Loop until button is pressed */
        {
          showScreenNoEEPROM();
        }

        break;


      case CALIBRATION:
        /* Read Throttle */
        throttleCalibration(g_escVar.trigger_raw);    /* trigger raw is continuously read on task2 */
        showScreenCalibration(g_escVar.trigger_raw);  /* Show calibration screen */
        /* Exit calibration if button is presseded */
        if (g_rotaryEncoder.isEncoderButtonClicked())  /* exit calibration and save calibration data to EEPROM */
        {
          if (g_storedVar.soundMode == SOUND_MODE_ALL || g_storedVar.soundMode == SOUND_MODE_BOOT) {
            offSound();
          }
          initMenuItems();  /* Init Menu Items */
          saveEEPROM(g_storedVar);  /* Save modified calibration values to EEPROM */
          HalfBridge_Enable();    /* Enable HalfBridge */
          g_currState = WELCOME;  /* Go to WELCOME state */
        }
        break;


      case WELCOME:
        /* This WELCOME state is only used to show the SW versions on the Screen, but the controller is actually fully operational:
            - Calibration is OKAY (either just done, or using stored values)
            - User param are OKAY (either just initialized to default, or using stored values)
            - Trigger is being read on Task 2

          The user trigger input is being elaborated and the correct speed (PWM) output is being produced for the whole duration of the WELCOME state */

        showScreenWelcome();    /* Show welcome screen */
        delay(1500);            /* Wait one second */
        g_currState = RUNNING;  /* Go to RUNNING state */
        break;


      case RUNNING: /* when the global variable State is in RUNNING the Task2 will elaborate the trigger to produce the PWM out */

        /* Set encoder boundaries based on view mode (on first entry) */
        static bool encoderBoundariesSet = false;
        if (!encoderBoundariesSet) {
          /* Force LIST mode if race view is OFF */
          if (g_storedVar.viewMode == VIEW_MODE_GRID && g_storedVar.raceViewMode == RACE_VIEW_OFF) {
            g_storedVar.viewMode = VIEW_MODE_LIST;
          }

          if (g_storedVar.viewMode == VIEW_MODE_GRID) {
            uint8_t gridItems;
            if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
              gridItems = g_storedVar.gridCarSelectEnabled ? 3 : 2;  /* SIMPLE: BRAKE, SENSI, CAR (optional) */
            } else {
              gridItems = g_storedVar.gridCarSelectEnabled ? 5 : 4;  /* FULL: BRAKE, SENSI, ANTIS, CURVE, CAR (optional) */
            }
            g_rotaryEncoder.setBoundaries(1, gridItems, false);
          } else {
            g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);  /* Normal menu items */
          }
          encoderBoundariesSet = true;
        }

        /* Check for long press to toggle view mode */
        static uint32_t buttonPressStartTime = 0;
        static bool buttonWasPressed = false;
        static uint32_t lastLongPressTime = 0;

        if (digitalRead(ENCODER_BUTTON_PIN) == BUTTON_PRESSED) {
          if (!buttonWasPressed) {
            buttonPressStartTime = millis();
            buttonWasPressed = true;
          }
          /* If button held for defined duration, toggle view mode immediately */
          if (millis() - buttonPressStartTime > BUTTON_LONG_PRESS_MS &&
              millis() - lastLongPressTime > BUTTON_LONG_PRESS_MS) {
            lastLongPressTime = millis();  /* Record when long press happened */

            /* Only allow toggling to GRID mode if race view is not OFF */
            if (g_storedVar.viewMode == VIEW_MODE_LIST && g_storedVar.raceViewMode != RACE_VIEW_OFF) {
              g_storedVar.viewMode = VIEW_MODE_GRID;
            }
            else if (g_storedVar.viewMode == VIEW_MODE_GRID) {
              g_storedVar.viewMode = VIEW_MODE_LIST;
            }

            /* Clear display completely when switching views */
            obdFill(&g_obd, OBD_WHITE, 1);

            /* Reset to item selection mode (not value editing) */
            menuState = ITEM_SELECTION;

            /* Update encoder boundaries for new view mode */
            if (g_storedVar.viewMode == VIEW_MODE_GRID) {
              uint8_t gridItems;
              if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
                gridItems = g_storedVar.gridCarSelectEnabled ? 3 : 2;  /* SIMPLE: BRAKE, SENSI, CAR (optional) */
              } else {
                gridItems = g_storedVar.gridCarSelectEnabled ? 5 : 4;  /* FULL: BRAKE, SENSI, ANTIS, CURVE, CAR (optional) */
              }
              g_rotaryEncoder.setBoundaries(1, gridItems, false);
              g_rotaryEncoder.reset(1);  /* Reset to first grid item */
            } else {
              g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);  /* Normal menu items */
              g_rotaryEncoder.reset(1);  /* Reset to first menu item */
            }
            g_encoderMainSelector = 1;
            g_escVar.encoderPos = 1;

            saveEEPROM(g_storedVar);
            if (g_storedVar.soundMode == SOUND_MODE_ALL) {
              keySound();
            }
            g_lastEncoderInteraction = millis();

            /* Clear the encoder click state to prevent short press from triggering */
            g_rotaryEncoder.isEncoderButtonClicked();
          }
        } else {
          buttonWasPressed = false;
        }

        /* Check for brake button press - acts as "back" in edit mode */
        static bool brakeButtonWasPressedInMenu = false;
        static uint32_t lastBrakeButtonPressTime = 0;

        /* In GRID mode: brake button exits edit mode (in addition to reducing brake) */
        if (g_storedVar.viewMode == VIEW_MODE_GRID && menuState == VALUE_SELECTION && digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
          if (!brakeButtonWasPressedInMenu && millis() - lastBrakeButtonPressTime > BUTTON_SHORT_PRESS_DEBOUNCE_MS) {
            brakeButtonWasPressedInMenu = true;
            lastBrakeButtonPressTime = millis();

            /* Restore original value (cancel changes) */
            if (g_encoderSelectedValuePtr != NULL) {
              *g_encoderSelectedValuePtr = g_originalValueBeforeEdit;
              g_encoderSelectedValuePtr = NULL;
            }

            menuState = ITEM_SELECTION;
            g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);

            uint8_t gridItems;
            if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
              gridItems = g_storedVar.gridCarSelectEnabled ? 3 : 2;
            } else {
              gridItems = g_storedVar.gridCarSelectEnabled ? 5 : 4;
            }
            g_rotaryEncoder.setBoundaries(1, gridItems, false);
            g_rotaryEncoder.reset(g_encoderMainSelector);
            g_escVar.encoderPos = g_encoderMainSelector;
            g_isEditingCarSelection = false;
            obdFill(&g_obd, OBD_WHITE, 1);
            g_lastEncoderInteraction = millis();
          }
        }
        else if (g_storedVar.viewMode == VIEW_MODE_LIST && digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
          if (!brakeButtonWasPressedInMenu && millis() - lastBrakeButtonPressTime > BUTTON_SHORT_PRESS_DEBOUNCE_MS) {
            brakeButtonWasPressedInMenu = true;
            lastBrakeButtonPressTime = millis();

            /* If in VALUE_SELECTION, cancel changes and go back to ITEM_SELECTION */
            if (menuState == VALUE_SELECTION) {
              /* Restore original value (cancel changes) */
              if (g_encoderSelectedValuePtr != NULL) {
                *g_encoderSelectedValuePtr = g_originalValueBeforeEdit;
                g_encoderSelectedValuePtr = NULL;  /* Clear pointer after use */
              }

              menuState = ITEM_SELECTION;
              g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
              g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);
              g_rotaryEncoder.reset(g_encoderMainSelector);
              g_escVar.encoderPos = g_encoderMainSelector;
              /* Clear car editing flag */
              g_isEditingCarSelection = false;
              /* Do NOT save to EEPROM - we're canceling the change */
              obdFill(&g_obd, OBD_WHITE, 1);  /* Clear screen */
              g_lastEncoderInteraction = millis();
            }
            /* If already in ITEM_SELECTION, brake button doesn't do anything in main menu */
          }
        }
        /* Reset flag when button is released */
        if (digitalRead(BUTT_PIN) != BUTTON_PRESSED) {
          brakeButtonWasPressedInMenu = false;
        }

        /* Change menu state if encoder button is clicked (short press) */
        /* Only process if sufficient time has passed since last long press */
        if ((lastLongPressTime == 0 || millis() - lastLongPressTime > BUTTON_DEBOUNCE_AFTER_LONG_MS) &&
            g_rotaryEncoder.isEncoderButtonClicked())
        {
          /* If screensaver is active (timeout exceeded), just wake up - don't process menu action */
          if (g_storedVar.screensaverTimeout > 0 && millis() - g_lastEncoderInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
            g_lastEncoderInteraction = millis();  /* Wake from screensaver */
          } else {
            menuState = rotary_onButtonClick(menuState);  /* This function is called if the encoder is pressed
                                                             Take the current menu state and returns the next menu state */
            g_lastEncoderInteraction = millis();          /* Update last encoder interaction */
          }
        }

        /* Get encoder position if it was changed*/
        if (g_rotaryEncoder.encoderChanged()) 
        {
          g_escVar.encoderPos = g_rotaryEncoder.readEncoder();  /* Update the global ESC variable keeping track of the encoder value (position) */
          g_lastEncoderInteraction = millis();  /* Update last encoder interaction */
        }

        /* Change Encoder variable depending on menu state */
        if (menuState == ITEM_SELECTION) 
        {
          g_encoderMainSelector = g_escVar.encoderPos;  /* If in ITEM_SELECTION, update the encoder MainSelector with the encoder position */
        }
        if (menuState == VALUE_SELECTION)
        {
          g_encoderSecondarySelector = g_escVar.encoderPos;         /* If in ITEM_SELECTION, update the encoder SecondaryEncoder with the encoder position */
          uint16_t prevLanguage = g_storedVar.language;             /* Store previous language for change detection */
          *g_encoderSelectedValuePtr = g_encoderSecondarySelector;  /* Also update the value of the selected parameter */

          /* If language changed, reinitialize menu items with new language strings */
          if (g_storedVar.language != prevLanguage) {
            initMenuItems();
            obdFill(&g_obd, OBD_WHITE, 1);  /* Clear screen to prevent leftover text */
          }
        }

        /* Show Main Menu display */
        printMainMenu(menuState);
        if (g_storedVar.carParam[g_carSel].freqPWM != prevFreqPWM)  /* if PWM freq parameter is changed, update motor PWM */
        {
          prevFreqPWM = g_storedVar.carParam[g_carSel].freqPWM;
          ledcDetach(HB_IN_PIN);
          ledcDetach(HB_INH_PIN);
          uint16_t freqTmp = g_storedVar.carParam[g_carSel].freqPWM * 100;
          ledcAttachChannel(HB_IN_PIN, freqTmp, THR_PWM_RES_BIT, THR_IN_PWM_CHAN);
          ledcAttachChannel(HB_INH_PIN, freqTmp, THR_PWM_RES_BIT, THR_INH_PWM_CHAN);
        }
        if (g_escVar.outputSpeed_pct == 100) /* indicate 100% throttle also on the internal ESP32 LED*/
          digitalWrite(LED_BUILTIN, 1);
        else
          digitalWrite(LED_BUILTIN, 0);
        break;


      case FAULT:
        /* FAULT state, not currently used */
        break;


      default:
        /* Default case, do nothing */
        break;
    }

    if (g_currState != prevState) /* Every time FSM machine change state */
      obdFill(&g_obd, OBD_WHITE, 1);
  }
}

/**
 * @brief Task 2: Trigger Reading and Motor Control
 * @details Reads trigger input, applies throttle curve and anti-spin, controls motor PWM
 * @note Runs on Core 1 with higher priority for real-time motor control
 */
void Task2code(void *pvParameters) {
  static unsigned long prevCallTime_uS = 0;
  static unsigned long currTrigger_raw = 0, prevTrigger_raw = 0;

  HalfBridge_Enable();

  for (;;) {
    unsigned long currCallTime_uS = micros();
    unsigned long deltaTime_uS = currCallTime_uS - prevCallTime_uS;
    
    /* Execute every ESC_PERIOD_US microseconds */
    if (deltaTime_uS > ESC_PERIOD_US) {
      prevCallTime_uS = currCallTime_uS;

      /* Read and filter trigger input */
      prevTrigger_raw = currTrigger_raw;
      currTrigger_raw = HAL_ReadTriggerRaw();
      g_escVar.trigger_raw = (prevTrigger_raw + currTrigger_raw) / 2;  /* Simple moving average filter */
      
      /* Normalize and apply deadband */
      g_escVar.trigger_norm = normalizeAndClamp(g_escVar.trigger_raw, g_storedVar.minTrigger_raw, 
                                                g_storedVar.maxTrigger_raw, THROTTLE_NORMALIZED, THROTTLE_REV);
      g_escVar.trigger_norm = addDeadBand(g_escVar.trigger_norm, 0, THROTTLE_NORMALIZED, THROTTLE_DEADBAND_NORM);
      
      /* Apply motor control (skip if in calibration or init state) */
      if (!(g_currState == CALIBRATION || g_currState == INIT)) {
        if (g_escVar.trigger_norm == 0) {
          /* Apply brake when trigger is released */
          /* Check if brake button is pressed - use alternate brake value */
          uint16_t effectiveBrake = g_storedVar.carParam[g_carSel].brake;
          if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
            /* Use brakeButtonReduction as alternate brake value (not a reduction) */
            effectiveBrake = g_storedVar.carParam[g_carSel].brakeButtonReduction;
          }
          HalfBridge_SetPwmDrag(0, effectiveBrake);
          g_escVar.outputSpeed_pct = 0;
          throttleAntiSpin3(0);  /* Keep anti-spin timer updated */
        } else {
          /* Apply throttle curve and anti-spin */
          g_escVar.outputSpeed_pct = throttleCurve2(g_escVar.trigger_norm);
          g_escVar.outputSpeed_pct = throttleAntiSpin3(g_escVar.outputSpeed_pct);
          HalfBridge_SetPwmDrag(g_escVar.outputSpeed_pct, 0);
          /* Update last interaction time to prevent screensaver while driving */
          g_lastEncoderInteraction = millis();
        }
      }
    }
  }
}

/**
 * @brief Main loop (unused - real loops are in FreeRTOS tasks)
 */
void loop() {}

/*********************************************************************************************************************/
/*                                           Initialization Functions                                               */
/*********************************************************************************************************************/

/**
 * @brief Initialize OLED display and rotary encoder
 * @details Performed separately from HW init to reduce startup time
 */
void initDisplayAndEncoder() 
{
  uint16_t rc;
  /***** OLED Display Setup *****/
  rc = obdI2CInit(&g_obd, MY_OLED, OLED_ADDR, FLIP180, INVERT_DISP, USE_HW_I2C, SDA1_PIN, SCL1_PIN, RESET_PIN, 800000L);  // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND) 
  {
    obdSetBackBuffer(&g_obd, ucBackBuffer);
    obdFill(&g_obd, OBD_WHITE, 1);
  } 
  else 
  {
    Serial.println("Error! Failed OLED Display initialization!");
  }

  /***** Encoder Setup *****/
  g_rotaryEncoder.begin();
  g_rotaryEncoder.setup(readEncoderISR);
  g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false); /* minValue, maxValue, circleValues true|false (when max go to min and vice versa) */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);        /* Larger number = more accelearation; 0 or 1 means disabled acceleration */
}


/* Rotary Encoder ISR */
void IRAM_ATTR readEncoderISR() {
  g_rotaryEncoder.readEncoder_ISR();
}


/**
 * Initialize the stored variables with default values.
   This is done for every CAR in the CarParam array.
 */
void initStoredVariables() {
  for (int i = 0; i < CAR_MAX_COUNT; i++) {
    g_storedVar.carParam[i].minSpeed = MIN_SPEED_DEFAULT;
    g_storedVar.carParam[i].brake = BRAKE_DEFAULT;
    g_storedVar.carParam[i].dragBrake = DRAG_BRAKE_DEFAULT;
    g_storedVar.carParam[i].maxSpeed = MAX_SPEED_DEFAULT;
    g_storedVar.carParam[i].throttleCurveVertex = { THROTTLE_CURVE_INPUT_THROTTLE_DEFAULT, THROTTLE_CURVE_SPEED_DIFF_DEFAULT };
    g_storedVar.carParam[i].antiSpin = ANTISPIN_DEFAULT;
    g_storedVar.carParam[i].freqPWM = PWM_FREQ_DEFAULT;
    g_storedVar.carParam[i].carNumber = i;
    g_storedVar.carParam[i].brakeButtonReduction = BRAKE_BUTTON_REDUCTION_DEFAULT;
    sprintf(g_storedVar.carParam[i].carName, "CAR%d", i);
  }
  g_storedVar.selectedCarNumber = 0;
  g_storedVar.minTrigger_raw = 0;
  g_storedVar.maxTrigger_raw = ACD_RESOLUTION_STEPS;
  g_storedVar.viewMode = VIEW_MODE_LIST;
  g_storedVar.screensaverTimeout = SCREENSAVER_TIMEOUT_DEFAULT;
  g_storedVar.soundMode = SOUND_MODE_DEFAULT;
  g_storedVar.gridCarSelectEnabled = 0;  /* Car select in grid view disabled by default */
  g_storedVar.raceViewMode = RACE_VIEW_DEFAULT;  /* Default race view mode */
  g_storedVar.language = LANG_DEFAULT;  /* Default language */
  g_storedVar.textCase = TEXT_CASE_DEFAULT;  /* Default text case style */
  g_storedVar.listFontSize = FONT_SIZE_DEFAULT;  /* Default list view font size */
}


/**
 * Initialize the menu items with the value from the stored variables.
   Insert the items one by one in the main menu global instance.
   Then insert the items (cars) in the car menu.
   To add an item:
    - update the value of MENU_ITEMS_COUNT to match the amount of items in the menu.
    - update MAX_ITEMS so that it is greater or equal MENU_ITEMS_COUNT.
    - Add the item here, in the desired position (check the comment in slot_ESC.h MenuItem_type to know more).
 */
void initMenuItems() {
  int i = 0;
  uint8_t lang = g_storedVar.language;
  /* Init menu items - using language-specific names */

  sprintf(g_mainMenu.item[i].name, "%s", getMenuName(lang, 0));  /* BRAKE/BREMS */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].brake;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "%%");
  g_mainMenu.item[i].maxValue = BRAKE_MAX_VALUE;
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 1));  /* SENSI/ATTCK */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].minSpeed;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "%%");
  g_mainMenu.item[i].maxValue = min(MIN_SPEED_MAX_VALUE, (int)g_storedVar.carParam[g_carSel].maxSpeed);
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 2));  /* ANTIS/CHOKE */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].antiSpin;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "ms");
  g_mainMenu.item[i].maxValue = ANTISPIN_MAX_VALUE;
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 3));  /* CURVE/KURVE/PROFL */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "%%");
  g_mainMenu.item[i].maxValue = THROTTLE_CURVE_SPEED_DIFF_MAX_VALUE;
  g_mainMenu.item[i].minValue = THROTTLE_CURVE_SPEED_DIFF_MIN_VALUE;
  g_mainMenu.item[i].callback = &showCurveSelection;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 4));  /* PWM_F */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].freqPWM;
  g_mainMenu.item[i].type = VALUE_TYPE_DECIMAL;
  sprintf(g_mainMenu.item[i].unit, "k");
  g_mainMenu.item[i].maxValue = FREQ_MAX_VALUE / 100;
  g_mainMenu.item[i].minValue = FREQ_MIN_VALUE / 100;
  g_mainMenu.item[i].decimalPoint = 1;
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 5));  /* B_BTN/B_KNP */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].brakeButtonReduction;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "%%");
  g_mainMenu.item[i].maxValue = 100;
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 6));  /* LIMIT */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].maxSpeed;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "%%");
  g_mainMenu.item[i].maxValue = MAX_SPEED_DEFAULT;
  g_mainMenu.item[i].minValue = max(5, (int)g_storedVar.carParam[g_carSel].minSpeed + 5);
  g_mainMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 7));  /* SETTINGS/INNSTILL */
  g_mainMenu.item[i].value = ITEM_NO_VALUE;
  g_mainMenu.item[i].type = VALUE_TYPE_INTEGER;
  sprintf(g_mainMenu.item[i].unit, "");
  g_mainMenu.item[i].maxValue = 0;
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = &showSettingsMenu;

  sprintf(g_mainMenu.item[++i].name, "%s", getMenuName(lang, 8));  /* CAR or BIL */
  g_mainMenu.item[i].value = (void *)&g_storedVar.carParam[g_carSel].carName;
  g_mainMenu.item[i].type = VALUE_TYPE_STRING;
  g_mainMenu.item[i].maxValue = CAR_MAX_COUNT - 1;  // so menu will scroll in the array (CAR_MAX_COUNT long)
  g_mainMenu.item[i].minValue = 0;
  g_mainMenu.item[i].callback = &showSelectRenameCar;

  /* Init Car selection menu items */
  for (uint8_t j = 0; j < CAR_MAX_COUNT; j++)
  {
    sprintf(g_carMenu.item[j].name, (const char *)g_storedVar.carParam[j].carName);
    g_carMenu.item[j].value = (void *)&g_storedVar.carParam[j].carNumber;
  }
}


/**
 * Initialize the settings submenu items
 * Order: SCRSV, SOUND, VIEW, LANG, CASE, BACK
 */
void initSettingsMenuItems() {
  int i = 0;
  uint8_t lang = g_storedVar.language;

  sprintf(g_settingsMenu.item[i].name, "%s", getSettingsMenuName(lang, 0));  /* SCRSV/SKJSP */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.screensaverTimeout;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;  /* Changed to STRING to handle OFF/AV display */
  sprintf(g_settingsMenu.item[i].unit, "s");
  g_settingsMenu.item[i].maxValue = SCREENSAVER_TIMEOUT_MAX;
  g_settingsMenu.item[i].minValue = 0;  /* 0 = OFF */
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 1));  /* SOUND/LYD */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.soundMode;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = SOUND_MODE_ALL;
  g_settingsMenu.item[i].minValue = SOUND_MODE_OFF;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 2));  /* VIEW/VISN */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.raceViewMode;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = RACE_VIEW_SIMPLE;
  g_settingsMenu.item[i].minValue = RACE_VIEW_OFF;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 3));  /* LANG/SPRK */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.language;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = LANG_ACD;
  g_settingsMenu.item[i].minValue = LANG_NOR;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 4));  /* CASE/STYL */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.textCase;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = TEXT_CASE_PASCAL;
  g_settingsMenu.item[i].minValue = TEXT_CASE_UPPER;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 5));  /* FSIZE/STRL */
  g_settingsMenu.item[i].value = (void *)&g_storedVar.listFontSize;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = FONT_SIZE_SMALL;
  g_settingsMenu.item[i].minValue = FONT_SIZE_LARGE;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;

  sprintf(g_settingsMenu.item[++i].name, "%s", getSettingsMenuName(lang, 6));  /* BACK/TILBAKE */
  g_settingsMenu.item[i].value = ITEM_NO_VALUE;
  g_settingsMenu.item[i].type = VALUE_TYPE_STRING;
  sprintf(g_settingsMenu.item[i].unit, "");
  g_settingsMenu.item[i].maxValue = 0;
  g_settingsMenu.item[i].minValue = 0;
  g_settingsMenu.item[i].callback = ITEM_NO_CALLBACK;
}


/**
 * Show the Welcome screen
 */
void showScreenWelcome()
{
  /* Display "ESPEED" in large font */
  obdWriteString(&g_obd, 0, 24, 14, (char *)"ESPEED", FONT_12x16, OBD_BLACK, 1);

  /* Display "v3.1" in smaller font, centered below with spacing */
  /* v3.0 is 4 chars × 6px = 24px wide, center at (128-24)/2 = 52 */
  obdWriteString(&g_obd, 0, 52, 36, (char *)"v3.1", FONT_6x8, OBD_BLACK, 1);
}


/**
 * Show the Pre-Calibration screen, when the button is pressed during startup, but not yet released
 */
void showScreenPreCalibration() 
{
  sprintf(msgStr, "ESPEED32 v%d.%02d", SW_MAJOR_VERSION, SW_MINOR_VERSION);  //print SW version
  obdWriteString(&g_obd, 0, 8, 0, msgStr, FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 1 * HEIGHT8x8, (char *)"Release button", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 2 * HEIGHT8x8, (char *)"to calibrate", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 3 * HEIGHT8x8, (char *)"     OR    ", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 4 * HEIGHT8x8, (char *)"remove power", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 5 * HEIGHT8x8, (char *)"  to exit  ", FONT_8x8, OBD_BLACK, 1);
}


/**
 * Show the screen indicating that the stored variables are not present in the EEPROM
 */
void showScreenNoEEPROM() 
{
  sprintf(msgStr, "ESPEED32 v%d.%02d", SW_MAJOR_VERSION, SW_MINOR_VERSION);  //print SW version
  obdWriteString(&g_obd, 0, 0, 0, msgStr, FONT_8x8, OBD_WHITE, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 64, 3 * HEIGHT8x8, (char *)"EEPROM NOT init!", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 5 * HEIGHT8x8, (char *)"Press button", FONT_8x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, (OLED_WIDTH / 2) - 48, 6 * HEIGHT8x8, (char *)"to calibrate", FONT_8x8, OBD_BLACK, 1);
}


/**
 * Show the calibration screen. It displays the current trigger raw value, as well as the max and min encountered values.
 * 
 * @param adcRaw The raw trigger value read from the ADC
 */
void showScreenCalibration(int16_t adcRaw)
{
  sprintf(msgStr, "CALIBRATION");
  obdWriteString(&g_obd, 0, (OLED_WIDTH - 66) / 2, 0, msgStr, FONT_6x8, OBD_WHITE, 1);

  sprintf(msgStr, "press/releas throttle");
  obdWriteString(&g_obd, 0, 0, 8, msgStr, FONT_6x8, OBD_BLACK, 1);

  sprintf(msgStr, "Raw throttle %4d  ", adcRaw);
  obdWriteString(&g_obd, 0, 0, 24, msgStr, FONT_6x8, OBD_BLACK, 1);

  sprintf(msgStr, "Min throttle %4d   ", g_storedVar.minTrigger_raw);
  obdWriteString(&g_obd, 0, 0, 32, msgStr, FONT_6x8, OBD_BLACK, 1);

  sprintf(msgStr, "Max throttle %4d   ", g_storedVar.maxTrigger_raw);
  obdWriteString(&g_obd, 0, 0, 40, msgStr, FONT_6x8, OBD_BLACK, 1);

  sprintf(msgStr, " push when done ");
  obdWriteString(&g_obd, 0, 0, 56, msgStr, FONT_6x8, OBD_BLACK, 1);
}

/**
 * @brief Display bottom status line with throttle, car name and voltage
 * @details Common function used by both main menu and screensaver
 */
void displayStatusLine() {
  static uint16_t lastCarNum = 999;

  /* Throttle % or Brake button preview - far left (position 0) */
  if (digitalRead(BUTT_PIN) == BUTTON_PRESSED && g_escVar.trigger_norm == 0) {
    /* Show brake button value when button is held and not on throttle */
    sprintf(msgStr, "B%3d%c", g_storedVar.carParam[g_carSel].brakeButtonReduction, '%');
    obdWriteString(&g_obd, 0, 0, 3 * HEIGHT12x16 + HEIGHT8x8, msgStr, FONT_8x8, OBD_WHITE, 1);
  } else {
    /* Normal throttle display */
    sprintf(msgStr, "%4d%c", g_escVar.outputSpeed_pct, '%');
    obdWriteString(&g_obd, 0, 0, 3 * HEIGHT12x16 + HEIGHT8x8, msgStr, FONT_8x8, (g_escVar.outputSpeed_pct == 100) ? OBD_WHITE : OBD_BLACK, 1);
  }

  /* Car ID - centered with proper clearing and highlighting */
  sprintf(msgStr, "%s", g_storedVar.carParam[g_carSel].carName);
  uint8_t carNameWidth = strlen(msgStr) * 6;  /* 6 pixels per char for FONT_6x8 */

  /* Clear car name area when car changes to prevent flicker */
  if (g_carSel != lastCarNum) {
    /* Clear centered area (48px = 8 chars × 6px) to handle varying name lengths */
    obdWriteString(&g_obd, 0, (OLED_WIDTH - 48) / 2, 3 * HEIGHT12x16 + HEIGHT8x8, (char *)"        ", FONT_6x8, OBD_BLACK, 1);
    lastCarNum = g_carSel;
  }

  /* Determine if CAR is selected in grid mode */
  bool carSelected = false;
  if (g_storedVar.viewMode == VIEW_MODE_GRID && g_storedVar.gridCarSelectEnabled) {
    /* Check if we're on CAR item - position depends on race view mode */
    if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
      /* SIMPLE mode: CAR is item 2, encoder position 3 */
      if (g_encoderMainSelector == 3) {
        carSelected = true;
      }
    } else {
      /* FULL mode: CAR is item 4, encoder position 5 */
      if (g_encoderMainSelector == 5) {
        carSelected = true;
      }
    }
  }

  uint8_t carColor = carSelected ? OBD_WHITE : OBD_BLACK;
  obdWriteString(&g_obd, 0, (OLED_WIDTH - carNameWidth) / 2, 3 * HEIGHT12x16 + HEIGHT8x8, msgStr, FONT_6x8, carColor, 1);

  /* Update dualCurve flag but don't display 'D' indicator */
  if (g_storedVar.carParam[g_carSel].dragBrake > 100 - (uint16_t)g_storedVar.carParam[g_carSel].minSpeed) {
    g_escVar.dualCurve = true;
  } else {
    g_escVar.dualCurve = false;
  }

  /* Input voltage - far right aligned */
  sprintf(msgStr, "%d.%01dV", g_escVar.Vin_mV / 1000, (g_escVar.Vin_mV % 1000) / 100);
  obdWriteString(&g_obd, 0, OLED_WIDTH - 30, 3 * HEIGHT12x16 + HEIGHT8x8, msgStr, FONT_6x8, OBD_BLACK, 1);
}

/**
 * @brief Display simple race mode - shows only BRAKE and SENSI with larger font
 * @details Simplified race view with just the two most important parameters
 * @param selectedItem Item selected for editing (0=BRAKE, 1=SENSI, 2=CAR if enabled)
 * @param isEditing True if currently editing a value
 */
void displayRaceModeSimple(uint8_t selectedItem, bool isEditing) {
  static uint16_t lastBrake = 999;
  static uint16_t lastSensi = 999;
  static uint8_t lastSelectedItem = 255;
  static bool lastIsEditing = false;
  static uint16_t lastCarSel = 999;

  /* Simple mode: 0=BRAKE, 1=SENSI, 2=CAR (if enabled) */
  int col1_center = 32;   /* Center of left half (128/4 = 32) */
  int col2_center = 96;   /* Center of right half (128*3/4 = 96) */

  /* Check if forced redraw, selection or car changed - force update of ALL items */
  if (g_forceRaceRedraw || selectedItem != lastSelectedItem || isEditing != lastIsEditing || g_carSel != lastCarSel) {
    lastBrake = 999;
    lastSensi = 999;
    lastSelectedItem = selectedItem;
    lastIsEditing = isEditing;
    lastCarSel = g_carSel;
  }

  /* Determine colors based on selection state */
  uint8_t colorBrake = (selectedItem == 0) ? OBD_WHITE : OBD_BLACK;
  uint8_t colorSensi = (selectedItem == 1) ? OBD_WHITE : OBD_BLACK;

  /* BRAKE - left column, using FONT_12x16 for both label and value */
  if (g_storedVar.carParam[g_carSel].brake != lastBrake) {
    /* Label - using language-specific text with FONT_12x16: 5 chars × 12px = 60px wide */
    const char* brakeLabel = getRaceLabel(g_storedVar.language, 0);
    uint8_t labelWidth = strlen(brakeLabel) * 12;
    obdWriteString(&g_obd, 0, col1_center - (labelWidth / 2), 0, (char *)brakeLabel, FONT_12x16, colorBrake, 1);
    /* Value - "100%" with FONT_12x16: 4 chars × 12px = 48px wide, center at col1_center - 24 */
    sprintf(msgStr, "%3d%%", g_storedVar.carParam[g_carSel].brake);
    obdWriteString(&g_obd, 0, col1_center - 24, 16, msgStr, FONT_12x16, colorBrake, 1);
    lastBrake = g_storedVar.carParam[g_carSel].brake;
  }

  /* SENSI - right column, using FONT_12x16 for both label and value */
  if (g_storedVar.carParam[g_carSel].minSpeed != lastSensi) {
    /* Label - using language-specific text with FONT_12x16: 5 chars × 12px = 60px wide */
    const char* sensiLabel = getRaceLabel(g_storedVar.language, 1);
    uint8_t labelWidth = strlen(sensiLabel) * 12;
    obdWriteString(&g_obd, 0, col2_center - (labelWidth / 2), 0, (char *)sensiLabel, FONT_12x16, colorSensi, 1);
    /* Value - "100%" with FONT_12x16: 4 chars × 12px = 48px wide */
    sprintf(msgStr, "%3d%%", g_storedVar.carParam[g_carSel].minSpeed);
    obdWriteString(&g_obd, 0, col2_center - 24, 16, msgStr, FONT_12x16, colorSensi, 1);
    lastSensi = g_storedVar.carParam[g_carSel].minSpeed;
  }

  /* Note: Car name, voltage, and LIMITER warning are displayed by displayStatusLine() */
}


/**
 * @brief Display race mode - compact grid showing all key parameters
 * @details Shows throttle, brake, sensitivity, antispin, curve, limit, car name and voltage
 * @param selectedItem Item selected for editing (0-5, or 255 if none selected)
 * @param isEditing True if currently editing a value
 */
void displayRaceMode(uint8_t selectedItem, bool isEditing) {
  static uint16_t lastBrake = 999;
  static uint16_t lastSensi = 999;
  static uint16_t lastAntis = 999;
  static uint16_t lastCurve = 999;
  static uint8_t lastSelectedItem = 255;
  static bool lastIsEditing = false;
  static uint16_t lastCarSel = 999;

  /* Vertical layout - label above value, centered */
  /* Grid items: 0=BRAKE, 1=SENSI, 2=ANTIS, 3=CURVE, 4=CAR (if enabled) */
  int col1_center = 32;   /* Center of left half (128/4 = 32) */
  int col2_center = 96;   /* Center of right half (128*3/4 = 96) */

  /* Check if forced redraw, selection or car changed - force update of ALL items */
  if (g_forceRaceRedraw || selectedItem != lastSelectedItem || isEditing != lastIsEditing || g_carSel != lastCarSel) {
    /* Force redraw of all items when selection changes */
    lastBrake = 999;
    lastSensi = 999;
    lastAntis = 999;
    lastCurve = 999;

    lastSelectedItem = selectedItem;
    lastIsEditing = isEditing;
    lastCarSel = g_carSel;
  }

  /* Determine colors based on selection state */
  uint8_t colorBrake = (selectedItem == 0) ? OBD_WHITE : OBD_BLACK;
  uint8_t colorSensi = (selectedItem == 1) ? OBD_WHITE : OBD_BLACK;
  uint8_t colorAntis = (selectedItem == 2) ? OBD_WHITE : OBD_BLACK;
  uint8_t colorCurve = (selectedItem == 3) ? OBD_WHITE : OBD_BLACK;
  uint8_t colorCar = (selectedItem == 4) ? OBD_WHITE : OBD_BLACK;

  /* BRAKE - left column */
  if (g_storedVar.carParam[g_carSel].brake != lastBrake) {
    /* Label - using language-specific text, dynamically centered */
    const char* brakeLabel = getRaceLabel(g_storedVar.language, 0);
    uint8_t labelWidth = strlen(brakeLabel) * 6;
    obdWriteString(&g_obd, 0, col1_center - (labelWidth / 2), 2, (char *)brakeLabel, FONT_6x8, colorBrake, 1);
    /* Value - "100%" is 4 chars × 8px = 32px wide, center at col1_center - 16 */
    sprintf(msgStr, "%3d%%", g_storedVar.carParam[g_carSel].brake);
    obdWriteString(&g_obd, 0, col1_center - 16, 12, msgStr, FONT_8x8, colorBrake, 1);
    lastBrake = g_storedVar.carParam[g_carSel].brake;
  }

  /* SENSI - right column */
  if (g_storedVar.carParam[g_carSel].minSpeed != lastSensi) {
    /* Label - using language-specific text, shifted 1px right */
    const char* sensiLabel = getRaceLabel(g_storedVar.language, 1);
    uint8_t labelWidth = strlen(sensiLabel) * 6;
    obdWriteString(&g_obd, 0, col2_center - (labelWidth / 2) + 1, 2, (char *)sensiLabel, FONT_6x8, colorSensi, 1);
    /* Value */
    sprintf(msgStr, "%3d%%", g_storedVar.carParam[g_carSel].minSpeed);
    obdWriteString(&g_obd, 0, col2_center - 16, 12, msgStr, FONT_8x8, colorSensi, 1);
    lastSensi = g_storedVar.carParam[g_carSel].minSpeed;
  }

  /* ANTIS - left column, lower */
  if (g_storedVar.carParam[g_carSel].antiSpin != lastAntis) {
    /* Label - using language-specific text, dynamically centered */
    const char* antisLabel = getRaceLabel(g_storedVar.language, 2);
    uint8_t labelWidth = strlen(antisLabel) * 6;
    obdWriteString(&g_obd, 0, col1_center - (labelWidth / 2), 24, (char *)antisLabel, FONT_6x8, colorAntis, 1);
    /* Value - "255ms" is 5 chars × 8px = 40px wide, center at col1_center - 20 */
    sprintf(msgStr, "%3dms", g_storedVar.carParam[g_carSel].antiSpin);
    obdWriteString(&g_obd, 0, col1_center - 20, 34, msgStr, FONT_8x8, colorAntis, 1);
    lastAntis = g_storedVar.carParam[g_carSel].antiSpin;
  }

  /* CURVE - right column, lower */
  if (g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff != lastCurve) {
    /* Label - using language-specific text, shifted 1px right */
    const char* curveLabel = getRaceLabel(g_storedVar.language, 3);
    uint8_t labelWidth = strlen(curveLabel) * 6;
    obdWriteString(&g_obd, 0, col2_center - (labelWidth / 2) + 1, 24, (char *)curveLabel, FONT_6x8, colorCurve, 1);
    /* Value */
    sprintf(msgStr, "%3d%%", g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff);
    obdWriteString(&g_obd, 0, col2_center - 16, 34, msgStr, FONT_8x8, colorCurve, 1);
    lastCurve = g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff;
  }

  /* Note: Car name, voltage, and LIMITER warning are displayed by displayStatusLine() */
  /* CAR selection (item 4) uses the existing car name display in status line when enabled */
}

/**
 * @brief Show screensaver with branding
 * @details Displays personalized branding with LIMITER warning and status line
 *          Text is configured in screensaver_config.h (git-ignored)
 */
void showScreensaver() {
  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Calculate text width for centering (16 pixels per character for FONT_16x32) */
  int line1_width = strlen(SCREENSAVER_LINE1) * 16;
  int line1_x = (OLED_WIDTH - line1_width) / 2;

  /* Display main text in extra large font centered */
  obdWriteString(&g_obd, 0, line1_x, 8, (char *)SCREENSAVER_LINE1, FONT_16x32, OBD_BLACK, 1);

  /* Calculate text width for centering (6 pixels per character for FONT_6x8) */
  int line2_width = strlen(SCREENSAVER_LINE2) * 6;
  int line2_x = (OLED_WIDTH - line2_width) / 2;

  /* Display subtitle in smaller font centered below */
  obdWriteString(&g_obd, 0, line2_x, 34, (char *)SCREENSAVER_LINE2, FONT_6x8, OBD_BLACK, 1);

  /* Display LIMITER warning if active at same position as in menu */
  if (g_storedVar.carParam[g_carSel].maxSpeed < MAX_SPEED_DEFAULT)
  {
    obdWriteString(&g_obd, 0, WIDTH8x8, 3 * HEIGHT12x16, (char *)" - LIMITER - ", FONT_8x8, OBD_WHITE, 1);
  }

  /* Display bottom status line */
  displayStatusLine();
}

/**
 * Print the main menu.
 * Takes care of printing the menu items and to scroll them according to the encoder position.
 * The current menu state is used to highlight decide whether to highlight only the item or also the value.
 * 
 * @param currMenuState The current menu state (ITEM_SELECTION or VALUE_SELECTION)
 */
void printMainMenu(MenuState_enum currMenuState) 
{
  static uint16_t tmp = 0;
  static bool screensaverActive = false;

  /* "Frame" indicates which items are currently displayed.
     It consist of a lower and upper bound: only the items within this boundaries are displayed.
     The difference between upper and lower bound is fixed to be visibleLines
     It's important that the encoder boundaries matches the menu items (e.g., 8 items, encoder boundaries must be [1,8]) */
  static uint16_t frameUpper = 1;
  static uint16_t frameLower = 3;
  static uint8_t lastVisibleLines = 3;
  uint8_t visibleLines = getMenuLines();

  /* If font size changed, reset frame */
  if (visibleLines != lastVisibleLines) {
    frameUpper = 1;
    frameLower = visibleLines;
    lastVisibleLines = visibleLines;
    obdFill(&g_obd, OBD_WHITE, 1);
  }

  /* In encoder move out of frame, adjust frame */
  if (g_encoderMainSelector > frameLower)
  {
    frameLower = g_encoderMainSelector;
    frameUpper = frameLower - visibleLines + 1;
    obdFill(&g_obd, OBD_WHITE, 1);
    screensaverActive = false;
  }
  else if (g_encoderMainSelector < frameUpper)
  {
    frameUpper = g_encoderMainSelector;
    frameLower = frameUpper + visibleLines - 1;
    obdFill(&g_obd, OBD_WHITE, 1);
    screensaverActive = false;
  }

  /* Check what to display based on view mode */
  static uint16_t lastViewMode = 255;  /* Track view mode changes */

  if (g_storedVar.viewMode == VIEW_MODE_GRID)
  {
    /* GRID mode: always show race mode with editing capability */
    /* Grid items depend on race view mode:
       FULL: 0=BRAKE, 1=SENSI, 2=ANTIS, 3=CURVE, 4=CAR (if enabled)
       SIMPLE: 0=BRAKE, 1=SENSI, 2=CAR (if enabled) */
    static uint8_t gridSelectedItem = 0;  /* Currently selected grid item */
    static MenuState_enum gridMenuState = ITEM_SELECTION;  /* Grid edit state */

    /* Force redraw when entering GRID mode */
    if (lastViewMode != VIEW_MODE_GRID) {
      lastViewMode = VIEW_MODE_GRID;
      g_forceRaceRedraw = true;
      obdFill(&g_obd, OBD_WHITE, 1);
    }

    /* Clear screen if coming from screensaver */
    if (screensaverActive) {
      obdFill(&g_obd, OBD_WHITE, 1);
      screensaverActive = false;
    }

    /* Calculate max grid item based on race view mode */
    uint8_t maxGridItem;
    if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
      /* SIMPLE: BRAKE, SENSI, CAR (if enabled) */
      maxGridItem = g_storedVar.gridCarSelectEnabled ? 3 : 2;
    }
    else {
      /* FULL: BRAKE, SENSI, ANTIS, CURVE, CAR (if enabled) */
      maxGridItem = g_storedVar.gridCarSelectEnabled ? 5 : 4;
    }

    if (g_encoderMainSelector < 1) g_encoderMainSelector = 1;
    if (g_encoderMainSelector > maxGridItem) g_encoderMainSelector = maxGridItem;
    gridSelectedItem = g_encoderMainSelector - 1;

    /* Determine if we're editing based on menu state */
    bool isEditing = (currMenuState == VALUE_SELECTION);

    /* Call appropriate display function based on race view mode */
    if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
      displayRaceModeSimple(gridSelectedItem, isEditing);
    }
    else {
      displayRaceMode(gridSelectedItem, isEditing);
    }
    g_forceRaceRedraw = false;  /* Reset force redraw flag after display */

    /* Print LIMITER warning if LIMIT is any value other than 100% */
    if (g_storedVar.carParam[g_carSel].maxSpeed < MAX_SPEED_DEFAULT)
    {
      obdWriteString(&g_obd, 0, WIDTH8x8, 3 * HEIGHT12x16, (char *)" - LIMITER - ", FONT_8x8, OBD_WHITE, 1);
    }
    else
    {
      obdWriteString(&g_obd, 0, WIDTH8x8, 3 * HEIGHT12x16, (char *)"             ", FONT_8x8, OBD_BLACK, 1);
    }
  }
  else {
  /* LIST mode: show screensaver or menu */
  lastViewMode = VIEW_MODE_LIST;  /* Track that we're in LIST mode */

  /* Calculate throttle percentage for screensaver logic */
  uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

  /* Track encoder position for screensaver wake-up */
  static uint16_t screensaverEncoderPos = 0;

  /* Check for any wake-up input (throttle, encoder change, or button press) */
  if (screensaverActive) {
    uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
    if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
        currentEncoderPos != screensaverEncoderPos ||
        digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      /* Wake from screensaver */
      obdFill(&g_obd, OBD_WHITE, 1);
      screensaverActive = false;
      g_lastEncoderInteraction = millis();
    }
  }

  /* Keep resetting timeout while throttle is above threshold (prevents screensaver activation) */
  if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD) {
    g_lastEncoderInteraction = millis();
  }

  if (g_storedVar.screensaverTimeout > 0 && millis() - g_lastEncoderInteraction > (g_storedVar.screensaverTimeout * 1000UL))
  {
    /* Timeout reached and throttle below threshold - show screensaver */
    if (!screensaverActive) {
      screensaverActive = true;
      screensaverEncoderPos = g_rotaryEncoder.readEncoder();  /* Save position when entering screensaver */
      showScreensaver();
    }
    /* Screensaver is active - don't draw menu */
  }
  else if (!screensaverActive)
  {
    /* Not in screensaver - show normal menu */
    /* Determine font size and dimensions based on setting */
    uint8_t menuFont = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? FONT_8x8 : FONT_12x16;
    uint8_t charWidth = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? WIDTH8x8 : WIDTH12x16;
    uint8_t lineHeight = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? 8 : HEIGHT12x16;

    for (uint8_t i = 0; i < visibleLines; i++)
    {
      /* Print item name */
      /* Item color: WHITE if item is selected, black otherwise */
      obdWriteString(&g_obd, 0, 0, i * lineHeight, g_mainMenu.item[frameUpper - 1 + i].name, menuFont, (g_encoderMainSelector - frameUpper == i) ? OBD_WHITE : OBD_BLACK, 1);

      /* Only print value if value != ITEM_NO_VALUE */
      /* Value color: WHITE if corresponding item is selected AND menu state is VALUE_SELECTION, black otherwise */
      if (g_mainMenu.item[frameUpper - 1 + i].value != ITEM_NO_VALUE) 
      {
        /* if the value is a number, cast to *(unit16_t *), then print number and unit */
        if (g_mainMenu.item[frameUpper - 1 + i].type == VALUE_TYPE_INTEGER)
        {
          /* value is a generic pointer to void, so first cast to uint16_t pointer, then take the pointed value */
          sprintf(msgStr, "%3d%s", *(uint16_t *)(g_mainMenu.item[frameUpper - 1 + i].value), g_mainMenu.item[frameUpper - 1 + i].unit);
          /* Right-align: calculate text width and position from right edge */
          int textWidth = strlen(msgStr) * charWidth;
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, i * lineHeight, msgStr, menuFont, (((g_encoderMainSelector - frameUpper == i) && (currMenuState == VALUE_SELECTION)) ? OBD_WHITE : OBD_BLACK), 1);
        }
        /* If the value is a decimal, cast to *(unit16_t *), divide by 10^decimalPoint then print number and unit */
        else if (g_mainMenu.item[frameUpper - 1 + i].type == VALUE_TYPE_DECIMAL)
        {
          /* value is a generic pointer to void, so first cast to uint16_t pointer, then take the pointed value */
          tmp = *(uint16_t *)(g_mainMenu.item[frameUpper - 1 + i].value);
          sprintf(msgStr, " %d.%01d%s", tmp / 10, (tmp % 10), g_mainMenu.item[frameUpper - 1 + i].unit);
          /* Right-align: calculate text width and position from right edge */
          int textWidth = strlen(msgStr) * charWidth;
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, i * lineHeight, msgStr, menuFont, (((g_encoderMainSelector - frameUpper == i) && (currMenuState == VALUE_SELECTION)) ? OBD_WHITE : OBD_BLACK), 1);
        }
        /* If the value is a string, cast to (char *) then print the string */
        else if (g_mainMenu.item[frameUpper - 1 + i].type == VALUE_TYPE_STRING)
        {
          /* Special handling for SOUND/LYD menu item - display language-specific labels */
          if (strcmp(g_mainMenu.item[frameUpper - 1 + i].name, "SOUND") == 0 ||
              strcmp(g_mainMenu.item[frameUpper - 1 + i].name, "LYD") == 0) {
            uint16_t soundMode = *(uint16_t *)(g_mainMenu.item[frameUpper - 1 + i].value);
            uint16_t lang = g_storedVar.language;
            sprintf(msgStr, "%5s", SOUND_MODE_LABELS[lang][soundMode]);
          }
          /* Special handling for VIEW menu item - display language-specific labels */
          else if (strcmp(g_mainMenu.item[frameUpper - 1 + i].name, "VIEW") == 0) {
            uint16_t raceViewMode = *(uint16_t *)(g_mainMenu.item[frameUpper - 1 + i].value);
            uint16_t lang = g_storedVar.language;
            sprintf(msgStr, "%6s", VIEW_MODE_LABELS[lang][raceViewMode]);
          }
          /* Special handling for LANG menu item - display "NOR", "ENG", or "ACD" */
          else if (strcmp(g_mainMenu.item[frameUpper - 1 + i].name, "LANG") == 0) {
            uint16_t language = *(uint16_t *)(g_mainMenu.item[frameUpper - 1 + i].value);
            sprintf(msgStr, "%3s", (language == LANG_NOR) ? "NOR" : ((language == LANG_ENG) ? "ENG" : "ACD"));
          }
          else {
            /* value is a generic pointer to void, so cast to string pointer */
            sprintf(msgStr, "%s", (char *)(g_mainMenu.item[frameUpper - 1 + i].value));
          }
          /* Right-align: calculate text width and position from right edge */
          int textWidth = strlen(msgStr) * charWidth;
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, i * lineHeight, msgStr, menuFont, (((g_encoderMainSelector - frameUpper == i) && (currMenuState == VALUE_SELECTION)) ? OBD_WHITE : OBD_BLACK), 1);
        }
      }
    }

    initMenuItems();  /* update menu items with the storedVar that could have been changed in previous for cycle */
    /* Print LIMITER warning if LIMIT is any value other than 100% */
    if (g_storedVar.carParam[g_carSel].maxSpeed < MAX_SPEED_DEFAULT) 
    {
      obdWriteString(&g_obd, 0, WIDTH8x8, 3 * HEIGHT12x16, (char *)" - LIMITER - ", FONT_8x8, OBD_WHITE, 1);
    } 
    else
    {
      obdWriteString(&g_obd, 0, WIDTH8x8, 3 * HEIGHT12x16, (char *)"             ", FONT_8x8, OBD_BLACK, 1);
    }
  }
  } /* End of else (LIST mode) */

  /* Display bottom status line */
  displayStatusLine();
}


#define ANTIS_SPEED_START_MIN 30  /* [%] Start anti-spin only for throttle requests above this threshold */
#define ANTIS_SPEED_START_MAX 65  /* [%] Maximum anti-spin start threshold */

/**
 * @brief Apply anti-spin control to prevent car drift
 * @details Applies a ramp to output speed to prevent sudden speed changes that cause wheel spin.
 *          Anti-spin time is the time taken from minSpeed to maxSpeed, selected by user.
 *          Anti-spin is bypassed at low duty cycles (< antispinPercStart) where current is too low to cause spinning.
 *          The antispinPercStart threshold varies with the antiSpin setting:
 *          - High antiSpin (200ms) = Low threshold (powerful motor/slippery track)
 *          - Low antiSpin = High threshold (good traction)
 * 
 * @param requestedSpeed [%] Requested output speed (0-100%)
 * @return [%] Actual output speed respecting anti-spin ramp limits
 */
uint16_t throttleAntiSpin3(uint16_t requestedSpeed) {
  static uint32_t lastOutputSpeedx1000 = 0;
  static unsigned long prevCall_uS = 0;
  
  unsigned long currCall_uS = micros();
  unsigned long deltaTime_uS = currCall_uS - prevCall_uS;
  prevCall_uS = currCall_uS;

  /* Calculate dynamic anti-spin start threshold based on anti-spin setting */
  uint16_t antispinPercStart = map((long)g_storedVar.carParam[g_carSel].antiSpin, 0, (long)ANTISPIN_MAX_VALUE, 
                                    (long)ANTIS_SPEED_START_MAX, (long)ANTIS_SPEED_START_MIN);

  /* Bypass anti-spin if disabled */
  if (g_storedVar.carParam[g_carSel].antiSpin == 0) {
    lastOutputSpeedx1000 = g_storedVar.carParam[g_carSel].minSpeed * 1000;
    return requestedSpeed;
  }

  /* Bypass anti-spin at low speeds (insufficient current for wheel spin) */
  if (requestedSpeed < antispinPercStart) {
    lastOutputSpeedx1000 = requestedSpeed * 1000;
    return requestedSpeed;
  }

  /* Allow immediate deceleration (braking) */
  if ((uint32_t)requestedSpeed * 1000 <= lastOutputSpeedx1000) {
    lastOutputSpeedx1000 = requestedSpeed * 1000;
    return requestedSpeed;
  }

  /* Apply anti-spin ramp for acceleration */
  uint16_t minSpeedTmp = max((uint16_t)g_storedVar.carParam[g_carSel].minSpeed, antispinPercStart);
  
  /* Calculate maximum allowed speed change: deltaSpeed = ((minSpeed-maxSpeed) * deltaTime) / antiSpin */
  uint32_t maxDeltaSpeedx1000 = ((g_storedVar.carParam[g_carSel].maxSpeed - minSpeedTmp) * deltaTime_uS) / 
                                 g_storedVar.carParam[g_carSel].antiSpin;

  uint32_t outputSpeedX1000;
  
  /* Check if we can increase speed by full delta or if we're close to target */
  if (lastOutputSpeedx1000 < ((uint32_t)requestedSpeed * 1000 - maxDeltaSpeedx1000)) {
    outputSpeedX1000 = lastOutputSpeedx1000 + maxDeltaSpeedx1000;
  } else {
    outputSpeedX1000 = requestedSpeed * 1000;  /* Target reached */
  }

  /* Ensure ramp starts from minSpeed, not zero */
  if (outputSpeedX1000 < g_storedVar.carParam[g_carSel].minSpeed * 1000) {
    outputSpeedX1000 = g_storedVar.carParam[g_carSel].minSpeed * 1000;
  }

  lastOutputSpeedx1000 = outputSpeedX1000;
  return outputSpeedX1000 / 1000;
}


/**
 * Accounts for a deadband in an input value.
 * 
 * @param inputVal The input value
 * @param minVal The lower bound of the input value range
 * @param maxVal The upper bound of the input value range
 * @param deadBand The deadband as absolute value (not a percentage)
 * @return If the input value is less than the minVal + deadBand, it returns minVal.
           If the input value is more than the maxVal - deadBand, it returns the maxVal.
           Otherwise, it returns the inputVal, scaled in order to range from minVal to maxVal.
 */
uint16_t addDeadBand(uint16_t inputVal, uint16_t minVal, uint16_t maxVal, uint16_t deadBand) 
{
  uint16_t retVal = 0;

  /* If the inputVal is less than deadBand_pct, return 0 */
  if (inputVal < minVal + deadBand) 
  {
    retVal = 0;
  } 
  /* If the inputVal is more than maxValue - deadBand, return maxValue */
  else if (inputVal > maxVal - deadBand) 
  {
    retVal = maxVal;
  } 
  else 
  {
    /* retVal = (THROTTLE_NORMALIZED * (inputVal - deadBand)) / (THROTTLE_NORMALIZED - 2 * deadBand); TODO: verify what this is suppose to do */
    retVal = map(inputVal, deadBand, maxVal - deadBand, minVal, maxVal);  /* Scale the inputValue (which ranges from (minVal + deadBand) to (maxVal - deadBand))
                                                                             so that it ranges from minVal to maxVal */
  }

  return retVal;
}

/**
 * throttleCurve2: Map trigger position(throttle) to speed (duty) on a broken line curve, with midpoint set as throttleCurveVertex
 * dual throttle curve: When decelerating , if dragB is higher than 100%-minSpeed, then set a lower minSpeed
 * @param inputThrottleNorm The input Trigger value, normalized between 0 and THROTTLE_NORMALIZED
 * @return duty cyle to be applied at that specific thrigger position on the selected curve
 */
uint16_t throttleCurve2(uint16_t inputThrottleNorm )
{
  uint16_t outputSpeed = 0;           /* The requested output speed (duty cycle) from 0% to 100% */
  uint32_t throttleCurveVertexSpeed;  /* The output speed when the throttle is at 50% (that is, the value of throttleCurveVertex.inputThrottle) */
  uint16_t tmpMinSpeed;               /* Minimum speed may change when decelerating due to drag brake, so create a temporary min speed */

  /* dual throttle curve: When decelerating , if dragB is higher than 100%-minSpeed, then set a lower minSpeed on the curve to allow the desired drag brake to be applied*/
  tmpMinSpeed = g_storedVar.carParam[g_carSel].minSpeed;

  /* Calculate the output speed of the throttle curve vertex
     This is calculated as the curveSpeedDiff (from 10% to 90%) percentage of the difference between minSpeed and maxSpeed */
  throttleCurveVertexSpeed = tmpMinSpeed + (((uint32_t)g_storedVar.carParam[g_carSel].maxSpeed - (uint32_t)tmpMinSpeed) * ((uint32_t)g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff) / 100);

  if (inputThrottleNorm == 0)   /* If input throttle is 0 --> output speed is 0% */
  {
    outputSpeed = 0;
  } 
  else if (inputThrottleNorm <= g_storedVar.carParam[g_carSel].throttleCurveVertex.inputThrottle) /* If the input throttle is less than the vertex point (fixed at 50%), than map the output speed from 0 to the throttleCurveVertexSpeed */
  {
    outputSpeed = map(inputThrottleNorm, 0, g_storedVar.carParam[g_carSel].throttleCurveVertex.inputThrottle, tmpMinSpeed, throttleCurveVertexSpeed);
  } 
  else  /* If the input throttle is more than the vertex point (fixed at 50%), than map the output speed from throttleCurveVertexSpeed to the maxSpeed*/
  {
    outputSpeed = map(inputThrottleNorm, g_storedVar.carParam[g_carSel].throttleCurveVertex.inputThrottle, THROTTLE_NORMALIZED, throttleCurveVertexSpeed, g_storedVar.carParam[g_carSel].maxSpeed);
  }

  return outputSpeed;
}

/**
 * Call this when calibrating the throttle.
 * Check if the parameter adcRaw is bigger/smaller than the stored max/min values, and updates them accordingly.
 * @param inputThrottle The raw ADC value
 */
void throttleCalibration(int16_t adcRaw)
{
  if (g_storedVar.maxTrigger_raw < adcRaw)
    {
      g_storedVar.maxTrigger_raw = adcRaw;
    }
  if (g_storedVar.minTrigger_raw > adcRaw)
    {
      g_storedVar.minTrigger_raw = adcRaw;
    }
}


/**
 * Reacts to the rotary encoder being clicked.
 * If the menu is in ITEM_SELECTION, it must select the correct item (update the g_encoderSelectedValuePtr) or invoking the item's callback --> then return the next state VALUE_SELECTION
 * If the menu is in VALUE_SELECTION, it must return to ITEM_SELECTION
 * 
 * @param currMenuState The current menu state.
 * @return The next menu state.
 */
MenuState_enum rotary_onButtonClick(MenuState_enum currMenuState)
{
  static unsigned long lastTimePressed = 0;
  static uint16_t selectedParamMaxValue = 100;
  static uint16_t selectedParamMinValue = 0;

  /* Ignore multiple presses that are too close together */
  if (millis() - lastTimePressed < BUTTON_SHORT_PRESS_DEBOUNCE_MS)
  {
    return currMenuState;
  }

  lastTimePressed = millis();

  if (currMenuState == ITEM_SELECTION) /* If the current state is ITEM_SELECTION */
  {
    /* Special handling for GRID mode - map grid item to car parameter */
    if (g_storedVar.viewMode == VIEW_MODE_GRID)
    {
      uint8_t gridItem = g_encoderMainSelector - 1;  /* 0-4 (FULL) or 0-2 (SIMPLE) */
      g_rotaryEncoder.setAcceleration(SEL_ACCELERATION);

      /* Map grid item to parameter pointer and limits based on race view mode */
      if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
        /* SIMPLE mode: 0=BRAKE, 1=SENSI, 2=CAR */
        switch (gridItem) {
          case 0:  /* BRAKE */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].brake;
            selectedParamMaxValue = BRAKE_MAX_VALUE;
            selectedParamMinValue = 0;
            break;
          case 1:  /* SENSI (minSpeed) */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].minSpeed;
            selectedParamMaxValue = MIN_SPEED_MAX_VALUE;
            selectedParamMinValue = 0;
            break;
          case 2:  /* CAR - select different car */
            g_encoderSelectedValuePtr = &g_storedVar.selectedCarNumber;
            selectedParamMaxValue = CAR_MAX_COUNT - 1;
            selectedParamMinValue = 0;
            g_isEditingCarSelection = true;  /* Prevent g_carSel update during edit */
            break;
          default:
            return ITEM_SELECTION;
        }
      }
      else {
        /* FULL mode: 0=BRAKE, 1=SENSI, 2=ANTIS, 3=CURVE, 4=CAR */
        switch (gridItem) {
          case 0:  /* BRAKE */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].brake;
            selectedParamMaxValue = BRAKE_MAX_VALUE;
            selectedParamMinValue = 0;
            break;
          case 1:  /* SENSI (minSpeed) */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].minSpeed;
            selectedParamMaxValue = MIN_SPEED_MAX_VALUE;
            selectedParamMinValue = 0;
            break;
          case 2:  /* ANTIS (antiSpin) */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].antiSpin;
            selectedParamMaxValue = ANTISPIN_MAX_VALUE;
            selectedParamMinValue = 0;
            break;
          case 3:  /* CURVE */
            g_encoderSelectedValuePtr = &g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff;
            selectedParamMaxValue = THROTTLE_CURVE_SPEED_DIFF_MAX_VALUE;
            selectedParamMinValue = THROTTLE_CURVE_SPEED_DIFF_MIN_VALUE;
            break;
          case 4:  /* CAR - select different car */
            g_encoderSelectedValuePtr = &g_storedVar.selectedCarNumber;
            selectedParamMaxValue = CAR_MAX_COUNT - 1;
            selectedParamMinValue = 0;
            g_isEditingCarSelection = true;  /* Prevent g_carSel update during edit */
            break;
          default:
            return ITEM_SELECTION;
        }
      }

      g_rotaryEncoder.setBoundaries(selectedParamMinValue, selectedParamMaxValue, false);
      g_rotaryEncoder.reset(*g_encoderSelectedValuePtr);
      g_escVar.encoderPos = *g_encoderSelectedValuePtr;
      g_originalValueBeforeEdit = *g_encoderSelectedValuePtr;  /* Save original value for cancel */
      return VALUE_SELECTION;
    }
    /* LIST mode handling */
    /* If an item has no callback, go in menu state VALUE_SELECTION */
    else if (g_mainMenu.item[g_encoderMainSelector - 1].callback == ITEM_NO_CALLBACK)
    {
      g_rotaryEncoder.setAcceleration(SEL_ACCELERATION); /* Set higher encoder acceleration so it doesn't require too many turns to make a big value change */


      g_encoderSelectedValuePtr = (uint16_t *)g_mainMenu.item[g_encoderMainSelector - 1].value;   /* Update the g_encoderSelectedValuePtr to point to the value of the selected item.
                                                                                                     value is a generic pointer to void, so cast to uint16_t pointer */
      selectedParamMaxValue = g_mainMenu.item[g_encoderMainSelector - 1].maxValue;                /* Set Max and Min boundaries according to the selected items max and min value */
      selectedParamMinValue = g_mainMenu.item[g_encoderMainSelector - 1].minValue;
      g_rotaryEncoder.setBoundaries(selectedParamMinValue, selectedParamMaxValue, false);
      g_rotaryEncoder.reset(*g_encoderSelectedValuePtr);  /* Reset the encoder to the current value of the selected item */
      g_escVar.encoderPos = *g_encoderSelectedValuePtr;   /* Set the encoderPos global variable to the current value of the selected item */
      g_originalValueBeforeEdit = *g_encoderSelectedValuePtr;  /* Save original value for cancel */
      return VALUE_SELECTION;                             /* Return the VALUE_SELECTION state */
    }
    /* if an item has a callback, execute it, then return to ITEM SELECTION */
    else
    {
      g_mainMenu.item[g_encoderMainSelector - 1].callback();  /* Invoke the selected item's callback */
      return ITEM_SELECTION;
    }
  }
  else /* If the current state is VALUE_SELECTION */
  {
    g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);         /* Set the encoder acceleration to MENU_ACCELERATION */

    /* Set boundaries based on view mode */
    if (g_storedVar.viewMode == VIEW_MODE_GRID) {
      uint8_t gridItems;
      if (g_storedVar.raceViewMode == RACE_VIEW_SIMPLE) {
        gridItems = g_storedVar.gridCarSelectEnabled ? 3 : 2;  /* SIMPLE: BRAKE, SENSI, CAR (optional) */
      } else {
        gridItems = g_storedVar.gridCarSelectEnabled ? 5 : 4;  /* FULL: BRAKE, SENSI, ANTIS, CURVE, CAR (optional) */
      }
      g_rotaryEncoder.setBoundaries(1, gridItems, false);
    } else {
      g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);  /* Set the encoder boundaries to the menu boundaries */
    }

    g_rotaryEncoder.reset(g_encoderMainSelector);               /* Reset the encoder value to g_encoderMainSelector, so that it doesn't change the selected item */
    g_escVar.encoderPos = g_encoderMainSelector;

    g_isEditingCarSelection = false;  /* Clear flag - editing complete */
    saveEEPROM(g_storedVar);  /* Save modified values to EEPROM */
    return ITEM_SELECTION;    /* Return the ITEM_SELECTION state */
  }
}


/**
 * Show the Car selection menu.
 * Uses a "Frame" just like the main menu to display and scroll through the carMenu items.
 * Scrolling the Cars is actually changing the value of selectedCarNumber.
 */
void showCarSelection() {
  /* "Frame" indicates which items are currently displayed.
     It consist of a lower and upper bound: only the items within this boundaries are displayed.
     The difference between upper and lower bound is fixed to be g_carMenu.lines
     It's important that the encoder boundaries matches the menu items (e.g., 10 items (cars), encoder boundaries must be [0,9]) */
  static uint16_t frameUpper = 1;
  static uint16_t frameLower = g_carMenu.lines;

  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Save original value for cancel */
  uint16_t originalCarNumber = g_storedVar.selectedCarNumber;

  /* Set encoder to car selection parameter */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(0, CAR_MAX_COUNT - 1, false);
  g_rotaryEncoder.reset(g_storedVar.selectedCarNumber);

  /* Screensaver support */
  uint32_t lastInteraction = millis();
  bool screensaverActive = false;
  uint16_t screensaverEncoderPos = 0;

  /* Exit car selection when encoder is clicked */
  while (!g_rotaryEncoder.isEncoderButtonClicked())
  {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (screensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != screensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        screensaverActive = false;
        lastInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!screensaverActive) {
          screensaverActive = true;
          screensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for brake button press - cancel and exit */
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      lastInteraction = millis();
      delay(BUTTON_SHORT_PRESS_DEBOUNCE_MS);
      g_storedVar.selectedCarNumber = originalCarNumber;  /* Restore original */
      obdFill(&g_obd, OBD_WHITE, 1);
      return;
    }

    /* Get encoder value if changed */
    if (g_rotaryEncoder.encoderChanged()) {
      lastInteraction = millis();
      g_storedVar.selectedCarNumber = g_rotaryEncoder.readEncoder();
    }

    /* If encoder move out of frame, adjust frame */
    if (g_storedVar.selectedCarNumber > frameLower)
    {
      frameLower = g_storedVar.selectedCarNumber;
      frameUpper = frameLower - g_carMenu.lines + 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }
    else if (g_storedVar.selectedCarNumber < frameUpper)
    {
      frameUpper = g_storedVar.selectedCarNumber;
      frameLower = frameUpper + g_carMenu.lines - 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }

    /* Print car menu */
    for (uint8_t i = 0; i < g_carMenu.lines; i++)
    {
      /* Print the item (car) name */
      obdWriteString(&g_obd, 0, 0, i * HEIGHT12x16, g_carMenu.item[frameUpper + i].name, FONT_12x16, (g_storedVar.selectedCarNumber - frameUpper == i) ? OBD_WHITE : OBD_BLACK, 1);
      if (g_carMenu.item[frameUpper + i].value != ITEM_NO_VALUE)
      {
        /* value is a generic pointer to void, so first cast to uint16_t pointer, then take the pointed value */
        sprintf(msgStr, "%2d", *(uint16_t *)(g_carMenu.item[frameUpper + i].value));
        /* Print the item value (car number) */
        obdWriteString(&g_obd, 0, OLED_WIDTH - 24, i * HEIGHT12x16, msgStr, FONT_12x16, OBD_BLACK, 1);
      }
    }

    /* Print "-SELECT THE CAR-" on the bottom of the screen */
    obdWriteString(&g_obd, 0, 16, OLED_HEIGHT - HEIGHT8x8, (char *)"-SELECT THE CAR-", FONT_6x8, OBD_WHITE, 1);
  }

  /* Reset encoder and clear is done in caller routine */
  return;
}


/**
 * Show the Copy Car Settings screen. Allows copying all parameters from one car to another.
 */
void showCopyCarSettings() {
  static uint16_t frameUpper = 1;
  static uint16_t frameLower = g_carMenu.lines;
  uint16_t sourceCar = 0;
  uint16_t destCar = 0;

  /* ========== SELECT SOURCE CAR (FROM) ========== */
  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Screensaver support */
  uint32_t lastInteraction = millis();
  bool screensaverActive = false;
  uint16_t screensaverEncoderPos = 0;

  /* Set encoder to car selection parameter */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(0, CAR_MAX_COUNT - 1, false);
  g_rotaryEncoder.reset(g_storedVar.selectedCarNumber);
  sourceCar = g_storedVar.selectedCarNumber;

  /* Select source car */
  while (!g_rotaryEncoder.isEncoderButtonClicked())
  {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (screensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != screensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        screensaverActive = false;
        lastInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!screensaverActive) {
          screensaverActive = true;
          screensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for brake button press - cancel and exit */
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      lastInteraction = millis();
      delay(BUTTON_SHORT_PRESS_DEBOUNCE_MS);
      obdFill(&g_obd, OBD_WHITE, 1);
      return;
    }

    /* Get encoder value if changed */
    if (g_rotaryEncoder.encoderChanged()) {
      lastInteraction = millis();
      sourceCar = g_rotaryEncoder.readEncoder();
    }

    /* If encoder move out of frame, adjust frame */
    if (sourceCar > frameLower)
    {
      frameLower = sourceCar;
      frameUpper = frameLower - g_carMenu.lines + 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }
    else if (sourceCar < frameUpper)
    {
      frameUpper = sourceCar;
      frameLower = frameUpper + g_carMenu.lines - 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }

    /* Print car menu */
    for (uint8_t i = 0; i < g_carMenu.lines; i++)
    {
      /* Print the item (car) name */
      obdWriteString(&g_obd, 0, 0, i * HEIGHT12x16, g_carMenu.item[frameUpper + i].name, FONT_12x16, (sourceCar - frameUpper == i) ? OBD_WHITE : OBD_BLACK, 1);
      if (g_carMenu.item[frameUpper + i].value != ITEM_NO_VALUE)
      {
        /* Print the item value (car number) */
        sprintf(msgStr, "%2d", *(uint16_t *)(g_carMenu.item[frameUpper + i].value));
        obdWriteString(&g_obd, 0, OLED_WIDTH - 24, i * HEIGHT12x16, msgStr, FONT_12x16, OBD_BLACK, 1);
      }
    }

    /* Print "COPY FROM:" on the bottom of the screen */
    obdWriteString(&g_obd, 0, 28, OLED_HEIGHT - HEIGHT8x8, (char *)"-COPY FROM:-", FONT_6x8, OBD_WHITE, 1);
  }

  /* Small delay to prevent double-click */
  delay(200);

  /* ========== SELECT DESTINATION CAR (TO) ========== */
  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Reset screensaver tracking */
  lastInteraction = millis();
  screensaverActive = false;

  /* Reset encoder for destination car selection (CAR_MAX_COUNT = ALL option) */
  g_rotaryEncoder.setBoundaries(0, CAR_MAX_COUNT, false);  /* 0-19 = cars, 20 = ALL */
  g_rotaryEncoder.reset(g_storedVar.selectedCarNumber);
  destCar = g_storedVar.selectedCarNumber;

  /* Reset frame if needed */
  frameUpper = 1;
  frameLower = g_carMenu.lines;

  uint8_t visibleLines = g_carMenu.lines;
  const uint16_t ALL_CARS_OPTION = CAR_MAX_COUNT;  /* Index for "ALL" option */

  /* Select destination car */
  while (!g_rotaryEncoder.isEncoderButtonClicked())
  {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (screensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != screensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        screensaverActive = false;
        lastInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!screensaverActive) {
          screensaverActive = true;
          screensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for brake button press - cancel and exit */
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      lastInteraction = millis();
      delay(BUTTON_SHORT_PRESS_DEBOUNCE_MS);
      obdFill(&g_obd, OBD_WHITE, 1);
      return;
    }

    /* Get encoder value if changed */
    if (g_rotaryEncoder.encoderChanged()) {
      lastInteraction = millis();
      destCar = g_rotaryEncoder.readEncoder();
    }

    /* If encoder move out of frame, adjust frame */
    if (destCar > frameLower)
    {
      frameLower = destCar;
      frameUpper = frameLower - visibleLines + 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }
    else if (destCar < frameUpper)
    {
      frameUpper = destCar;
      frameLower = frameUpper + visibleLines - 1;
      obdFill(&g_obd, OBD_WHITE, 1);
    }

    /* Print car menu */
    for (uint8_t i = 0; i < visibleLines; i++)
    {
      uint16_t itemIndex = frameUpper + i;
      bool isSelected = (destCar == itemIndex);

      if (itemIndex == ALL_CARS_OPTION) {
        /* Print "ALL" option */
        obdWriteString(&g_obd, 0, 0, i * HEIGHT12x16, (char *)"ALL", FONT_12x16, isSelected ? OBD_WHITE : OBD_BLACK, 1);
      } else if (itemIndex < CAR_MAX_COUNT) {
        /* Print the item (car) name */
        obdWriteString(&g_obd, 0, 0, i * HEIGHT12x16, g_carMenu.item[itemIndex].name, FONT_12x16, isSelected ? OBD_WHITE : OBD_BLACK, 1);
        if (g_carMenu.item[itemIndex].value != ITEM_NO_VALUE)
        {
          /* Print the item value (car number) */
          sprintf(msgStr, "%2d", *(uint16_t *)(g_carMenu.item[itemIndex].value));
          obdWriteString(&g_obd, 0, OLED_WIDTH - 24, i * HEIGHT12x16, msgStr, FONT_12x16, OBD_BLACK, 1);
        }
      }
    }

    /* Print "-COPY TO:-" on the bottom of the screen */
    obdWriteString(&g_obd, 0, 34, OLED_HEIGHT - HEIGHT8x8, (char *)"-COPY TO:-", FONT_6x8, OBD_WHITE, 1);
  }

  /* Copy car parameters */
  if (destCar == ALL_CARS_OPTION) {
    /* Copy to ALL cars (except source car) */
    for (uint16_t i = 0; i < CAR_MAX_COUNT; i++) {
      if (i != sourceCar) {
        g_storedVar.carParam[i].minSpeed = g_storedVar.carParam[sourceCar].minSpeed;
        g_storedVar.carParam[i].brake = g_storedVar.carParam[sourceCar].brake;
        g_storedVar.carParam[i].dragBrake = g_storedVar.carParam[sourceCar].dragBrake;
        g_storedVar.carParam[i].maxSpeed = g_storedVar.carParam[sourceCar].maxSpeed;
        g_storedVar.carParam[i].throttleCurveVertex.inputThrottle = g_storedVar.carParam[sourceCar].throttleCurveVertex.inputThrottle;
        g_storedVar.carParam[i].throttleCurveVertex.curveSpeedDiff = g_storedVar.carParam[sourceCar].throttleCurveVertex.curveSpeedDiff;
        g_storedVar.carParam[i].antiSpin = g_storedVar.carParam[sourceCar].antiSpin;
        g_storedVar.carParam[i].freqPWM = g_storedVar.carParam[sourceCar].freqPWM;
        g_storedVar.carParam[i].brakeButtonReduction = g_storedVar.carParam[sourceCar].brakeButtonReduction;
      }
    }
    /* Show confirmation message */
    obdFill(&g_obd, OBD_WHITE, 1);
    obdWriteString(&g_obd, 0, 0, 24, (char *)"COPIED ALL", FONT_12x16, OBD_BLACK, 1);
    delay(1000);
  } else if (sourceCar != destCar) {
    /* Copy to single car */
    g_storedVar.carParam[destCar].minSpeed = g_storedVar.carParam[sourceCar].minSpeed;
    g_storedVar.carParam[destCar].brake = g_storedVar.carParam[sourceCar].brake;
    g_storedVar.carParam[destCar].dragBrake = g_storedVar.carParam[sourceCar].dragBrake;
    g_storedVar.carParam[destCar].maxSpeed = g_storedVar.carParam[sourceCar].maxSpeed;
    g_storedVar.carParam[destCar].throttleCurveVertex.inputThrottle = g_storedVar.carParam[sourceCar].throttleCurveVertex.inputThrottle;
    g_storedVar.carParam[destCar].throttleCurveVertex.curveSpeedDiff = g_storedVar.carParam[sourceCar].throttleCurveVertex.curveSpeedDiff;
    g_storedVar.carParam[destCar].antiSpin = g_storedVar.carParam[sourceCar].antiSpin;
    g_storedVar.carParam[destCar].freqPWM = g_storedVar.carParam[sourceCar].freqPWM;
    g_storedVar.carParam[destCar].brakeButtonReduction = g_storedVar.carParam[sourceCar].brakeButtonReduction;

    /* Show confirmation message */
    obdFill(&g_obd, OBD_WHITE, 1);
    obdWriteString(&g_obd, 0, 34, 24, (char *)"COPIED!", FONT_12x16, OBD_BLACK, 1);
    delay(1000);
  }

  /* Reset frame for next time */
  frameUpper = 1;
  frameLower = g_carMenu.lines;

  return;
}


/**
 * Show the options to Select or Rename the Car, called upon selecting the CAR item in the main menu
 */
void showSelectRenameCar() {

  /* Trigger reading stops, so stop the motor */
  /* Set trigRaw to max throttle if throttle is reversed, set to min throttle otherwise */
  /* g_escVar.trigger_raw = THROTTLE_REV ? g_storedVar.maxTrigger_raw : g_storedVar.minTrigger_raw; */ /*TODO: decide what to do now that trigger reading is done on task 2 */

  uint16_t selectedOption = 0;
  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Set encoder to selection parameter */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(0, 5, false); /* Boundaries are [0, 5] because there are six options */
  g_rotaryEncoder.reset(selectedOption);

  /* Setup scrolling frame - number of visible items depends on font size */
  const uint8_t totalOptions = 6;
  uint8_t visibleLines = getMenuLines();
  uint8_t frameUpper = 0;
  uint8_t frameLower = visibleLines - 1;

  /* Track editing state for RACESWP option */
  bool isEditingRaceswp = false;
  uint16_t tempRaceswpValue = g_storedVar.gridCarSelectEnabled;

  /* Screensaver support */
  uint32_t lastInteraction = millis();
  bool screensaverActive = false;
  uint16_t screensaverEncoderPos = 0;

  /* Exit car selection when encoder is clicked */
  while (!g_rotaryEncoder.isEncoderButtonClicked())
  {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (screensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != screensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        screensaverActive = false;
        lastInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!screensaverActive) {
          screensaverActive = true;
          screensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for brake button press - acts as "back" in CAR menu */
    static bool brakeBtnInCarMenu = false;
    static uint32_t lastBrakeBtnCarMenuTime = 0;
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      if (!brakeBtnInCarMenu && millis() - lastBrakeBtnCarMenuTime > BUTTON_SHORT_PRESS_DEBOUNCE_MS) {
        brakeBtnInCarMenu = true;
        lastBrakeBtnCarMenuTime = millis();
        lastInteraction = millis();

        if (isEditingRaceswp) {
          /* Cancel RACESWP editing */
          isEditingRaceswp = false;
          g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
          g_rotaryEncoder.setBoundaries(0, 5, false);
          g_rotaryEncoder.reset(selectedOption);
        } else {
          /* Exit CAR menu completely */
          goto exitCarMenu;
        }
      }
    } else {
      brakeBtnInCarMenu = false;
    }

    /* Get encoder value if changed */
    if (g_rotaryEncoder.encoderChanged()) {
      lastInteraction = millis();
      if (!isEditingRaceswp) {
        selectedOption = g_rotaryEncoder.readEncoder();
      } else {
        /* When editing RACESWP, encoder changes the value */
        tempRaceswpValue = g_rotaryEncoder.readEncoder();
      }
    }

    /* Adjust frame if selection moves outside visible area (only when not editing) */
    if (!isEditingRaceswp) {
      if (selectedOption > frameLower)
      {
        frameLower = selectedOption;
        frameUpper = frameLower - visibleLines + 1;
        obdFill(&g_obd, OBD_WHITE, 1);
      }
      else if (selectedOption < frameUpper)
      {
        frameUpper = selectedOption;
        frameLower = frameUpper + visibleLines - 1;
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Determine font size and dimensions based on setting */
    uint8_t menuFont = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? FONT_8x8 : FONT_12x16;
    uint8_t charWidth = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? WIDTH8x8 : WIDTH12x16;
    uint8_t lineHeight = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? 8 : HEIGHT12x16;

    /* Display only the visible items within the frame */
    for (uint8_t i = 0; i < visibleLines; i++)
    {
      uint8_t optionIndex = frameUpper + i;
      if (optionIndex >= totalOptions) break;

      uint8_t yPos = i * lineHeight;
      bool isSelected = (optionIndex == selectedOption);

      uint16_t lang = g_storedVar.language;

      switch (optionIndex)
      {
        case CAR_OPTION_SELECT:
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 0), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          break;

        case CAR_OPTION_RENAME:
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 1), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          break;

        case CAR_OPTION_GRID_SEL:
        {
          /* Grid select option - show label and right-aligned ON/OFF value */
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 2), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          /* Show temp value when editing, stored value otherwise */
          uint16_t displayValue = isEditingRaceswp ? tempRaceswpValue : g_storedVar.gridCarSelectEnabled;
          sprintf(msgStr, "%s", getOnOffLabel(lang, displayValue ? 1 : 0));
          int textWidth = strlen(msgStr) * charWidth;
          /* Value is white when editing, follows selection otherwise */
          uint8_t valueColor = isEditingRaceswp ? OBD_WHITE : (isSelected ? OBD_WHITE : OBD_BLACK);
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, yPos, msgStr, menuFont, valueColor, 1);
          break;
        }

        case CAR_OPTION_COPY:
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 3), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          break;

        case CAR_OPTION_RESET:
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 4), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          break;

        case CAR_OPTION_BACK:
        {
          /* Display BACK option using helper for text case support */
          obdWriteString(&g_obd, 0, 0, yPos, (char *)getBackLabel(lang), menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);
          break;
        }
      }
    }
  }

  /* Handle encoder click based on current state */
  if (selectedOption == CAR_OPTION_GRID_SEL && !isEditingRaceswp) {
    /* First click on RACESWP: enter edit mode */
    isEditingRaceswp = true;
    g_rotaryEncoder.setAcceleration(SEL_ACCELERATION);
    g_rotaryEncoder.setBoundaries(0, 1, false);  /* 0=OFF, 1=ON */
    g_rotaryEncoder.reset(tempRaceswpValue);
    /* Wait for second click to confirm */
    while (!g_rotaryEncoder.isEncoderButtonClicked()) {
      /* Check for brake button to cancel editing */
      if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        delay(BUTTON_SHORT_PRESS_DEBOUNCE_MS);
        /* Cancel editing - restore encoder for option selection */
        isEditingRaceswp = false;
        g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
        g_rotaryEncoder.setBoundaries(0, 5, false);
        g_rotaryEncoder.reset(selectedOption);
        obdFill(&g_obd, OBD_WHITE, 1);
        break;
      }

      tempRaceswpValue = g_rotaryEncoder.encoderChanged() ? g_rotaryEncoder.readEncoder() : tempRaceswpValue;

      /* Redraw the RACESWP option with updated value */
      uint8_t optionScreenPos = CAR_OPTION_GRID_SEL - frameUpper;
      if (optionScreenPos < visibleLines) {
        /* Determine font size and dimensions based on setting */
        uint8_t menuFont = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? FONT_8x8 : FONT_12x16;
        uint8_t charWidth = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? WIDTH8x8 : WIDTH12x16;
        uint8_t lineHeight = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? 8 : HEIGHT12x16;
        uint8_t yPos = optionScreenPos * lineHeight;
        uint16_t lang = g_storedVar.language;

        obdWriteString(&g_obd, 0, 0, yPos, (char *)getCarMenuOption(lang, 2), menuFont, OBD_WHITE, 1);
        sprintf(msgStr, "%s", getOnOffLabel(lang, tempRaceswpValue ? 1 : 0));
        int textWidth = strlen(msgStr) * charWidth;
        obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, yPos, msgStr, menuFont, OBD_WHITE, 1);
      }
    }
    /* Save the confirmed value (only if we didn't cancel) */
    if (isEditingRaceswp) {
      g_storedVar.gridCarSelectEnabled = tempRaceswpValue;
      selectedOption = CAR_OPTION_GRID_SEL;  /* Mark as handled */
    }
  }

  /* If RENAME option was selected, go to renameCar routine */
  if (selectedOption == CAR_OPTION_RENAME)
  {
    showRenameCar();
    saveEEPROM(g_storedVar);
  }
  /* If SELECT option was selected, go to showCarSelection routine */
  else if (selectedOption == CAR_OPTION_SELECT)
  {
    showCarSelection();
    saveEEPROM(g_storedVar);
  }
  /* If RACESWP option was selected, value was already saved in the edit loop above */
  else if (selectedOption == CAR_OPTION_GRID_SEL)
  {
    saveEEPROM(g_storedVar);
  }
  /* If COPY option was selected, go to showCopyCarSettings routine */
  else if (selectedOption == CAR_OPTION_COPY)
  {
    showCopyCarSettings();
    saveEEPROM(g_storedVar);
  }
  /* If RESET option was selected, reset all car parameters with double confirmation */
  else if (selectedOption == CAR_OPTION_RESET)
  {
    /* Clear screen and show first confirmation */
    obdFill(&g_obd, OBD_WHITE, 1);
    uint16_t lang = g_storedVar.language;
    const char* confirmText1 = (lang == LANG_NOR) ? "NULLSTILL ALLE" : "RESET ALL CARS";
    const char* confirmText2 = (lang == LANG_NOR) ? "BILER?" : "?";
    const char* confirmText3 = (lang == LANG_NOR) ? "TRYKK 2 GANGER" : "PRESS TWICE";
    const char* cancelText = (lang == LANG_NOR) ? "BREMSEKNAPP=AVBRYT" : "BRAKE BUTTON=CANCEL";

    obdWriteString(&g_obd, 0, 10, 5, (char *)confirmText1, FONT_8x8, OBD_BLACK, 1);
    obdWriteString(&g_obd, 0, 10, 15, (char *)confirmText2, FONT_8x8, OBD_BLACK, 1);
    obdWriteString(&g_obd, 0, 10, 30, (char *)confirmText3, FONT_6x8, OBD_BLACK, 1);
    obdWriteString(&g_obd, 0, 10, 45, (char *)cancelText, FONT_6x8, OBD_BLACK, 1);

    /* Wait for first confirmation click or brake button to cancel */
    bool cancelled = false;
    while (!g_rotaryEncoder.isEncoderButtonClicked()) {
      if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        cancelled = true;
        break;
      }
      delay(10);
    }
    if (cancelled) {
      /* Show cancelled message */
      obdFill(&g_obd, OBD_WHITE, 1);
      const char* cancelledText = (lang == LANG_NOR) ? "AVBRUTT!" : "CANCELLED!";
      int textWidth = strlen(cancelledText) * WIDTH12x16;
      obdWriteString(&g_obd, 0, (OLED_WIDTH - textWidth) / 2, 24, (char *)cancelledText, FONT_12x16, OBD_BLACK, 1);
      delay(1000);
    } else {
      delay(200);  /* Debounce */

      /* Show second confirmation */
      obdFill(&g_obd, OBD_WHITE, 1);
      const char* confirmText4 = (lang == LANG_NOR) ? "TRYKK IGJEN" : "PRESS AGAIN";
      const char* confirmText5 = (lang == LANG_NOR) ? "FOR A BEKREFTE" : "TO CONFIRM";
      obdWriteString(&g_obd, 0, 10, 10, (char *)confirmText4, FONT_8x8, OBD_BLACK, 1);
      obdWriteString(&g_obd, 0, 10, 20, (char *)confirmText5, FONT_6x8, OBD_BLACK, 1);
      obdWriteString(&g_obd, 0, 10, 45, (char *)cancelText, FONT_6x8, OBD_BLACK, 1);

      /* Wait for second confirmation click or brake button to cancel */
      while (!g_rotaryEncoder.isEncoderButtonClicked()) {
        if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
          cancelled = true;
          break;
        }
        delay(10);
      }

      if (cancelled) {
        /* Show cancelled message */
        obdFill(&g_obd, OBD_WHITE, 1);
        const char* cancelledText = (lang == LANG_NOR) ? "AVBRUTT!" : "CANCELLED!";
        int textWidth = strlen(cancelledText) * WIDTH12x16;
        obdWriteString(&g_obd, 0, (OLED_WIDTH - textWidth) / 2, 24, (char *)cancelledText, FONT_12x16, OBD_BLACK, 1);
        delay(1000);
      } else {
        delay(200);  /* Debounce */

        /* Reset all car parameters to defaults */
        for (uint8_t i = 0; i < CAR_MAX_COUNT; i++) {
          g_storedVar.carParam[i].minSpeed = MIN_SPEED_DEFAULT;
          g_storedVar.carParam[i].brake = BRAKE_DEFAULT;
          g_storedVar.carParam[i].dragBrake = DRAG_BRAKE_DEFAULT;
          g_storedVar.carParam[i].antiSpin = ANTISPIN_DEFAULT;
          g_storedVar.carParam[i].maxSpeed = MAX_SPEED_DEFAULT;
          g_storedVar.carParam[i].throttleCurveVertex.inputThrottle = THROTTLE_CURVE_INPUT_THROTTLE_DEFAULT;
          g_storedVar.carParam[i].throttleCurveVertex.curveSpeedDiff = THROTTLE_CURVE_SPEED_DIFF_DEFAULT;
          g_storedVar.carParam[i].freqPWM = PWM_FREQ_DEFAULT;
          g_storedVar.carParam[i].brakeButtonReduction = BRAKE_BUTTON_REDUCTION_DEFAULT;
          sprintf(g_storedVar.carParam[i].carName, "CAR%d", i);
        }

        /* Show confirmation message - centered */
        obdFill(&g_obd, OBD_WHITE, 1);
        const char* doneText = (lang == LANG_NOR) ? "NULLSTILT!" : "RESET DONE!";
        int textWidth = strlen(doneText) * WIDTH12x16;
        obdWriteString(&g_obd, 0, (OLED_WIDTH - textWidth) / 2, 24, (char *)doneText, FONT_12x16, OBD_BLACK, 1);
        delay(1500);

        saveEEPROM(g_storedVar);
      }
    }
  }
  /* If BACK option was selected, simply exit without changes */
  /* Note: No action needed for BACK, we just fall through to the reset code below */

exitCarMenu:
  /* Reset encoder */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);
  g_rotaryEncoder.reset(g_encoderMainSelector);
  g_escVar.encoderPos = g_encoderMainSelector;
  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  return;
}


/**
 * Show the Rename car screen. Called by selecting RENAME option on the showSelectRenameCar screen.
 */
void showRenameCar() {

  uint16_t selectedChar = RENAME_CAR_MIN_ASCII; /* the selected char: starts from 33 (ASCII for !) to 122 (ASCII for z)*/
  uint16_t selectedOption = 0;                  /* The selected option, could be one of the char of the name (0 : CAR_NAME_MAX_SIZE - 2) or the confirm option (CAR_NAME_MAX_SIZE - 1)*/
                                                /* Remember that CAR_NAME_MAX_SIZE includes the last terminator char */
  char tmpName[CAR_NAME_MAX_SIZE];  /* Array of chars containing the temporary name */
  uint16_t mode = RENAME_CAR_SELECT_OPTION_MODE;  /* Initial mode. There are two mode:
                                                     - RENAME_CAR_SELECT_OPTION_MODE, when scrolling the encoder changes the selectedOption (pick which char to change, or the OK option)
                                                     - RENAME_CAR_SELECT_CHAR_MODE, when scrolling the encoder changes the selectedChar, that is the value of the selectedOption */
  sprintf(tmpName, "%s", g_storedVar.carParam[g_storedVar.selectedCarNumber].carName); /* Store the current carName in the temporary name */

  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Set encoder to selection parameter */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(0, CAR_NAME_MAX_SIZE - 1, false);
  g_rotaryEncoder.reset(selectedOption);

  /* Print "-RENAME THE CAR-"  and "-CLICK OK TO CONFIRM" */
  obdWriteString(&g_obd, 0, 16, 0, (char *)"-RENAME THE CAR-", FONT_6x8, OBD_WHITE, 1);
  obdWriteString(&g_obd, 0, 1, OLED_HEIGHT - HEIGHT8x8, (char *)"-CLICK OK TO CONFIRM-", FONT_6x8, OBD_WHITE, 1);

  /* Draw the right arrow */
  for (uint8_t j = 0; j < 8; j++)
  {
    obdDrawLine(&g_obd, 80 + j, 16 + j, 80 + j, 30 - j, OBD_BLACK, 1);
  }
  obdDrawLine(&g_obd, 72, 22, 80, 22, OBD_BLACK, 1);
  obdDrawLine(&g_obd, 72, 23, 80, 23, OBD_BLACK, 1);
  obdDrawLine(&g_obd, 72, 24, 80, 24, OBD_BLACK, 1);

  /* Screensaver support */
  uint32_t lastInteraction = millis();
  bool screensaverActive = false;
  uint16_t screensaverEncoderPos = 0;

  /* Exit car renaming when encoder is clicked AND CONFIRM is selected */
  while (1)
  {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (screensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != screensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        screensaverActive = false;
        lastInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
        /* Redraw static elements */
        obdWriteString(&g_obd, 0, 16, 0, (char *)"-RENAME THE CAR-", FONT_6x8, OBD_WHITE, 1);
        obdWriteString(&g_obd, 0, 1, OLED_HEIGHT - HEIGHT8x8, (char *)"-CLICK OK TO CONFIRM-", FONT_6x8, OBD_WHITE, 1);
        for (uint8_t j = 0; j < 8; j++) {
          obdDrawLine(&g_obd, 80 + j, 16 + j, 80 + j, 30 - j, OBD_BLACK, 1);
        }
        obdDrawLine(&g_obd, 72, 22, 80, 22, OBD_BLACK, 1);
        obdDrawLine(&g_obd, 72, 23, 80, 23, OBD_BLACK, 1);
        obdDrawLine(&g_obd, 72, 24, 80, 24, OBD_BLACK, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!screensaverActive) {
          screensaverActive = true;
          screensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for brake button press - cancel and exit */
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      lastInteraction = millis();
      delay(BUTTON_SHORT_PRESS_DEBOUNCE_MS);
      /* Don't save changes - just exit */
      obdFill(&g_obd, OBD_WHITE, 1);
      return;
    }

    /* Get encoder value if changed */
    if (g_rotaryEncoder.encoderChanged()) {
      lastInteraction = millis();
      /* Change selectedOption if in RENAME_CAR_SELECT_OPTION_MODE */
      if (mode == RENAME_CAR_SELECT_OPTION_MODE) {
        selectedOption = g_rotaryEncoder.readEncoder();
      }
      /* Change selectedChar if in RENAME_CAR_SELECT_CHAR_MODE */
      if (mode == RENAME_CAR_SELECT_CHAR_MODE) {
        selectedChar = g_rotaryEncoder.readEncoder();
        tmpName[selectedOption] = (char)selectedChar; /* Change the value of the selected char in the temp name */

        /* Draw the upward and downward arrows on the selected char to indicate that it can be changed */
        for (uint8_t j = 0; j < 6; j++) {
          obdDrawLine(&g_obd, 1 + j + (selectedOption * 12), 14 - j, 11 - j + (selectedOption * 12), 14 - j, OBD_BLACK, 1);
          obdDrawLine(&g_obd, 1 + j + (selectedOption * 12), 33 + j, 11 - j + (selectedOption * 12), 33 + j, OBD_BLACK, 1);
        }
      }
    }

    /* Print each Char of the name, only the selected one is highlighted (WHITE color) */
    for (uint8_t i = 0; i < CAR_NAME_MAX_SIZE - 1; i++) 
    {
      sprintf(msgStr, "%c", tmpName[i]);
      obdWriteString(&g_obd, 0, 0 + (i * 12), 22, msgStr, FONT_12x16, (selectedOption == i) ? OBD_WHITE : OBD_BLACK, 1);
    }

    /* Print the confirm button */
    obdWriteString(&g_obd, 0, OLED_WIDTH - 24, 22, (char *)"OK", FONT_12x16, (selectedOption == CAR_NAME_MAX_SIZE - 1) ? OBD_WHITE : OBD_BLACK, 1);

    /* If encoder button is clicked */
    if (g_rotaryEncoder.isEncoderButtonClicked())
    {
      lastInteraction = millis();
      if (screensaverActive) {
        screensaverActive = false;
        obdFill(&g_obd, OBD_WHITE, 1);
        /* Redraw static elements */
        obdWriteString(&g_obd, 0, 16, 0, (char *)"-RENAME THE CAR-", FONT_6x8, OBD_WHITE, 1);
        obdWriteString(&g_obd, 0, 1, OLED_HEIGHT - HEIGHT8x8, (char *)"-CLICK OK TO CONFIRM-", FONT_6x8, OBD_WHITE, 1);
        for (uint8_t j = 0; j < 8; j++) {
          obdDrawLine(&g_obd, 80 + j, 16 + j, 80 + j, 30 - j, OBD_BLACK, 1);
        }
        obdDrawLine(&g_obd, 72, 22, 80, 22, OBD_BLACK, 1);
        obdDrawLine(&g_obd, 72, 23, 80, 23, OBD_BLACK, 1);
        obdDrawLine(&g_obd, 72, 24, 80, 24, OBD_BLACK, 1);
        continue;
      }
      /* Exit renameCar routing when CONFIRM is selected */
      if (selectedOption == CAR_NAME_MAX_SIZE - 1)
      {
        /* Change the name of the Car */
        sprintf(g_storedVar.carParam[g_storedVar.selectedCarNumber].carName, "%s", tmpName);
        /* Menu variables are initialized in main loop */
        return;
      }

      /* If in RENAME_CAR_SELECT_OPTION_MODE */
      if (mode == RENAME_CAR_SELECT_OPTION_MODE) {
        /* switch mode */
        mode = RENAME_CAR_SELECT_CHAR_MODE;
        /* Reset encode */
        g_rotaryEncoder.setBoundaries(RENAME_CAR_MIN_ASCII, RENAME_CAR_MAX_ASCII, false);
        g_rotaryEncoder.reset((uint16_t)tmpName[selectedOption]);
        selectedChar = (uint16_t)tmpName[selectedOption];
      }
      /* If in RENAME_CAR_SELECT_CHAR_MODE */
      else {
        /* switch mode */
        mode = RENAME_CAR_SELECT_OPTION_MODE;
        /* Reset encode */
        g_rotaryEncoder.setBoundaries(0, CAR_NAME_MAX_SIZE - 1, false);
        g_rotaryEncoder.reset(selectedOption);
        /* Cancel the upward and downward arrows (draw them black) */
        for (uint8_t j = 0; j < 6; j++) {
          obdDrawLine(&g_obd, 1 + j + (selectedOption * 12), 14 - j, 11 - j + (selectedOption * 12), 14 - j, OBD_WHITE, 1);
          obdDrawLine(&g_obd, 1 + j + (selectedOption * 12), 33 + j, 11 - j + (selectedOption * 12), 33 + j, OBD_WHITE, 1);
        }
      }
    }
  }
}


/**
 * Show the Throttle Curve selection screen. Shwon when the CURVE item is selected.
 * Draws the throttle curve graph as two segmented lines, that changes when the encoder is rotated (that is, the CURVE parameter is being changed).
 * The calculation for drawing the throttle curve are the same as the ones done in the throttleCurve function.
 * The CURVE parameter and the current trigger value are also displayed.
 */
void showCurveSelection()
{
  uint16_t throttleCurveVertexSpeed;
  uint16_t prevTrigger = g_escVar.outputSpeed_pct;
  uint16_t inputThrottle = (g_storedVar.carParam[g_carSel].throttleCurveVertex.inputThrottle * 100) / THROTTLE_NORMALIZED;  //Take inputThrottle (from 0 to THROTTLE NORMALIZED) and convert it in a 0% to 100% value
  
  /*The inputThrottle (X axis) (that ranges from 0 to THROTTLE_NORMALIZED) is converted to the 0-100 range, to simplify calculations.
    The output speed (Y axis) is already expressed in the 0-100 range.
    The origin OLED display screen, which is 128x64, is located on the top-left corner of the screen.
    The origin of the graph is therefore shifted to the pixel (25, 50). Given that the screen heigth is only 64, the y values are also scaled to range from 0 to 50 (they are divided by 2).
    The x pixel values increases from left to right, but the y pixel values increases from top to bottom, therefore every (x, y) value in the (throttle, speed) domain is converted in the pixel domain as:
    x_pixel = (x_throttle + 25);
    y_pixel = (50 - (y_speed / 2)); */
  /* Clear screen and draw x and y axis */
  obdFill(&g_obd, OBD_WHITE, 1);
  obdDrawLine(&g_obd, 25, 0, 25, 50, OBD_BLACK, 1);
  obdDrawLine(&g_obd, 25, 50, 125, 50, OBD_BLACK, 1);
  /* Write the 100%, 0%, 50% and MIN and MAXpoints labels */
  obdWriteString(&g_obd, 0, 0, 0, (char *)"100%", FONT_6x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, 0, 58, (char *)"  0%", FONT_6x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, 104, 58, (char *)"100%", FONT_6x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, 0, map(g_storedVar.carParam[g_carSel].minSpeed, 0, 100, 50, 8), (char *)"MIN", FONT_6x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, 28, 50 - (g_storedVar.carParam[g_carSel].maxSpeed / 2), (char *)"MAX", FONT_6x8, OBD_BLACK, 1);
  obdWriteString(&g_obd, 0, 64, 58, (char *)"50%", FONT_6x8, OBD_BLACK, 1);

  /* Draw axis ticks at 50%, MIN SPEED and MAX speed points*/
  obdSetPixel(&g_obd, 24, 50 - (g_storedVar.carParam[g_carSel].minSpeed / 2), OBD_BLACK, 1);
  obdSetPixel(&g_obd, 23, 50 - (g_storedVar.carParam[g_carSel].minSpeed / 2), OBD_BLACK, 1);
  obdSetPixel(&g_obd, 25 + inputThrottle, 51, OBD_BLACK, 1);
  obdSetPixel(&g_obd, 25 + inputThrottle, 52, OBD_BLACK, 1);
  obdSetPixel(&g_obd, 26, 50 - (g_storedVar.carParam[g_carSel].maxSpeed / 2), OBD_BLACK, 1);
  obdSetPixel(&g_obd, 27, 50 - (g_storedVar.carParam[g_carSel].maxSpeed / 2), OBD_BLACK, 1);

  /* Set encoder to curve parameters */
  g_rotaryEncoder.setAcceleration(SEL_ACCELERATION);
  g_rotaryEncoder.setBoundaries(THROTTLE_CURVE_SPEED_DIFF_MIN_VALUE, THROTTLE_CURVE_SPEED_DIFF_MAX_VALUE, false);
  g_rotaryEncoder.reset(g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff);

  /* Save original curve value for cancel */
  uint16_t originalCurveValue = g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff;
  bool curveCanceled = false;

  /* Calculate the output speed of the throttle curve vertex (as in throttleCurve() function)
     This is calculated as the curveSpeedDiff (from 10% to 90%) percentage of the difference between minSpeed and maxSpeed */
  throttleCurveVertexSpeed = g_storedVar.carParam[g_carSel].minSpeed + (((uint32_t)g_storedVar.carParam[g_carSel].maxSpeed - (uint32_t)g_storedVar.carParam[g_carSel].minSpeed) * ((uint32_t)g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff) / 100);

  /* Draw Line from MIN SPEED, to middle point */
  obdDrawLine(&g_obd, 25, 50 - (g_storedVar.carParam[g_carSel].minSpeed / 2), 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), OBD_BLACK, 1);
  /* Draw Line from middle point to 100% */
  obdDrawLine(&g_obd, 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), 125, map(g_storedVar.carParam[g_carSel].maxSpeed, 0, 100, 50, 0), OBD_BLACK, 1);

  /* Write the CURVE value */
  sprintf(msgStr, "%3d%c", g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff, '%');
  obdWriteString(&g_obd, 0, OLED_WIDTH - 48, 34, msgStr, FONT_12x16, OBD_BLACK, 1);

  /* Write the trigger value */
  sprintf(msgStr, "%3d%c", prevTrigger, '%');
  obdWriteString(&g_obd, 0, OLED_WIDTH - 32, 26, msgStr, FONT_8x8, OBD_BLACK, 1);

  /* Exit curve function when encoder is clicked */
  while (!g_rotaryEncoder.isEncoderButtonClicked() && !curveCanceled)
  {
    /* Check for brake button press - acts as "cancel" in curve screen */
    static bool brakeBtnInCurve = false;
    static uint32_t lastBrakeBtnCurveTime = 0;
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      if (!brakeBtnInCurve && millis() - lastBrakeBtnCurveTime > BUTTON_SHORT_PRESS_DEBOUNCE_MS) {
        brakeBtnInCurve = true;
        lastBrakeBtnCurveTime = millis();
        /* Cancel changes - restore original value */
        g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff = originalCurveValue;
        curveCanceled = true;
      }
    } else {
      brakeBtnInCurve = false;
    }

    /* Write the trigger value only if it changed */
    if (g_escVar.outputSpeed_pct != prevTrigger)
    {
      /* Update trigger */
      prevTrigger = g_escVar.outputSpeed_pct;

      /* Write the trigger value */
      sprintf(msgStr, "%3d%c", prevTrigger, '%');
      obdWriteString(&g_obd, 0, OLED_WIDTH - 32, 26, msgStr, FONT_8x8, OBD_BLACK, 1);
    }

    /* Get encoder position if it was changed and correct the new lines*/
    if (g_rotaryEncoder.encoderChanged())
    {
      /* Cancel the old lines (draw them in black) */
      obdDrawLine(&g_obd, 25, 50 - (g_storedVar.carParam[g_carSel].minSpeed / 2), 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), OBD_WHITE, 1);
      obdDrawLine(&g_obd, 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), 125, map(g_storedVar.carParam[g_carSel].maxSpeed, 0, 100, 50, 0), OBD_WHITE, 1);
      
      /* Update the speed coordinate of the vertex */
      g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff = g_rotaryEncoder.readEncoder();
      sprintf(msgStr, "%3d%c", g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff, '%');
      throttleCurveVertexSpeed = g_storedVar.carParam[g_carSel].minSpeed + ((uint32_t)g_storedVar.carParam[g_carSel].maxSpeed - (uint32_t)g_storedVar.carParam[g_carSel].minSpeed) * ((uint32_t)g_storedVar.carParam[g_carSel].throttleCurveVertex.curveSpeedDiff) / 100;
      obdWriteString(&g_obd, 0, OLED_WIDTH - 48, 34, msgStr, FONT_12x16, OBD_BLACK, 1);
      
      /* Draw the new lines */
      obdDrawLine(&g_obd, 25, 50 - (g_storedVar.carParam[g_carSel].minSpeed / 2), 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), OBD_BLACK, 1);
      obdDrawLine(&g_obd, 25 + inputThrottle, map(throttleCurveVertexSpeed, 0, 100, 50, 0), 125, map(g_storedVar.carParam[g_carSel].maxSpeed, 0, 100, 50, 0), OBD_BLACK, 1);
    }
    else
    {
      /* Service the watchdog, to prevent CPU reset */
      vTaskDelay(10);
    }
  }

  /* Reset encoder */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);
  g_rotaryEncoder.reset(g_encoderMainSelector);
  g_escVar.encoderPos = g_encoderMainSelector;

  /* Only save if not canceled */
  if (!curveCanceled) {
    saveEEPROM(g_storedVar);          /* Save modified values to EEPROM */
  }

  obdFill(&g_obd, OBD_WHITE, 1);    /* Clear screen */

  return;
}


/**
 * Show the Settings submenu
 * This function is called when SETTINGS item is selected in the main menu
 * It displays and manages navigation through the settings submenu items:
 * SCRSV, SOUND, VIEW, LANG, BACK
 */
void showSettingsMenu() {
  /* Initialize settings menu items with current values */
  initSettingsMenuItems();

  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);

  /* Set flag that we're in settings menu */
  g_inSettingsMenu = true;

  /* Set encoder to navigate through settings items (1 to SETTINGS_ITEMS_COUNT) */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(1, SETTINGS_ITEMS_COUNT, false);
  g_rotaryEncoder.reset(1);  /* Start at first settings item */

  uint16_t settingsSelector = 1;
  uint16_t prevSettingsSelector = 0;
  MenuState_enum settingsMenuState = ITEM_SELECTION;
  uint16_t *settingsValuePtr = NULL;
  uint16_t originalSettingsValue = 0;  /* Store original value for cancel */
  uint16_t prevLanguage = g_storedVar.language;
  uint16_t tempLanguage = g_storedVar.language;  /* Temporary language value for editing */
  bool isEditingLanguage = false;  /* Track if we're editing language */
  uint16_t prevTextCase = g_storedVar.textCase;
  uint16_t tempTextCase = g_storedVar.textCase;  /* Temporary text case value for editing */
  bool isEditingTextCase = false;  /* Track if we're editing text case */
  uint16_t prevFontSize = g_storedVar.listFontSize;
  uint16_t tempFontSize = g_storedVar.listFontSize;  /* Temporary font size value for editing */
  bool isEditingFontSize = false;  /* Track if we're editing font size */

  /* Setup scrolling frame - number of visible items depends on font size */
  uint16_t frameUpper = 1;
  uint8_t visibleLines = getMenuLines();
  uint16_t frameLower = visibleLines;

  /* Settings menu loop */
  uint32_t lastSettingsInteraction = millis();
  bool settingsScreensaverActive = false;
  uint16_t settingsScreensaverEncoderPos = 0;

  while (true) {
    /* Calculate throttle percentage for screensaver wake-up */
    uint8_t throttle_pct = (g_escVar.trigger_norm * 100) / THROTTLE_NORMALIZED;

    /* Check for any wake-up input first (encoder, button, throttle) */
    bool wakeUpTriggered = false;
    if (settingsScreensaverActive) {
      uint16_t currentEncoderPos = g_rotaryEncoder.readEncoder();
      if (throttle_pct >= SCREENSAVER_WAKEUP_THRESHOLD ||
          currentEncoderPos != settingsScreensaverEncoderPos ||
          digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
        wakeUpTriggered = true;
        settingsScreensaverActive = false;
        lastSettingsInteraction = millis();
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Check for screensaver timeout */
    if (!wakeUpTriggered && g_storedVar.screensaverTimeout > 0 && millis() - lastSettingsInteraction > (g_storedVar.screensaverTimeout * 1000UL)) {
      if (throttle_pct < SCREENSAVER_WAKEUP_THRESHOLD) {
        if (!settingsScreensaverActive) {
          settingsScreensaverActive = true;
          settingsScreensaverEncoderPos = g_rotaryEncoder.readEncoder();
          showScreensaver();
        }
        delay(10);  /* Small delay to prevent watchdog timeout */
        continue;  /* Don't draw menu while screensaver is active */
      }
    }

    /* Check for button click */
    if (g_rotaryEncoder.isEncoderButtonClicked()) {
      lastSettingsInteraction = millis();
      if (settingsMenuState == ITEM_SELECTION) {
        /* Check if BACK button (last item) is selected */
        if (settingsSelector == SETTINGS_ITEMS_COUNT) {
          /* BACK selected - exit settings menu */
          break;
        }
        /* Check if selected item has a value to edit */
        if (g_settingsMenu.item[settingsSelector - 1].value != ITEM_NO_VALUE) {
          /* Check if this is the LANG item (index 3 in settings menu, 0-based) */
          if (settingsSelector == 4) {  /* LANG is 4th item (SCRSV, SOUND, VIEW, LANG, CASE, FSIZE, BACK) */
            isEditingLanguage = true;
            tempLanguage = g_storedVar.language;
            originalSettingsValue = g_storedVar.language;
          }
          /* Check if this is the CASE item */
          else if (settingsSelector == 5) {  /* CASE is 5th item (SCRSV, SOUND, VIEW, LANG, CASE, FSIZE, BACK) */
            isEditingTextCase = true;
            tempTextCase = g_storedVar.textCase;
            originalSettingsValue = g_storedVar.textCase;
          }
          /* Check if this is the FSIZE item */
          else if (settingsSelector == 6) {  /* FSIZE is 6th item (SCRSV, SOUND, VIEW, LANG, CASE, FSIZE, BACK) */
            isEditingFontSize = true;
            tempFontSize = g_storedVar.listFontSize;
            originalSettingsValue = g_storedVar.listFontSize;
          } else {
            /* Save original value for other items */
            settingsValuePtr = (uint16_t *)g_settingsMenu.item[settingsSelector - 1].value;
            originalSettingsValue = *settingsValuePtr;
          }
          /* Enter value editing mode for selected item */
          settingsMenuState = VALUE_SELECTION;
          g_rotaryEncoder.setAcceleration(SEL_ACCELERATION);
          if (!isEditingLanguage && !isEditingTextCase && !isEditingFontSize) {
            settingsValuePtr = (uint16_t *)g_settingsMenu.item[settingsSelector - 1].value;
          }
          g_rotaryEncoder.setBoundaries(g_settingsMenu.item[settingsSelector - 1].minValue,
                                       g_settingsMenu.item[settingsSelector - 1].maxValue, false);
          uint16_t resetValue = isEditingLanguage ? tempLanguage : (isEditingTextCase ? tempTextCase : (isEditingFontSize ? tempFontSize : *settingsValuePtr));
          g_rotaryEncoder.reset(resetValue);
        }
      } else {
        /* Exit value editing mode and return to item selection */
        settingsMenuState = ITEM_SELECTION;
        g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
        g_rotaryEncoder.setBoundaries(1, SETTINGS_ITEMS_COUNT, false);
        g_rotaryEncoder.reset(settingsSelector);

        /* If we were editing language, apply the temp language value */
        if (isEditingLanguage) {
          g_storedVar.language = tempLanguage;
          isEditingLanguage = false;
        }

        /* If we were editing text case, apply the temp text case value */
        if (isEditingTextCase) {
          g_storedVar.textCase = tempTextCase;
          isEditingTextCase = false;
        }

        /* If we were editing font size, apply the temp font size value */
        if (isEditingFontSize) {
          g_storedVar.listFontSize = tempFontSize;
          isEditingFontSize = false;
        }

        saveEEPROM(g_storedVar);  /* Save modified values */

        /* If language, text case, or font size changed, reinitialize and clear screen */
        if (g_storedVar.language != prevLanguage || g_storedVar.textCase != prevTextCase || g_storedVar.listFontSize != prevFontSize) {
          initSettingsMenuItems();
          initMenuItems();  /* Also reinit main menu */
          prevLanguage = g_storedVar.language;
          prevTextCase = g_storedVar.textCase;
          prevFontSize = g_storedVar.listFontSize;
          /* Reset frame to top when font size changes */
          visibleLines = getMenuLines();
          frameUpper = 1;
          frameLower = visibleLines;
          obdFill(&g_obd, OBD_WHITE, 1);  /* Clear screen */
        }
      }
      delay(200);  /* Debounce */
    }

    /* Read encoder position */
    if (g_rotaryEncoder.encoderChanged()) {
      lastSettingsInteraction = millis();
      if (settingsMenuState == ITEM_SELECTION) {
        settingsSelector = g_rotaryEncoder.readEncoder();
      } else {
        /* Update the value */
        if (isEditingLanguage) {
          /* Update temp language value instead of actual language */
          tempLanguage = g_rotaryEncoder.readEncoder();
        } else if (isEditingTextCase) {
          /* Update temp text case value instead of actual text case */
          uint16_t newTextCase = g_rotaryEncoder.readEncoder();
          if (newTextCase != tempTextCase) {
            tempTextCase = newTextCase;
            obdFill(&g_obd, OBD_WHITE, 1);  /* Clear to prevent text overlap */
          }
        } else if (isEditingFontSize) {
          /* Update temp font size value instead of actual font size */
          tempFontSize = g_rotaryEncoder.readEncoder();
        } else {
          *settingsValuePtr = g_rotaryEncoder.readEncoder();
        }
      }
    }

    /* Check for brake button press - acts as "back" in settings menu */
    static bool brakeBtnInSettings = false;
    static uint32_t lastBrakeBtnSettingsTime = 0;
    if (digitalRead(BUTT_PIN) == BUTTON_PRESSED) {
      if (!brakeBtnInSettings && millis() - lastBrakeBtnSettingsTime > BUTTON_SHORT_PRESS_DEBOUNCE_MS) {
        brakeBtnInSettings = true;
        lastBrakeBtnSettingsTime = millis();
        lastSettingsInteraction = millis();

        if (settingsMenuState == VALUE_SELECTION) {
          /* Cancel changes and go back to item selection */
          if (isEditingLanguage) {
            /* Restore original language value (cancel) */
            tempLanguage = originalSettingsValue;
            g_storedVar.language = originalSettingsValue;
            isEditingLanguage = false;
          } else if (isEditingTextCase) {
            /* Restore original text case value (cancel) */
            tempTextCase = originalSettingsValue;
            g_storedVar.textCase = originalSettingsValue;
            isEditingTextCase = false;
          } else if (isEditingFontSize) {
            /* Restore original font size value (cancel) */
            tempFontSize = originalSettingsValue;
            g_storedVar.listFontSize = originalSettingsValue;
            isEditingFontSize = false;
          } else if (settingsValuePtr != NULL) {
            /* Restore original value (cancel) */
            *settingsValuePtr = originalSettingsValue;
          }

          settingsMenuState = ITEM_SELECTION;
          g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
          g_rotaryEncoder.setBoundaries(1, SETTINGS_ITEMS_COUNT, false);
          g_rotaryEncoder.reset(settingsSelector);
          /* Do NOT save to EEPROM - we're canceling the change */
          obdFill(&g_obd, OBD_WHITE, 1);  /* Clear screen */
        } else {
          /* In ITEM_SELECTION - exit settings menu completely */
          break;
        }
      }
    } else {
      brakeBtnInSettings = false;
    }

    /* Check for long press to exit settings menu */
    static uint32_t settingsButtonPressStart = 0;
    static bool settingsButtonWasPressed = false;
    if (digitalRead(ENCODER_BUTTON_PIN) == BUTTON_PRESSED) {
      if (!settingsButtonWasPressed) {
        settingsButtonPressStart = millis();
        settingsButtonWasPressed = true;
      }
      if (millis() - settingsButtonPressStart > BUTTON_LONG_PRESS_MS) {
        /* Long press detected - exit settings menu */
        break;
      }
    } else {
      settingsButtonWasPressed = false;
    }

    /* Update frame if selection moves outside visible area */
    if (settingsMenuState == ITEM_SELECTION) {
      if (settingsSelector > frameLower) {
        frameLower = settingsSelector;
        frameUpper = frameLower - visibleLines + 1;
        obdFill(&g_obd, OBD_WHITE, 1);
      } else if (settingsSelector < frameUpper) {
        frameUpper = settingsSelector;
        frameLower = frameUpper + visibleLines - 1;
        obdFill(&g_obd, OBD_WHITE, 1);
      }
    }

    /* Determine font size and dimensions based on actual saved setting (not temp value) */
    uint8_t menuFont = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? FONT_8x8 : FONT_12x16;
    uint8_t charWidth = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? WIDTH8x8 : WIDTH12x16;
    uint8_t lineHeight = (g_storedVar.listFontSize == FONT_SIZE_SMALL) ? 8 : HEIGHT12x16;

    /* Display settings menu items */
    for (uint8_t i = 0; i < visibleLines; i++) {
      uint16_t itemIndex = frameUpper - 1 + i;
      if (itemIndex >= SETTINGS_ITEMS_COUNT) break;

      /* Print item name */
      bool isSelected = (settingsSelector - frameUpper == i && settingsMenuState == ITEM_SELECTION);
      obdWriteString(&g_obd, 0, 0, i * lineHeight, g_settingsMenu.item[itemIndex].name,
                    menuFont, isSelected ? OBD_WHITE : OBD_BLACK, 1);

      /* Print item value */
      if (g_settingsMenu.item[itemIndex].value != ITEM_NO_VALUE) {
        bool isValueSelected = (settingsSelector - frameUpper == i && settingsMenuState == VALUE_SELECTION);

        if (g_settingsMenu.item[itemIndex].type == VALUE_TYPE_INTEGER) {
          sprintf(msgStr, "%3d%s", *(uint16_t *)(g_settingsMenu.item[itemIndex].value),
                 g_settingsMenu.item[itemIndex].unit);
          int textWidth = strlen(msgStr) * charWidth;
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, i * lineHeight, msgStr,
                        menuFont, isValueSelected ? OBD_WHITE : OBD_BLACK, 1);
        } else if (g_settingsMenu.item[itemIndex].type == VALUE_TYPE_STRING) {
          /* Handle special string values */
          uint16_t value = *(uint16_t *)(g_settingsMenu.item[itemIndex].value);
          uint16_t lang = g_storedVar.language;

          /* SCRSV menu item - show OFF/AV when 0, otherwise show value with 's' */
          if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 0)) == 0) {
            if (value == 0) {
              sprintf(msgStr, "%3s", getOnOffLabel(lang, 0));  /* OFF/AV */
            } else {
              sprintf(msgStr, "%3ds", value);
            }
          }
          /* SOUND menu item */
          else if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 1)) == 0) {
            sprintf(msgStr, "%5s", getSoundModeLabel(lang, value));
          }
          /* VIEW menu item */
          else if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 2)) == 0) {
            sprintf(msgStr, "%6s", getViewModeLabel(lang, value));
          }
          /* LANG menu item */
          else if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 3)) == 0) {
            /* Use tempLanguage when editing, otherwise use actual value */
            uint16_t displayLang = (isEditingLanguage && isValueSelected) ? tempLanguage : value;
            sprintf(msgStr, "%3s", LANG_LABELS[displayLang]);
          }
          /* CASE menu item */
          else if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 4)) == 0) {
            /* Use tempTextCase when editing, otherwise use actual value */
            uint16_t displayTextCase = (isEditingTextCase && isValueSelected) ? tempTextCase : value;
            sprintf(msgStr, "%6s", TEXT_CASE_LABELS[lang][displayTextCase]);
          }
          /* FSIZE menu item */
          else if (strcmp(g_settingsMenu.item[itemIndex].name, getSettingsMenuName(lang, 5)) == 0) {
            /* Use tempFontSize when editing, otherwise use actual value */
            uint16_t displayFontSize = (isEditingFontSize && isValueSelected) ? tempFontSize : value;
            sprintf(msgStr, "%5s", FONT_SIZE_LABELS[lang][displayFontSize]);
          } else {
            sprintf(msgStr, "%3d", value);
          }

          int textWidth = strlen(msgStr) * charWidth;
          obdWriteString(&g_obd, 0, OLED_WIDTH - textWidth, i * lineHeight, msgStr,
                        menuFont, isValueSelected ? OBD_WHITE : OBD_BLACK, 1);
        }
      }
    }

    vTaskDelay(10);  /* Small delay to prevent watchdog reset */
  }

  /* Exiting settings menu */
  g_inSettingsMenu = false;

  /* Reset encoder to main menu */
  g_rotaryEncoder.setAcceleration(MENU_ACCELERATION);
  g_rotaryEncoder.setBoundaries(1, MENU_ITEMS_COUNT, false);
  g_rotaryEncoder.reset(g_encoderMainSelector);
  g_escVar.encoderPos = g_encoderMainSelector;

  /* Save any changes */
  saveEEPROM(g_storedVar);

  /* Clear screen */
  obdFill(&g_obd, OBD_WHITE, 1);
}


/**
 * Take an ADC raw value where the max and min has been recorded and returns the value scaled
 * 
 * @param raw The raw ADC value
 * @param minIn The lowest reading of the ADC
 * @param maxIn The highest reading of the ADC
 * @param normalizedMax The new max value of the scale
 * @param isReversed Whether the throttle is reversed or not
 * @return The raw ADC value scaled from 0 to normalizedMax
 */
uint16_t normalizeAndClamp(uint16_t raw, uint16_t minIn, uint16_t maxIn, uint16_t normalizedMax, bool isReversed)
{
  uint16_t retVal = 0;  /* From 0 to normalizedMax */

  if (maxIn == minIn)  /* If maxIn == minIn avoid division by 0 */
  {
    retVal = 0;
  }
  else
  {
    raw = constrain(raw, minIn, maxIn); /* Make sure the raw value is constrained between minIn and maxIn */

    if (isReversed == true)  /* If throttle is reversed (it goes to low values when pressed) */
    {
      raw = abs(maxIn - raw);
    }
    else
    {
      raw = abs(raw - minIn);
    }

    retVal = ((uint32_t)raw * normalizedMax) / (maxIn - minIn); /* Scale the raw reading */
  }

  return retVal;
}

/**
 * Saturate an input value between a upper and lower bound
 * 
 * @param paramValue The input value to be saturated
 * @param minValue The lower bound
 * @param maxValue The upper bound
 * @return The saturated input value.
 */
uint16_t saturateParamValue(uint16_t paramValue, uint16_t minValue, uint16_t maxValue) 
{
  uint16_t retValue = paramValue;

  if (paramValue > maxValue) 
  {
    retValue = maxValue;
  } else if (paramValue < minValue) 
  {
    retValue = minValue;
  }

  return retValue;
}


void saveEEPROM(StoredVar_type toSave) {
  g_pref.begin("stored_var", false);                      /* Open the "stored" namespace in read/write mode */
  g_pref.putBytes("user_param", &toSave, sizeof(toSave)); /* Put the value of the stored user_param */
  g_pref.end();                                           /* Close the namespace */
}