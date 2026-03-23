#pragma once

#include "hashtable.h"
#include <string>
#include <vector>
class Serializer {};

class Manager {
private:
  bool running;
  Hashtable hashtable;
  // Serializer *serializer;

public:
  Manager();
  ~Manager();

  void loop();
};
