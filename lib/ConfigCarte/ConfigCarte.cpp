#include <Arduino.h>
#include <EEPROM.h>
#include <ServoTimer2.h>


#include "ConfigCarte.h"

ServoTimer2   Servo;

char message[TAILLE_MAX_SERIAL_MESSAGE];
bool nouveauMessageDisponible = true;

void purgeMessage() {
    memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
    Serial.print(F("\x1b[2J\x1b[;H"));
    nouveauMessageDisponible = true;
    prossesMenu();
}

uint16_t getMaxServoGauche() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ANGLE_GAUCHE, maxAngleServo);

    return maxAngleServo;
}

uint16_t getMaxServoDroite() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ANGLE_DROITE, maxAngleServo);

    return maxAngleServo;
}

uint16_t getAdresseAiguillage() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE, maxAngleServo);

    return maxAngleServo;
}

uint16_t getAdresseDetecteur1() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_DETECTION1, maxAngleServo);

    return maxAngleServo;
}

uint16_t getAdresseDetecteur2() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_DETECTION2, maxAngleServo);

    return maxAngleServo;
}

uint8_t getNombreAiguillage() {
    uint8_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_NOMBRE_MOTEUR, maxAngleServo);

    return maxAngleServo;
}

bool getIssolementCarte() {
    bool maxAngleServo;
    EEPROM.get(ADRESSE_MEMOIRE_CARTE_ISOLEE, maxAngleServo);

    return maxAngleServo;
}

bool getSensLogique() {
    bool maxAngleServo;
    EEPROM.get(ADRESSE_MEMOIRE_SENS_LOGIQUE, maxAngleServo);

    return maxAngleServo;
}

void menuReglage() {

    Serial.println(F(""));

    Serial.println(F("Paramettre Carte :"));
    Serial.println(F(""));

    Serial.print(F("Carte Issolee : "));

    if (!getIssolementCarte()) {
        Serial.println(F("Issolee"));
    } else {
        Serial.println(F("En Service"));
    }

    Serial.print(F("Sens Logique : "));
    if (getSensLogique()) {
        Serial.println(F("Normal"));
        Serial.println(F(""));
    } else {
        Serial.println(F("Inverser"));
        Serial.println(F(""));
    }

    Serial.print(F("Nombre Moteur : "));
    Serial.println(getNombreAiguillage());
    Serial.println(F(""));

    Serial.print(F("Adresse Aiguillage : "));
    Serial.println(getAdresseAiguillage());
    Serial.print(F("Adresse Detecteur 1 : "));
    Serial.println(getAdresseDetecteur1());
    Serial.print(F("Adresse Detecteur 2 : "));
    Serial.println(getAdresseDetecteur2());
    Serial.println(F(""));

    Serial.println(F("Angle servomoteur : "));
    Serial.print(F("gauche : "));
    Serial.println(getMaxServoGauche());
    Serial.print(F("droite : "));
    Serial.println(getMaxServoDroite());
    Serial.println(F(""));

}

void menuHelp() {

    Serial.println(F(""));

    Serial.println(F("Help menu :"));
    Serial.print(MENU_REGLAGE);
    Serial.println(F(" : voire les reglage"));
    Serial.print(MENU_REGLAGE_POINT_MILLIEU);
    Serial.println(F(" : Reglage point millieu servo moteur"));
    Serial.print(MENU_REGLAGE_GAUCHE_DROITE);
    Serial.println(F(" : Reglage fin de course gauche / droite"));
    Serial.print(MENU_REGLAGE_ADRESSE_AIGUILLAGE);
    Serial.println(F(" : Reglage adresse commande aiguillage"));
    Serial.print(MENU_REGLAGE_ADRESSE_DETECTION);
    Serial.println(F(" : Reglage adresse detection"));
    Serial.print(MENU_REGLAGE_NOMBRE_AIGUILLAGE);
    Serial.println(F(" : Reglage nombre de moteur aiguillage"));
    Serial.print(MENU_REGLAGE_SENS_LOGIQUE);
    Serial.println(F(" : Reglage sens logique moteur aiguillage"));
    Serial.print(MENU_REGLAGE_ISSOLEMENT);
    Serial.println(F(" : Issolement carte"));
    Serial.print(MENU_EXIT_MODE_CONFIGURATION);
    Serial.println(F(" : Quite le mode configuration"));
    Serial.print(MENU_HELP);
    Serial.println(F(" : Commande help"));
    Serial.println(F(""));

}

void menuExploitation() {

    Serial.println(F("Entree 'C' pour passer en mode configuration : "));
    if (strstr(message, MENU_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuAccueil() {

    if (strstr(message, MENU_HELP)) {

        menuHelp();
        memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
        nouveauMessageDisponible = true;
        prossesMenu();

    } else if (strstr(message, MENU_REGLAGE_GAUCHE_DROITE)) {

        menuConfiguration = reglageGaucheDroite;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE_POINT_MILLIEU)) {

        menuConfiguration = reglagePointMillieu;
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
        
    } else if (strstr(message, MENU_REGLAGE_SENS_LOGIQUE)) {

        menuConfiguration = reglageSensLogique;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE_ISSOLEMENT)) {

        menuConfiguration = reglageIssolement;
        purgeMessage();
        
    } else if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {

        menuConfiguration = exploitation;
        purgeMessage();
        
    } else if (strstr(message, MENU_REGLAGE)) {

        menuReglage();
        memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
        nouveauMessageDisponible = true;
        prossesMenu();
        
    } else {

        memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
        char buffer[60];
        sprintf(buffer, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "Commande (", MENU_REGLAGE , "/" , MENU_REGLAGE_POINT_MILLIEU, "/" , MENU_REGLAGE_SENS_LOGIQUE, "/", MENU_REGLAGE_GAUCHE_DROITE, "/", MENU_REGLAGE_ADRESSE_AIGUILLAGE, "/", MENU_REGLAGE_ADRESSE_DETECTION, "/", MENU_REGLAGE_NOMBRE_AIGUILLAGE, "/", MENU_REGLAGE_ISSOLEMENT, "/", MENU_EXIT_MODE_CONFIGURATION, "/", MENU_HELP, ") : ");
        Serial.write(buffer);

        Serial.println("");
        
    }

}

void menuReglageAdresseAiguillage() {

    Serial.print(F("\x1b[2J\x1b[;H"));
    static bool adresseConfigure = false;

    Serial.println(F(""));
    Serial.println(F("Configuration adresse commande moteur aiguillage"));
    Serial.println(F(""));

    if (!adresseConfigure) {

        uint16_t adresse = atoi(message);
        if (adresse > 0 && adresse < 2048) {
            EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE, adresse);
            adresseConfigure = true;
        } else {
            Serial.println(F("Entree une adresse entre 0 et 2048 : "));
            return;
        }

        Serial.println(F(""));
        Serial.print(F("Nouvelle adresse configure : ")); Serial.println(adresse);

    }

    Serial.println(F("Entree 'E' pour quitee : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuReglageAdresseDetection() {

    Serial.print(F("\x1b[2J\x1b[;H"));
    static bool adresseConfigure = false;
    static bool adresseDetecteur1 = false;
    static bool adresseDetecteur2 = false;
    static uint16_t adresse1 = 2;
    static uint16_t adresse2 = 3;

    Serial.println(F(""));
    Serial.println(F("Configuration adresse detecteur"));
    Serial.println(F(""));

    if (!adresseConfigure) {

        if (!adresseDetecteur1) {
            adresse1 = atoi(message);
            if (adresse1 > 0 && adresse1 < 2048) {
                EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_DETECTION1, adresse1);
                adresseDetecteur1 = true;
                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
            } else {
                Serial.print(F("Detect 1 : "));
                Serial.println(F("Entree une adresse entre 0 et 2048 : "));
                return;
            }
        }

        if (!adresseDetecteur2) {
            adresse2 = atoi(message);
            if (adresse2 > 0 && adresse2 < 2048) {
                EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_DETECTION2, adresse2);
                adresseDetecteur2 = true;
            } else {
                Serial.print(F("Detect 2 : "));
                Serial.println(F("Entree une adresse entre 0 et 2048 : "));
                return;
            }
        }

        adresseConfigure = true;

    }

    Serial.println(F(""));
    Serial.println(F("Detecteur 1"));
    Serial.print(F("Nouvelle adresse configure : ")); Serial.println(adresse1);
    Serial.println(F(""));
    Serial.println(F("Detecteur 2"));
    Serial.print(F("Nouvelle adresse configure : ")); Serial.println(adresse2);
    Serial.println(F(""));

    Serial.println(F("Entree 'E' pour quitter : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        adresseDetecteur1 = false;
        adresseDetecteur2 = false;
        menuConfiguration = accueil;
        purgeMessage();
    }

}

void menuReglageGaucheDroite() {

    Serial.print(F("\x1b[2J\x1b[;H"));
    static bool servo = false;
    static bool gauche = false;
    static bool droite = false;

    static uint16_t angleGauche = 1500;
    static uint16_t angleDroite = 1500;

    Serial.println(F(""));
    Serial.println(F("Configuration possition gauche / droite servo"));
    Serial.println(F(""));

    Serial.println(F(""));
    Serial.println(F("Entree '+' pour ajouter de l'angle"));
    Serial.println(F("Entree '-' pour retiree de l'angle"));
    Serial.println(F("Entree 'D' pour la configuration par default (moteur decapod)"));
    Serial.println(F("Entree 'V' pour validee"));
    Serial.println(F("")); Serial.println(F(""));

    Servo.attach(PIN_SERVO);

    if (!servo) {

        if (!gauche) {

            Servo.write(angleGauche);

            if (strstr(message, "+")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                angleGauche = angleGauche - 10;

            } else if (strstr(message, "-")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                angleGauche = angleGauche + 10;

            } else if (strstr(message, "D")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                EEPROM.put(ADRESSE_MEMOIRE_ANGLE_GAUCHE, DEFAULT_SERVO_MAX_GAUCHE);
                angleGauche = DEFAULT_SERVO_MAX_GAUCHE;
                gauche = true;

            } else if (strstr(message, "V")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                EEPROM.put(ADRESSE_MEMOIRE_ANGLE_GAUCHE, angleGauche);
                gauche = true;

            }

            Serial.print(F("GAUCHE : ")); Serial.print(angleGauche);
            return;
            
        }

        if (!droite) {

            Servo.write(angleDroite);

            if (strstr(message, "+")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                angleDroite = angleDroite + 10;

            } else if (strstr(message, "-")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                angleDroite = angleDroite - 10;

            }else if (strstr(message, "D")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                EEPROM.put(ADRESSE_MEMOIRE_ANGLE_DROITE, DEFAULT_SERVO_MAX_DROITE);
                angleDroite = DEFAULT_SERVO_MAX_DROITE;
                droite = true;

            } else if (strstr(message, "V")) {

                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
                EEPROM.put(ADRESSE_MEMOIRE_ANGLE_DROITE, angleDroite);
                droite = true;

            }

            Serial.print(F("DROITE : ")); Serial.print(angleDroite);
            return;
            
        }

        servo = true;
        return;

    }

    Serial.println(F(""));
    Serial.print(F("Angle gauche : ")); Serial.println(angleGauche);
    Serial.print(F("Angle droite : ")); Serial.println(angleDroite);
    Serial.println(F(""));

    Servo.detach();

    Serial.println(F("Entree 'E' pour quitter : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        servo = false;
        gauche = false;
        droite = false;
        menuConfiguration = accueil;
        purgeMessage();
    }
}

void menuReglageIssolement() {

    Serial.print(F("\x1b[2J\x1b[;H"));

    static bool isolementCarte = false;
    static bool parametres = false;

    if (!parametres) {

        Serial.println(F(""));
        Serial.println(F("Entree 'C' pour change d'etat"));
        Serial.println(F("Entree 'V' pour validee"));
        Serial.println(F("")); Serial.println(F(""));;

        if (strstr(message, "C")) {

            isolementCarte = !isolementCarte;

            if (!isolementCarte) {
                Serial.println(F("CARTE ISOLEE"));
            } else {
                Serial.println(F("CARTE EN SERVICE"));
            }

            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

        }

        if (strstr(message, "V")) {

            EEPROM.put(ADRESSE_MEMOIRE_CARTE_ISOLEE, isolementCarte);
            Serial.println(F("Paramettre enregistres"));
            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

            parametres = true;

        }

        return;
    }

    Serial.println(F("Entree 'E' pour quitee : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        parametres = false;
        purgeMessage();
    }
    
}

void menuReglageSensLogique() {

    Serial.print(F("\x1b[2J\x1b[;H"));

    static bool isolementCarte = false;
    static bool parametres = false;

    if (!parametres) {

        Serial.println(F(""));
        Serial.println(F("Entree 'C' pour change d'etat"));
        Serial.println(F("Entree 'V' pour validee"));
        Serial.println(F("")); Serial.println(F(""));

        if (strstr(message, "C")) {

            isolementCarte = !isolementCarte;

            if (!isolementCarte) {
                Serial.println(F("Sens Logique inverser"));
            } else {
                Serial.println(F("Sens Logique normal"));
            }

            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

        }

        if (strstr(message, "V")) {

            EEPROM.put(ADRESSE_MEMOIRE_SENS_LOGIQUE, isolementCarte);
            Serial.println(F("Paramettre enregistres"));
            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

            parametres = true;

        }

        return;
    }

    Serial.println(F("Entree 'E' pour quitee : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        parametres = false;
        purgeMessage();
    }
    
}

void menuReglagePointMillieu() {
    
    Serial.print(F("\x1b[2J\x1b[;H"));
    Servo.attach(PIN_SERVO);

    Serial.println(F(""));
    Serial.println(F(""));
    Serial.println(F("REGLAGE POINT MILLIEU..."));
    Serial.println(F("Entree 'E' pour quitee : "));

    Servo.write(POINT_MILLIEU_SERVO);

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        Servo.detach();
        purgeMessage();
    }
}

void menuReglageNombreAiguillage() {

    Serial.print(F("\x1b[2J\x1b[;H"));
    static bool adresseConfigure = false;

    Serial.println(F(""));
    Serial.println(F("Configuration nombre de moteur"));
    Serial.println(F(""));

    if (!adresseConfigure) {

        int adresse = atoi(message);
        if (adresse == 1 || adresse == 2) {
            EEPROM.put(ADRESSE_MEMOIRE_NOMBRE_MOTEUR, adresse);
            adresseConfigure = true;
        } else {
            Serial.println(F("Entree le nombre de moteur entre 1 et 2 : "));
            return;
        }

        Serial.println(F(""));
        Serial.print(F("nombre de moteur configuree : ")); Serial.println(adresse);

    }

    Serial.println(F("Entree 'E' pour quitee : "));

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        adresseConfigure = false;
        menuConfiguration = accueil;
        purgeMessage();
    }
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

            case reglageSensLogique:
                menuReglageSensLogique();
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

        nouveauMessageDisponible = false; // Reinitialiser le flag
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