#ifndef GestionAiguillage_h
#define GestionAiguillage_h

bool getDetection1(uint8_t pinBouton);
bool getDetection2(uint8_t pinBouton);
void changementPossition(uint8_t pinServo, uint8_t pinRelais, bool etatPossitionAiguillage);

#endif // CarteAiguillage_h