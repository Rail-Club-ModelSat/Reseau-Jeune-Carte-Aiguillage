#include <Arduino.h>
#include <ServoTimer2.h>

#include "CarteAiguillage.h"

ServoTimer2   ServoMoteur;

void CarteAiguillage::serialEvent() {
  char carlu = 0;
  int cardispo = 0;

  cardispo = Serial.available();

  while(cardispo > 0) {
    carlu = Serial.read();

    if(carlu == 77) {
      Serial.println("Réglage du point millieu : ");
    }

    cardispo = Serial.available();
  }
}

void setServo(int state) {
  int targetPosition = (state == TURNOUT_NORMAL) ? SERVO_VALL_NORMAL : SERVO_VALL_TURNOUT;

  int currentPosition = ServoMoteur.read();
  unsigned long previousMillis = millis();

  while (currentPosition != targetPosition) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1) {
      previousMillis = currentMillis;

      currentPosition = (currentPosition < targetPosition) ? currentPosition + 1 : currentPosition - 1;
      ServoMoteur.write(currentPosition);
    }
  }
}

void handleTurnoutPosition() {
  if (etatPossitionAiguillage != old_etatPossitionAiguillage) {
    old_etatPossitionAiguillage = etatPossitionAiguillage;
    digitalWrite(RELAI_PIN, etatPossitionAiguillage);
    ServoMoteur.attach(SERVO_PIN);
    setServo(etatPossitionAiguillage);
    ServoMoteur.detach();
    Serial.print("Changement Etat aiguillage : ");
    Serial.println(etatPossitionAiguillage);
  }
}


void notifyButtonState(int buttonPin, int sensorAddress, const char *sensorName) {
  bool &didStatus = (buttonPin == N_BUTTON_PIN) ? didStatusN : didStatusD;
  bool &oldDidStatus = (buttonPin == N_BUTTON_PIN) ? oldDidStatusN : oldDidStatusD;
  unsigned long &lastDebounceTime = (buttonPin == N_BUTTON_PIN) ? lastDebounceTimeN : lastDebounceTimeD;
  unsigned long &debounceDelay = (buttonPin == N_BUTTON_PIN) ? debounceDelayN : debounceDelayD;

  int reading = digitalRead(buttonPin);

  if (reading != oldDidStatus) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) >= debounceDelay) {
    if (reading != didStatus) {
      didStatus = reading;
      LocoNet.reportSensor(sensorAddress, reading);
      Serial.print("Changement Etat ");
      Serial.print(sensorName);
      Serial.print(" : ");
      Serial.println(reading);
    }
  }

  oldDidStatus = reading;
}

void notifyButtonStates() {
  notifyButtonState(N_BUTTON_PIN, ADRESSE_SENSOR1, "Sensor 1");
  notifyButtonState(D_BUTTON_PIN, ADRESSE_SENSOR2, "Sensor 2");
}