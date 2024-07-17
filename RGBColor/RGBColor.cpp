#include "RGBColor.hpp"

#include <stdexcept>

RGBColor::RGBColor():
  value_(0x000000)
{}

RGBColor::RGBColor(unsigned int red, unsigned int green, unsigned int blue):
  RGBColor()
{
  if (red > 255 || green > 255 || blue > 255)
  {
    throw std::invalid_argument("RGBColor.cpp: some color > 255");
  }
  value_ = red << 16;
  value_ = value_ | green << 8;
  value_ = value_ | blue;
}

unsigned int RGBColor::getRed() const
{
  return (value_ >> 16) & 0x0000FF;
}

unsigned int RGBColor::getGreen() const
{
  return (value_ >> 8) & 0x0000FF;
}

unsigned int RGBColor::getBlue() const
{
  return value_ & 0x0000FF;
}
