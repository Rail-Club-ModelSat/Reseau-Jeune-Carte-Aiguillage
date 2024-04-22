#include <Arduino.h>
#include <LocoNet.h>
#include <ConfigCarte.h>
#include <GestionAiguillage.h>

#include "constante.h"

lnMsg        *LnPacket;

void setup() {
  LocoNet.init();

  pinMode(PIN_RELAIS, OUTPUT);
  pinMode(PIN_BOUTON_DETECT1, INPUT_PULLUP);
  pinMode(PIN_BOUTON_DETECT2, INPUT_PULLUP);

  pinMode(PIN_LED_POSSITION_AIGUIL, OUTPUT);
  pinMode(PIN_LED_DATA, OUTPUT);
  pinMode(PIN_LED_ERREUR, OUTPUT);

  Serial.begin(VITESSE_TRAMSMISSION);
  Serial.println(F("")); Serial.println(F(""));
  Serial.println(F("Rail Club ModelSat - Carte Loconet Arduino"));
  Serial.println(F("Par MARTIN Mathis - V1.0.0"));
  Serial.println(F("")); Serial.println(F("")); Serial.println(F(""));

  if (!getIssolementCarte()) {
    Serial.println(F("/!\\ CARTE ISSOLER /!\\"));
    Serial.println(F(""));
  }

  digitalWrite(PIN_LED_DATA, HIGH);
  digitalWrite(PIN_LED_POSSITION_AIGUIL, HIGH);

}

void serialEvent() {

  boolean messageEnCours = true;

  while (Serial.available() && messageEnCours) {

    char lectureCarathere = Serial.read();
    messageEnCours = getCarathere(lectureCarathere);

  }

}

void loconetMessage() {

  LnPacket = LocoNet.receive();

  if (LnPacket) {
    LocoNet.processSwitchSensorMessage(LnPacket);
  }

}

void getDetection() {

  bool etatDetection1 = getDetection1(PIN_BOUTON_DETECT1);
  bool etatDetection2 = getDetection2(PIN_BOUTON_DETECT2);

  if (etatDetection1) {
    LocoNet.reportSensor(getAdresseDetecteur1(), etatDetection1);
  }


  if (etatDetection2 && getNombreAiguillage() == 2) {
    LocoNet.reportSensor(getAdresseDetecteur1(), etatDetection2);
  }

}

bool getEtatSensLogique() {
  bool etatSensLogique = getSensLogique() ^ etatPossitionAiguillage;
  return etatSensLogique;
}

void gestionLedErreur() {

  if (!getIssolementCarte()) {

    digitalWrite(PIN_LED_ERREUR, LOW);

  } else if (!etatPowerDCC) {

    static long currentTime = 0;
    static unsigned long previousTime = 0;
    static bool etatLedErreur = true;

    currentTime = millis();
    if((currentTime - previousTime) > 600){

      digitalWrite(PIN_LED_ERREUR, etatLedErreur);
      newLoconetData = false;

      etatLedErreur = !etatLedErreur;

      previousTime = currentTime;
    }

  } else {
    digitalWrite(PIN_LED_ERREUR, HIGH);
  }
  
}

void newData() {
  if (newLoconetData) {
    static long currentTime = 0;
    static unsigned long previousTime = 0;

    digitalWrite(PIN_LED_DATA, LOW);

    currentTime = millis();
    if((currentTime - previousTime) > 300){

      digitalWrite(PIN_LED_DATA, HIGH);
      newLoconetData = false;

      previousTime = currentTime;
    }
  }
  
}

void dispatch() {

  prossesMenu();
  gestionLedErreur();
  newData();

  if (getIssolementCarte() && menuConfiguration == exploitation) {
    loconetMessage();
    changementPossition(PIN_SERVO, PIN_RELAIS, getEtatSensLogique());
    digitalWrite(PIN_LED_POSSITION_AIGUIL, !etatPossitionAiguillage);
    getDetection();
  }

}

void loop() {
  dispatch();
}

void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;
}

void notifySwitchReport( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;  
}

void notifySwitchState( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;
}

void notifyPower(uint8_t State) {
  etatPowerDCC = State;
  newLoconetData = true;
}