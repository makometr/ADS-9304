#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>
#include <memory>

#include "node.h"

enum Color {
  kDefault = 0,
  kBlack = 30,
  kRed,
  kGreen,
  kYellow,
  kBlue,
  kPurple,
  kWave,
  kGrey
};

std::ostream& operator<<(std::ostream& out, Color color) {
  out << "\033[" << (int)color << "m";
  return out;
}

#endif  // COLOR_H_