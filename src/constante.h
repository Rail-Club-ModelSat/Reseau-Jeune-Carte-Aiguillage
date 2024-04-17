// Définition des adresse
#define ADRESSE_AIGUILL 5
#define ADRESSE_SENSOR1 202
#define ADRESSE_SENSOR2 203

// Valeur Normal / Dévié servomoteur
#define SERVO_VALL_NORMAL  1050    // 50°C
#define SERVO_VALL_TURNOUT 1800    // 120°C
#define POINT_MILLIEU_SERVO 1500   // 90°

// pin carte
#define LN_TX_PIN     7
#define RELAI_PIN     5
#define SERVO_PIN     9
#define N_BUTTON_PIN  2
#define D_BUTTON_PIN  3

#define MENU_REGLAGE_POINT_MILLIEU                  "M"   // M
#define MENU_REGLAGE_GAUCHE_DROITE                  "P"   // P
#define MENU_REGLAGE_ADRESSE_AIGUILLAGE             "A"   // A
#define MENU_REGLAGE_ADRESSE_DETECTION              "D"   // D
#define MENU_REGLAGE_NOMBRE_AIGUILLAGE              "N"   // N
#define MENU_REGLAGE_ISSOLEMENT                     "I"   // I
#define MENU_MODE_CONFIGURATION                     "C"   // C
#define MENU_HELP                                   "?"   // ?

int  etatPossitionAiguillage;
int  old_etatPossitionAiguillage;

// Gestion du rebond pour les boutons
bool didStatusN = false;
bool oldDidStatusN = false;
unsigned long lastDebounceTimeN = 0;
unsigned long debounceDelayN = 20;

bool didStatusD = false;
bool oldDidStatusD = false;
unsigned long lastDebounceTimeD = 0;
unsigned long debounceDelayD = 20;

enum TurnoutState {
  TURNOUT_NORMAL = 1,
  TURNOUT_DIVERGING = 0
};