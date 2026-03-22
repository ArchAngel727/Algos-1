#pragma once

#include "aktie.h"
#include <optional>
#include <string>
#include <vector>
class Hashtable {
private:
  std::vector<std::optional<Aktie>> vec;
  size_t fillrate;
  size_t calculateFillRate();
  bool exists(size_t);
  const size_t hash(const std::string &) const;
  void rehash();

public:
  Hashtable();
  ~Hashtable();

  const bool insert(const std::string &, Aktie);
  const std::optional<Aktie> get(std::string &) const;
  void remove(std::string &);

  void debug_print();
};
