#include "../headers/date.h"
#include <string>

Date::Date() {
  this->day = 0;
  this->month = 0;
  this->year = 0;
}

Date::Date(short day, short month, short year) {
  this->day = day;
  this->month = month;
  this->year = year;
}

Date::~Date() {}

std::string Date::to_string() {
  std::string str;

  if (this->day < 10) {
    str.append("0");
  }

  str.append(std::to_string(this->day));
  str.append("/");

  if (this->month < 10) {
    str.append("0");
  }

  str.append(std::to_string(this->month));
  str.append("/");
  str.append(std::to_string(this->year));

  return str;
}

bool Date::operator>(const Date &date) const {
  bool am_i_bigger = false;

  if (this->year > date.year) {
    am_i_bigger = false;
  } else if (this->year < date.year) {
    am_i_bigger = true;
  } else {
    if (this->month > date.month) {
      am_i_bigger = false;
    } else if (this->month < date.month) {
      am_i_bigger = true;
    } else {
      if (this->day > date.day) {
        am_i_bigger = false;
      } else if (this->day < date.day) {
        am_i_bigger = true;
      }
    }
  }

  return am_i_bigger;
}
