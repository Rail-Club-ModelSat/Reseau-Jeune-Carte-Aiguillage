#include <Arduino.h>
#include <EEPROM.h>
#include "ConfigCarte.h"

enum { exploitation, accueil, reglageAdresseAiguillage, reglageAdresseDetection, reglageGaucheDroite, reglageIssolement, reglageNombreAiguillage, reglagePointMillieu } menuConfiguration;

char message[TAILLE_MAX_SERIAL_MESSAGE];

bool nouveauMessageDisponible = true;


void purgeMessage() {
    strcpy(message, "");
    Serial.print("\x1b[2J\x1b[;H");
    nouveauMessageDisponible = true;
    prossesMenu();
}

void menuHelp() {

    Serial.println("");

    Serial.println("MENU_HELP");
    Serial.print(MENU_REGLAGE_POINT_MILLIEU);
    Serial.println(" : Réglage point millieu servo moteur");
    Serial.print(MENU_REGLAGE_GAUCHE_DROITE);
    Serial.println(" : Réglage fin de course gauche / droite");
    Serial.print(MENU_REGLAGE_ADRESSE_AIGUILLAGE);
    Serial.println(" : Réglage adresse commande aiguillage");
    Serial.print(MENU_REGLAGE_ADRESSE_DETECTION);
    Serial.println(" : Réglage adresse detection");
    Serial.print(MENU_REGLAGE_NOMBRE_AIGUILLAGE);
    Serial.println(" : Réglage nombre de moteur aiguillage");
    Serial.print(MENU_REGLAGE_ISSOLEMENT);
    Serial.println(" : Issolement carte");
    Serial.print(MENU_EXIT_MODE_CONFIGURATION);
    Serial.println(" : Quité le mode configuration");
    Serial.print(MENU_HELP);
    Serial.println(" : Commande help");
    Serial.println("");
}

void menuReglageAdresseAiguillage() {
    
    Serial.println("reglage adresse : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuExploitation() {

    Serial.println("Entrée 'C' pour passer en mode configuration : ");
    if (strstr(message, MENU_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuAccueil() {

    if (strstr(message, MENU_HELP)) {

        menuHelp();
        strcpy(message, "");
        nouveauMessageDisponible = true;
        prossesMenu();

    } else if (strstr(message, MENU_REGLAGE_GAUCHE_DROITE)) {

        menuConfiguration = reglageGaucheDroite;
        purgeMessage();

    } else if (strstr(message, MENU_REGLAGE_ADRESSE_AIGUILLAGE)) {

        menuConfiguration = reglageAdresseAiguillage;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE_ADRESSE_DETECTION)) {

        menuConfiguration = reglageAdresseDetection;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE_NOMBRE_AIGUILLAGE)) {

        menuConfiguration = reglageNombreAiguillage;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE_ISSOLEMENT)) {

        menuConfiguration = reglageIssolement;
        purgeMessage();
        
    } else if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {

        menuConfiguration = exploitation;
        purgeMessage();
        
    } else {

        strcpy(message, "");
        char buffer[33];
        sprintf(buffer, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "Commande (", MENU_REGLAGE_POINT_MILLIEU, "/", MENU_REGLAGE_GAUCHE_DROITE, "/", MENU_REGLAGE_ADRESSE_AIGUILLAGE, "/", MENU_REGLAGE_ADRESSE_DETECTION, "/", MENU_REGLAGE_NOMBRE_AIGUILLAGE, "/", MENU_REGLAGE_ISSOLEMENT, "/", MENU_EXIT_MODE_CONFIGURATION, "/", MENU_HELP, ") : ");
        Serial.write(buffer);

        Serial.println("");
        
    }

}

void prossesMenu() {

    if (nouveauMessageDisponible) {

        switch (menuConfiguration) {
            case reglageAdresseAiguillage:
                menuReglageAdresseAiguillage();

                break;

            case reglageAdresseDetection:

                break;

            case reglageGaucheDroite:

                break;

            case reglageIssolement:

                break;

            case reglageNombreAiguillage:

                break;

            case reglagePointMillieu:

                break;

            case accueil:
                menuAccueil();
                break;

            case exploitation:
                menuExploitation();
                break;
            
            default:
                break;
        }

        Serial.println(message);
        nouveauMessageDisponible = false; // Réinitialiser le flag
    }

}

bool getCarathere(char lectureCarathere) {
    static byte indexMessage = 0;
    boolean messageEnCours = true;

    if (lectureCarathere != -1) {
        switch (lectureCarathere) {
            case '\n': // Fin de message
                message[indexMessage] = '\0';
                indexMessage = 0;
                messageEnCours = false;
                nouveauMessageDisponible = true;
                break;
            default:
                if (indexMessage < TAILLE_MAX_SERIAL_MESSAGE) {
                    message[indexMessage++] = (char)lectureCarathere;
                }
                break;
        }
    }

    return messageEnCours;
}