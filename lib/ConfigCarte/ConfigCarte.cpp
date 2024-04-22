#include <Arduino.h>
#include <EEPROM.h>
#include <ServoTimer2.h>


#include "ConfigCarte.h"

ServoTimer2   Servo;

char message[TAILLE_MAX_SERIAL_MESSAGE];
bool nouveauMessageDisponible = true;

void purgeMessage() {
    memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
    Serial.print("\x1b[2J\x1b[;H");
    nouveauMessageDisponible = true;
    prossesMenu();
}

int getMaxServoGauche() {
    int maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ANGLE_GAUCHE, maxAngleServo);

    return maxAngleServo;
}

int getMaxServoDroite() {
    int maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ANGLE_DROITE, maxAngleServo);

    return maxAngleServo;
}

uint16_t getAdresseAiguillage() {
    uint16_t maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE, maxAngleServo);

    return maxAngleServo;
}

int getAdresseDetecteur1() {
    int maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_DETECTION1, maxAngleServo);

    return maxAngleServo;
}

int getAdresseDetecteur2() {
    int maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_ADRESSE_DETECTION2, maxAngleServo);

    return maxAngleServo;
}

int getNombreAiguillage() {
    int maxAngleServo = 0;
    EEPROM.get(ADRESSE_MEMOIRE_NOMBRE_MOTEUR, maxAngleServo);

    return maxAngleServo;
}

bool getIssolementCarte() {
    bool maxAngleServo;
    EEPROM.get(ADRESSE_MEMOIRE_CARTE_ISOLEE, maxAngleServo);

    return maxAngleServo;
}

void menuReglage() {

    Serial.println("");

    Serial.println("Paramettre Carte :");
    Serial.println("");

    Serial.print("Carte Issolee : ");

    if (!getIssolementCarte()) {
        Serial.println("Issolee");
        Serial.println("");
    } else {
        Serial.println("En Service");
        Serial.println("");
    }

    Serial.print("Nombre Moteur : ");
    Serial.println(getNombreAiguillage());
    Serial.println("");

    Serial.print("Adresse Aiguillage : ");
    Serial.println(getAdresseAiguillage());
    Serial.println("");

    Serial.print("Adresse Detecteur 1 : ");
    Serial.println(getAdresseDetecteur1());
    Serial.print("Adresse Detecteur 2 : ");
    Serial.println(getAdresseDetecteur2());
    Serial.println("");

    Serial.println("Angle servomoteur : ");
    Serial.print("gauche : ");
    Serial.println(getMaxServoGauche());
    Serial.print("droite : ");
    Serial.println(getMaxServoDroite());
    Serial.println("");

}

void menuHelp() {

    Serial.println("");

    Serial.println("Help menu :");
    Serial.print(MENU_REGLAGE);
    Serial.println(" : voire les reglage");
    Serial.print(MENU_REGLAGE_POINT_MILLIEU);
    Serial.println(" : Reglage point millieu servo moteur");
    Serial.print(MENU_REGLAGE_GAUCHE_DROITE);
    Serial.println(" : Reglage fin de course gauche / droite");
    Serial.print(MENU_REGLAGE_ADRESSE_AIGUILLAGE);
    Serial.println(" : Reglage adresse commande aiguillage");
    Serial.print(MENU_REGLAGE_ADRESSE_DETECTION);
    Serial.println(" : Reglage adresse detection");
    Serial.print(MENU_REGLAGE_NOMBRE_AIGUILLAGE);
    Serial.println(" : Reglage nombre de moteur aiguillage");
    Serial.print(MENU_REGLAGE_ISSOLEMENT);
    Serial.println(" : Issolement carte");
    Serial.print(MENU_EXIT_MODE_CONFIGURATION);
    Serial.println(" : Quite le mode configuration");
    Serial.print(MENU_HELP);
    Serial.println(" : Commande help");
    Serial.println("");

}

void menuExploitation() {

    Serial.println("Entree 'C' pour passer en mode configuration : ");
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
        char buffer[33];
        sprintf(buffer, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", "Commande (", MENU_REGLAGE , "/" , MENU_REGLAGE_POINT_MILLIEU, "/", MENU_REGLAGE_GAUCHE_DROITE, "/", MENU_REGLAGE_ADRESSE_AIGUILLAGE, "/", MENU_REGLAGE_ADRESSE_DETECTION, "/", MENU_REGLAGE_NOMBRE_AIGUILLAGE, "/", MENU_REGLAGE_ISSOLEMENT, "/", MENU_EXIT_MODE_CONFIGURATION, "/", MENU_HELP, ") : ");
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
            EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_AIGUILLAGE, adresse);
            adresseConfigure = true;
        } else {
            Serial.println("Entree une adresse entre 0 et 2048 : ");
            return;
        }

        Serial.println("");
        Serial.print("Nouvelle adresse configure : "); Serial.println(adresse);

    }

    Serial.println("Entree 'E' pour quitee : ");

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
                EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_DETECTION1, adresse1);
                adresseDetecteur1 = true;
                memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);
            } else {
                Serial.print("Detect 1 : ");
                Serial.println("Entree une adresse entre 0 et 2048 : ");
                return;
            }
        }

        if (!adresseDetecteur2) {
            adresse2 = atoi(message);
            if (adresse2 > 0 && adresse2 < 2048) {
                EEPROM.put(ADRESSE_MEMOIRE_ADRESSE_DETECTION2, adresse2);
                adresseDetecteur2 = true;
            } else {
                Serial.print("Detect 2 : ");
                Serial.println("Entree une adresse entre 0 et 2048 : ");
                return;
            }
        }

        adresseConfigure = true;

    }

    Serial.println("");
    Serial.println("Detecteur 1");
    Serial.print("Nouvelle adresse configure : "); Serial.println(adresse1);
    Serial.println("");
    Serial.println("Detecteur 2");
    Serial.print("Nouvelle adresse configure : "); Serial.println(adresse2);
    Serial.println("");

    Serial.println("Entree 'E' pour quitter : ");

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

    static int angleGauche = getMaxServoGauche();
    static int angleDroite = getMaxServoDroite();

    Serial.println("");
    Serial.println("Configuration possition gauche / droite servo");
    Serial.println("");

    Serial.println("");
    Serial.println("Entree '+' pour ajouter de l'angle");
    Serial.println("Entree '-' pour retiree de l'angle");
    Serial.println("Entree 'D' pour la configuration par default (moteur decapod)");
    Serial.println("Entree 'V' pour validee");
    Serial.println(""); Serial.println("");

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

            Serial.print("GAUCHE : "); Serial.print(angleGauche);
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

            Serial.print("DROITE : "); Serial.print(angleDroite);
            return;
            
        }

        servo = true;
        return;

    }

    Serial.println("");
    Serial.print("Angle gauche : "); Serial.println(angleGauche);
    Serial.print("Angle droite : "); Serial.println(angleDroite);
    Serial.println("");

    Servo.detach();

    Serial.println("Entree 'E' pour quitter : ");

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
        Serial.println("Entree 'C' pour change d'etat");
        Serial.println("Entree 'V' pour validee");
        Serial.println(""); Serial.println("");

        if (strstr(message, "C")) {

            isolementCarte = !isolementCarte;

            if (!isolementCarte) {
                Serial.println("CARTE ISOLeE");
            } else {
                Serial.println("CARTE EN SERVICE");
            }

            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

        }

        if (strstr(message, "V")) {

            EEPROM.put(ADRESSE_MEMOIRE_CARTE_ISOLEE, isolementCarte);
            Serial.println("Paramettre enregistres");
            memset(message, 0, TAILLE_MAX_SERIAL_MESSAGE);

            parametres = true;

        }

        return;
    }

    Serial.println("Entree 'E' pour quitee : ");

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        parametres = false;
        purgeMessage();
    }
    
}

void menuReglagePointMillieu() {
    
    Serial.print("\x1b[2J\x1b[;H");
    Servo.attach(PIN_SERVO);

    Serial.println("");
    Serial.println("");
    Serial.println("REGLAGE POINT MILLIEU...");
    Serial.println("Entree 'E' pour quitee : ");

    Servo.write(POINT_MILLIEU_SERVO);

    if (strstr(message, MENU_EXIT_MODE_CONFIGURATION)) {
        menuConfiguration = accueil;
        Servo.detach();
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
            EEPROM.put(ADRESSE_MEMOIRE_NOMBRE_MOTEUR, adresse);
            adresseConfigure = true;
        } else {
            Serial.println("Entree le nombre de moteur entre 1 et 2 : ");
            return;
        }

        Serial.println("");
        Serial.print("nombre de moteur configuree : "); Serial.println(adresse);

    }

    Serial.println("Entree 'E' pour quitee : ");

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