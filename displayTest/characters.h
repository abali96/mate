//left half of LED matrix are pins 32-37
//right half of LED matrix are pins 22-27
#include "Arduino.h"
static const struct Characters {
  const bool space[5][3] = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
  const bool zero[5][3] = {{1,1,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,1,1}};
  const bool one[5][3] = {{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}};
  const bool two[5][3] = {{1,1,1}, {0,0,1}, {1,1,1}, {1,0,0}, {1,1,1}};
  const bool three[5][3] = {{1,1,1}, {0,0,1}, {1,1,1}, {0,0,1}, {1,1,1}};
  const bool four[5][3] = {{1,0,1}, {1,0,1}, {1,1,1}, {0,0,1}, {0,0,1}};
  const bool five[5][3] = {{1,1,1}, {1,0,0}, {1,1,1}, {0,0,1}, {1,1,1}};
  const bool six[5][3] = {{1,1,1}, {1,0,0}, {1,1,1}, {1,0,1}, {1,1,1}};
  const bool seven[5][3] = {{1,1,1}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1}};
  const bool eight[5][3] = {{1,1,1}, {1,0,1}, {1,1,1}, {1,0,1}, {1,1,1}};
  const bool nine[5][3] = {{1,1,1}, {1,0,1}, {1,1,1}, {0,0,1}, {1,1,1}};
} characters;
