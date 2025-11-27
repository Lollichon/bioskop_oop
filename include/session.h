#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Kursi.h"

class Session {
private:
    int id;
    std::string judul;
    std::string jadwal;
    int studioId;
    int harga;
    Kursi kursi;

public:
    Session(int id, const std::string &judul, const std::string &jadwal,
            int studioId, int harga, int rows = 5, int cols = 5);

    int getId() const;
    std::string getJudul() const;
    std::string getJadwal() const;
    int getStudioId() const;
    int getHarga() const;

    int getRows() const;
    int getCols() const;

    // tampil dengan warna
    void tampilkanKursi() const;

    // validasi format kode (A1, B3), tanpa leading zero
    bool validasiKursi(const std::string &kode) const;

    // pesan berdasarkan kode (A1)
    bool pesanKursiByNomor(const std::string &kode);

    // hitung kursi kosong/terisi
    int hitungKursiKosong() const;
    int hitungKursiTerisi() const;
};

#endif // SESSION_H
