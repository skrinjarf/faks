struct emisija{
    char ime[20], zanr[20], kanal[20];
    int poc_s, poc_m, kraj_s, kraj_m;

    emisija();
    emisija(char *_ime, int poc_s, int poc_m, int kraj_s, int kraj_m, char *_zanr,char *_kanal);
    char* get_ime(void);
    char* get_zanr(void);
    char* get_kanal(void);
    int get_pocetak_m(void);
    int get_pocetak_s(void);
    int get_kraj_m(void);
    int get_kraj_s(void);

};

struct program{

    emisija data[100];
    int zadnji;

    program();
    int get_broj_emisija(void);
    emisija get_emisija(int index);
    bool dodaj_emisiju(emisija e);
    program daj_kanal(char *kanal);
    program daj_zanr(char* zanr);
    program daj_raspon(int poc_s, int poc_m, int kraj_s, int kraj_m);
};


