#include <Arduino.h>
#include <LocoNet.h>
#include <EEPROM.h>
#include "constante.h"

lnMsg        *LnPacket;

void processeLocoNetPacket() {
  LnPacket = LocoNet.receive();
  if (LnPacket) {
    LocoNet.processSwitchSensorMessage(LnPacket);
  }
}

void loop() {
  processeLocoNetPacket();
}

void notifySwitchRequest(uint16_t Address, uint8_t Output, uint8_t Direction)
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifySwitchReport(uint16_t Address, uint8_t Output, uint8_t Direction)
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }

void notifySwitchState(uint16_t Address, uint8_t Output, uint8_t Direction)
{ if (Address == ADRESSE_AIGUILL) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } }