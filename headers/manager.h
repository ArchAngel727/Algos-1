#pragma once

#include "hashtable.h"
#include <string>
#include <vector>
class Serializer {};

enum Command { ADD, DEL, IMPORT, SEARCH, PLOT, SAVE, LOAD, QUIT };

class Manager {
private:
  bool running;
  Hashtable Hashtable;
  Serializer *serializer;

public:
  Manager();
  ~Manager();

  void loop();
};
