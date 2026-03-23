#pragma once

#include "date.h"
#include <optional>
#include <string>
#include <vector>
struct Data {
  Date date;
  double close;
  int volume;
  double open;
  double high;
  double low;
};

std::string data_to_string(Data data);
std::vector<Data> load_data(std::string &);

class Aktie {
private:
  unsigned int wkn;
  std::string kuerzel;
  std::string name;
  std::optional<std::vector<Data>> data;

public:
  Aktie(unsigned int, std::string, std::string);
  Aktie(const Aktie &);
  ~Aktie();

  void set_data(std::vector<Data> data);

  const unsigned int &get_wkn() const;
  const std::string &get_kuerzel() const;
  const std::string &get_name() const;
  const std::optional<std::vector<Data>> &get_data() const;

  bool const operator==(const Aktie &) const;

  friend std::vector<Data> load_data(std::string &);
  friend std::string data_to_string(Data data);
};
