#include <Arduino.h>
#include "ConfigCarte.h"

#define MENU_REGLAGE_POINT_MILLIEU                  77   // M
#define MENU_REGLAGE_GAUCHE_DROITE                  80   // P
#define MENU_REGLAGE_ADRESSE_AIGUILLAGE             65   // A
#define MENU_REGLAGE_ADRESSE_DETECTION              68   // D
#define MENU_REGLAGE_NOMBRE_AIGUILLAGE              78   // N
#define MENU_REGLAGE_ISSOLEMENT                     73   // I
#define MENU_MODE_CONFIGURATION                     67   // C
#define MENU_HELP                                   63   // ?
#define FIN_TRANMISSION                             -1   // null

void getCarathere(char lectureCarathere) {
    if (mode == configuration) {

        switch (lectureCarathere) {
            case MENU_HELP:
                Serial.println("MENU_HELP");
                Serial.println("M : Réglage point millieu servo moteur");
                Serial.println("P : Réglage fin de course gauche / droite");
                Serial.println("A : Réglage adresse commande aiguillage");
                Serial.println("D : Réglage adresse detection");
                Serial.println("N : Réglage nombre de moteur aiguillage");
                Serial.println("I : Issolement carte");
                Serial.println("C : Quité le mode configuration");
                Serial.println("? : HELP !");
                Serial.println("");
                Serial.println("Commande (M/P/A/D/T/I/C/?) : ");
                break;
            
            case MENU_MODE_CONFIGURATION:
                Serial.println("MENU_MODE_CONFIGURATION");
                break;

            case MENU_REGLAGE_ADRESSE_AIGUILLAGE:
                Serial.println("MENU_REGLAGE_ADRESSE_AIGUILLAGE");
                break;

            case MENU_REGLAGE_ADRESSE_DETECTION:
                Serial.println("MENU_REGLAGE_ADRESSE_DETECTION");
                break;

            case MENU_REGLAGE_GAUCHE_DROITE:
                Serial.println("MENU_REGLAGE_GAUCHE_DROITE");
                break;

            case MENU_REGLAGE_ISSOLEMENT:
                Serial.println("MENU_REGLAGE_ISSOLEMENT");
                break;

            case MENU_REGLAGE_NOMBRE_AIGUILLAGE:
                Serial.println("MENU_REGLAGE_NOMBRE_AIGUILLAGE");
                break;

            case MENU_REGLAGE_POINT_MILLIEU:
                Serial.println("MENU_REGLAGE_POINT_MILLIEU");
                break;

            case FIN_TRANMISSION:
                break;
            
            default:
                Serial.println("Commande (M/P/A/D/T/I/C/?) : ");
                break;
        }

    }
}