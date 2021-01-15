#include "Edge.hh"

float Edge::Size() {
  return std::pow(0.5f,
                  std::pow(2.0f, v2[COORD_X_INDEX] - v1[COORD_X_INDEX]) +
                      std::pow(2.0f, v2[COORD_Y_INDEX] - v1[COORD_Y_INDEX]) +
                      std::pow(2.0f, v2[COORD_Y_INDEX] - v1[COORD_Y_INDEX]));
}
