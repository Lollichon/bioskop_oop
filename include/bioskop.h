#ifndef BIOSKOP_H
#define BIOSKOP_H

#include <vector>
#include <queue>
#include <string>
#include "Studio.h"
#include "Session.h"
#include "Tiket.h"

class Bioskop
{
private:
    std::vector<Studio> studios;
    std::vector<Session> sessions;
    std::queue<Tiket> antrian;
    int nextStudioId;
    int nextSessionId;
    int nextQueueNo;

    int findSessionIndexById(int sessionId) const;

public:
    Bioskop();

    // admin
    void adminTambahStudio(const std::string &nama);
    void adminTambahSession(const std::string &judul, const std::string &jadwal,
                            int studioId, int harga, int rows = 5, int cols = 5);
    void adminHapusSession(int sessionId);
    void adminLihatFilm() const;
    void adminLihatAntrian() const;
    void adminLayaniAntrian();

    // user
    void userLihatFilm() const;
    void userLihatDetailSession(int sessionId) const;
    void userPesanTiket(const std::string &nama, int sessionId, const std::vector<std::string> &daftarKursi);
};

#endif // BIOSKOP_H
