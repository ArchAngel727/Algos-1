#include "../headers/aktie.h"
#include <optional>
#include <string>
#include <vector>

Aktie::Aktie(int wkn, std::string kuerzel, std::string name) {
  this->wkn = wkn;
  this->kuerzel = kuerzel;
  this->name = name;
  this->data = std::nullopt;
}

Aktie::Aktie(const Aktie &aktie) {
  this->wkn = aktie.wkn;
  this->kuerzel = aktie.kuerzel;
  this->name = aktie.name;
  this->data = aktie.data;
}

Aktie::~Aktie() {}

void Aktie::set_data(std::vector<Data> data) { this->data = data; };

const int &Aktie::get_wkn() const { return this->wkn; }
const std::string &Aktie::get_kuerzel() const { return this->kuerzel; }
const std::string &Aktie::get_name() const { return this->name; }
const std::optional<std::vector<Data>> &Aktie::get_data() const {
  return this->data;
}

bool const Aktie::operator==(const Aktie &aktie) const {
  return this->wkn == aktie.get_wkn() && this->kuerzel == aktie.get_kuerzel() &&
         this->name == aktie.get_name();
}
