#ifndef ConfigCarte_h
#define ConfigCarte_h

#define PIN_SERVO                                   9

#define MENU_REGLAGE_POINT_MILLIEU                  "M"   // M
#define MENU_REGLAGE_GAUCHE_DROITE                  "P"   // P
#define MENU_REGLAGE_ADRESSE_AIGUILLAGE             "A"   // A
#define MENU_REGLAGE_ADRESSE_DETECTION              "D"   // D
#define MENU_REGLAGE_NOMBRE_AIGUILLAGE              "N"   // N
#define MENU_REGLAGE_ISSOLEMENT                     "I"   // I
#define MENU_MODE_CONFIGURATION                     "C"   // C
#define MENU_EXIT_MODE_CONFIGURATION                "E"   // E
#define MENU_REGLAGE_SENS_LOGIQUE                   "S"   // S
#define MENU_REGLAGE                                "R"   // R
#define MENU_HELP                                   "?"   // ?

#define ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE          5000
#define ADRESSE_MEMOIRE_ADRESSE_DETECTION1          5100
#define ADRESSE_MEMOIRE_ADRESSE_DETECTION2          5200
#define ADRESSE_MEMOIRE_ANGLE_GAUCHE                5300
#define ADRESSE_MEMOIRE_ANGLE_DROITE                5400
#define ADRESSE_MEMOIRE_CARTE_ISOLEE                5500
#define ADRESSE_MEMOIRE_NOMBRE_MOTEUR               5600
#define ADRESSE_MEMOIRE_SENS_LOGIQUE                5700

#define DEFAULT_SERVO_MAX_GAUCHE                    1050
#define DEFAULT_SERVO_MAX_DROITE                    1800
#define POINT_MILLIEU_SERVO                         1500

#define TAILLE_MAX_SERIAL_MESSAGE 10

enum { exploitation, accueil, reglageSensLogique, reglageAdresseAiguillage, reglageAdresseDetection, reglageGaucheDroite, reglageIssolement, reglageNombreAiguillage, reglagePointMillieu } menuConfiguration;

bool getCarathere(char lectureCarathere);
void prossesMenu();

uint16_t getMaxServoGauche();
uint16_t getMaxServoDroite();
uint16_t getAdresseAiguillage();
uint16_t getAdresseDetecteur1();
uint16_t getAdresseDetecteur2();
uint8_t getNombreAiguillage();
bool getIssolementCarte();
bool getSensLogique();

#endif // ConfigCarte_h