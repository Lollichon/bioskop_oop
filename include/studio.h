#ifndef STUDIO_H
#define STUDIO_H

#include <string>

class Studio
{
private:
    int id;
    std::string nama;

public:
    Studio(int id_, const std::string &nama_);
    int getId() const;
    std::string getNama() const;
};

#endif // STUDIO_H
