#include <Arduino.h>
#include <LocoNet.h>
#include <ServoTimer2.h>
#include <EEPROM.h>

// Définition des adresse
#define ADRESSE_AIGUILL 5
#define ADRESSE_SENSOR1 202
#define ADRESSE_SENSOR2 203

// Valeur Normal / Dévié servomoteur
#define SERVO_VALL_NORMAL  1050    // 50°C
#define SERVO_VALL_TURNOUT 1800    // 120°C

#define POINT_MILLIEU_SERVO 1500   // 90°

#define LN_TX_PIN     7
#define RELAI_PIN     5
#define SERVO_PIN     9
#define N_BUTTON_PIN  2
#define D_BUTTON_PIN  3

int  etatPossitionAiguillage;
int  old_etatPossitionAiguillage;

// Gestion du rebond pour les boutons
bool didStatusN = false;
bool oldDidStatusN = false;
unsigned long lastDebounceTimeN = 0;
unsigned long debounceDelayN = 20;

bool didStatusD = false;
bool oldDidStatusD = false;
unsigned long lastDebounceTimeD = 0;
unsigned long debounceDelayD = 20;

lnMsg        *LnPacket;
ServoTimer2   ServoMoteur;

enum TurnoutState {
  TURNOUT_NORMAL = 1,
  TURNOUT_DIVERGING = 0
};

void pointMillieuServo() {
  ServoMoteur.attach(SERVO_PIN);
  ServoMoteur.write(POINT_MILLIEU_SERVO);
  ServoMoteur.detach();
}

void serialEvent() {

  char carlu = 0;
  int cardispo = 0;

  cardispo = Serial.available();

  while(cardispo > 0) {
    carlu = Serial.read();

    if(carlu == 77) {
      Serial.println("Réglage du point millieu : ");
      pointMillieuServo();
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

void setup() {
  Serial.begin(9600);
  LocoNet.init(LN_TX_PIN);
  pinMode(RELAI_PIN, OUTPUT);
  pinMode(N_BUTTON_PIN, INPUT_PULLUP);
  pinMode(D_BUTTON_PIN, INPUT_PULLUP);
  etatPossitionAiguillage = TURNOUT_NORMAL;
}

void loop() {
  // Check for any received LocoNet packets
  LnPacket = LocoNet.receive();
  if (LnPacket) {
    LocoNet.processSwitchSensorMessage(LnPacket);
    // this function will call the specially named functions below...
  }

  handleTurnoutPosition();
  notifyButtonStates();
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