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
  Serial.println("");Serial.println("");
  Serial.println("Rail Club ModelSat - Carte Loconet Arduino");
  Serial.println("Par MARTIN Mathis - V1.0.0");
  Serial.println("");Serial.println("");Serial.println("");

  if (!getIssolementCarte()) {
    Serial.println("/!\\ CARTE ISSOLER /!\\");
    Serial.println("");
  }

}

void serialEvent() {

  boolean messageEnCours = true;

  while (Serial.available() && messageEnCours) {

    int lectureCarathere = Serial.read();
    messageEnCours = getCarathere(lectureCarathere);

  }

}

void loconetMessage() {
  
  LnPacket = LocoNet.receive();

  if (LnPacket) {
    
    Serial.print("RX: ");
    uint8_t msgLen = getLnMsgSize(LnPacket);

    for (uint8_t x = 0; x < msgLen; x++) {

      uint8_t val = LnPacket->data[x];
      
      if (val < 16) Serial.print('0');

      Serial.print(val, HEX);
      Serial.print(' ');

    }

    if (!LocoNet.processSwitchSensorMessage(LnPacket)) {
      Serial.println();
    }

  }

}

void getDetection() {

  bool etatDetection1 = getDetection1(PIN_BOUTON_DETECT1);
  bool etatDetection2 = getDetection2(PIN_BOUTON_DETECT2);

  if (etatDetection1) {
    LocoNet.reportSensor(getAdresseDetecteur1(), etatDetection1);
  }

  if (etatDetection2) {
    LocoNet.reportSensor(getAdresseDetecteur1(), etatDetection2);
  }

}

void dispatch() {
  prossesMenu();

  if (getIssolementCarte() && menuConfiguration == exploitation) {
    loconetMessage();
    changementPossition(PIN_SERVO, PIN_RELAIS, etatPossitionAiguillage);
    getDetection();
  }
}

void loop() {
  dispatch();
}

void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction )
{ 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 

  Serial.print("Switch Request: ");
  Serial.print(Address, DEC);
  Serial.print(':');
  Serial.print(Direction ? "Closed" : "Thrown");
  Serial.print(" - ");
  Serial.println(Output ? "On" : "Off");

}

void notifySwitchReport( uint16_t Address, uint8_t Output, uint8_t Direction )
{ if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifySwitchState( uint16_t Address, uint8_t Output, uint8_t Direction )
{ if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifyPower(uint8_t State) { etatPowerDCC = State; }