// pin carte
#define LN_TX_PIN     7

#define PIN_SERVO                   9
#define PIN_RELAIS                  5
#define PIN_BOUTON_DETECT1          2
#define PIN_BOUTON_DETECT2          3

#define VITESSE_TRAMSMISSION        57600

#define PIN_LED_POSSITION_AIGUIL    16
#define PIN_LED_DATA                17
#define PIN_LED_ERREUR              18

bool etatPowerDCC;

enum TurnoutState {
  TURNOUT_NORMAL = 1,
  TURNOUT_DIVERGING = 0
};

bool etatPossitionAiguillage;