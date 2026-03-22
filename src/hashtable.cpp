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
const size_t Hashtable::hash(const std::string &str) const {
  // magic prime number
  size_t hash = 5381;

  for (auto chr : str) {
    hash =
        ((hash << 5) + hash) +
        static_cast<unsigned char>(chr); // hash * 33 + chr / bitshift so fast
  }

  hash = hash % this->vec.size();

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
  return (this->vec.size() >= hash && this->vec[hash].has_value());
}

void Hashtable::remove(std::string &key) {
  const size_t hash = this->hash(key);

  auto it = this->vec.begin() + hash;

  while (it != this->vec.end() && it->value().get_kuerzel() != key) {
    ++it;
  }

  if (it == this->vec.end()) {
    return;
  }

  this->vec.erase(std::next(this->vec.begin(), hash));
}

const bool Hashtable::insert(const std::string &key, Aktie val) {
  size_t hash = this->hash(key);

  for (int i = 0; this->exists(hash); i++) {
    hash = static_cast<size_t>(hash + std::pow(i, 2)) % this->vec.size();
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
      Aktie tmp = item.value();
      auto it = std::find(this->vec.begin(), this->vec.end(), tmp);
      if (it != this->vec.end()) {
        this->vec.erase(it);
        new_vec[this->hash(tmp.get_kuerzel())] = item;
      }
    }
  }

  this->vec = std::move(new_vec);
}

const std::optional<Aktie> Hashtable::get(std::string &key) const {
  size_t hash = this->hash(key);

  return this->vec.at(hash);
}

void Hashtable::debug_print() {
  unsigned int empty = 0;

  for (auto item : this->vec) {
    if (item.has_value()) {
      std::cout << item.value().get_kuerzel() << " | "
                << this->hash(item.value().get_kuerzel()) << "\n";
    } else {
      empty += 1;
    }
  }

  std::cout << "Size: " << this->vec.size() << "\n";
  std::cout << "Empty: " << empty << "\n";
}
