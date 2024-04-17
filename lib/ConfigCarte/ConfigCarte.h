#ifndef ConfigCarte_h
#define ConfigCarte_h

enum { configuration, exploitation } mode;
void getCarathere(char lectureCarathere);

class ConfigCarte {

    public:

    private:
    enum { reglagePointMillieu, reglageGeucheDroite, setAdresseAiguillage, setAdresseDetection, setIsolement, help, sortieConfiguration } _menuConfiguration;

};

#endif // ConfigCarte_h