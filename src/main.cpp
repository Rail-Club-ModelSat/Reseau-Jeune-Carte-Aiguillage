#include <Arduino.h>
#include <LocoNet.h>
#include <ConfigCarte.h>
#include <GestionAiguillage.h>

#include "constante.h"

lnMsg        *LnPacket;


/**
 * Fonction : setup
 * ----------------
 * Initialise le système, configure les broches et affiche les informations de démarrage sur le moniteur série.
 */
void setup() {
  LocoNet.init(LN_TX_PIN);

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


/**
 * Fonction : serialEvent
 * ----------------------
 * Traite les événements série en lisant les caractères entrants tant qu'ils sont disponibles.
 */
void serialEvent() {

  boolean messageEnCours = true;

  while (Serial.available() && messageEnCours) {

    char lectureCarathere = Serial.read();
    messageEnCours = getCarathere(lectureCarathere);

  }

}


/**
 * Fonction : loconetMessage
 * -------------------------
 * Réceptionne et traite les messages Loconet reçus.
 */
void loconetMessage() {

  LnPacket = LocoNet.receive();

  if (LnPacket) {
    LocoNet.processSwitchSensorMessage(LnPacket);
  }

}


/**
 * Fonction : getDetection
 * -----------------------
 * Vérifie l'état de détection des entrées et envoie des rapports de capteur Loconet selon l'état de détection.
 */
void getDetection() {

  bool etatDetection1 = !getDetection1(PIN_BOUTON_DETECT1);
  bool etatDetection2 = !getDetection2(PIN_BOUTON_DETECT2);

  static bool ancienEtat1 = false;
  static bool ancienEtat2 = false;

  static bool etatActuel1 = false;
  static bool etatActuel2 = false;

  static unsigned long delaiRebond = 60;

  static unsigned long dernierTempsRebond1 = 0;
  static unsigned long dernierTempsRebond2 = 0;

  if (etatDetection1 != ancienEtat1) {
    dernierTempsRebond1 = millis();
  }

  if (etatDetection2 != ancienEtat2) {
    dernierTempsRebond2 = millis();
  }
  
  if ((millis() - dernierTempsRebond1) >= delaiRebond) {
    if (etatActuel1 != etatDetection1) {

      uint16_t adresseDetecte1 = getAdresseDetecteur1();

      LocoNet.reportSensor(adresseDetecte1, etatDetection1);
      newLoconetData = true;
      etatActuel1 = etatDetection1;

    }
  }

  if ((millis() - dernierTempsRebond2) >= delaiRebond) {
    if (etatActuel2 != etatDetection2 && getNombreAiguillage() == 2) {

      uint16_t adresseDetecte2 = getAdresseDetecteur2();

      LocoNet.reportSensor(adresseDetecte2, etatDetection2);
      newLoconetData = true;
      etatActuel2 = etatDetection2;

    }
  }

  ancienEtat1 = etatDetection1;
  ancienEtat2 = etatDetection2;

}


/**
 * Fonction : getEtatSensLogique
 * -----------------------------
 * Calcule l'état logique actuel basé sur le sens et la position de l'aiguillage.
 *
 * @return bool : L'état logique calculé.
 */
bool getEtatSensLogique() {
  bool etatSensLogique = getSensLogique() ^ etatPossitionAiguillage;
  return etatSensLogique;
}


/**
 * Fonction : gestionLedErreur
 * ---------------------------
 * Gère l'état de la LED d'erreur en fonction de l'état d'isolation de la carte et de l'alimentation DCC.
 */
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


/**
 * Fonction : newData
 * ------------------
 * Gère l'indication visuelle des nouvelles données Loconet à l'aide d'une LED.
 */
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


/**
 * Fonction : dispatch
 * -------------------
 * Dispatch gère différentes fonctions de contrôle, y compris la gestion de menu, des LEDs, et des messages Loconet.
 */
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


/**
 * Fonction : loop
 * ---------------
 * Boucle principale du programme
 */
void loop() {
  dispatch();
}


/**
 * Fonction : notifySwitchRequest
 * ------------------------------
 * Notifie une requête de commutation d'aiguillage et met à jour l'état de position.
 *
 * @param Address    Adresse de l'aiguillage.
 * @param Output     Sortie contrôlée.
 * @param Direction  Direction de la commutation.
 */
void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;
}


/**
 * Fonction : notifySwitchReport
 * -----------------------------
 * Notifie un rapport de commutation d'aiguillage et met à jour l'état de position.
 *
 * @param Address    Adresse de l'aiguillage.
 * @param Output     Sortie contrôlée.
 * @param Direction  Direction de la commutation.
 */
void notifySwitchReport( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;  
}


/**
 * Fonction : notifySwitchState
 * ----------------------------
 * Notifie l'état de commutation d'aiguillage et met à jour l'état de position.
 *
 * @param Address    Adresse de l'aiguillage.
 * @param Output     Sortie contrôlée.
 * @param Direction  Direction de la commutation.
 */
void notifySwitchState( uint16_t Address, uint8_t Output, uint8_t Direction ) { 
  if (Address == getAdresseAiguillage()) { etatPossitionAiguillage = ((Direction & 0x20) >> 5); } 
  newLoconetData = true;
}


/**
 * Fonction : notifyPower
 * ----------------------
 * Notifie l'état de l'alimentation DCC et met à jour l'état des données Loconet.
 *
 * @param State    État de l'alimentation DCC.
 */
void notifyPower(uint8_t State) {
  etatPowerDCC = State;
  newLoconetData = true;
}