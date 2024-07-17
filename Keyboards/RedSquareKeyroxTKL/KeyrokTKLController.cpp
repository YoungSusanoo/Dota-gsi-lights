#include "KeyrokTKLController.hpp"

#include <thread>
#include <chrono>
#include <cstring>
#include <stdexcept>

namespace
{
  std::vector< unsigned int > led_sequence_positions =
  {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 70, 51, 52, 53,
    58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 50,
    75, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 88, 89,
    94, 95, 96, 98, 100, 101, 102, 103, 104, 105, 106
  };
  /*
    0,        1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,       13,  14,  15,
    16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,       30,  31,  32,
    37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  70,       51,  52,  53,
    58,       59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,       50,
    75,       77,  78,  79,  80,  81,  82,  83,  84,  85,  86,       88,            89,
    94,  95,  96,                 98,                100, 101, 102, 103,      104, 105, 106
  */
}

KeyrokTKLController::KeyrokTKLController(hid_device* device):
  packetDataLength_(520),
  brightness_(200),
  mode_(KeyroxModes::CUSTOM_MODE_VALUE),
  device_(device)
{
  if (!device_)
  {
    throw std::invalid_argument("KeyroxTKLController.cpp: !device_");
  }
}

KeyrokTKLController::~KeyrokTKLController()
{
  hid_close(device_);
}

void KeyrokTKLController::setMode(KeyroxModes mode)
{
  unsigned char usb_buf[packetDataLength_];
  memset(usb_buf, 0x00, packetDataLength_);

  usb_buf[4] = 0x01;
  usb_buf[6] = 0x04;
  usb_buf[8] = static_cast< unsigned char >(mode);

  mode_ = mode;

  sendData(usb_buf);
}

void KeyrokTKLController::setColors(const std::vector< RGBColor >& colors)
{
  if (colors.size() != 87)
  {
    throw std::invalid_argument("KeyroxTKLController.cpp: colors.size() != 87");
  }

  setMode(KeyroxModes::CUSTOM_MODE_VALUE);

  unsigned char usb_buf[packetDataLength_];
  memset(usb_buf, 0x00, packetDataLength_);

  usb_buf[4] = 0xB0;
  usb_buf[5] = 0x01;
  usb_buf[6] = 0x07;

  for (unsigned int i = 0; i < colors.size(); i++)
  {
    int offset = 7 + led_sequence_positions[i] * 4;
    usb_buf[offset + 1] = colors[i].getRed();
    usb_buf[offset + 2] = colors[i].getGreen();
    usb_buf[offset + 3] = colors[i].getBlue();
    usb_buf[offset + 4] = brightness_;
  }

  sendData(usb_buf);
}

void KeyrokTKLController::setBrightness(unsigned int brightness)
{
  brightness_ = brightness;
}

void KeyrokTKLController::sendData(const unsigned char data[])
{
  unsigned char usb_buf[packetDataLength_ + 1];

  usb_buf[0] = 0x00;

  for (int x = 0; x < packetDataLength_; x++)
  {
    usb_buf[x + 1] = data[x];
  }

  hid_send_feature_report(device_, usb_buf, packetDataLength_ + 1);

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(10ms);
}
