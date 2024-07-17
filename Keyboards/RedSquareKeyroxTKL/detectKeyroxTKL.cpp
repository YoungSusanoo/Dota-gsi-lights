#include "detectKeyroxTKL.hpp"

#include <stdexcept>

bool isNeeded(hid_device_info* info, size_t usagePage, size_t usage, size_t interface)
{
  bool condition = false;
  if (info)
  {
    condition = info->usage_page == usagePage;
    condition = condition && info->usage == usage;
    condition = condition && info->interface_number == interface;
  }
  return condition;
}

hid_device* detectKeyroxTKL()
{
  size_t vendorId = 0x1A2C;
  size_t productId = 0x1511;
  size_t usagePage = 0xFF00;
  size_t usage = 2;
  size_t interface = 3;
  hid_device_info* infoList = hid_enumerate(vendorId, productId);
  while (!isNeeded(infoList, usagePage, usage, interface))
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
