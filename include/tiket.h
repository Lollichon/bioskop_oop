#ifndef TIKET_H
#define TIKET_H

#include <string>

struct Tiket {
    int noAntrian;
    std::string namaPembeli;
    int sessionId;
    std::string kodeKursi; // e.g., A1
    int harga;
};

#endif // TIKET_H
