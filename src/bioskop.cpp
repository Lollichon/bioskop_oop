#include "Bioskop.h"
#include <iostream>
#include <iomanip>

using namespace std;

Bioskop::Bioskop() : nextStudioId(1), nextSessionId(1), nextQueueNo(1)
{
    // default studios
    adminTambahStudio("Studio 1");
    adminTambahStudio("Studio 2");
    adminTambahStudio("Studio 3");

    // default sessions (id auto)
    adminTambahSession("Avengers: Endgame", "12:00", 1, 35000, 6, 8);
    adminTambahSession("Spiderman: No Way Home", "14:00", 2, 40000, 5, 7);
    adminTambahSession("Joker", "16:00", 3, 30000, 5, 6);
    adminTambahSession("Toy Story 4", "10:00", 2, 25000, 5, 7);
    adminTambahSession("One Piece Film Red", "19:00", 3, 50000, 7, 9);

    cout << "[SYSTEM] Daftar film & studio default berhasil dimuat.\n";
}

int Bioskop::findSessionIndexById(int sessionId) const
{
    for (size_t i = 0; i < sessions.size(); ++i)
        if (sessions[i].getId() == sessionId)
            return (int)i;
    return -1;
}

// ADMIN
void Bioskop::adminTambahStudio(const string &nama)
{
    studios.emplace_back(nextStudioId++, nama);
    cout << "Studio added: " << nama << "\n";
}

void Bioskop::adminTambahSession(const string &judul, const string &jadwal,
                                 int studioId, int harga, int rows, int cols)
{
    sessions.emplace_back(nextSessionId++, judul, jadwal, studioId, harga, rows, cols);
    cout << "Session added: " << judul << " (Studio " << studioId << ")\n";
}

void Bioskop::adminHapusSession(int sessionId)
{
    int idx = findSessionIndexById(sessionId);
    if (idx == -1)
    {
        cout << "Session ID not found.\n";
        return;
    }
    cout << "Deleting session: " << sessions[idx].getJudul() << "\n";
    sessions.erase(sessions.begin() + idx);
}

void Bioskop::adminLihatFilm() const
{
    cout << "\n==== ALL SESSIONS ====\n";
    if (sessions.empty())
        cout << "(no sessions)\n";
    for (const auto &s : sessions)
    {
        cout << "ID[" << s.getId() << "] " << setw(30) << left << s.getJudul()
             << " | Jadwal: " << s.getJadwal()
             << " | Studio: " << s.getStudioId()
             << " | Harga: Rp " << s.getHarga() << "\n";
    }
}

void Bioskop::adminLihatAntrian() const
{
    cout << "\n==== QUEUE ====\n";
    if (antrian.empty())
    {
        cout << "(empty)\n";
        return;
    }
    queue<Tiket> tmp = antrian;
    while (!tmp.empty())
    {
        const Tiket &t = tmp.front();
        cout << "#" << t.noAntrian << " | " << t.namaPembeli << " | Session " << t.sessionId
             << " | Seat " << t.kodeKursi << " | Rp " << t.harga << "\n";
        tmp.pop();
    }
}

void Bioskop::adminLayaniAntrian()
{
    if (antrian.empty())
    {
        cout << "No queue.\n";
        return;
    }
    Tiket t = antrian.front();
    antrian.pop();
    cout << "\nServing: #" << t.noAntrian << " " << t.namaPembeli << "\n";
    cout << "Session: " << t.sessionId << " Seat: " << t.kodeKursi << " Total: Rp " << t.harga << "\n";
    cout << "Please make payment and print ticket.\n";
}

// USER
void Bioskop::userLihatFilm() const { adminLihatFilm(); }

void Bioskop::userLihatDetailSession(int sessionId) const
{
    int idx = findSessionIndexById(sessionId);
    if (idx == -1)
    {
        cout << "Session not found.\n";
        return;
    }
    const Session &s = sessions[idx];
    cout << "\n==== DETAIL SESSION ====\n";
    cout << "ID: " << s.getId() << " | " << s.getJudul() << " | Jadwal: " << s.getJadwal() << "\n";
    cout << "Studio: " << s.getStudioId() << " | Harga: Rp " << s.getHarga() << "\n";
    cout << "Total kursi: " << s.getRows() * s.getCols() << "\n";
    cout << "Terisi: " << s.hitungKursiTerisi() << " | Tersisa: " << s.hitungKursiKosong() << "\n";
    s.tampilkanKursi();
}

void Bioskop::userPesanTiket(const string &nama, int sessionId, const vector<string> &daftarKursi)
{
    int idx = findSessionIndexById(sessionId);
    if (idx == -1)
    {
        cout << "Session not found.\n";
        return;
    }
    Session &s = sessions[idx];

    vector<string> berhasil;
    vector<string> gagal;

    for (const string &kodeRaw : daftarKursi)
    {
        // normalize: trim spaces and uppercase first char
        string kode = kodeRaw;
        // simple trim front/back
        while (!kode.empty() && isspace(kode.front()))
            kode.erase(kode.begin());
        while (!kode.empty() && isspace(kode.back()))
            kode.pop_back();

        if (!s.validasiKursi(kode))
        {
            gagal.push_back(kode + " (format salah)");
            continue;
        }
        if (!s.pesanKursiByNomor(kode))
        {
            gagal.push_back(kode + " (sudah terisi)");
            continue;
        }
        berhasil.push_back(kode);
    }

    cout << "\n===== HASIL PEMESANAN =====\n";
    if (!berhasil.empty())
    {
        cout << "Kursi berhasil: ";
        for (const auto &k : berhasil)
            cout << k << " ";
        cout << "\nTotal harga: Rp " << (long long)berhasil.size() * s.getHarga() << "\n";

        // push one tiket per kursi ke antrian
        for (const auto &k : berhasil)
        {
            Tiket t;
            t.noAntrian = nextQueueNo++;
            t.namaPembeli = nama;
            t.sessionId = sessionId;
            t.kodeKursi = k;
            t.harga = s.getHarga();
            antrian.push(t);
        }
    }
    else
    {
        cout << "Tidak ada kursi yang berhasil dipesan.\n";
    }

    if (!gagal.empty())
    {
        cout << "Kursi gagal: ";
        for (const auto &g : gagal)
            cout << g << " ";
        cout << "\n";
    }
}
