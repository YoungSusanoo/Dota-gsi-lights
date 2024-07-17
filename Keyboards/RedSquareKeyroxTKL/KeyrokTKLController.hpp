#ifndef KEYROKTKLCONTROLLER_HPP
#define KEYROKTKLCONTROLLER_HPP

#include <vector>
#include <hidapi/hidapi.h>

#include "KeyroxTKLModes.hpp"
#include "../../RGBColor/RGBColor.hpp"

class KeyrokTKLController
{
public:
  explicit KeyrokTKLController(hid_device* device);

  ~KeyrokTKLController();

  void setMode(KeyroxTKLModes mode);
  void setColors(const std::vector< RGBColor >& colors);
  void setBrightness(unsigned int brightness);

private:
  hid_device* device_;
  unsigned int brightness_;
  KeyroxTKLModes mode_;
  const size_t packetDataLength_;

  void sendData(const unsigned char data[]);
};

#endif
