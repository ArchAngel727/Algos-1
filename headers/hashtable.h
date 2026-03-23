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
  const size_t hash(const std::string &, const size_t &) const;
  void rehash();
  std::optional<size_t> find_index(const std::string &key) const;

public:
  Hashtable();
  ~Hashtable();

  const bool insert(const std::string &, Aktie);
  std::optional<Aktie> &get(std::string &);
  void remove(std::string &);

  void debug_print();
};
