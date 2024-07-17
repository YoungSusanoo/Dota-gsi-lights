#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP

class RGBColor
{
public:
  RGBColor();
  RGBColor(unsigned int red, unsigned int green, unsigned int blue);

  unsigned int getRed() const;
  unsigned int getGreen() const;
  unsigned int getBlue() const;

private:
  unsigned int value_;
};

#endif
