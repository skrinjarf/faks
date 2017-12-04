#ifndef VN_H
#define VN_H

#include<vector>
#include<string>
#include<chrono>
#include <iostream>


/// Sučelje za svaki instrument povezan na sabirnicu.
class Instrument {
public:
    /// pošalji instrumentu naredbu
    virtual void send(std::string) = 0;                     ///PURE
    /// preuzmi od instrumenta vrijednost
    virtual float receive() = 0;                            ///PURE
    /// ime instrumenta
    virtual std::string deviceName() const = 0 ;
    /// implemenatcijski dio klase
    void setPort(int port) {mPort = port; }
    int  getPort() const { return mPort; }

    virtual ~Instrument() {}
protected:
    int mPort = -1;
};

/// Sučelje za sve generatore podataka
class DataGenerator {
public:
    /// odaberi signal
    virtual void setMode(int) = 0;                          ///PURE
    virtual ~DataGenerator() {}
};

/// Sučelje za sve sakupljače podataka
class DataRecorder{
  public:
    /// Postavi broj očitavanja podataka
    void  setNoReads(int nr) { mNoReads = nr;  }

    virtual ~DataRecorder() {}
  protected:
    int mNoReads = -1;
};

/// Sabirnica.
class BusController {
public:
        /// konstruktor
    BusController()=default;

        /// insertiraj instrunment i postavi mu broj porta. Radi provjere ispisati da je operacija
        /// izvršena
    void insert(Instrument * p);                                                                  ///T

        /// Pošalji naredbu cmd uređaju na danoj adresi. Izbaci izuzetak ako nema uređaja.
    void send(unsigned int address, std::string cmd);                                               ///T

        /// Zatraži vrijednost od uređaja na danoj adresi.  Izbaci izuzetak ako nema uređaja.
    float receive(unsigned int address);                                                           ///T
private:
        /// Prisutni instrumenti. Indeksi su "portovi"
    std::vector<Instrument*> mDevices;
};

/// Konkretan generator podataka
class DataFast : public DataGenerator, public Instrument {
public:
    explicit DataFast(BusController& bus) ;                                                          ///T
    virtual float receive();                                                                  ///T
    virtual void send(std::string);                                                           ///T
    virtual void setMode(int);                                                                ///T
    virtual std::string deviceName() const { return "DataFast"; }                             ///T

private:
    BusController & mCntrl;
    int mMode;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
};


/// Konkretan sakupljač podataka
class Statistics : public Instrument, public DataRecorder {
public:
    explicit Statistics(BusController&);                                                       ///T
    virtual void send(std::string);                                                     ///T
    virtual float receive(){return arSredina; };                                        ///T
    virtual std::string deviceName() const { return "Statistics"; }                    ///T
private:
    BusController & mCntrl;
    float arSredina;
};

#endif /// VN_H
