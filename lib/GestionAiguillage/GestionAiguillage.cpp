#include <Arduino.h>
#include <ServoTimer2.h>
#include <ConfigCarte.h>
#include "GestionAiguillage.h"

ServoTimer2   ServoMoteur;


/**
 * Fonction : setServo
 * -------------------
 * Déplace le servo à la position cible en fonction de l'état de position de l'aiguillage.
 *
 * @param etatPossitionAiguillage  État de position de l'aiguillage (0 pour droite, 1 pour gauche).
 * @param pinServo                 Broche du microcontrôleur où le servo est connecté.
 */
void setServo(bool etatPossitionAiguillage, uint8_t pinServo) {

    ServoMoteur.attach(pinServo);

    uint16_t targetPosition = (etatPossitionAiguillage == 0) ? getMaxServoDroite() : getMaxServoGauche();

    uint16_t currentPosition = ServoMoteur.read();
    unsigned long previousMillis = millis();

    while (currentPosition != targetPosition) {
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= 1) {

            currentPosition = (currentPosition < targetPosition) ? currentPosition + 1 : currentPosition - 1;
            ServoMoteur.write(currentPosition);

            previousMillis = currentMillis;
        }
    }

    ServoMoteur.detach();
}


/**
 * Fonction : changementPossition
 * ------------------------------
 * Change la position de l'aiguillage si l'état de la position a changé.
 *
 * @param pinServo                 Broche du microcontrôleur où le servo est connecté.
 * @param pinRelais                Broche du microcontrôleur où le relais est connecté.
 * @param etatPossitionAiguillage  Nouvel état de position de l'aiguillage.
 */
void changementPossition(uint8_t pinServo, uint8_t pinRelais, bool etatPossitionAiguillage) {

    static bool old_etatPossitionAiguillage;

    if (etatPossitionAiguillage != old_etatPossitionAiguillage) {

        digitalWrite(pinRelais, etatPossitionAiguillage);
        setServo(etatPossitionAiguillage, pinServo);

        old_etatPossitionAiguillage = etatPossitionAiguillage;
    }

}


/**
 * Fonction : getDetection1
 * ------------------------
 * Détecte les changements d'état pour un bouton connecté à une broche spécifiée.
 *
 * @param pinBouton  Broche du microcontrôleur où le bouton est connecté.
 * @return bool : Vrai si un changement d'état vers l'état haut est détecté.
 */
bool getDetection1(uint8_t pinBouton) {
    bool etatBouton = digitalRead(pinBouton);
    static bool old_etatBouton = false;

    if (old_etatBouton != etatBouton) {
        old_etatBouton = etatBouton;
        if (etatBouton) return true;
    }

    return false;
}


/**
 * Fonction : getDetection2
 * ------------------------
 * Détecte les changements d'état pour un bouton connecté à une broche spécifiée, similaire à getDetection1.
 *
 * @param pinBouton  Broche du microcontrôleur où le bouton est connecté.
 * @return bool : Vrai si un changement d'état vers l'état haut est détecté.
 */
bool getDetection2(uint8_t pinBouton) {
    bool etatBouton = digitalRead(pinBouton);
    static bool old_etatBouton = false;

    if (old_etatBouton != etatBouton) {
        old_etatBouton = etatBouton;
        if (etatBouton) return true;
    }

    return false;
}