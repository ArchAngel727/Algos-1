#pragma once

#include <string>
class Date {
private:
  short day, month, year;

public:
  Date();
  Date(short, short, short);
  ~Date();

  std::string to_string();

  bool operator>(const Date &) const;
};
