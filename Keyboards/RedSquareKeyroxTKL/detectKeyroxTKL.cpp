#include "detectKeyroxTKL.hpp"

#include <stdexcept>

hid_device* detectKeyroxTKL()
{
  size_t redSquareVendorId = 0x1A2C;
  size_t keyroxTklProductId = 0x1511;
  size_t usagePage = 0xFF00;
  size_t usage = 2;
  hid_device_info* infoList = hid_enumerate(redSquareVendorId, keyroxTklProductId);
  while (infoList->usage_page != usagePage && infoList->usage != usage)
  {
    if (!infoList->next)
    {
      hid_free_enumeration(infoList);
      throw std::invalid_argument("keyboardDetect.cpp: !infoList->next");
    }
    infoList = infoList->next;
  }
  hid_device* keyboardDevice = hid_open_path(infoList->path);
  hid_free_enumeration(infoList);
  if (!keyboardDevice)
  {
    throw std::invalid_argument("keyboardDetect.cpp: !keyboardDevice");
  }
  return keyboardDevice;
}