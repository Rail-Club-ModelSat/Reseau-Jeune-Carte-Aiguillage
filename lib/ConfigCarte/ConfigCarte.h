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
#define MENU_REGLAGE                                "R"   // R
#define MENU_HELP                                   "?"   // ?

#define ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE          10
#define ADRESSE_MEMOIRE_ADRESSE_DETECTION1          15
#define ADRESSE_MEMOIRE_ADRESSE_DETECTION2          16

#define ADRESSE_MEMOIRE_ANGLE_GAUCHE                17
#define ADRESSE_MEMOIRE_ANGLE_DROITE                19

#define ADRESSE_MEMOIRE_CARTE_ISOLEE                21

#define ADRESSE_MEMOIRE_NOMBRE_MOTEUR               22

#define DEFAULT_SERVO_MAX_GAUCHE                    1050
#define DEFAULT_SERVO_MAX_DROITE                    1800
#define POINT_MILLIEU_SERVO                         1500

#define TAILLE_MAX_SERIAL_MESSAGE 10

bool getCarathere(char lectureCarathere);
void prossesMenu();

// class ConfigCarte {

//     public:

//     private:

// };

#endif // ConfigCarte_h