#include "Tiket.h"

Tiket::Tiket(const std::string& nama, int sessionId)
    : namaPembeli(nama), sessionId(sessionId) {}

std::string Tiket::getNama() const {
    return namaPembeli;
}

int Tiket::getSessionId() const {
    return sessionId;
}
