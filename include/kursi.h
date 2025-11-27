#ifndef KURSI_H
#define KURSI_H

#include <vector>

class Kursi {
private:
    int rows;
    int cols;
    std::vector<std::vector<bool>> map; // true = terisi, false = kosong

public:
    Kursi(int r = 5, int c = 5);

    int getRows() const;
    int getCols() const;

    bool isTerisi(int r, int c) const;
    bool pesan(int r, int c); // pesan kursi (set terisi)
    void batal(int r, int c); // batalkan pesan
};

#endif // KURSI_H
