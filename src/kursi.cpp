#include "Kursi.h"

Kursi::Kursi(int r, int c) : rows(r), cols(c)
{
    map.assign(rows, std::vector<bool>(cols, false));
}

int Kursi::getRows() const { return rows; }
int Kursi::getCols() const { return cols; }

bool Kursi::isTerisi(int r, int c) const
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return true;
    return map[r][c];
}

bool Kursi::pesan(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return false;
    if (map[r][c])
        return false;
    map[r][c] = true;
    return true;
}

void Kursi::batal(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return;
    map[r][c] = false;
}
