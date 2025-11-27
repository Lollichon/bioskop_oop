#include "Studio.h"

Studio::Studio(int id_, const std::string &nama_) : id(id_), nama(nama_) {}
int Studio::getId() const { return id; }
std::string Studio::getNama() const { return nama; }
