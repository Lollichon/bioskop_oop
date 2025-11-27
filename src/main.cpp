#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Login.h"
#include "Bioskop.h"

using namespace std;

void menuAdmin(Bioskop &b)
{
    int pil;
    while (true)
    {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Tambah Studio\n";
        cout << "2. Tambah Session Film\n";
        cout << "3. Hapus Session Film\n";
        cout << "4. Lihat Semua Film\n";
        cout << "5. Lihat Antrian\n";
        cout << "6. Layani Antrian\n";
        cout << "7. Logout\n";
        cout << "Pilih: ";
        if (!(cin >> pil))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (pil == 1)
        {
            string nama;
            cout << "Nama Studio: ";
            cin.ignore();
            getline(cin, nama);
            b.adminTambahStudio(nama);
        }
        else if (pil == 2)
        {
            string judul, jadwal;
            int studioId, harga, row, col;
            cin.ignore();
            cout << "Judul Film: ";
            getline(cin, judul);
            cout << "Jadwal (contoh 10:00): ";
            getline(cin, jadwal);
            cout << "Studio ID: ";
            cin >> studioId;
            cout << "Harga tiket: ";
            cin >> harga;
            cout << "Jumlah baris kursi: ";
            cin >> row;
            cout << "Jumlah kolom kursi: ";
            cin >> col;
            b.adminTambahSession(judul, jadwal, studioId, harga, row, col);
        }
        else if (pil == 3)
        {
            int id;
            cout << "ID Session yang akan dihapus: ";
            cin >> id;
            b.adminHapusSession(id);
        }
        else if (pil == 4)
        {
            b.adminLihatFilm();
        }
        else if (pil == 5)
        {
            b.adminLihatAntrian();
        }
        else if (pil == 6)
        {
            b.adminLayaniAntrian();
        }
        else if (pil == 7)
        {
            cout << "Logout berhasil.\n";
            break;
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void menuUser(Bioskop &b)
{
    int pil;
    while (true)
    {
        cout << "\n===== MENU USER =====\n";
        cout << "1. Lihat Semua Film\n";
        cout << "2. Detail Film & Peta Kursi\n";
        cout << "3. Pesan Tiket (multi-seat, contoh: A1 A2 B3)\n";
        cout << "4. Lihat Antrian\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        if (!(cin >> pil))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (pil == 1)
        {
            b.userLihatFilm();
        }
        else if (pil == 2)
        {
            int id;
            cout << "ID Session: ";
            cin >> id;
            b.userLihatDetailSession(id);
        }
        else if (pil == 3)
        {
            string nama;
            int id;
            cout << "Nama Pemesan: ";
            cin >> ws;
            getline(cin, nama);
            cout << "ID Session: ";
            cin >> id;
            cout << "Masukkan daftar kursi (contoh: A1 A2 B3): ";
            cin.ignore();
            string line;
            getline(cin, line);

            vector<string> kursiDipilih;
            stringstream ss(line);
            string token;
            while (ss >> token)
                kursiDipilih.push_back(token);

            b.userPesanTiket(nama, id, kursiDipilih);
        }
        else if (pil == 4)
        {
            b.adminLihatAntrian(); // public view of queue
        }
        else if (pil == 5)
        {
            cout << "Kembali ke menu utama...\n";
            break;
        }
        else
        {
            cout << "Input tidak valid.\n";
        }
    }
}

int main()
{
    Login login;
    Bioskop bioskop;

    while (true)
    {
        cout << "\n===== SISTEM BIOSKOP =====\n";
        cout << "1. Login Admin\n";
        cout << "2. Masuk Sebagai User\n";
        cout << "3. Keluar Program\n";
        cout << "Pilih: ";
        int pilihan;
        if (!(cin >> pilihan))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (pilihan == 1)
        {
            string user, pass;
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;
            if (login.authenticateAdmin(user, pass))
            {
                cout << "Login berhasil.\n";
                menuAdmin(bioskop);
            }
            else
                cout << "Login gagal.\n";
        }
        else if (pilihan == 2)
        {
            menuUser(bioskop);
        }
        else if (pilihan == 3)
        {
            cout << "Terima kasih. Keluar.\n";
            break;
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
