#ifndef ConfigCarte_h
#define ConfigCarte_h

#define MENU_REGLAGE_POINT_MILLIEU                  "M"   // M
#define MENU_REGLAGE_GAUCHE_DROITE                  "P"   // P
#define MENU_REGLAGE_ADRESSE_AIGUILLAGE             "A"   // A
#define MENU_REGLAGE_ADRESSE_DETECTION              "D"   // D
#define MENU_REGLAGE_NOMBRE_AIGUILLAGE              "N"   // N
#define MENU_REGLAGE_ISSOLEMENT                     "I"   // I
#define MENU_MODE_CONFIGURATION                     "C"   // C
#define MENU_EXIT_MODE_CONFIGURATION                "E"   // E
#define MENU_HELP                                   "?"   // ?

#define TAILLE_MAX_SERIAL_MESSAGE 10

bool getCarathere(char lectureCarathere);
void prossesMenu();

// class ConfigCarte {

//     public:

//     private:

// };

#endif // ConfigCarte_h