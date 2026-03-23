#include "../headers/hashtable.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

Hashtable::Hashtable() {
  this->vec = std::vector<std::optional<Aktie>>(2048);
  this->fillrate = 0;
}

Hashtable::~Hashtable() {}

// djb2 Hashing Algorithm
const size_t Hashtable::hash(const std::string &str,
                             const size_t &vec_size) const {
  // magic prime number
  size_t hash = 5381;

  for (auto chr : str) {
    hash =
        ((hash << 5) + hash) +
        static_cast<unsigned char>(chr); // hash * 33 + chr / bitshift so fast
  }

  hash = hash % vec_size;

  return hash;
}

size_t Hashtable::calculateFillRate() {
  if (vec.empty()) {
    return 0;
  }

  size_t fill_rate =
      std::count_if(this->vec.begin(), this->vec.end(),
                    [](const auto &opt) { return opt.has_value(); });

  return (fill_rate * 100) / this->vec.size();
}

bool Hashtable::exists(size_t hash) {
  return (hash < this->vec.size() && this->vec[hash].has_value());
}

std::optional<size_t> Hashtable::find_index(const std::string &str) const {
  if (vec.empty()) {
    return std::nullopt;
  }

  const size_t hash = this->hash(str, this->vec.size());

  for (size_t i = 0; i < this->vec.size(); ++i) {
    size_t index = (hash + i * i) % this->vec.size();
    const auto &opt = this->vec.at(index);

    if (!opt.has_value()) {
      return std::nullopt;
    }

    if (opt->get_kuerzel() == str) {
      return index;
    }
  }

  return std::nullopt;
}

void Hashtable::remove(std::string &str) {
  const size_t hash = this->hash(str, this->vec.size());
  size_t i = 0;
  size_t slot = 0;

  auto index = this->find_index(str);

  if (index.has_value()) {
    this->vec.at(*index) = std::nullopt;
  }
}

const bool Hashtable::insert(const std::string &str, Aktie val) {
  size_t hash = this->hash(str, this->vec.size());

  for (size_t i = 0; this->exists(hash); ++i) {
    hash = (hash + i * i) % this->vec.size();
  }

  this->vec[hash] = std::optional<Aktie>(val);

  if (this->calculateFillRate() > 75) {
    this->rehash();
  }

  return true;
}

void Hashtable::rehash() {
  size_t new_size = std::ceil(this->vec.size() * 1.5f);
  std::vector<std::optional<Aktie>> new_vec(new_size);

  for (auto &item : this->vec) {
    if (item.has_value()) {
      Aktie &tmp = item.value();

      auto index = this->find_index(tmp.get_kuerzel());

      if (index.has_value()) {
        new_vec.at(this->hash(tmp.get_kuerzel(), new_vec.size())) = item;
      }
    }
  }

  this->vec = std::move(new_vec);
}

std::optional<Aktie> &Hashtable::get(std::string &str) {
  auto index = this->find_index(str);

  return this->vec.at(*index);
}

void Hashtable::debug_print() {
  unsigned int empty = 0;

  for (auto item : this->vec) {
    if (item.has_value()) {
      std::cout << item.value().get_kuerzel() << " | "
                << this->hash(item.value().get_kuerzel(), this->vec.size())
                << "\n";
    } else {
      empty += 1;
    }
  }

  std::cout << "Size: " << this->vec.size() << "\n";
  std::cout << "Empty: " << empty << "\n";
}
