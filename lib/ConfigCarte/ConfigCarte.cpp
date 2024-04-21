#include <Arduino.h>
#include <EEPROM.h>
#include <ServoTimer2.h>
#include "ConfigCarte.h"

ServoTimer2   ServoMoteur;

enum { exploitation, accueil, reglage, reglageAdresseAiguillage, reglageAdresseDetection, reglageGaucheDroite, reglageIssolement, reglageNombreAiguillage, reglagePointMillieu } menuConfiguration;

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

    Serial.println("Help menu :");
    Serial.print(MENU_REGLAGE);
    Serial.println(" : voire les reglage");
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

void menuReglageAdresseAiguillage() {

    Serial.print("\x1b[2J\x1b[;H");
    static bool adresseConfigure = false;

    Serial.println("");
    Serial.println("Configuration adresse commande moteur aiguillage");
    Serial.println("");

    if (!adresseConfigure) {

        int adresse = atoi(message);
        if (adresse > 0 && adresse < 2048) {
            EEPROM.write(ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE, adresse);
            adresseConfigure = true;
        } else {
            Serial.println("Entrée une adresse entre 0 et 2048 : ");
            return;
        }

        Serial.println("");
        Serial.print("Nouvelle adresse configuré : "); Serial.println(adresse);

    }

    Serial.println("Entrée 'E' pour quitée : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuReglageAdresseDetection() {

    Serial.print("\x1b[2J\x1b[;H");
    static bool adresseConfigure = false;
    static bool adresseDetecteur1 = false;
    static bool adresseDetecteur2 = false;
    static int adresse1 = 2;
    static int adresse2 = 3;

    Serial.println("");
    Serial.println("Configuration adresse detecteur");
    Serial.println("");

    if (!adresseConfigure) {

        if (!adresseDetecteur1) {
            adresse1 = atoi(message);
            if (adresse1 > 0 && adresse1 < 2048) {
                EEPROM.write(ADRESSE_MEMOIRE_ADRESSE_DETECTION1, adresse1);
                adresseDetecteur1 = true;
                strcpy(message, "");
            } else {
                Serial.print("Detect 1 : ");
                Serial.println("Entrée une adresse entre 0 et 2048 : ");
                return;
            }
        }

        if (!adresseDetecteur2) {
            adresse2 = atoi(message);
            if (adresse2 > 0 && adresse2 < 2048) {
                EEPROM.write(ADRESSE_MEMOIRE_ADRESSE_DETECTION2, adresse2);
                adresseDetecteur2 = true;
            } else {
                Serial.print("Detect 2 : ");
                Serial.println("Entrée une adresse entre 0 et 2048 : ");
                return;
            }
        }

        adresseConfigure = true;

    }

    Serial.println("");
    Serial.println("Detecteur 1");
    Serial.print("Nouvelle adresse configuré : "); Serial.println(adresse1);
    Serial.println("");
    Serial.println("Detecteur 2");
    Serial.print("Nouvelle adresse configuré : "); Serial.println(adresse2);
    Serial.println("");

    Serial.println("Entrée 'E' pour quitter : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        adresseDetecteur1 = false;
        adresseDetecteur2 = false;
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuReglageGaucheDroite() {

    Serial.print("\x1b[2J\x1b[;H");
    static bool servo = false;
    static bool gauche = false;
    static bool droite = false;
    static int maxGauche = DEFAULT_SERVO_MAX_GAUCHE;
    static int maxDroite = DEFAULT_SERVO_MAX_DROITE;

    static int angleGauche = 1500;
    static int angleDroite = 1500;

    Serial.println("");
    Serial.println("Configuration possition gauche / droite servo");
    Serial.println("");

    ServoMoteur.attach(PIN_SERVO);

    if (!servo) {

        if (!gauche) {

            ServoMoteur.write(angleGauche);

            Serial.println("");
            Serial.println("Entrée '+' pour ajouter de l'angle");
            Serial.println("Entrée '-' pour retirée de l'angle");
            Serial.println("Entrée 'V' pour validée");
            Serial.println(""); Serial.println("");

            if (strstr(message, "+")) {

                strcpy(message, "");
                angleGauche = angleGauche - 10;

            } else if (strstr(message, "-")) {

                strcpy(message, "");
                angleGauche = angleGauche + 10;

            } else if (strstr(message, "V")) {

                strcpy(message, "");
                EEPROM.write(ADRESSE_MEMOIRE_ANGLE_GAUCHE, angleGauche);
                gauche = true;

            }

            Serial.print("GAUCHE : "); Serial.print(angleGauche);
            return;
            
        }

        if (!droite) {

            ServoMoteur.write(angleDroite);

            Serial.println("");
            Serial.println("Entrée '+' pour ajouter de l'angle");
            Serial.println("Entrée '-' pour retirée de l'angle");
            Serial.println("Entrée 'V' pour validée");
            Serial.println(""); Serial.println("");

            if (strstr(message, "+")) {

                strcpy(message, "");
                angleDroite = angleDroite + 10;

            } else if (strstr(message, "-")) {

                strcpy(message, "");
                angleDroite = angleDroite - 10;

            } else if (strstr(message, "V")) {

                strcpy(message, "");
                EEPROM.write(ADRESSE_MEMOIRE_ANGLE_DROITE, angleDroite);
                droite = true;

            }

            Serial.print("DROITE : "); Serial.print(angleGauche);
            return;
            
        }

        servo = true;
        return;

    }

    Serial.println("");
    Serial.print("Angle gauche : "); Serial.println(angleGauche);
    Serial.print("Angle droite : "); Serial.println(angleDroite);
    Serial.println("");

    ServoMoteur.detach();

    Serial.println("Entrée 'E' pour quitter : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        servo = false;
        gauche = false;
        droite = false;
        menuConfiguration = accueil;
        purgeMessage();
    }
}

void menuReglageIssolement() {

    Serial.print("\x1b[2J\x1b[;H");

    static bool isolementCarte = false;
    static bool parametres = false;

    if (!parametres) {

        Serial.println("");
        Serial.println("Entrée 'C' pour changé d'état");
        Serial.println("Entrée 'V' pour validée");
        Serial.println(""); Serial.println("");

        if (strstr(message, "C")) {

            isolementCarte = !isolementCarte;

            if (!isolementCarte) {
                Serial.println("CARTE ISOLÉE");
            } else {
                Serial.println("CARTE EN SERVICE");
            }

            strcpy(message, "");

        }

        if (strstr(message, "V")) {

            EEPROM.write(ADRESSE_MEMOIRE_CARTE_ISOLEE, isolementCarte);
            Serial.println("Paramettre enregistrés");
            strcpy(message, "");

            parametres = true;

        }

        return;
    }

    Serial.println("Entrée 'E' pour quitée : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        parametres = false;
        purgeMessage();
    }
    
}

void menuReglagePointMillieu() {
    
    Serial.print("\x1b[2J\x1b[;H");

    Serial.println("");
    Serial.println("");
    Serial.println("REGLAGE POINT MILLIEU...");
    Serial.println("Entrée 'E' pour quitée : ");

    ServoMoteur.attach(PIN_SERVO);
    ServoMoteur.write(POINT_MILLIEU_SERVO);
    ServoMoteur.detach();

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        purgeMessage();
    }
}

void menuReglageNombreAiguillage() {

    Serial.print("\x1b[2J\x1b[;H");
    static bool adresseConfigure = false;

    Serial.println("");
    Serial.println("Configuration nombre de moteur");
    Serial.println("");

    if (!adresseConfigure) {

        int adresse = atoi(message);
        if (adresse == 1 || adresse == 2) {
            EEPROM.write(ADRESSE_MEMOIRE_NOMBRE_MOTEUR, adresse);
            adresseConfigure = true;
        } else {
            Serial.println("Entrée le nombre de moteur entre 1 et 2 : ");
            return;
        }

        Serial.println("");
        Serial.print("nombre de moteur configurée : "); Serial.println(adresse);

    }

    Serial.println("Entrée 'E' pour quitée : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        menuConfiguration = accueil;
        purgeMessage();
    }
}

void menuReglage() {
    
}

void prossesMenu() {

    if (nouveauMessageDisponible) {

        switch (menuConfiguration) {
            case reglageAdresseAiguillage:
                menuReglageAdresseAiguillage();
                break;

            case reglageAdresseDetection:
                menuReglageAdresseDetection();
                break;

            case reglageGaucheDroite:
                menuReglageGaucheDroite();
                break;

            case reglageIssolement:
                menuReglageIssolement();
                break;

            case reglageNombreAiguillage:
                menuReglageNombreAiguillage();
                break;

            case reglagePointMillieu:
                menuReglagePointMillieu();
                break;

            case reglage:
                menuReglage();
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