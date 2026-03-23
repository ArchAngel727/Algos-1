#include "../headers/manager.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

Manager::Manager() {
  this->running = false;
  this->hashtable = Hashtable();
}

Manager::~Manager() {}

void Manager::loop() {
  this->running = true;
  std::string command;

  while (this->running) {
    std::cout << '\n';
    std::cin >> command;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "dbp") {
      this->hashtable.debug_print();
    }

    if (command == "add") {
      unsigned int wkn;
      std::string name;
      std::string kuerzel;

      std::cout << "\nName: ";
      std::cin >> name;
      std::cout << "\nKürzel: ";
      std::cin >> kuerzel;
      std::cout << "\nWKN: ";
      std::cin >> wkn;

      Aktie aktie(wkn, kuerzel, name);

      this->hashtable.insert(kuerzel, aktie);
    }

    if (command == "del") {
      std::string kuerzel;

      std::cout << "\nKürzel: ";
      std::cin >> kuerzel;

      this->hashtable.remove(kuerzel);
    }

    if (command == "import") {
      std::string kuerzel;
      std::string file;

      std::cout << "\nFile name: ";
      std::cin >> file;

      std::cout << "\nKürzel: ";
      std::cin >> kuerzel;

      if (file.compare(file.size() - 4, 4, ".csv") != 0) {
        file.append(".csv");
      }

      if (std::filesystem::exists(file)) {
        auto &item = this->hashtable.get(kuerzel);
        if (item.has_value()) {
          item->set_data(load_data(file));
        } else {
          std::cout << "No data\n";
        }
      } else {
        std::cout << file << '\n';
      }
    }

    if (command == "search") {
      std::string kuerzel;

      std::cout << "\nKürzel: ";
      std::cin >> kuerzel;

      std::optional<Aktie> tmp = this->hashtable.get(kuerzel);

      if (tmp.has_value()) {
        std::cout << tmp.value().get_kuerzel() << '\n';
        if (tmp->get_data().has_value()) {
          for (auto &item : *tmp->get_data()) {
            std::cout << data_to_string(item);
          }
        }
      }
    }

    if (command == "plot") {
    }

    if (command == "save") {
    }

    if (command == "load") {
    }

    if (command == "quit") {
      this->running = false;
    }
  }
}
