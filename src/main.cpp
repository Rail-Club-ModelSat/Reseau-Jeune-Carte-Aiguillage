#include <Arduino.h>
#include <LocoNet.h>
#include <ServoTimer2.h>
#include <ConfigCarte.h>

#include "constante.h"

lnMsg *LnPacket;

void start() {
  Serial.begin(9600);
  LocoNet.init(LN_TX_PIN);
  pinMode(RELAI_PIN, OUTPUT);
  pinMode(N_BUTTON_PIN, INPUT_PULLUP);
  pinMode(D_BUTTON_PIN, INPUT_PULLUP);
  etatPossitionAiguillage = TURNOUT_NORMAL;
}

void setup() {
  start();
}

void serialEvent() {

  boolean messageEnCours = true;

  while (Serial.available() && messageEnCours) {

    int lectureCarathere = Serial.read();
    messageEnCours = getCarathere(lectureCarathere);

  }

}

void loop() {
  LnPacket = LocoNet.receive();
  if (LnPacket) {
    LocoNet.processSwitchSensorMessage(LnPacket);
  }

  prossesMenu();

}

// Callbacks from LocoNet.processSwitchSensorMessage() ...
// We tie into the ones connected to turnouts so we can capture anything
// that can change (or indicatea change to) a turnout's position.

void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction )
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifySwitchReport( uint16_t Address, uint8_t Output, uint8_t Direction )
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifySwitchState( uint16_t Address, uint8_t Output, uint8_t Direction )
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifyPower(uint8_t State) {
  if (State) { 
    // Faire clignoté la led rouge
  }
  
}