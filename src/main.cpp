#include "../headers/hashtable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void hash_table_testing() {
  Hashtable hashtable;
  Aktie aktie(0, "AMD", "Advanced Micro Devices");

  for (int i = 0; i < 2000; i++) {
    std::string str = std::to_string(i);
    std::cout << i << " | " << hashtable.insert(str, aktie) << "\n";
  }

  hashtable.debug_print();
}

std::vector<std::string> split(std::string &str, const std::string &delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  size_t pos = 0;

  while ((pos = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, pos);
    tokens.push_back(token);
    str.erase(0, pos + delimiter.length());
  }

  tokens.push_back(str);
  str.erase();

  return tokens;
}

double str_to_double(std::string &str) {
  return std::stod(str.substr(1, str.size() - 1));
}

std::vector<Data> load_data(std::string path) {
  std::ifstream infile(path);
  std::string line;
  std::vector<Data> vec_data;

  for (int row = 0; std::getline(infile, line); row++) {
    if (row == 0) {
      continue;
    }

    std::istringstream iss(line);
    std::string str;

    iss >> str;

    auto splits = split(str, ",");

    Data data;

    // Wir gehen davon aus das die CSV Datei das Format MM/DD/YYYY verwendet
    data.date = Date(std::stoi(splits[0].substr(3, 2)),
                     std::stoi(splits[0].substr(0, 2)),
                     std::stoi(splits[0].substr(6, 4)));

    data.close = str_to_double(splits[1]);
    data.volume = std::stoi(splits[2]);
    data.open = str_to_double(splits[3]);
    data.high = str_to_double(splits[4]);
    data.low = str_to_double(splits[5]);

    vec_data.push_back(data);
  }

  std::sort(vec_data.begin(), vec_data.end(),
            [](const Data &a, const Data &b) { return b.date > a.date; });

  if (vec_data.size() > 30) {
    vec_data.erase(vec_data.begin() + 30, vec_data.end());
  }

  return vec_data;
}

std::string pad(std::string str, size_t size) {
  if (str.size() >= size) {
    return str;
  }

  std::string new_str = str;

  if (str.size() == 3) {
    new_str += '0';
    new_str += std::string(size - str.size() - 1, ' ');
  } else {
    new_str += std::string(size - str.size(), ' ');
  }

  return new_str;
}

std::string format(double d) {
  std::string str = std::to_string(d);
  str.erase(str.find_last_not_of('0') + 1, std::string::npos);
  str.erase(str.find_last_not_of('.') + 1, std::string::npos);

  return str;
}

void print_data(Data data) {
  std::cout << "| ";
  std::cout << data.date.to_string();
  std::cout << " | ";
  std::cout << "$" << pad(format(data.close), 8);
  std::cout << " | ";
  std::cout << pad(format(data.volume), 9);
  std::cout << " | ";
  std::cout << "$" << pad(format(data.open), 8);
  std::cout << " | ";
  std::cout << "$" << pad(format(data.high), 8);
  std::cout << " | ";
  std::cout << "$" << pad(format(data.low), 8);
  std::cout << " |";
  std::cout << "\n";
}

void testing_loading() {
  Aktie qcom(0, "QCOM", "Quallcom");

  qcom.set_data(load_data("./test_data/qcom.csv"));

  std::cout
      << "|    Date    |   Close   |  Volume   |   Open    |   High    |  "
         "Low      |\n"
      << "+------------+-----------+-----------+-----------+-----------+-------"
         "----+"
         "\n";

  // Date,Close/Last,Volume,Open,High,Low

  for (auto &item : qcom.get_data().value()) {
    print_data(item);
  }

  std::cout << qcom.get_data().value().size() << '\n';
  std::cout << qcom.get_data().value().capacity();
}

int main() { return 0; }
