#include <Arduino.h>
#include <ServoTimer2.h>
#include <ConfigCarte.h>
#include "GestionAiguillage.h"

ServoTimer2   ServoMoteur;

void setServo(bool etatPossitionAiguillage, uint8_t pinServo) {

    ServoMoteur.attach(pinServo);

    int targetPosition = (etatPossitionAiguillage == 0) ? getMaxServoDroite() : getMaxServoGauche();

    int currentPosition = ServoMoteur.read();
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

void changementPossition(uint8_t pinServo, uint8_t pinRelais, bool etatPossitionAiguillage) {

    static bool old_etatPossitionAiguillage;

    if (etatPossitionAiguillage != old_etatPossitionAiguillage) {

        digitalWrite(pinRelais, etatPossitionAiguillage);
        setServo(etatPossitionAiguillage, pinServo);

        old_etatPossitionAiguillage = etatPossitionAiguillage;
    }

}

bool getDetection1(uint8_t pinBouton) {
    bool etatBouton = digitalRead(pinBouton);
    static bool old_etatBouton = false;

    if (old_etatBouton != etatBouton) {
        old_etatBouton = etatBouton;
        if (etatBouton) return true;
    }

    return false;
}

bool getDetection2(uint8_t pinBouton) {
    bool etatBouton = digitalRead(pinBouton);
    static bool old_etatBouton = false;

    if (old_etatBouton != etatBouton) {
        old_etatBouton = etatBouton;
        if (etatBouton) return true;
    }

    return false;
}