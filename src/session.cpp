#include "Session.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

Session::Session(int id_, const std::string &judul_, const std::string &jadwal_,
                 int studioId_, int harga_, int rows, int cols)
    : id(id_), judul(judul_), jadwal(jadwal_), studioId(studioId_), harga(harga_), kursi(rows, cols) {}

int Session::getId() const { return id; }
std::string Session::getJudul() const { return judul; }
std::string Session::getJadwal() const { return jadwal; }
int Session::getStudioId() const { return studioId; }
int Session::getHarga() const { return harga; }

int Session::getRows() const { return kursi.getRows(); }
int Session::getCols() const { return kursi.getCols(); }

void Session::tampilkanKursi() const
{
    cout << "\nPeta Kursi ( " << RED << "X" << RESET << " = terisi, " << GREEN << "A1" << RESET << " = tersedia )\n\n";

    char rowLabel = 'A';
    for (int r = 0; r < getRows(); ++r)
    {
        cout << rowLabel << " ";
        for (int c = 0; c < getCols(); ++c)
        {
            if (kursi.isTerisi(r, c))
            {
                cout << RED << " X " << RESET;
            }
            else
            {
                // print like A1, A2 (align)
                string kode;
                kode.push_back(rowLabel);
                kode += to_string(c + 1);
                // pad to width 3
                if (kode.size() == 2)
                    cout << GREEN << " " << kode << " " << RESET;
                else if (kode.size() == 3)
                    cout << GREEN << kode << " " << RESET;
                else
                    cout << GREEN << " " << kode << " " << RESET;
            }
        }
        cout << "\n";
        ++rowLabel;
    }
    cout << "\n";
}

bool Session::validasiKursi(const std::string &kode) const
{
    if (kode.size() < 2 || kode.size() > 3)
        return false; // e.g., A1..A12 allowed if cols up to 12
    char rowChar = toupper(kode[0]);
    if (rowChar < 'A')
        return false;
    int r = rowChar - 'A';
    if (r < 0 || r >= getRows())
        return false;

    // check remaining are digits and no leading zero
    if (!isdigit(kode[1]))
        return false;
    if (kode[1] == '0')
        return false; // disallow leading zero like A01

    for (size_t i = 2; i < kode.size(); ++i)
        if (!isdigit(kode[i]))
            return false;

    int col = stoi(kode.substr(1));
    if (col < 1 || col > getCols())
        return false;

    return true;
}

bool Session::pesanKursiByNomor(const std::string &kode)
{
    if (!validasiKursi(kode))
        return false;

    char rowChar = toupper(kode[0]);
    int r = rowChar - 'A';
    int c = stoi(kode.substr(1)) - 1;

    return kursi.pesan(r, c);
}

int Session::hitungKursiKosong() const
{
    int cnt = 0;
    for (int r = 0; r < getRows(); ++r)
        for (int c = 0; c < getCols(); ++c)
            if (!kursi.isTerisi(r, c))
                ++cnt;
    return cnt;
}

int Session::hitungKursiTerisi() const
{
    return getRows() * getCols() - hitungKursiKosong();
}
